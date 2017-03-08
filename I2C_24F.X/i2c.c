/*
 * File:   i2c.c
 * Author: cuki
 *
 * Created on 8 de Março de 2017, 12:15
 */

#include "i2c.h"
#include <libpic30.h>
#include <stdio.h>

i2c_t i2c1;

void I2C1_envia_stop(void) {
    if (I2C1STATbits.ACKSTAT) { //nao houve ack
        i2c1.slv_ack = false;
        I2C1STATbits.ACKSTAT = 0;
    } else {
        i2c1.slv_ack = true;
    }

    I2C1CONLbits.PEN = 1;
    i2c1.estado = ENVIA_START;
    i2c1.snd = false;
    i2c1.done = true;
#ifdef DOUBLE_WORD_ADDRESS
    i2c1.mem_h_send = true;
#endif
    return;
}

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void) {
    IFS1bits.MI2C1IF = 0;

    if (I2C1STATbits.IWCOL) {
        I2C1STATbits.IWCOL = 0;
        i2c1.estado = ENVIA_START;
        i2c1.snd = false;
        i2c1.done = true;
#ifdef DOUBLE_WORD_ADDRESS
        i2c1.mem_h_send = true;
#endif
        return;
    }

    switch (i2c1.estado) {
        case ENVIA_START:
            if (i2c1.snd) {
                I2C1CONLbits.SEN = 1;
                i2c1.done = false;

                switch (i2c1.comando) {
                    case ESCREVE:
                    case LER_ACK:
                    case LER:
                        i2c1.estado = EVNIA_ENDERECO_SLV;
                        break;

                    default:
                    case IDDLE:
                        I2C1_envia_stop();
                        break;
                }
            }

            break;

        case EVNIA_ENDERECO_SLV:
            I2C1TRN = i2c1.slv_addr;

            switch (i2c1.comando) {
                case LER_ACK:
                    i2c1.estado = ENVIA_STOP;
                    break;

                case LER:
                case ESCREVE:
                    if (i2c1.slv_addr & 1) {
                        i2c1.estado = S_MASTER_ACK_ADDR;
                    } else {
                        i2c1.estado = ENVIA_ENDERECO_MEM;
                    }

#ifdef DOUBLE_WORD_ADDRESS
                    i2c1.mem_h_send = true;
#endif
                    break;

                default:
                case IDDLE:
                    I2C1_envia_stop();
                    break;
            }

            break;

        case ENVIA_ENDERECO_MEM:
            if (I2C1STATbits.ACKSTAT) {
                I2C1_envia_stop();
            } else {
#ifdef DOUBLE_WORD_ADDRESS
                if (i2c1.mem_h_send) {
                    i2c1.mem_h_send = false;
                    I2C1TRN = (i2c1.mem_addr & 0xFF00) >> 8;
                } else {
                    I2C1TRN = i2c1.mem_addr & 0xFF;

                    switch (i2c1.comando) {
                        case ESCREVE:
                            i2c1.estado = ENVIA_DATA;
                            i2c1.count = 0;
                            break;
                        case LER:
                            i2c1.estado = ENVIA_START_REPETIDO;
                            break;
                        default:
                        case IDDLE:
                        case LER_ACK:
                            I2C1_envia_stop();
                            break;
                    }
                }
#else
                I2C1TRN = i2c1.mem_addr;

                switch (i2c1.comando) {
                    case ESCREVE:
                        i2c1.estado = ENVIA_DATA;
                        i2c1.count = 0;
                        break;
                    case LER:
                        i2c1.estado = ENVIA_START_REPETIDO;
                        break;
                    default:
                    case IDDLE:
                    case LER_ACK:
                        I2C1_envia_stop();
                        break;
                }
#endif
            }

            break;

        case ENVIA_DATA:
            if (I2C1STATbits.ACKSTAT) {
                I2C1_envia_stop();
            } else {
                if (i2c1.count < i2c1.buffer_size) {
                    I2C1TRN = i2c1.buffer[i2c1.count];
                    i2c1.count++;

                    if (i2c1.count >= i2c1.buffer_size) {
                        i2c1.count = 0;
                        i2c1.estado = ENVIA_STOP;
                    }
                }
            }

            break;

        default:
        case ENVIA_STOP:
            I2C1_envia_stop();
            break;

        case ENVIA_START_REPETIDO:
            if (I2C1STATbits.ACKSTAT) { //nao houve ack
                I2C1_envia_stop();
            } else {
                I2C1CONLbits.SEN = 1;
                i2c1.slv_addr++;
                i2c1.estado = EVNIA_ENDERECO_SLV;
            }

            break;

        case MESTRE_RECEBE:
            i2c1.buffer[i2c1.count] = I2C1RCV;

            if (i2c1.count < (i2c1.buffer_size - 1)) {
                I2C1CONLbits.ACKDT = 0;
                i2c1.estado = S_MASTER_RCV_DATA;
            } else {
                I2C1CONLbits.ACKDT = 1;
                i2c1.estado = ENVIA_STOP;
            }

            I2C1CONLbits.ACKEN = 1;
            i2c1.count++;
            break;

        case S_MASTER_ACK_ADDR:
            if (I2C1STATbits.ACKSTAT) { //nao houve ack
                I2C1_envia_stop();
            } else {
                I2C1CONLbits.RCEN = 1;
                i2c1.estado = MESTRE_RECEBE;
                i2c1.count = 0;
            }

            break;

        case S_MASTER_RCV_DATA:
            I2C1CONLbits.RCEN = 1;
            i2c1.estado = MESTRE_RECEBE;
            break;
    }
}

void I2C1_Initialize(void) {
    i2c1.comando = IDDLE;
    i2c1.done = false;
    i2c1.estado = ENVIA_START;
    i2c1.mem_addr = 0;
#ifdef DOUBLE_WORD_ADDRESS    
    i2c1.mem_h_send = true;
#endif    
    i2c1.slv_ack = false;
    i2c1.slv_addr = 0;
    i2c1.snd = false;
    i2c1.buffer = NULL;
    i2c1.count = 0;
    i2c1.buffer_size = 0;

    // initialize the hardware
    I2C1BRG = I2C_BRG;
    // ACKEN disabled; STRICT disabled; STREN disabled; GCEN disabled; SMEN disabled; DISSLW disabled; I2CSIDL disabled; ACKDT Sends ACK; SCLREL Holds; RSEN disabled; A10M 7 Bit; PEN disabled; RCEN disabled; SEN disabled; I2CEN enabled; 
    I2C1CONL = 0x8200;
    // BCL disabled; D_nA disabled; R_nW disabled; P disabled; S disabled; I2COV disabled; IWCOL disabled; 
    I2C1STAT = 0x0000;

    /* MI2C1 - I2C1 Master Events */
    // clear the master interrupt flag
    IFS1bits.MI2C1IF = 0;
    // enable the master interrupt
    IEC1bits.MI2C1IE = 1;
}

void I2C1_send(void) {
    i2c1.snd = true;
    IFS1bits.MI2C1IF = 1;
    i2c1.done = false;
}

bool I2C1_get_ack(uint8_t addr) {
    i2c1.comando = LER_ACK;
    i2c1.slv_addr = addr;
    i2c1.mem_addr = 0;
    i2c1.buffer = NULL;
    i2c1.buffer_size = 1;
    I2C1_send();

    while (!i2c1.done)
        ;

    __delay_us(100);
    return i2c1.slv_ack;
}

#ifdef DOUBLE_WORD_ADDRESS

bool I2C1_send_data(uint8_t addr, uint16_t mem, uint8_t *data, uint16_t length) {
#else

bool I2C1_send_data(uint8_t addr, uint8_t mem, uint8_t *data, uint16_t length) {
#endif    
    i2c1.comando = ESCREVE;
    i2c1.slv_addr = addr;
    i2c1.mem_addr = mem;
    i2c1.buffer = data;
    i2c1.buffer_size = length;
    I2C1_send();

    while (!i2c1.done)
        ;

    __delay_us(100);
    return i2c1.slv_ack;
}

#ifdef DOUBLE_WORD_ADDRESS

bool I2C1_get_data(uint8_t addr, uint16_t mem, uint8_t *data, uint16_t length) {
#else

bool I2C1_get_data(uint8_t addr, uint8_t mem, uint8_t *data, uint16_t length) {
#endif    
    i2c1.comando = LER;
    i2c1.slv_addr = addr;
    i2c1.mem_addr = mem;
    i2c1.buffer = data;
    i2c1.buffer_size = length;
    I2C1_send();

    while (!i2c1.done)
        ;

    __delay_us(100);
    return i2c1.slv_ack;
}
