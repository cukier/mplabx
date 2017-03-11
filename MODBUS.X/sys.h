#ifndef SYS_H
#define	SYS_H

#define USE_UART_1
#define USE_UART_2
#define USE_I2C_1
//#define MODBUS_UART_1
#define MODBUS_UART_2

#define FOSC                    (16000000ULL)
#define SERIAL_BUFFER_SIZE      256
#define FCY                     (FOSC/2)
#define BAUDRATE_1              (19200)
#define BAUDRATE_2              (9600)
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

