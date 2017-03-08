/*
 * File:   main.c
 * Author: cuki
 *
 * Created on 2 de Março de 2017, 13:51
 */
// FSEC
#pragma config BWRP = OFF               // Boot Segment Write-Protect bit (Boot Segment may be written)
#pragma config BSS = DISABLED           // Boot Segment Code-Protect Level bits (No Protection (other than BWRP))
#pragma config BSEN = OFF               // Boot Segment Control bit (No Boot Segment)
#pragma config GWRP = OFF               // General Segment Write-Protect bit (General Segment may be written)
#pragma config GSS = DISABLED           // General Segment Code-Protect Level bits (No Protection (other than GWRP))
#pragma config CWRP = OFF               // Configuration Segment Write-Protect bit (Configuration Segment may be written)
#pragma config CSS = DISABLED           // Configuration Segment Code-Protect Level bits (No Protection (other than CWRP))
#pragma config AIVTDIS = OFF            // Alternate Interrupt Vector Table bit (Disabled AIVT)

// FBSLIM
#pragma config BSLIM = 0x1FFF           // Boot Segment Flash Page Address Limit bits (Boot Segment Flash page address  limit)

// FSIGN

// FOSCSEL
#pragma config FNOSC = PRI              // Oscillator Source Selection (Primary Oscillator (XT, HS, EC))
#pragma config PLLMODE = DISABLED       // PLL Mode Selection (No PLL used; PLLEN bit is not available)
#pragma config IESO = OFF               // Two-speed Oscillator Start-up Enable bit (Start up with user-selected oscillator source)

// FOSC
#pragma config POSCMD = HS              // Primary Oscillator Mode Select bits (HS Crystal Oscillator Mode)
#pragma config OSCIOFCN = ON            // OSC2 Pin Function bit (OSC2 is general purpose digital I/O pin)
#pragma config SOSCSEL = ON             // SOSC Power Selection Configuration bits (SOSC is used in crystal (SOSCI/SOSCO) mode)
#pragma config PLLSS = PLL_PRI          // PLL Secondary Selection Configuration bit (PLL is fed by the Primary oscillator)
#pragma config IOL1WAY = ON             // Peripheral pin select configuration bit (Allow only one reconfiguration)
#pragma config FCKSM = CSDCMD           // Clock Switching Mode bits (Both Clock switching and Fail-safe Clock Monitor are disabled)

// FWDT
#pragma config WDTPS = PS32768          // Watchdog Timer Postscaler bits (1:32,768)
#pragma config FWPSA = PR128            // Watchdog Timer Prescaler bit (1:128)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bits (WDT and SWDTEN disabled)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable bit (Watchdog Timer in Non-Window mode)
#pragma config WDTWIN = WIN25           // Watchdog Timer Window Select bits (WDT Window is 25% of WDT period)
#pragma config WDTCMX = WDTCLK          // WDT MUX Source Select bits (WDT clock source is determined by the WDTCLK Configuration bits)
#pragma config WDTCLK = LPRC            // WDT Clock Source Select bits (WDT uses LPRC)

// FPOR
#pragma config BOREN = OFF              // Brown Out Enable bit (Brown Out Disabled)
#pragma config LPCFG = OFF              // Low power regulator control (No Retention Sleep)
#pragma config DNVPEN = ENABLE          // Downside Voltage Protection Enable bit (Downside protection enabled using ZPBOR when BOR is inactive)

// FICD
#pragma config ICS = PGD1               // ICD Communication Channel Select bits (Communicate on PGEC1 and PGED1)
#pragma config JTAGEN = OFF             // JTAG Enable bit (JTAG is disabled)
#pragma config BTSWP = OFF              // BOOTSWP Disable (BOOTSWP instruction disabled)

// FDEVOPT1
#pragma config ALTCMPI = DISABLE        // Alternate Comparator Input Enable bit (C1INC, C2INC, and C3INC are on their standard pin locations)
#pragma config TMPRPIN = OFF            // Tamper Pin Enable bit (TMPRN pin function is disabled)
#pragma config SOSCHP = OFF             // SOSC High Power Enable bit (valid only when SOSCSEL = 1 (Enable SOSC low power mode)
#pragma config ALTVREF = ALTREFEN       // Alternate Voltage Reference Location Enable bit (VREF+ and CVREF+ on RA10, VREF- and CVREF- on RA9)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define FOSC        (16000000ULL)
#define FCY         (FOSC/2)
#define FSCK        (100000)
#define I2C_BRG     ((FCY/2/FSCK)-1)
#define BAUDRATE    (9600)
#define BRGVAL      (((FCY/BAUDRATE)/16)-1)

//#define DOUBLE_WORD_ADDRESS
//#define TESTA_ENVIO
#define TESTA_RECEBIMENTO

#include <xc.h>
#include <libpic30.h>
#include <p24FJ1024GB606.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum i2c_estado_e {
    ENVIA_START,
    EVNIA_ENDERECO_SLV,
    ENVIA_ENDERECO_MEM,
    ENVIA_DATA,
    ENVIA_STOP,
    ENVIA_START_REPETIDO,
    MESTRE_RECEBE,
    S_MASTER_ACK_ADDR,
    S_MASTER_RCV_DATA
} i2c_state_t;

typedef enum i2c_comandos_e {
    IDDLE,
    LER_ACK,
    ESCREVE,
    LER
} i2c_comando_t;

typedef struct i2c_str {
    i2c_state_t estado;
    i2c_comando_t comando;
    uint8_t *buffer;
    uint8_t slv_addr;
#ifdef DOUBLE_WORD_ADDRESS
    uint16_t mem_addr;
    bool mem_h_send;
#else
    uint8_t mem_addr;
#endif    
    uint16_t buffer_size;
    uint16_t count;
    bool snd;
    bool slv_ack;
    bool done;
} i2c_t;

i2c_t i2c1;

#define EEPROM_ADDR			0xA0

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

int main(void) {
#ifdef TESTA_ENVIO
    uint8_t data[3] = {1, 2, 3};
#endif
#ifdef TESTA_RECEBIMENTO
    uint8_t rdata[64] = {0};
#endif

    I2C1_Initialize();
    __delay_ms(500);
    if (I2C1_get_ack(EEPROM_ADDR)) {
#ifdef TESTA_ENVIO
        I2C1_send_data(EEPROM_ADDR, 0x0010, data, sizeof (data));
        __delay_ms(10);
#endif
#ifdef TESTA_RECEBIMENTO
        I2C1_get_data(EEPROM_ADDR, 0x0010, rdata, sizeof (rdata));
#endif
    }

    Nop();

    while (1) {

    }

    return 0;
}
