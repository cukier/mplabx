#pragma config BWRP = OFF
#pragma config BSS = DISABLED
#pragma config BSEN = OFF
#pragma config GWRP = OFF
#pragma config GSS = DISABLED
#pragma config CWRP = OFF
#pragma config CSS = DISABLED
#pragma config AIVTDIS = OFF
#pragma config BSLIM = 0x1FFF
#pragma config FNOSC = PRI
#pragma config PLLMODE = DISABLED
#pragma config IESO = ON
#pragma config POSCMD = HS
#pragma config OSCIOFCN = OFF
#pragma config SOSCSEL = ON
#pragma config PLLSS = PLL_PRI
#pragma config IOL1WAY = ON
#pragma config FCKSM = CSDCMD
#pragma config WDTPS = PS32768
#pragma config FWPSA = PR128
#pragma config FWDTEN = ON
#pragma config WINDIS = OFF
#pragma config WDTWIN = WIN25
#pragma config WDTCMX = WDTCLK
#pragma config WDTCLK = LPRC
#pragma config BOREN = ON
#pragma config LPCFG = OFF
#pragma config DNVPEN = ENABLE
#pragma config ICS = PGD1
#pragma config JTAGEN = OFF
#pragma config BTSWP = OFF
#pragma config ALTCMPI = DISABLE
#pragma config TMPRPIN = OFF
#pragma config SOSCHP = ON
#pragma config ALTVREF = ALTREFEN

#include <xc.h>
#include <p24FJ1024GB606.h>
#include <stdint.h>

#define FOSC    (16000000ULL)
#define FCY     (FOSC/2)

#include <libpic30.h>


int main(void) {
    TRISE = 0;
    
    while (1) {        
        LATE = 0;
        __delay_ms(10);
        LATE = 32;
        __delay_ms(5);
    }
    
    return 0;
}
