/*
 * pivo_mem.c
 *
 *  Created on: 22 de dez de 2016
 *      Author: cuki
 */

#include "mem.h"
#include "ext_eeprom.h"

#include <stdlib.h>

union {
    uint8_t a[4];
    float b;
    uint32_t c;
} itofl;

void MEM_init(void) {
    ext_eeprom_init();
    return;
}

bool MEM_ready(void) {
    return ext_eeprom_ready();
}

uint32_t MEM_get_dword(uint16_t address) {
    uint16_t addr = address * 4;
    uint32_t ret = 0;
    uint8_t data[4];

    if (ext_eeprom_ready()) {
        ext_eeprom_read(addr, data, 4);
        ret = make32(data[2], data[3], data[0], data[1]);
    } else {
        ret = 0xFFFFFFFF;
    }

    return ret;
}

bool MEM_set_dword(uint16_t address, uint32_t i_value) {
    uint16_t addr = address * 4;
    uint8_t data[4];

    if (ext_eeprom_ready()) {
        data[0] = make8((uint64_t) i_value, 1);
        data[1] = make8((uint64_t) i_value, 0);
        data[2] = make8((uint64_t) i_value, 3);
        data[3] = make8((uint64_t) i_value, 2);
        ext_eeprom_write(addr, data, 4);
    } else {
        return false;
    }

    return true;
}

uint16_t MEM_get_register(uint16_t address) {
    uint16_t addr = address * 2, ret;
    uint8_t data[2];

    ret = 0;

    if (ext_eeprom_ready()) {
        ext_eeprom_read(addr, data, 2);
        ret = make16(data[0], data[1]);
    } else {
        ret = 0xFFFF;
    }

    return ret;
}

bool MEM_set_register(uint16_t address, uint16_t value) {
    uint16_t addr = address * 2;
    uint8_t data[2];

    if (ext_eeprom_ready()) {
        data[0] = make8(value, 1);
        data[1] = make8(value, 0);
        ext_eeprom_write(addr, data, 2);
    } else {
        return false;
    }

    return true;
}

uint8_t MEM_get_byte(uint16_t address) {
    uint8_t ret = 0;

    if (ext_eeprom_ready()) {
        ext_eeprom_read(address, &ret, 1);
    } else {
        ret = 0xFF;
    }

    return ret;
}

bool MEM_set_byte(uint16_t address, uint8_t value) {

    if (ext_eeprom_ready()) {
        ext_eeprom_write(address, &value, 1);
    } else {
        return false;
    }

    return true;
}

bool MEM_get_str(uint16_t address, uint8_t *data, uint16_t i_size) {
    if (!data || !i_size)
        return false;

    return ext_eeprom_read(address, data, i_size);
}

bool MEM_set_str(uint16_t address, uint8_t *data, uint16_t i_size) {
    if (!data || !i_size)
        return false;

    return ext_eeprom_write(address, data, i_size);
}

float MEM_get_mb_float(uint16_t address) {
    uint32_t dw;

    dw = MEM_get_dword(address);
    itofl.a[0] = make8(dw, 0);
    itofl.a[1] = make8(dw, 1);
    itofl.a[2] = make8(dw, 2);
    itofl.a[3] = make8(dw, 3);

    return (float) itofl.b;
}

bool MEM_set_mb_float(uint16_t address, float value) {
    uint8_t aux[4];

    itofl.b = 0;
    itofl.b = value;
    aux[0] = itofl.a[0];
    aux[1] = itofl.a[1];
    aux[2] = itofl.a[2];
    aux[3] = itofl.a[3];
    //MEM_set_str(address * 4, aux, 4);
    MEM_set_dword(address, itofl.c);

    return true;
}

bool bit_test(uint64_t val, uint8_t bit) {
    uint64_t mask;

    mask = 1;
    mask <<= bit;

    return ((val & mask) == mask);
}

void bit_set(uint16_t *val, uint8_t bit) {
    uint16_t mask;

    mask = 0;
    mask = (1 << bit);
    *val |= mask;

    return;
}

void bit_clear(uint16_t *val, uint8_t bit) {
    uint16_t mask;

    mask = 0;
    mask = ~(1 << bit);
    *val &= mask;

    return;
}

bool MEM_get_bit(uint16_t address) {
    uint16_t addr, val;
    uint8_t bit;
    bool ret;

    ret = false;
    addr = (uint16_t) (address / 16);
    bit = (uint8_t) (address - (addr * 16));
    val = MEM_get_register(addr);
    ret = bit_test((uint64_t) val, bit);

    return ret;
}

void MEM_set_bit(uint16_t address, bool value) {
    uint16_t addr, val;
    uint8_t bit;

    addr = (uint16_t) (address / 16);
    bit = (uint8_t) (address - (addr * 16));
    val = MEM_get_register(addr);

    if (value) {
        bit_set(&val, bit);
    } else {
        bit_clear(&val, bit);
    }

    MEM_set_register(addr, val);

    return;
}
