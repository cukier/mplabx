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

#define MB_MAX_SIZE EEPROM_SIZE

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
    return uart3_send(data, i_size);
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
    uint8_t my_address, response[256], request[256], tmp_var[2];
    uint16_t register_value, register_address, b_count, cont,
            aux, aux_addr, index_rda, n;
    bool ret, respond_now;

    ret = false;
    respond_now = false;
    n = 0;
    n = uart3_get(request, 256);
    
    if (n != 0) {        
        index_rda = n;
        respond_now = true;
#ifdef USE_PIVO_STR
        my_address = pivo->endereco;
#elif defined SLV_ADDR_1
        my_address = SLV_ADDR_1;
#else
        my_address = 1;
#endif
    }

    if (respond_now) {
        respond_now = false;
        register_value = (request[MODBUS_FIELDS_REGISTER_VALUE_H] << 8) |
                request[MODBUS_FIELDS_REGISTER_VALUE_L];
        register_address = (request[MODBUS_FIELDS_REGISTER_ADDRESS_H] << 8) |
                request[MODBUS_FIELDS_REGISTER_ADDRESS_L];
        b_count = request[MODBUS_FIELDS_BYTE_COUNT];
        aux_addr = 2 * register_address;
        aux = ((request[index_rda - 1] << 8) | (request[index_rda - 2]));

        if ((my_address == request[MODBUS_FIELDS_ADDRESS])
                && (CRC16(request, index_rda - 2) == aux)) {
            switch (request[MODBUS_FIELDS_FUNCTION]) {
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
                        response[0] = my_address;
                        response[1] = READ_HOLDING_REGISTERS_COMMAND;
                        response[2] = (uint8_t) b_count;
                        read_ext_eeprom(aux_addr, &response[3], b_count);
                        aux = CRC16(response, b_count + 3);
                        response[b_count + 3] = (uint8_t) (aux & 0xFF);
                        response[b_count + 4] = (uint8_t) ((aux & 0xFF00) >> 8);
                        ret = send_modbus(response, b_count + 5);
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

                        for (cont = 0; cont < index_rda; ++cont) {
                            response[cont] = request[cont];
                        }

                        ret = send_modbus(response, index_rda);
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
                        write_ext_eeprom(aux_addr, &request[7], b_count);
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
                    }
                    break;
            }
        }
    }

    return ret;
}

bool modbus_init(void) {
    init_ext_eeprom();

    if (!ext_eeprom_ready())
        return false;

    return true;
}