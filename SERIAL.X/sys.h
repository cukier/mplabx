#ifndef SYS_H
#define	SYS_H

#define FOSC                    (16000000ULL)
#define SERIAL_BUFFER_SIZE      256
#define FCY                     (FOSC/2)
#define BAUDRATE                (9600)
#define BRGVAL                  (((FCY/BAUDRATE)/16)-1)

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

