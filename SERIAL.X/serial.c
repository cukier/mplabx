#include "serial.h"
#include "sys.h"
#include <libpic30.h>

void uart_init(uint8_t uartNr) {

    switch (uartNr) {
        default:
        case 1:
            U1MODE = 0;
            U1BRG = BRGVAL; //Baudrate
            U1STAbits.UTXEN = 1;
            RPOR6bits.RP12R = 3;
            U1MODEbits.UARTEN = 1;
            __C30_UART = 1;
            break;
        case 2:
            U2MODE = 0;
            U2BRG = BRGVAL; //Baudrate
            U2STAbits.UTXEN = 1;
            RPOR11bits.RP23R = 5;
            U2MODEbits.UARTEN = 1;
            __C30_UART = 2;
            break;
        case 3:
            U3MODE = 0;
            U3BRG = BRGVAL; //Baudrate
            U3STAbits.UTXEN = 1;
            RPOR6bits.RP12R = 19;
            U3MODEbits.UARTEN = 1;
            __C30_UART = 3;
            break;
        case 4:
            U4MODE = 0;
            U4BRG = BRGVAL; //Baudrate
            U4STAbits.UTXEN = 1;
            RPOR1bits.RP2R = 21;
            U4MODEbits.UARTEN = 1;
            __C30_UART = 4;
            break;
        case 5:
            U5MODE = 0;
            U5BRG = BRGVAL; //Baudrate
            U5STAbits.UTXEN = 1;
            U5MODEbits.UARTEN = 1;
            __C30_UART = 5;
            break;
        case 6:
            U6MODE = 0;
            U6BRG = BRGVAL; //Baudrate
            U6STAbits.UTXEN = 1;
            U6MODEbits.UARTEN = 1;
            __C30_UART = 6;
            break;
    }
    return;
}
