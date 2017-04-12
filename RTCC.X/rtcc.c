
#include "rtcc.h"


void RTCC_init(void) {
    __builtin_write_RTCC_WRLOCK(); // Clear WRLOCK to modify RTCC as needed

    RTCCON1Lbits.OUTSEL=0b001; // 0b001 -> second clock
    //RTCCON1Lbits.OUTSEL = 0b000; // 0b000 -> alarm event
    RTCCON1Lbits.RTCOE = 1; // RTCC pin pulses for debugging
    //RTCCON2Lbits.CLKSEL=0b01; // 0b01 -> LPRC
    RTCCON2Lbits.CLKSEL = 0b00; // 0b00 -> SOSC

    // Set some random times
    if ((DATEH & 0xFF1F) == 0x0001) // Reset value
    {
        TIMEL = 0x5000;
        TIMEH = 0x1346;
        DATEL = 0x3105;
        DATEH = 0x1612;
    }

    // Interrupt every 1/2s
    RTCCON1Hbits.AMASK = 0b0000; // 0b0000 -> every 1/2 sec
    RTCCON1Hbits.CHIME = 1;
    RTCCON1Hbits.ALRMEN = 1;
    IFS3bits.RTCIF = 0;
    IEC3bits.RTCIE = 1;
    RTCCON1Lbits.RTCEN = 1;
    RTCCON1Lbits.WRLOCK = 1; // Lock the RTCC registers

}

void RTCC_reset(uint8_t u8) {
    __builtin_write_RTCC_WRLOCK();
    TIMEL = 0; // Reset seconds
    TIMEH = (TIMEH & 0xFF00) | u8;
    RTCCON1Lbits.WRLOCK = 1;
}

void __attribute__((interrupt, no_auto_psv)) _RTCCInterrupt(void)
{
    _LATG8 = !_LATG8;
    IFS3bits.RTCIF=0;
}