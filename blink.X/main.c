#include <18F45K22.h>

#fuses  mclr, primary_on, intrc, nopllen, nowdt
#use delay(internal=16MHz)

int main(void) {
    
    while(TRUE) {
        output_toggle(PIN_C0);
        delay_ms(1000);
    }
    
    return 0;
}



//#include<p18f45k20.h>
//#include<delays.h>
//
//#pragma config FOSC = INTIO67, FCMEN = OFF, IESO = OFF
//#pragma config PWRT = OFF, BOREN = SBORDIS, BORV = 30
//#pragma config WDTEN = OFF, WDTPS = 32768
//#pragma config MCLRE = OFF, LPT1OSC = OFF, PBADEN = ON, CCP2MX = PORTC
//#pragma config STVREN = ON, LVP = OFF, XINST = OFF
//#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF
//#pragma config CPB = OFF, CPD = OFF
//#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF
//#pragma config WRTB = OFF, WRTC = OFF, WRTD = OFF
//#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF
//#pragma config EBTRB = OFF
//
//static unsigned char cont = 7;
//
//void run_setup(void) {
//    TRISD = 0;
//    PORTD = 0;
//}
//
//void run(void) {
//    PORTD = cont;
//    cont <<= 1;
//    if (cont == 0xC0 || cont == 0x82 || cont == 0x06)
//        cont++;
//}
//
//void main(void) {
//    run_setup();
//    while (1) {
//        run();
//        Delay1KTCYx(5);
//    }
//}