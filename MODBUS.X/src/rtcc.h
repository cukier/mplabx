#ifndef RTCC_H
#define RTCC_H

#include "sys.h"
#include <stdint.h>
#include <stdbool.h>

#define _2S_TICKS   4

typedef struct cal_str {
    uint16_t _ano;
    uint8_t _mes;
    uint8_t _dia;
    uint8_t _hora;
    uint8_t _minuto;
    uint8_t _segundo;
    uint32_t timestamp;
} cal_t;

void __attribute__((interrupt, no_auto_psv)) _RTCCInterrupt(void);
void RTCC_init(void);
void RTCC_reset(uint8_t time_h);
void RTCC_update(void);
void RTCC_set(cal_t c);
void RTCC_getCal(cal_t *cal);
uint32_t RTCC_get_ticks(void);
void RTCC_set_ticks(uint32_t val);

#endif