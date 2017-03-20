#ifndef SYS_H
#define	SYS_H

#define FOSC                    (32000000ULL)
#define SERIAL1_BUFFER_SIZE     (256)
#define SERIAL2_BUFFER_SIZE     (60)
#define FCY                     (FOSC/2)
#define BAUDRATE_1              (9600)
#define BAUDRATE_2              (115200)
#define FSCK_1                  (100000)
#define SLV_ADDR_1              (1)
#define SLV_ADDR_2              (1)

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

