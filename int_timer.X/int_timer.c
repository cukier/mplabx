#include <p18f452.h>
#include <delays.h>
#include <stdio.h>
#include <lcd.h>
#include <timers.h>

#pragma config OSC = HSPLL, OSCS = OFF
#pragma config PWRT = OFF
#pragma config BOR = OFF, BORV = 20
#pragma config WDT = OFF, WDTPS = 128
#pragma config CCP2MUX = OFF
#pragma config STVR = OFF
#pragma config LVP = OFF
#pragma config DEBUG = OFF
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF, WRTC = OFF, WRTD = OFF
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF

void timer0_isr(void);

#pragma code HIGH_INTERRUPT_VECTOR = 0x8

void high_ISR(void) {
    _asm
    goto timer0_isr
            _endasm
}
#pragma code

#pragma interrupt timer0_isr

void timer0_isr(void) {
    INTCONbits.TMR0IF = 0;
    TMR0H = 0;
    TMR0L = 0;
    PORTCbits.RC2 = !PORTCbits.RC2;
}

void EnableHighInterrupts(void) {
    RCONbits.IPEN = 1;
    INTCONbits.GIEH = 1;
}

void main(void) {

    TRISCbits.RC2 = 0;
    TRISDbits.RD0 = 0;
    PORTDbits.RD0 = 1;

    EnableHighInterrupts();
    OpenTimer0(TIMER_INT_ON & T0_SOURCE_INT & T0_16BIT & T0_PS_1_16);

    while (1) {
        Delay10KTCYx(2500);
        PORTDbits.RD0 = !PORTDbits.RD0;
    }
    return;
}
