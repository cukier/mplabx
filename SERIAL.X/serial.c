#include "serial.h"
#include "sys.h"
#include <libpic30.h>

#ifdef USE_UART_1
uint16_t serial_buffer_index1, serial_buff_rec1;
uint8_t *serial_buffer1;
bool rec_ok1;
#endif

#ifdef USE_UART_2
uint16_t serial_buffer_index2, serial_buff_rec2;
uint8_t *serial_buffer2;
bool rec_ok2;
#endif

#ifdef USE_UART_3
#define TX_BUFFER_SIZE      SERIAL_BUFFER_SIZE
#define RX_BUFFER_SIZE      SERIAL_BUFFER_SIZE
#define _ISR_   void __attribute__((interrupt, no_auto_psv))

uint8_t TX_buffer[TX_BUFFER_SIZE] = {0};
uint16_t TX_head = 0;
uint16_t TX_next = 0;

uint8_t RX_buffer[RX_BUFFER_SIZE] = {0};
uint16_t RX_head = 0;
uint16_t RX_next = 0;

#define OFF     (0)
#define YES     (1)
#define ON      (1)
#endif

#ifdef USE_UART_1
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
    rec_ok1 = false;

    if (in_buffer != NULL)
        serial_buffer1 = in_buffer;

    U1MODEbits.STSEL = 0; // 1 stop bit
    U1MODEbits.PDSEL = 0; // 8-bit data, no parity
    U1MODEbits.ABAUD = 0; // Baud rate measurement is disabled or completed
    U1MODEbits.BRGH = 0; // Standard Speed mode

    U1BRG = BRGVAL_1; //Baudrate

    U1MODEbits.UARTEN = 0; // UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0>    
    U1STAbits.UTXEN = 1; // Transmit is enabled, UxTX pin is controlled by UARTx
//    U1STAbits.URXEN = 0; // Recive is enabled

//    IFS0bits.U1RXIF = 0; //limpa falg int rx1
//    IEC0bits.U1RXIE = 1; //habilita interrupcao rx1  

//    IFS0bits.T1IF = 0;
//    IEC0bits.T1IE = 1;

//    RPINR18bits.U1RXR = U1_RX_RP; // Assign U1RX To Pin RP11    
    U1_TX_RP = 3; // Assign U1TX To Pin RP2

//    tmr1_init();

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
void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void) {
    serial_buffer2[serial_buffer_index2++] = U2RXREG;

    if (serial_buffer_index2 >= SERIAL_BUFFER_SIZE)
        serial_buffer_index2 = 0;

    T2CONbits.TCKPS = 1; //1:8
    IFS1bits.U2RXIF = 0; //limpa flag int rx         
    T2CONbits.TON = 1; //liga timer 2    
    PR2 = UINT16_MAX; //periodo timer 2
    rec_ok2 = false;
}

void __attribute__((interrupt, auto_psv)) _T2Interrupt(void) {
    T2CONbits.TON = 0; //desliga timer    
    _T2IF = 0; //deliga flag interrupcao
    serial_buff_rec2 = serial_buffer_index2;
    serial_buffer_index2 = 0;
    rec_ok2 = true;
}

void tmr2_init() {
    T2CON = 0; //limpa registrador    
    _T2IP = 1; //prioriedade interrupcao timer 1 alta    
    _T2IF = 0; //limpa flag de disparo timer 1
    _T2IE = 1; //habilita interrupcao timer 1
    T2CONbits.T32 = 0; //16bit timer
    PR2 = 65535;
    //tempo = 2 x PR1 x TCKPS / FOSC
    //tempo = 2 x 30000 x 256 / 16000000
    return;
}

void uart2_init(uint8_t *in_buffer) {
    serial_buffer_index2 = 0;
    serial_buffer2 = in_buffer;
    rec_ok2 = false;

    U2MODEbits.STSEL = 0; // 1 stop bit
    U2MODEbits.PDSEL = 0; // 8-bit data, no parity
    U2MODEbits.ABAUD = 0; // Baud rate measurement is disabled or completed
    U2MODEbits.BRGH = 0; // Standard Speed mode

    U2BRG = BRGVAL_2; //Baudrate

    U2MODEbits.UARTEN = 0; // UARTx is enabled; all UARTx pins are controlled by UARTx as defined by UEN<1:0>    
    U2STAbits.UTXEN = 0; // Transmit is enabled, UxTX pin is controlled by UARTx
    U2STAbits.URXEN = 0; // Recive is enabled

    IFS1bits.U2RXIF = 0; //limpa falg int rx2
    IEC1bits.U2RXIE = 1; //habilita interrupcao rx2  

    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;

    //__builtin_write_OSCCONL(OSCCON & 0xbf); // Unlock Registers
    RPINR19bits.U2RXR = U2_RX_RP; // Assign U2RX To Pin RP11  
    U2_TX_RP = 5; // Assign U2TX To Pin RP12

    tmr2_init();

    U2MODEbits.UARTEN = 1;

    return;
}

uint16_t uart2_get_index(void) {
    return serial_buff_rec2;
}

bool uart2_get_rec(void) {
    return rec_ok2;
}

void uart2_set_rec(void) {
    rec_ok2 = false;
}
#endif

#ifdef USE_UART_3
void initUart(void) {
    _U3RXIE = 0; // disable UART Rx interrupt
    _U3TXIE = 0; // disable UART Tx interrupt

    U3MODEbits.UARTEN = OFF; // disable the UART module while configuring
    U3MODEbits.USIDL = OFF; // do not stop in idle mode
    U3MODEbits.IREN = OFF; // disable IrDA encode and decode
    U3MODEbits.UEN = 0b00; // manual hardware flow control
    U3MODEbits.WAKE = ON; // wake up on detection of start bit
    U3MODEbits.LPBACK = OFF; // disable loopback mode
    U3MODEbits.ABAUD = OFF; // disable baud rate auto-detect
    U3MODEbits.RXINV = ON; // invert Rx idle state
    U3MODEbits.BRGH = 1; // high speed baud rate
    U3MODEbits.PDSEL = 0b00; // 8-bit data, no parity
    U3MODEbits.STSEL = 0; // 1 stop bit
    U3STAbits.UTXISEL1 = 0b1; // interrupt when Tx buffer is empty
    U3STAbits.UTXISEL0 = 0b0; // interrupt when Tx buffer is empty
    U3STAbits.UTXINV = OFF; // do not invert Tx idle bit*/
    U3STAbits.UTXBRK = OFF; // disable sync break transmission
    U3STAbits.UTXEN = YES; // enable UART transmitter
    U3STAbits.URXISEL = 0b00; // interrupt when character received
    U3STAbits.OERR = 0; // clear Rx overrun error flag

    U3BRG = ((FCY / 9600) / 4) - 1; // calculate value for baud register

    /* configure pin direction */
    _TRISD11 = 0; // TX -> output
    _TRISD0 = 1; // RX -> input

    /* map modules to pins */
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock peripheral pin select registers
    _RP12R = 19; // Remmapable pin 12 is UART3 transmit
    _U3RXR = 11; // UART3 receive mapped to remmapable pin 11
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock peripheral pin select registers

    /* clear interrupts so they don't immediately interrupt */
    _U3RXIF = OFF; // clear Rx interrupt flag
    _U3TXIF = OFF; // clear Tx interrupt flag

    _U3RXIP = 6; // set Rx interrupt priority
    _U3TXIP = 4; // set Tx interrupt priority

    U3MODEbits.UARTEN = ON; // enable the UART module now that its configured

    /* Note: UART Tx cannot be enabled until the UART module itself has been enabled. */
    U3STAbits.UTXEN = YES; // enable UART transmitter

    _U3RXIE = 1; // enable UART Rx interrupt
}

uint16_t getTxSize(void) {
    return TX_next - TX_head
            + (TX_head > TX_next ? TX_BUFFER_SIZE : 0);
}

uint16_t getRxSize(void) {
    return RX_next - RX_head
            + (RX_head > RX_next ? RX_BUFFER_SIZE : 0);
}

uint16_t getTxSpace(void) {
    return TX_head - TX_next - 1
            + (TX_head <= TX_next ? TX_BUFFER_SIZE : 0);
}

_ISR_ _U3RXInterrupt(void) {

    while (U3STAbits.URXDA) // while data is available
    {
        RX_buffer[RX_next++] = U3RXREG; // copy byte to buffer

        RX_next %= RX_BUFFER_SIZE; // protect against rollover

        /* accommodate overflow */
        if (RX_head == RX_next)
            RX_head = (RX_head + 1) % RX_BUFFER_SIZE;
    }

    _U3RXIF = OFF; // clear Rx interrupt flag
}

void clearRx(void) {
    RX_head = RX_next;
}

_ISR_ _U3TXInterrupt(void) {
    _U3TXIF = OFF; // clear Tx interrupt flag

    /* transmit if transmit queue has room and buffer is not empty */
    while (!(U3STAbits.UTXBF) && (TX_head != TX_next)) {
        U3TXREG = TX_buffer[TX_head++];
        TX_head %= TX_BUFFER_SIZE;
    }
}

bool sendFrom(const uint8_t* startOfData, uint16_t bytesToSend) {
    /* can't send nonexistent data or no data */
    if (!startOfData || !bytesToSend)
        return false;

    /* make sure room is available in buffer */
    while (getTxSpace() < bytesToSend);

    /* pause background sending of data */
    _U3TXIE = 0; // disable UART Tx interrupt

    /* send bytes while bytes still need to be sent */
    while (bytesToSend--) {
        TX_buffer[TX_next++] = *startOfData;

        /* circular queue rollover protection */
        TX_next %= TX_BUFFER_SIZE;

        /* accommodate overflow */
        if (TX_head == TX_next)
            TX_head = (TX_head + 1) % TX_BUFFER_SIZE;

        ++startOfData;
    }

    /* continue with background transmitting */
    _U3TXIE = YES; // enable UART Tx interrupt

    /* force transmit process to start if haven't started already */
    _U3TXIF = YES; // trigger UART Tx interrupt

    return true;
}

void startRx(void) {
    clearRx(); // empty the Rx buffer
    _U3RXIE = 1; // enable Rx interrupt
}

void setBaudRate(uint64_t desiredBaudRate) {
    U3BRG = ((FCY / desiredBaudRate) / 4) - 1; // calculate value for baud register
}

int copyFrom(uint8_t* startOfStorage, int maxBytesToRead) {
    if (!startOfStorage)
        return 0;

    _U3RXIE = 0; /* disable UART Rx interrupt */

    int head = RX_head,
            next = RX_next,
            count = 0;

    while (maxBytesToRead-- && (head != next)) {
        startOfStorage[count++] = RX_buffer[head++];
        head %= RX_BUFFER_SIZE;
    }

    _U3RXIE = 1; /* enable UART Rx interrupt */

    return count;
}

uint16_t receiveFrom(uint8_t* startOfStorage, uint16_t maxBytesToRead) {
    if (!startOfStorage)
        return 0;

    uint16_t count = 0;

    while (maxBytesToRead-- && (RX_head != RX_next)) {
        startOfStorage[count++] = RX_buffer[RX_head++];
        RX_head %= RX_BUFFER_SIZE;
    }

    return count;
}

void dropFrom(int bytesToDrop) {
    if (bytesToDrop <= 0)
        return;
    _U3RXIE = 0; /* disable UART Rx interrupt */
    RX_head = (RX_head + bytesToDrop) % RX_BUFFER_SIZE;
    if (RX_head > RX_next)
        RX_head = RX_next;
    _U3RXIE = 1; /* enable UART Rx interrupt */
}

void flush(void) {
    RX_head = RX_next;
}
#endif