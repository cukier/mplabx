#include "fuses.h"

#define FCY 16000000UL

#include <libpic30.h>

int main(void) {
    _TRISE4 = 0;
        
    while (1) {        
        _LATE4 = !_LATE4;
        __delay_ms(1000);
        //_LATE4 = 0;
        //__delay_ms(1000);
    }
    
    return 0;
}
