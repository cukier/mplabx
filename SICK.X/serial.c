#include "serial.h"
#include "sys.h"
#include <libpic30.h>

#define RX_BUFFER_SIZE    0x012C
#define TX_BUFFER_SIZE    0x012C

#ifdef USE_UART_1
uint16_t rx_head_1, rx_next_1, tx_head_1, tx_next_1;
uint8_t rx_buffer_1[RX_BUFFER_SIZE], tx_buffer_1[RX_BUFFER_SIZE];
#endif
#ifdef USE_UART_2
uint16_t rx_head_2, rx_next_2, tx_head_2, tx_next_2;
uint8_t rx_buffer_2[RX_BUFFER_SIZE], tx_buffer_2[RX_BUFFER_SIZE];
#endif
#ifdef USE_UART_3
uint16_t rx_head_3, rx_next_3, tx_head_3, tx_next_3;
uint8_t rx_buffer_3[RX_BUFFER_SIZE], tx_buffer_3[RX_BUFFER_SIZE];
#endif

void uart_init(void) {
#ifdef USE_UART_1
    rx_head_1 = 0;
    rx_next_1 = 0;
    tx_head_1 = 0;
    tx_next_1 = 0;

    _U1RXIE = 0; // disable UART1 Rx interrupt
    _U1TXIE = 0; // disable UART1 Tx interrupt

    U1MODE = 0;
    U1MODEbits.BRGH = 1; // high speed baud rate
#ifdef ENCODER_USE_UART1
    U1MODEbits.PDSEL = 1; //8-bit data even parity
#endif
    U1STA = 0;
    U1STAbits.UTXISEL1 = 1; // interrupt when Tx buffer is empty
    U1STAbits.UTXEN = 1; // enable UART transmitter
    U1STAbits.URXEN = 1;

    U1BRG = ((FCY / BAUDRATE_1) / 4) - 1;

    _TRISD8 = 0; // TX1 -> output
    _TRISD1 = 1; // RX1 -> input
#endif
#ifdef USE_UART_2    
    rx_head_2 = 0;
    rx_next_2 = 0;
    tx_head_2 = 0;
    tx_next_2 = 0;

    _U2RXIE = 0; // disable UART2 Rx interrupt
    _U2TXIE = 0; // disable UART2 Tx interrupt

    U2MODEbits.UARTEN = 0; // disable the UART module while configuring
    U2MODE = 0;
    U2MODEbits.BRGH = 1; // high speed baud rate
#ifdef ENCODER_USE_UART2
    U2MODEbits.PDSEL = 1; //8-bit data even parity
#endif
    U2STA = 0;
    U2STAbits.UTXISEL1 = 1; // interrupt when Tx buffer is empty
    U2STAbits.UTXEN = 1; // enable UART transmitter
    U2STAbits.URXEN = 1;

    U2BRG = ((FCY / BAUDRATE_2) / 4) - 1;

    _TRISD2 = 0; // TX2 -> output
    _TRISD3 = 1; // RX2 -> input
#endif
#ifdef USE_UART_3    
    rx_head_3 = 0;
    rx_next_3 = 0;
    tx_head_3 = 0;
    tx_next_3 = 0;

    _U3RXIE = 0; // disable UART3 Rx interrupt
    _U3TXIE = 0; // disable UART3 Tx interrupt = 0; // disable the UART module while configuring

    U3MODEbits.UARTEN = 0; // disable the UART module while configuring
    U3MODE = 0;
    U3MODEbits.BRGH = 1; // high speed baud rate
#ifdef ENCODER_USE_UART3
    U3MODEbits.PDSEL = 1; //8-bit data even parity
#endif
    U3STA = 0;
    U3STAbits.UTXISEL1 = 1; // interrupt when Tx buffer is empty
    U3STAbits.UTXEN = 1; // enable UART transmitter
    U3STAbits.URXEN = 1;

    U3BRG = ((FCY / BAUDRATE_3) / 4) - 1;

    _TRISD11 = 0; // TX3 -> output
    _TRISD0 = 1; // RX3 -> input
#endif

    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock peripheral pin select registers
#ifdef USE_UART_1
    _RP2R = 3; // UART1 transmit
    _U1RXR = 24; // UART1 receive
#endif
#ifdef USE_UART_2    
    _RP23R = 5; // UART2 transmit
    _U2RXR = 22; // UART2 receive    
#endif
#ifdef USE_UART_3    
    _RP12R = 19; // UART3 transmit
    _U3RXR = 11; // UART2 receive
#endif    
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock peripheral pin select registers

#ifdef USE_UART_1    
    _U1RXIF = 0; // clear Rx interrupt flag
    _U1TXIF = 0; // clear Tx interrupt flag

    U1MODEbits.UARTEN = 1; // enable the UART module now that its configured    

    U1STAbits.UTXEN = 1; // enable UART transmitter
    U1STAbits.URXEN = 1;
    _U1RXIE = 1; // enable UART Rx interrupt
#endif    
#ifdef USE_UART_2    
    _U2RXIF = 0; // clear Rx interrupt flag
    _U2TXIF = 0; // clear Tx interrupt flag

    U2MODEbits.UARTEN = 1; // enable the UART module now that its configured

    U2STAbits.UTXEN = 1; // enable UART transmitter
    U2STAbits.URXEN = 1;
    _U2RXIE = 1; // enable UART Rx interrupt
#endif    
#ifdef USE_UART_3    
    _U3RXIF = 0; // clear Rx interrupt flag
    _U3TXIF = 0; // clear Tx interrupt flag

    U3MODEbits.UARTEN = 1; // enable the UART module now that its configured

    U3STAbits.UTXEN = 1; // enable UART transmitter
    U3STAbits.URXEN = 1;
    _U3RXIE = 1; // enable UART Rx interrupt
#endif
    return;
}

#ifdef USE_UART_1

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    while (U1STAbits.URXDA) { // while data is available    
        rx_buffer_1[rx_next_1++] = U1RXREG; // copy byte to buffer
        rx_next_1 %= RX_BUFFER_SIZE; // protect against rollover

        /* accommodate overflow */
        if (rx_head_1 == rx_next_1)
            rx_head_1 = (rx_head_1 + 1) % RX_BUFFER_SIZE;
    }

    _U1RXIF = 0; // clear Rx interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
    _U1TXIF = 0; // clear Tx interrupt flag

    /* transmit if transmit queue has room and buffer is not empty */
    while (!(U1STAbits.UTXBF) && (tx_head_1 != tx_next_1)) {
        U1TXREG = tx_buffer_1[tx_head_1++];
        tx_head_1 %= TX_BUFFER_SIZE;
    }
}

uint16_t getTxSpace_1(void) {
    return tx_head_1 - tx_next_1 - 1
            + (tx_head_1 <= tx_next_1 ? TX_BUFFER_SIZE : 0);
}

bool uart1_send(uint8_t *data, uint16_t size) {
    /* can't send nonexistent data or no data */
    if (!data || !size)
        return false;

    /* make sure room is available in buffer */
    while (getTxSpace_1() < size);

    /* send bytes while bytes still need to be sent */
    while (size--) {
        tx_buffer_1[tx_next_1++] = *data;

        /* circular queue rollover protection */
        tx_next_1 %= TX_BUFFER_SIZE;

        /* accommodate overflow */
        if (tx_head_1 == tx_next_1)
            tx_head_1 = (tx_head_1 + 1) % TX_BUFFER_SIZE;

        ++data;
    }

    _U1TXIE = 1;
    _U1TXIF = 1;

    return true;
}

uint16_t uart1_get(uint8_t *data, uint16_t size) {
    uint16_t count = 0;

    if (!data)
        return false;

    _U1RXIE = 0;

    while (size-- && (rx_head_1 != rx_next_1)) {
        data[count++] = rx_buffer_1[rx_head_1++];
        rx_head_1 %= RX_BUFFER_SIZE;
    }

    _U1RXIE = 1;

    return count;
}
#endif

#ifdef USE_UART_2

void __attribute__((interrupt, no_auto_psv)) _U2RXInterrupt(void) {
    while (U2STAbits.URXDA) { // while data is available    
        rx_buffer_2[rx_next_2++] = U2RXREG; // copy byte to buffer
        rx_next_2 %= RX_BUFFER_SIZE; // protect against rollover

        /* accommodate overflow */
        if (rx_head_2 == rx_next_2)
            rx_head_2 = (rx_head_2 + 1) % RX_BUFFER_SIZE;
    }

    _U2RXIF = 0; // clear Rx interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _U2TXInterrupt(void) {
    _U2TXIF = 0; // clear Tx interrupt flag

    /* transmit if transmit queue has room and buffer is not empty */
    while (!(U2STAbits.UTXBF) && (tx_head_2 != tx_next_2)) {
        U2TXREG = tx_buffer_2[tx_head_2++];
        tx_head_2 %= TX_BUFFER_SIZE;
    }
}

uint16_t getTxSpace_2(void) {
    return tx_head_2 - tx_next_2 - 1
            + (tx_head_2 <= tx_next_2 ? TX_BUFFER_SIZE : 0);
}

bool uart2_send(uint8_t *data, uint16_t size) {
    /* can't send nonexistent data or no data */
    if (!data || !size)
        return false;

    /* make sure room is available in buffer */
    while (getTxSpace_2() < size);

    /* send bytes while bytes still need to be sent */
    while (size--) {
        tx_buffer_2[tx_next_2++] = *data;

        /* circular queue rollover protection */
        tx_next_2 %= TX_BUFFER_SIZE;

        /* accommodate overflow */
        if (tx_head_2 == tx_next_2)
            tx_head_2 = (tx_head_2 + 1) % TX_BUFFER_SIZE;

        ++data;
    }

    _U2TXIE = 1;
    _U2TXIF = 1;

    return true;
}

uint16_t uart2_get(uint8_t *data, uint16_t size) {
    uint16_t count = 0;

    if (!data)
        return false;

    _U2RXIE = 0;

    while (size-- && (rx_head_2 != rx_next_2)) {
        data[count++] = rx_buffer_2[rx_head_2++];
        rx_head_2 %= RX_BUFFER_SIZE;
    }

    _U2RXIE = 1;

    return count;
}
#endif

#ifdef USE_UART_3

void __attribute__((interrupt, no_auto_psv)) _U3RXInterrupt(void) {
    while (U3STAbits.URXDA) { // while data is available    
        rx_buffer_3[rx_next_3++] = U3RXREG; // copy byte to buffer
        rx_next_3 %= RX_BUFFER_SIZE; // protect against rollover

        /* accommodate overflow */
        if (rx_head_3 == rx_next_3)
            rx_head_3 = (rx_head_3 + 1) % RX_BUFFER_SIZE;
    }

    _U3RXIF = 0; // clear Rx interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _U3TXInterrupt(void) {
    _U3TXIF = 0; // clear Tx interrupt flag

    /* transmit if transmit queue has room and buffer is not empty */
    while (!(U3STAbits.UTXBF) && (tx_head_3 != tx_next_3)) {
        U3TXREG = tx_buffer_3[tx_head_3++];
        tx_head_3 %= TX_BUFFER_SIZE;
    }
}

uint16_t getTxSpace_3(void) {
    return tx_head_3 - tx_next_3 - 1
            + (tx_head_3 <= tx_next_3 ? TX_BUFFER_SIZE : 0);
}

bool uart3_send(uint8_t *data, uint16_t size) {
    /* can't send nonexistent data or no data */
    if (!data || !size)
        return false;

    /* make sure room is available in buffer */
    while (getTxSpace_3() < size);

    /* send bytes while bytes still need to be sent */
    while (size--) {
        tx_buffer_3[tx_next_3++] = *data;

        /* circular queue rollover protection */
        tx_next_3 %= TX_BUFFER_SIZE;

        /* accommodate overflow */
        if (tx_head_3 == tx_next_3)
            tx_head_3 = (tx_head_3 + 1) % TX_BUFFER_SIZE;

        ++data;
    }

    _U3TXIE = 1;
    _U3TXIF = 1;

    return true;
}

uint16_t uart3_get(uint8_t *data, uint16_t size) {
    uint16_t count = 0;

    if (!data)
        return false;

    _U3RXIE = 0;

    while (size-- && (rx_head_3 != rx_next_3)) {
        data[count++] = rx_buffer_3[rx_head_3++];
        rx_head_3 %= RX_BUFFER_SIZE;
    }

    _U3RXIE = 1;

    return count;
}

uint16_t uart3_getRxSize(void) {
    return rx_next_3 - rx_head_3
            + (rx_head_3 > rx_next_3 ? RX_BUFFER_SIZE : 0);
}
#endif

