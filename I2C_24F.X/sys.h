#ifndef SYS_H
#define	SYS_H

#define USE_I2C_1

#define FOSC                    (16000000ULL)
#define FCY                     (FOSC/2)
#define FSCK_1                  (100000)

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

