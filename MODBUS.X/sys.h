#ifndef SYS_H
#define	SYS_H

#define FOSC                    (16000000ULL)
#define FCY                     (FOSC/2)
#define BAUDRATE_1              (19200)
#define BAUDRATE_2              (9600)
#define BAUDRATE_3              (19200)
#define FSCK_1                  (100000)
#define MODBUS_SLV_ADDR         (2)

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

