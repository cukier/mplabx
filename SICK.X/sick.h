#ifndef SICK_H
#define	SICK_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "sys.h"

#if !defined ENCODER_USE_UART1 & !defined ENCODER_USE_UART2
#error Necessario definir ENCODER_USE_UART1 ou ENCODER_USE_UART1
#endif

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    void DSF60_disable_encoder(void);
    void DSF60_enable_encoder(void);
    bool DSF60_init_encoder(void);
    void DSF60_read_position(void);
    bool DSF60_check(void);
    uint32_t DSF60_get_position(void);
    uint32_t DSF60_get_resolution(void);
    char *DSF60_get_partNumber(void);
    char *DSF60_get_encoderType(void);
    char *DSF60_get_dateCode(void);    

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

