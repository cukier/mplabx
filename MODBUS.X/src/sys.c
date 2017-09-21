/*
 * File:   sys.c
 * Author: cuki
 *
 * Created on 17 de Abril de 2017, 08:28
 */

#include "modbus.h"
#include "serial.h"
#include "modbus.h"
#include "sys.h"
#include "heart_beat.h"
#include "rtcc.h"
#include "mem.h"
#include "esp.h"
#include "ext_eeprom.h"

bool sys_init(void) {
    hb_init();
    uart_init();
    //RTCC_init();
    //esp_init();
    ext_eeprom_init();
    //PIVO_mem_init();
    //modbus_set_addr(PIVO_get_address());
    __delay_ms(300);
#ifdef DEBUG
    __C30_UART = 1;

#endif

    return true;
}

void sys_pooling(void) {
    RTCC_update();
    slave_response();
    esp_pool();
    __delay_ms(100);

    return;
}

uint8_t make8(uint64_t val, uint8_t index) {
    uint64_t mask;
    uint8_t ret;

    ret = 0;
    mask = 0xFF;

    mask <<= (8 * index);
    ret = (uint8_t) ((val & mask) >> (index * 8));

    return ret;
}

uint32_t make32(uint8_t hh, uint8_t hl, uint8_t lh, uint8_t ll) {
    uint32_t ret = 0;

    ret = (uint32_t) hh << 24;
    ret |= (uint32_t) hl << 16;
    ret |= (uint32_t) lh << 8;
    ret |= (uint32_t) ll;

    return ret;
}

uint16_t make16(uint8_t h, uint8_t l) {
    uint16_t ret = 0;

    ret = (uint16_t) h << 8;
    ret |= (uint16_t) l;

    return ret;
}