#ifndef RTCC_H
#define RTCC_H

#include "sys.h"

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct rtcc_str {
};

void RTCC_init(void);
void RTCC_reset(uint8_t u8);
void __attribute__((interrupt, no_auto_psv)) _RTCCInterrupt(void);

#endif