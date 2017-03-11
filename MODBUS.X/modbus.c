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

#define MODBUS_BUFFER_SIZE  SERIAL_BUFFER_SIZE
#define MB_MAX_SIZE         EEPROM_SIZE

#ifdef MODBUS_UART_1
uint8_t *buffer_rda1;
#endif

#ifdef MODBUS_UART_2
uint8_t *buffer_rda2;
#endif

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
    uint16_t cont;

    for (cont = 0; cont < i_size; ++cont)
        putchar(data[cont]);

    return true;
}

bool return_error(uint8_t address, modbus_command_t command,
        modbus_command_exception_code_t error) {
    uint8_t *resp, ex_code;
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

    resp = NULL;
    resp = (uint8_t *) malloc((uint16_t) (5 * sizeof (uint8_t)));

    if (resp == NULL) {
        free(resp);
        return false;
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
    free(resp);

    return true;
}

bool slave_response(void) {
    //register_address ou Starting Address
    //register_value ou Quantity of Registers
    uint8_t my_address, *response, *buff_aux, tmp_var[2];
    uint16_t register_value, register_address, b_count, cont, aux, aux_addr, index_rda;
    bool ret, respond_now;

    ret = false;
    respond_now = false;

#if defined USE_UART_1 & defined MODBUS_UART_1
    if (uart1_get_rec()) {
        uart1_set_rec();
        index_rda = uart1_get_index();
        buff_aux = buffer_rda1;
        respond_now = true;

#ifdef USE_PIVO_STR
        my_address = pivo->endereco;
#else
#ifdef SLV_ADDR_1
        my_address = SLV_ADDR_1;
#else
        my_address = 1;
#endif
#endif
    }
#endif

#if defined USE_UART_2 & defined MODBUS_UART_2
    if (uart2_get_rec()) {
        uart2_set_rec();
        index_rda = uart2_get_index();
        buff_aux = buffer_rda2;
        respond_now = true;

#ifdef USE_PIVO_STR
        my_address = pivo->endereco;
#else
#ifdef SLV_ADDR_2
        my_address = SLV_ADDR_2;
#else
        my_address = 1;
#endif    
#endif
    }
#endif

    if (respond_now) {
        respond_now = false;
        register_value = (buff_aux[MODBUS_FIELDS_REGISTER_VALUE_H] << 8) |
                buff_aux[MODBUS_FIELDS_REGISTER_VALUE_L];
        register_address = (buff_aux[MODBUS_FIELDS_REGISTER_ADDRESS_H] << 8) |
                buff_aux[MODBUS_FIELDS_REGISTER_ADDRESS_L];
        b_count = buff_aux[MODBUS_FIELDS_BYTE_COUNT];
        aux_addr = 2 * register_address;
        aux = ((buff_aux[index_rda - 1] << 8) | (buff_aux[index_rda - 2]));

        if ((my_address == buff_aux[MODBUS_FIELDS_ADDRESS])
                && (CRC16(buff_aux, index_rda - 2) == aux)) {
            switch (buff_aux[MODBUS_FIELDS_FUNCTION]) {
                case READ_HOLDING_REGISTERS_COMMAND:
                    if (register_value == 0 || register_value > 0x7D) {
                        ret = return_error(my_address, READ_HOLDING_REGISTERS_COMMAND,
                                EXCEPTION_CODE_3);
                    } else if (((register_value + register_address) * 2)
                            > (uint32_t) MB_MAX_SIZE) {
                        ret = return_error(my_address, READ_HOLDING_REGISTERS_COMMAND,
                                EXCEPTION_CODE_2);
                    } else if (!ext_eeprom_ready()) {
                        ret = return_error(my_address, READ_HOLDING_REGISTERS_COMMAND,
                                EXCEPTION_CODE_0);
                    } else {
                        b_count = 2 * register_value;
                        response = (uint8_t *) malloc((b_count + 5) * sizeof (uint8_t));

                        if (response == NULL) {
                            return false;
                        }

                        response[0] = my_address;
                        response[1] = READ_HOLDING_REGISTERS_COMMAND;
                        response[2] = (uint8_t) b_count;
                        read_ext_eeprom(aux_addr, &response[3], b_count);
                        aux = CRC16(response, b_count + 3);
                        response[b_count + 3] = (uint8_t) (aux & 0xFF);
                        response[b_count + 4] = (uint8_t) ((aux & 0xFF00) >> 8);
                        ret = send_modbus(response, b_count + 5);
                        free(response);
                    }
                    break;

                case WRITE_SINGLE_REGISTER_COMMAND:
                    if (((register_address + 1) * 2) > (uint32_t) MB_MAX_SIZE) {
                        ret = return_error(my_address, WRITE_SINGLE_REGISTER_COMMAND,
                                EXCEPTION_CODE_2);
                    } else if (!ext_eeprom_ready()) {
                        ret = return_error(my_address, READ_HOLDING_REGISTERS_COMMAND,
                                EXCEPTION_CODE_0);
                    } else {
                        tmp_var[0] = (uint8_t) ((register_value & 0xFF00) >> 8);
                        tmp_var[1] = (uint8_t) (register_value & 0xFF);
                        write_ext_eeprom(aux_addr, tmp_var, 2);
                        response = (uint8_t *) malloc(index_rda * sizeof (uint8_t));

                        for (cont = 0; cont < index_rda; ++cont) {
                            response[cont] = buff_aux[cont];
                        }

                        ret = send_modbus(response, index_rda);
                        free(response);
                    }
                    break;

                case WRITE_MULTIPLE_REGISTERS_COMMAND:
                    if (((register_address * 2) + b_count) > (uint32_t) MB_MAX_SIZE) {
                        ret = return_error(my_address, WRITE_SINGLE_REGISTER_COMMAND,
                                EXCEPTION_CODE_2);
                    } else if (!ext_eeprom_ready()) {
                        ret = return_error(my_address, READ_HOLDING_REGISTERS_COMMAND,
                                EXCEPTION_CODE_0);
                    } else {
                        response = (uint8_t *) malloc(8 * sizeof (uint8_t));

                        if (response == NULL) {
                            return false;
                        }

                        write_ext_eeprom(aux_addr, &buff_aux[7], b_count);
                        response[0] = my_address;
                        response[1] = WRITE_MULTIPLE_REGISTERS_COMMAND;
                        response[2] = (uint8_t) ((register_address & 0xFF00) >> 8);
                        response[3] = (uint8_t) (register_address & 0xFF);
                        response[4] = (uint8_t) ((register_value & 0xFF00) >> 8);
                        response[5] = (uint8_t) (register_value & 0xFF);
                        aux = CRC16(response, 6);
                        response[6] = (uint8_t) ((aux & 0xFF00) >> 8);
                        response[7] = (uint8_t) (aux & 0xFF);
                        ret = send_modbus(response, 8);
                        free(response);
                    }
                    break;
            }
        }
    }

    return ret;
}

bool modbus_init(void) {
    init_ext_eeprom();

#ifdef MODBUS_UART_1
    buffer_rda1 = NULL;
    buffer_rda1 = (uint8_t *) malloc(MODBUS_BUFFER_SIZE * sizeof (uint8_t));

    if (buffer_rda1 == NULL)
        return false;

    uart1_init(buffer_rda1);
#endif
#ifdef MODBUS_UART_2    
    buffer_rda2 = NULL;
    buffer_rda2 = (uint8_t *) malloc(MODBUS_BUFFER_SIZE * sizeof (uint8_t));

    if (buffer_rda2 == NULL)
        return false;

    uart2_init(buffer_rda2);
#endif

    if (!ext_eeprom_ready())
        return false;

    return true;
}