/*
 * File:   modbus.c
 * Author: cuki
 *
 * Created on 10 de Março de 2017, 08:22
 */

#include "modbus.h"
#include "serial.h"
#include "ext_eeprom.h"
#include <stdlib.h>
#include <libpic30.h>

#define MB_MAX_SIZE     EEPROM_SIZE
#define MB_BUFFER_SIZE  0x012C

volatile static uint8_t m_address = 1;

typedef enum modbus_command_exception_code {
    EXCEPTION_CODE_0,
    EXCEPTION_CODE_1,
    EXCEPTION_CODE_2,
    EXCEPTION_CODE_3,
    EXCEPTION_CODE_4
} modbus_command_exception_code_t;

typedef enum modbus_fields {
    MODBUS_FIELDS_ADDRESS,
    MODBUS_FIELDS_FUNCTION,
    MODBUS_FIELDS_REGISTER_ADDRESS_H,
    MODBUS_FIELDS_REGISTER_ADDRESS_L,
    MODBUS_FIELDS_REGISTER_VALUE_H,
    MODBUS_FIELDS_REGISTER_VALUE_L,
    MODBUS_FIELDS_BYTE_COUNT
} modbus_fields_t;

uint16_t CRC16(uint8_t *nData, uint16_t wLength) {
    uint8_t nTemp;
    uint16_t wCRCWord = 0xFFFF;

    while (wLength--) {
        nTemp = *nData++ ^ wCRCWord;
        wCRCWord >>= 8;
        wCRCWord ^= wCRCTable[nTemp];
    }

    return wCRCWord;
}

bool send_modbus(uint8_t *data, uint16_t i_size) {
    bool ret = false;
#ifdef MODBUS_UART_1
    ret = uart1_send(data, i_size);
#endif
#ifdef MODBUS_UART_2
    ret = uart2_send(data, i_size);
#endif
#ifdef MODBUS_UART_3
    ret = uart3_send(data, i_size);
#endif

    return ret;
}

bool return_error(uint8_t address, modbus_command_t command,
        modbus_command_exception_code_t error) {
    uint8_t resp[5], ex_code;
    uint16_t crc;

    switch (command) {
        case READ_HOLDING_REGISTERS_COMMAND:
            ex_code = 0x83;
            break;
        case WRITE_SINGLE_REGISTER_COMMAND:
            ex_code = 0x86;
            break;
        default:
        case NO_COMMAND:
        case READ_COILS_COMMAND:
        case READ_DISCRETE_INPUT_COMMAND:
        case READ_INPUT_REGISTERS_COMMAND:
        case WRITE_SINGLE_COIL_COMMAND:
            ex_code = 0;
            break;
    }

#ifdef ADDR_MY
    resp[0] = (uint8_t) get_byte(ADDR_MY);
#else
    resp[0] = address;
#endif
    resp[1] = ex_code;
    resp[2] = error;
    crc = CRC16(resp, 3);
    resp[3] = (uint8_t) ((crc & 0xFF00) >> 8);
    resp[4] = (uint8_t) (crc & 0xFF);

    send_modbus(resp, 5);

    return true;
}

bool slave_response(void) {
    uint8_t response[MB_BUFFER_SIZE], request[MB_BUFFER_SIZE], tmp_var[2];
    uint16_t register_value, register_address, b_count, cont,
            request_crc, aux_addr, index_rda, n, my_crc;
    bool ret, respond_now;

    ret = false;
    respond_now = false;
    n = 0;
#ifdef MODBUS_UART_1
    n = uart1_getRxSize();

    if (n != 0) {
        __delay_ms(100);
        n = uart1_get(request, MB_BUFFER_SIZE);
    }
#endif
#ifdef MODBUS_UART_2
    n = uart2_getRxSize();

    if (n != 0) {
        __delay_ms(100);
        n = uart2_get(request, MB_BUFFER_SIZE);
    }
#endif
#ifdef MODBUS_UART_3
    n = uart3_getRxSize();

    if (n != 0) {
        __delay_ms(100);
        n = uart3_get(request, MB_BUFFER_SIZE);
    }
#endif
    
    if (n != 0) {
        index_rda = n;
        respond_now = true;
    }

    if (respond_now) {
        respond_now = false;
        register_value = (request[MODBUS_FIELDS_REGISTER_VALUE_H] << 8) |
                request[MODBUS_FIELDS_REGISTER_VALUE_L];
        register_address = (request[MODBUS_FIELDS_REGISTER_ADDRESS_H] << 8) |
                request[MODBUS_FIELDS_REGISTER_ADDRESS_L];
        b_count = request[MODBUS_FIELDS_BYTE_COUNT];
        aux_addr = 2 * register_address;
        request_crc = ((request[index_rda - 1] << 8) | (request[index_rda - 2]));
        my_crc = CRC16(request, index_rda - 2);

        if ((m_address == request[MODBUS_FIELDS_ADDRESS])
                && (my_crc == request_crc)) {
            switch (request[MODBUS_FIELDS_FUNCTION]) {
                case READ_HOLDING_REGISTERS_COMMAND:
                    if (register_value == 0 || register_value > 0x7D) {
                        ret = return_error(m_address, READ_HOLDING_REGISTERS_COMMAND,
                                EXCEPTION_CODE_3);
                    } else if (((register_value + register_address) * 2)
                            > (uint32_t) MB_MAX_SIZE) {
                        ret = return_error(m_address, READ_HOLDING_REGISTERS_COMMAND,
                                EXCEPTION_CODE_2);
                    } else if (!ext_eeprom_ready()) {
                        ret = return_error(m_address, READ_HOLDING_REGISTERS_COMMAND,
                                EXCEPTION_CODE_0);
                    } else {
                        b_count = 2 * register_value;
                        response[0] = m_address;
                        response[1] = READ_HOLDING_REGISTERS_COMMAND;
                        response[2] = (uint8_t) b_count;
                        ext_eeprom_read(aux_addr, &response[3], b_count);
                        request_crc = CRC16(response, b_count + 3);
                        response[b_count + 3] = (uint8_t) (request_crc & 0xFF);
                        response[b_count + 4] = (uint8_t) ((request_crc & 0xFF00) >> 8);
                        ret = send_modbus(response, b_count + 5);
                    }
                    break;

                case WRITE_SINGLE_REGISTER_COMMAND:
                    if (((register_address + 1) * 2) > (uint32_t) MB_MAX_SIZE) {
                        ret = return_error(m_address, WRITE_SINGLE_REGISTER_COMMAND,
                                EXCEPTION_CODE_2);
                    } else if (!ext_eeprom_ready()) {
                        ret = return_error(m_address, READ_HOLDING_REGISTERS_COMMAND,
                                EXCEPTION_CODE_0);
                    } else {
                        tmp_var[0] = (uint8_t) ((register_value & 0xFF00) >> 8);
                        tmp_var[1] = (uint8_t) (register_value & 0xFF);
                        ext_eeprom_write(aux_addr, tmp_var, 2);

                        for (cont = 0; cont < index_rda; ++cont) {
                            response[cont] = request[cont];
                        }

                        ret = send_modbus(response, index_rda);
                    }
                    break;

                case WRITE_MULTIPLE_REGISTERS_COMMAND:
                    if (((register_address * 2) + b_count) > (uint32_t) MB_MAX_SIZE) {
                        ret = return_error(m_address, WRITE_SINGLE_REGISTER_COMMAND,
                                EXCEPTION_CODE_2);
                    } else if (!ext_eeprom_ready()) {
                        ret = return_error(m_address, READ_HOLDING_REGISTERS_COMMAND,
                                EXCEPTION_CODE_0);
                    } else {
                        ext_eeprom_write(aux_addr, &request[7], b_count);
                        response[0] = m_address;
                        response[1] = WRITE_MULTIPLE_REGISTERS_COMMAND;
                        response[2] = (uint8_t) ((register_address & 0xFF00) >> 8);
                        response[3] = (uint8_t) (register_address & 0xFF);
                        response[4] = (uint8_t) ((register_value & 0xFF00) >> 8);
                        response[5] = (uint8_t) (register_value & 0xFF);
                        request_crc = CRC16(response, 6);
                        response[6] = (uint8_t) ((request_crc & 0xFF00) >> 8);
                        response[7] = (uint8_t) (request_crc & 0xFF);
                        ret = send_modbus(response, 8);
                    }
                    break;
            }
        }
    }

    return ret;
}

bool modbus_init(void) {
    ext_eeprom_init();

    if (!ext_eeprom_ready())
        return false;

    return true;
}

void modbus_set_addr(uint16_t address) {
    m_address = address;
    uint8_t str[2] = { 0 };
    
    str[0] = (uint8_t) (address & 0xFF);
    
#ifdef MODBUS_UART_1
    uart1_send(str, 1);
#endif
#ifdef MODBUS_UART_2
    uart2_send(str, 1);
#endif
#ifdef MODBUS_UART_3
    uart3_send(str, 1);
#endif

    return;
}