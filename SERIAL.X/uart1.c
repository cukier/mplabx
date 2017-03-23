#include "uart1.h"

#define RX_BUFFER_SIZE    0x0800
#define TX_BUFFER_SIZE    0x0040

static uint8_t TX_buffer[TX_BUFFER_SIZE] = {0};
static volatile uint16_t TX_head = 0;
static volatile uint16_t TX_next = 0;

static uint8_t RX_buffer[RX_BUFFER_SIZE] = {0};
static volatile uint16_t RX_head = 0;
static volatile uint16_t RX_next = 0;

static void initUart(void) {
    _U1RXIE = 0; // disable UART Rx interrupt
    _U1TXIE = 0; // disable UART Tx interrupt

    U1MODEbits.UARTEN = OFF; // disable the UART module while configuring
    U1MODEbits.USIDL = OFF; // do not stop in idle mode
    U1MODEbits.IREN = OFF; // disable IrDA encode and decode
    U1MODEbits.UEN = 0b00; // manual hardware flow control
    U1MODEbits.WAKE = ON; // wake up on detection of start bit
    U1MODEbits.LPBACK = OFF; // disable loopback mode
    U1MODEbits.ABAUD = OFF; // disable baud rate auto-detect
    U1MODEbits.RXINV = OFF; // do not invert Rx idle state
    U1MODEbits.BRGH = 1; // high speed baud rate
    U1MODEbits.PDSEL = 0b00; // 8-bit data, no parity
    U1MODEbits.STSEL = 0; // 1 stop bit
    U1STAbits.UTXISEL1 = 0b1; // interrupt when Tx buffer is empty
    U1STAbits.UTXISEL0 = 0b0; // interrupt when Tx buffer is empty
    U1STAbits.UTXINV = OFF; // do not invert Tx idle bit*/
    U1STAbits.UTXBRK = OFF; // disable sync break transmission
    U1STAbits.UTXEN = YES; // enable UART transmitter
    U1STAbits.URXISEL = 0b00; // interrupt when character received
    U1STAbits.OERR = 0; // clear Rx overrun error flag

    U1BRG = ((FCY / 9600) / 4) - 1; // calculate value for baud register

    /* configure pin direction */
    _TRISD11 = 0; // TX -> output
    _TRISD10 = 1; // RX -> input

    /* map modules to pins */
    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock peripheral pin select registers
    _RP12R = 3; // Remmapable pin 12 is UART1 transmit
    _U1RXR = 11; // UART1 receive mapped to remmapable pin 11
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock peripheral pin select registers

    /* clear interrupts so they don't immediately interrupt */
    _U1RXIF = OFF; // clear Rx interrupt flag
    _U1TXIF = OFF; // clear Tx interrupt flag

    _U1RXIP = 6; // set Rx interrupt priority
    _U1TXIP = 4; // set Tx interrupt priority

    U1MODEbits.UARTEN = ON; // enable the UART module now that its configured

    /* Note: UART Tx cannot be enabled until the UART module itself has been enabled. */
    U1STAbits.UTXEN = YES; // enable UART transmitter

    _U1RXIE = 1; // enable UART Rx interrupt
}

inline static uint16_t getTxSize(void) {
    return TX_next - TX_head
            + (TX_head > TX_next ? TX_BUFFER_SIZE : 0);
}

inline static uint16_t getRxSize(void) {
    return RX_next - RX_head
            + (RX_head > RX_next ? RX_BUFFER_SIZE : 0);
}

inline static uint16_t getTxSpace(void) {
    return TX_head - TX_next - 1
            + (TX_head <= TX_next ? TX_BUFFER_SIZE : 0);
}

_ISR_ _U1RXInterrupt(void) {

    while (U1STAbits.URXDA) // while data is available
    {
        RX_buffer[RX_next++] = U1RXREG; // copy byte to buffer

        RX_next %= RX_BUFFER_SIZE; // protect against rollover

        /* accommodate overflow */
        if (RX_head == RX_next)
            RX_head = (RX_head + 1) % RX_BUFFER_SIZE;
    }

    _U1RXIF = OFF; // clear Rx interrupt flag
}

inline static void clearRx(void) {
    RX_head = RX_next;
}

_ISR_ _U1TXInterrupt(void) {
    _U1TXIF = OFF; // clear Tx interrupt flag

    /* transmit if transmit queue has room and buffer is not empty */
    while (!(U1STAbits.UTXBF) && (TX_head != TX_next)) {
        U1TXREG = TX_buffer[TX_head++];
        TX_head %= TX_BUFFER_SIZE;
    }
}

static bool sendFrom(const uint8_t* startOfData, uint16_t bytesToSend) {
    /* can't send nonexistent data or no data */
    if (!startOfData || !bytesToSend)
        return false;

    /* make sure room is available in buffer */
    while (getTxSpace() < bytesToSend);

    /* pause background sending of data */
    _U1TXIE = 0; // disable UART Tx interrupt

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
    _U1TXIE = YES; // enable UART Tx interrupt

    /* force transmit process to start if haven't started already */
    _U1TXIF = YES; // trigger UART Tx interrupt

    return true;
}

inline static void startRx(void) {
    clearRx(); // empty the Rx buffer
    _U1RXIE = 1; // enable Rx interrupt
}

inline static void setBaudRate(uint64_t desiredBaudRate) {
    U1BRG = ((FCY / desiredBaudRate) / 4) - 1; // calculate value for baud register
}

static int copyFrom(uint8_t* startOfStorage, int maxBytesToRead) {
    if (!startOfStorage)
        return 0;

    _U1RXIE = 0; /* disable UART Rx interrupt */

    int head = RX_head,
            next = RX_next,
            count = 0;

    while (maxBytesToRead-- && (head != next)) {
        startOfStorage[count++] = RX_buffer[head++];
        head %= RX_BUFFER_SIZE;
    }

    _U1RXIE = 1; /* enable UART Rx interrupt */

    return count;
}

static int receiveFrom(uint8_t* startOfStorage, int maxBytesToRead) {
    if (!startOfStorage)
        return 0;

    int count = 0;

    while (maxBytesToRead-- && (RX_head != RX_next)) {
        startOfStorage[count++] = RX_buffer[RX_head++];
        RX_head %= RX_BUFFER_SIZE;
    }

    return count;
}

static void dropFrom(int bytesToDrop) {
    if (bytesToDrop <= 0)
        return;
    
    _U1RXIE = 0; /* disable UART Rx interrupt */
    RX_head = (RX_head + bytesToDrop) % RX_BUFFER_SIZE;
    
    if (RX_head > RX_next)
        RX_head = RX_next;
    
    _U1RXIE = 1; /* enable UART Rx interrupt */
}

static void flush(void) {
    RX_head = RX_next;
}

const Uart uart1 = {
    baudrate : setBaudRate,
    copy : copyFrom,
    drop : dropFrom,
    flush : flush,
    size : getRxSize,
    send : sendFrom,
    init : initUart,
    receive : receiveFrom
};
