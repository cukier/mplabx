/*
 * File:   teste.c
 * Author: cuki
 *
 * Created on February 28, 2013, 7:29 AM
 */

#include <p18cxxx.h>

void main(void) {
    unsigned char a = 0x04;
    unsigned char b = a;
    unsigned char c = a;
    a = ~a;
    a &= 0x0F;
    b = ~b & 0x0F;
    return;
}
