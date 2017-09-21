
#include "rtcc.h"
#include <xc.h>
#include <stdio.h>

cal_t calendario;
uint32_t ticks;

void __attribute__((interrupt, no_auto_psv)) _RTCCInterrupt(void) {
    ticks++;
    LATG ^= (1 << 8);
    IFS3bits.RTCIF = 0;
}

void RTCC_init(void) {
    ticks = 0;

    __builtin_write_RTCC_WRLOCK(); // Clear WRLOCK to modify RTCC as needed

    RTCCON1Lbits.OUTSEL = 1; // 0b001 -> second clock
    //RTCCON1Lbits.OUTSEL = 0; // 0b000 -> alarm event
    RTCCON1Lbits.RTCOE = 1; // RTCC pin pulses for debugging
    RTCCON2Lbits.CLKSEL = 1; // 0b01 -> LPRC
    //RTCCON2Lbits.CLKSEL = 0; // 0b00 -> SOSC

    // Set some random times
    //    if ((DATEH & 0xFF1F) == 0x0001) // Reset value
    //    {
    //        TIMEL = 0x5000;
    //        TIMEH = 0x1346;
    //        DATEL = 0x3105;
    //        DATEH = 0x1612;
    //    }

    // Interrupt every 1/2s
    RTCCON1Hbits.AMASK = 0b0000; // 0b0000 -> every 1/2 sec
    RTCCON1Hbits.CHIME = 1;
    RTCCON1Hbits.ALRMEN = 1;
    RTCCON1Hbits.ALMRPT = 2;
    IFS3bits.RTCIF = 0;
    IEC3bits.RTCIE = 1;
    RTCCON1Lbits.RTCEN = 1;
    RTCCON1Lbits.WRLOCK = 1; // Lock the RTCC registers

    return;
}

void RTCC_reset(uint8_t time_h) {
    __builtin_write_RTCC_WRLOCK();
    TIMEL = 0; // Reset seconds
    TIMEH = (TIMEH & 0xFF00) | time_h;
    RTCCON1Lbits.WRLOCK = 1;
}

void RTCC_update(void) {
    calendario._ano = (uint16_t) ((DATEHbits.YRTEN * 10
            + DATEHbits.YRONE) + 2000);
    calendario._mes = (uint8_t) (DATEHbits.MTHTEN * 10
            + DATEHbits.MTHONE);
    calendario._dia = (uint8_t) (DATELbits.DAYTEN * 10
            + DATELbits.DAYONE);
    calendario._hora = (uint8_t) (TIMEHbits.HRTEN * 10
            + TIMEHbits.HRONE);
    calendario._minuto = (uint8_t) (TIMEHbits.MINTEN * 10
            + TIMEHbits.MINONE);
    calendario._segundo = (uint8_t) (TIMELbits.SECTEN * 10
            + TIMELbits.SECONE);

    calendario.timestamp = (uint32_t) (calendario._ano * 525600);
    calendario.timestamp += (uint32_t) (calendario._mes * 43800);
    calendario.timestamp += (uint32_t) (calendario._dia * 1440);
    calendario.timestamp += (uint32_t) (calendario._hora * 60);
    calendario.timestamp += (uint32_t) (calendario._minuto);

    return;
}

void RTCC_set(cal_t c) {
    uint8_t aux;

    aux = 0;

    if (c._ano >= 2000)
        c._ano -= 2000;

    __builtin_write_RTCC_WRLOCK();
    aux = (uint8_t) (c._ano / 10);
    DATEHbits.YRTEN = aux;
    DATEHbits.YRONE = (uint8_t) (c._ano - (aux * 10));

    aux = 0;
    aux = (uint8_t) (c._mes / 10);
    DATEHbits.MTHTEN = aux;
    DATEHbits.MTHONE = (uint8_t) (c._mes - (aux * 10));

    aux = 0;
    aux = (uint8_t) (c._dia / 10);
    DATELbits.DAYTEN = aux;
    DATELbits.DAYONE = (uint8_t) (c._dia - (aux * 10));

    aux = 0;
    aux = (uint8_t) (c._hora / 10);
    TIMEHbits.HRTEN = aux;
    TIMEHbits.HRONE = (uint8_t) (c._hora - (aux * 10));

    aux = 0;
    aux = (uint8_t) (c._minuto / 10);
    TIMEHbits.MINTEN = aux;
    TIMEHbits.MINONE = (uint8_t) (c._minuto - (aux * 10));

    aux = 0;
    TIMELbits.SECTEN = 0;
    TIMELbits.SECONE = 0;
    RTCCON1Lbits.WRLOCK = 1;

    return;
}

void RTCC_getCal(cal_t *cal) {
    cal->_ano = calendario._ano;
    cal->_mes = calendario._mes;
    cal->_dia = calendario._dia;
    cal->_hora = calendario._hora;
    cal->_minuto = calendario._minuto;
    cal->_segundo = calendario._segundo;
    cal->timestamp = calendario.timestamp;

    return;
}

uint32_t RTCC_get_ticks(void) {
    return ticks;
}

void RTCC_set_ticks(uint32_t val) {
    ticks = val;

    return;
}