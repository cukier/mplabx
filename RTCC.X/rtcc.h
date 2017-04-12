#ifndef RTCC_H
#define RTCC_H

#include <xc.h>
#include <stdint.h>

void RTCC_init(void);
void RTCC_reset(uint8_t u8);
void __attribute__((interrupt, no_auto_psv)) _RTCCInterrupt(void);

#endif