#ifndef I2C_H
#define	I2C_H

#include "sys.h"

#ifdef FSCK_1
#define I2C_BRG     ((FCY/2/FSCK_1)-1)
#else
#error Definir FSCK_1
#endif

#define DOUBLE_WORD_ADDRESS

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    typedef enum i2c_estado_e {
        ENVIA_START,
        EVNIA_ENDERECO_SLV,
        ENVIA_ENDERECO_MEM,
        ENVIA_DATA,
        ENVIA_STOP,
        ENVIA_START_REPETIDO,
        MESTRE_RECEBE,
        S_MASTER_ACK_ADDR,
        S_MASTER_RCV_DATA
    } i2c_state_t;

    typedef enum i2c_comandos_e {
        IDDLE,
        LER_ACK,
        ESCREVE,
        LER
    } i2c_comando_t;

    typedef struct i2c_str {
        i2c_state_t estado;
        i2c_comando_t comando;
        uint8_t *buffer;
        uint8_t slv_addr;
#ifdef DOUBLE_WORD_ADDRESS
        uint16_t mem_addr;
        bool mem_h_send;
#else
        uint8_t mem_addr;
#endif    
        uint16_t buffer_size;
        uint16_t count;
        bool snd;
        bool slv_ack;
        bool done;
    } i2c_t;

#ifdef USE_I2C_1
    void I2C1_Initialize(void);
    bool I2C1_get_ack(uint8_t addr);
#ifdef DOUBLE_WORD_ADDRESS
    bool I2C1_send_data(uint8_t addr, uint16_t mem, uint8_t *data, uint16_t length);
    bool I2C1_get_data(uint8_t addr, uint16_t mem, uint8_t *data, uint16_t length);
#else
    bool I2C1_send_data(uint8_t addr, uint8_t mem, uint8_t *data, uint16_t length);
    bool I2C1_get_data(uint8_t addr, uint8_t mem, uint8_t *data, uint16_t length);
#endif   
#endif

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

