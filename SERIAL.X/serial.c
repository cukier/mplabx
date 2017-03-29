#include "serial.h"
#include "sys.h"
#include <libpic30.h>

#define RX_BUFFER_SIZE    0x0800
#define TX_BUFFER_SIZE    0x0040

uint16_t rx_head_1, rx_next_1, tx_head_1, tx_next_1;
uint8_t rx_buffer_1[RX_BUFFER_SIZE], tx_buffer_1[RX_BUFFER_SIZE];
//uint16_t rx_head_2, rx_next_2, tx_head_2, tx_next_2;
//uint8_t rx_buffer_2[RX_BUFFER_SIZE], tx_buffer_2[RX_BUFFER_SIZE];
//uint16_t rx_head_3, rx_next_3, tx_head_3, tx_next_3;
//uint8_t rx_buffer_3[RX_BUFFER_SIZE], tx_buffer_3[RX_BUFFER_SIZE];

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    while(U1STAbits.URXDA) { // while data is available    
        rx_buffer_1[rx_next_1++] = U1RXREG; // copy byte to buffer
        rx_next_1 %= RX_BUFFER_SIZE; // protect against rollover

        /* accommodate overflow */
        if(rx_head_1 == rx_next_1)
            rx_head_1 = (rx_head_1 + 1) % RX_BUFFER_SIZE;
    }

    _U1RXIF = 0; // clear Rx interrupt flag
}

void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt (void) {
    _U1TXIF = 0; // clear Tx interrupt flag

    /* transmit if transmit queue has room and buffer is not empty */
    while (!(U1STAbits.UTXBF) && (tx_head_1 != tx_next_1))
    {
        U1TXREG = tx_buffer_1[tx_head_1++];
        tx_head_1 %= TX_BUFFER_SIZE;
    }
}

void uart_init(void) {
    rx_head_1 = 0;
    rx_next_1 = 0;
    tx_head_1 = 0;
    tx_next_1 = 0;

    _U1RXIE = 0; // disable UART Rx interrupt
    _U1TXIE = 0; // disable UART Tx interrupt

    U1MODEbits.UARTEN = 0; // disable the UART module while configuring
    U1MODE = 0;
    U1MODEbits.BRGH = 1; // high speed baud rate
    U1STA = 0;
    U1STAbits.UTXISEL1 = 1; // interrupt when Tx buffer is empty
    U1STAbits.UTXEN = 1; // enable UART transmitter
    U1STAbits.URXEN = 1;

    U1BRG = ((FCY / 9600) / 4) - 1;

    _TRISD8 = 0; // TX -> output
    _TRISD1 = 1; // RX -> input

    __builtin_write_OSCCONL(OSCCON & 0xBF); // unlock peripheral pin select registers
    _RP2R = 3; // UART1 transmit
    _U1RXR = 24; // UART1 receive
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock peripheral pin select registers
    
    _U1RXIF = 0; // clear Rx interrupt flag
    _U1TXIF = 0; // clear Tx interrupt flag
    
    U1MODEbits.UARTEN = 1; // enable the UART module now that its configured
    
    /* Note: UART Tx cannot be enabled until the UART module itself has been enabled. */
    U1STAbits.UTXEN = 1; // enable UART transmitter
    U1STAbits.URXEN = 1;
    
    _U1RXIE = 1; // enable UART Rx interrupt

    return;
}

uint16_t getTxSpace(void) {
    return  tx_head_1 - tx_next_1 - 1
            + (tx_head_1 <= tx_next_1 ? TX_BUFFER_SIZE: 0);
}

bool uart1_send(uint8_t *data, uint16_t size) {
    /* can't send nonexistent data or no data */
    if (!data || !size)
        return false;
    
    /* make sure room is available in buffer */
    while(getTxSpace() < size);
    
     /* send bytes while bytes still need to be sent */
    while(size--) {
        tx_buffer_1[tx_next_1++] = *data;

        /* circular queue rollover protection */
        tx_next_1 %= TX_BUFFER_SIZE;

        /* accommodate overflow */
        if(tx_head_1 == tx_next_1)
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