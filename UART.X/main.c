/*
 * File:   main.c
 * Author: cuki
 *
 * Created on 25 de Agosto de 2017, 13:25
 */



#include "fuses.h"
#include "serial.h"

#include <libpic30.h>
#include <string.h>
#define DELA 0xFFFF

int main(void) {
    char str[] = "Hello\n";
    
    uart_init();
    
    while(1)
    {
        uart1_send((uint8_t *) str, strlen(str));        
        __delay_ms(500);
    }
    
    return 0;
}
