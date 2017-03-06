/*
 * File:   main.c
 * Author: cuki
 *
 * Created on 2 de Março de 2017, 13:51
 */
// FSEC
#pragma config BWRP = OFF    // Boot Segment Write-Protect bit->Boot Segment may be written
#pragma config BSS = DISABLED    // Boot Segment Code-Protect Level bits->No Protection (other than BWRP)
#pragma config BSEN = OFF    // Boot Segment Control bit->No Boot Segment
#pragma config GWRP = OFF    // General Segment Write-Protect bit->General Segment may be written
#pragma config GSS = DISABLED    // General Segment Code-Protect Level bits->No Protection (other than GWRP)
#pragma config CWRP = OFF    // Configuration Segment Write-Protect bit->Configuration Segment may be written
#pragma config CSS = DISABLED    // Configuration Segment Code-Protect Level bits->No Protection (other than CWRP)
#pragma config AIVTDIS = OFF    // Alternate Interrupt Vector Table bit->Disabled AIVT

// FOSCSEL
#pragma config FNOSC = PRI    // Oscillator Source Selection->Primary Oscillator (XT, HS, EC)
#pragma config PLLMODE = DISABLED    // PLL Mode Selection->No PLL used; PLLEN bit is not available
#pragma config IESO = ON    // Two-speed Oscillator Start-up Enable bit->Start up device with FRC, then switch to user-selected oscillator source

// FOSC
#pragma config POSCMD = HS    // Primary Oscillator Mode Select bits->HS Crystal Oscillator Mode
#pragma config OSCIOFCN = ON    // OSC2 Pin Function bit->OSC2 is general purpose digital I/O pin
#pragma config SOSCSEL = ON    // SOSC Power Selection Configuration bits->SOSC is used in crystal (SOSCI/SOSCO) mode
#pragma config PLLSS = PLL_PRI    // PLL Secondary Selection Configuration bit->PLL is fed by the Primary oscillator
#pragma config IOL1WAY = ON    // Peripheral pin select configuration bit->Allow only one reconfiguration
#pragma config FCKSM = CSDCMD    // Clock Switching Mode bits->Both Clock switching and Fail-safe Clock Monitor are disabled

// FWDT
#pragma config WDTPS = PS32768    // Watchdog Timer Postscaler bits->1:32768
#pragma config FWPSA = PR128    // Watchdog Timer Prescaler bit->1:128
#pragma config FWDTEN = OFF    // Watchdog Timer Enable bits->WDT and SWDTEN disabled
#pragma config WINDIS = OFF    // Watchdog Timer Window Enable bit->Watchdog Timer in Non-Window mode
#pragma config WDTWIN = WIN25    // Watchdog Timer Window Select bits->WDT Window is 25% of WDT period
#pragma config WDTCMX = WDTCLK    // WDT MUX Source Select bits->WDT clock source is determined by the WDTCLK Configuration bits
#pragma config WDTCLK = LPRC    // WDT Clock Source Select bits->WDT uses LPRC

// FPOR
#pragma config BOREN = ON    // Brown Out Enable bit->Brown Out Enable Bit
#pragma config LPCFG = OFF    // Low power regulator control->No Retention Sleep
#pragma config DNVPEN = ENABLE    // Downside Voltage Protection Enable bit->Downside protection enabled using ZPBOR when BOR is inactive

// FICD
#pragma config ICS = PGD1    // ICD Communication Channel Select bits->Communicate on PGEC1 and PGED1
#pragma config JTAGEN = OFF    // JTAG Enable bit->JTAG is disabled
#pragma config BTSWP = OFF    // BOOTSWP Disable->BOOTSWP instruction disabled

// FDEVOPT1
#pragma config ALTCMPI = DISABLE    // Alternate Comparator Input Enable bit->C1INC, C2INC, and C3INC are on their standard pin locations
#pragma config TMPRPIN = OFF    // Tamper Pin Enable bit->TMPRN pin function is disabled
#pragma config SOSCHP = ON    // SOSC High Power Enable bit (valid only when SOSCSEL = 1->Enable SOSC high power mode (default)
#pragma config ALTVREF = ALTREFEN    // Alternate Voltage Reference Location Enable bit->VREF+ and CVREF+ on RA10, VREF- and CVREF- on RA9

// FBOOT
#pragma config BTMODE = SINGLE    // Boot Mode Configuration bits->Device is in Single Boot (legacy) mode

#define FOSC        (16000000ULL)
#define FCY         (FOSC/2)
#define FSCK        (100000)
#define I2C_BRG     ((FCY/2/FSCK)-1)
#define BAUDRATE    (9600)
#define BRGVAL      (((FCY/BAUDRATE)/16)-1)

#include <xc.h>
#include <libpic30.h>
#include <p24FJ1024GB606.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

uint8_t cont, data, slv_addr;
bool snd = false;

void __attribute__((interrupt, no_auto_psv)) _MI2C1Interrupt(void) {

    IFS1bits.MI2C1IF = 0;
    
    if (I2C1STATbits.IWCOL) {
        I2C1STATbits.IWCOL = 0;
        cont = 0;
        
        return;
    }

    switch (cont) {
        case 0:
            if (snd) {
                I2C1CONLbits.SEN = 1;
                cont = 1;
            }
            
            break;
        case 1:
            I2C1TRN = slv_addr;
            cont = 2;
            break;
        case 2:
            I2C1TRN = data;
            cont = 3;
            break;
        default:
        case 3:
            I2C1CONLbits.PEN = 1;
            cont = 0;
            snd = false;
            break;
    }
}

void I2C1_Initialize(void) {

    // initialize the hardware
    I2C1BRG = 0x0026;
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

void OSCILLATOR_Initialize(void)
{
    // CF no clock failure; NOSC PRI; SOSCEN disabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONL((uint8_t) (0x0200 & 0x00FF));
    // CPDIV 1:1; PLLEN disabled; DOZE 1:8; RCDIV PRI; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x3200;
    // STOR disabled; STORPOL Interrupt when STOR is 1; STSIDL disabled; STLPOL Interrupt when STLOCK is 1; STLOCK disabled; STSRC SOSC; STEN disabled; TUN Center frequency; 
    OSCTUN = 0x0000;
    // ROEN disabled; ROSEL FOSC; ROSIDL disabled; ROSWEN disabled; ROOUT disabled; ROSLP disabled; 
    REFOCONL = 0x0000;
    // RODIV 0; 
    REFOCONH = 0x0000;
    // ROTRIM 0; 
    REFOTRIML = 0x0000;
    // DCOTUN 0; 
    DCOTUN = 0x0000;
    // DCOFSEL 8; DCOEN disabled; 
    DCOCON = 0x0700;
    // DIV 0; 
    OSCDIV = 0x0000;
    // TRIM 0; 
    OSCFDIV = 0x0000;
    // WDTO disabled; TRAPR disabled; SLEEP disabled; BOR disabled; CM disabled; SWR disabled; SWDTEN disabled; EXTR disabled; POR disabled; SBOREN disabled; IDLE disabled; IOPUWR disabled; VREGS disabled; 
    RCON = 0x0000;
}

int main(void) {
    
    LATD = 0x0000;
    TRISD = 0x0FFF;
    IOCPDD = 0x0000;
    IOCPUD = 0x0000;
    ODCD = 0x0000;
    ANSD = 0x00C0;

    IPC4bits.MI2C1IP = 1;
    IPC4bits.SI2C1IP = 1;
    
    OSCILLATOR_Initialize();
    I2C1_Initialize();
    __delay_ms(500);

//    while (1) {        
        cont = 0;
        data = 0x10;
        slv_addr = 0x20;
        snd = true;
        IFS1bits.MI2C1IF = 1;
        __delay_ms(3000);
//    }
        
        while (1)
        {}

    return 0;
}
