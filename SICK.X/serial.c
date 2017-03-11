#include "serial.h"
#include <libpic30.h>

#ifdef USE_UART_1
uint16_t serial_buffer_index1, serial_buff_rec1;
uint8_t *serial_buffer1;
bool rec_ok1;

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    serial_buffer1[serial_buffer_index1++] = U1RXREG;

    if (serial_buffer_index1 >= SERIAL_BUFFER_SIZE)
        serial_buffer_index1 = 0;

    T1CONbits.TCKPS = 1; //1:8
    IFS0bits.U1RXIF = 0; //limpa flag int rx     
    T1CONbits.TON = 1; //liga timer 1
    PR1 = UINT16_MAX; //periodo timer 1
    rec_ok1 = false;
}

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void) {
    T1CONbits.TON = 0; //desliga timer    
    _T1IF = 0; //deliga flag interrupcao
    serial_buff_rec1 = serial_buffer_index1;
    serial_buffer_index1 = 0;
    rec_ok1 = true;
}

void tmr1_init() {
    T1CON = 0; //limpa registrador    
    _T1IP = 1; //prioriedade interrupcao timer 1 alta    
    _T1IF = 0; //limpa flag de disparo timer 1
    _T1IE = 1; //habilita interrupcao timer 1
    PR1 = 65535;
    //tempo = 2 x PR1 x TCKPS / FOSC
    //tempo = 2 x 30000 x 256 / 16000000
    return;
}

void uart1_init(uint8_t *in_buffer) {
    serial_buffer_index1 = 0;
    serial_buffer1 = in_buffer;
    rec_ok1 = false;

    U1MODEbits.STSEL = 0; // 1 stop bit
    U1MODEbits.PDSEL = 0; // 8-bit data, no parity
    U1MODEbits.ABAUD = 0; // Baud rate measurement is disabled or completed
    U1MODEbits.BRGH = 0; // Standard Speed mode

    U1BRG = BRGVAL; //Baudrate

    U1MODEbits.UARTEN = 0; // UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0>    
    U1STAbits.UTXEN = 0; // Transmit is enabled, UxTX pin is controlled by UARTx
    U1STAbits.URXEN = 0; // Recive is enabled

    IFS0bits.U1RXIF = 0; //limpa falg int rx1
    IEC0bits.U1RXIE = 1; //habilita interrupcao rx1  

    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;

    //__builtin_write_OSCCONL(OSCCON & 0xbf); // Unlock Registers
    RPINR18bits.U1RXR = U1_RX_RP; // Assign U1RX To Pin RP11    
    U1_TX_RP = 3; // Assign U1TX To Pin RP12
    __C30_UART = 1; // printf

    tmr1_init();

    U1MODEbits.UARTEN = 1;

    return;
}

uint16_t uart1_get_index(void) {
    return serial_buff_rec1;
}

bool uart1_get_rec(void) {
    return rec_ok1;
}

void uart1_set_rec(void) {
    rec_ok1 = false;
}
#endif

#ifdef USE_UART_2
uint16_t serial_buffer_index2, serial_buff_rec2;
uint8_t *serial_buffer2;
bool rec_ok2;

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void) {
    serial_buffer2[serial_buffer_index2++] = U1RXREG;

    if (serial_buffer_index2 >= SERIAL_BUFFER_SIZE)
        serial_buffer_index2 = 0;

    T1CONbits.TCKPS = 1; //1:8
    IFS0bits.U1RXIF = 0; //limpa flag int rx     
    T1CONbits.TON = 1; //liga timer 2
    PR2 = UINT16_MAX; //periodo timer 2
    rec_ok2 = false;
}

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    T1CONbits.TON = 0; //desliga timer    
    _T1IF = 0; //deliga flag interrupcao
    serial_buff_rec2 = serial_buffer_index2;
    serial_buffer_index2 = 0;
    rec_ok2 = true;
}

void tmr1_init() {
    T1CON = 0; //limpa registrador    
    _T1IP = 1; //prioriedade interrupcao timer 1 alta    
    _T1IF = 0; //limpa flag de disparo timer 1
    _T1IE = 1; //habilita interrupcao timer 1
    PR1 = 65535;
    //tempo = 2 x PR1 x TCKPS / FOSC
    //tempo = 2 x 30000 x 256 / 16000000
    return;
}

void uart1_init(uint8_t *in_buffer) {
    serial_buffer_index2 = 0;
    serial_buffer2 = in_buffer;
    rec_ok2 = false;

    U1MODEbits.STSEL = 0; // 1 stop bit
    U1MODEbits.PDSEL = 0; // 8-bit data, no parity
    U1MODEbits.ABAUD = 0; // Baud rate measurement is disabled or completed
    U1MODEbits.BRGH = 0; // Standard Speed mode

    U1BRG = BRGVAL; //Baudrate

    U1MODEbits.UARTEN = 0; // UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0>    
    U1STAbits.UTXEN = 0; // Transmit is enabled, UxTX pin is controlled by UARTx
    U1STAbits.URXEN = 0; // Recive is enabled

    IFS0bits.U1RXIF = 0; //limpa falg int rx1
    IEC0bits.U1RXIE = 1; //habilita interrupcao rx1  

    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;

    //__builtin_write_OSCCONL(OSCCON & 0xbf); // Unlock Registers
    RPINR18bits.U1RXR = U1_RX_RP; // Assign U1RX To Pin RP11    
    U1_TX_RP = 3; // Assign U1TX To Pin RP12
    __C30_UART = 1; // printf

    tmr1_init();

    U1MODEbits.UARTEN = 1;

    return;
}

uint16_t uart1_get_index(void) {
    return serial_buff_rec2;
}

bool uart1_get_rec(void) {
    return rec_ok2;
}

void uart1_set_rec(void) {
    rec_ok2 = false;
}
#endif