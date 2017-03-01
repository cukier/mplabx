/*
 * File:   int_ext.c
 * Author: cuki
 *
 * Created on February 28, 2013, 7:42 AM
 */
#include <p18f452.h>
#include <portb.h>
#include <stdio.h>
#include <delays.h>
#include <lcd.h>

#pragma config OSC = HSPLL
#pragma config WDT = OFF
#pragma config LVP = OFF
#pragma config DEBUG = ON

void toggle_led(void);

#pragma code HIGH_INTERRUPT_VECTOR = 0x8

void high_ISR(void) {
    _asm
    goto toggle_led
            _endasm
}
#pragma code

#pragma interrupt toggle_led

void toggle_led(void) {
    INTCONbits.INT0IF = 0;
    PORTDbits.RD0 = ~PORTDbits.RD0;
}

void EnableHighInterrupts(void) {
    RCONbits.IPEN = 1;
    INTCONbits.GIEH = 1;
    TRISD = 0;
}

void main(void) {
    EnableHighInterrupts();
    OpenRB0INT(PORTB_CHANGE_INT_ON & PORTB_PULLUPS_ON & FALLING_EDGE_INT);
    lcdInit();
    Delay10KTCYx(15);
    while (1) {
        printf("\fSaida: %d", PORTDbits.RD0);
        Delay10KTCYx(300);
    }
}
