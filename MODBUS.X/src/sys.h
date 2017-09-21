#ifndef SYS_H
#define	SYS_H

#define FOSC                    (16000000ULL)
#define FCY                     (FOSC/2)
#define BAUDRATE_1              (9600)
#define BAUDRATE_2              (19200)
#define BAUDRATE_3              (19200)
#define BAUDRATE_4              (115200)
#define FSCK_1                  (100000)
#define SLV_ADDR_1              (1)
#define SLV_ADDR_2              (1)

#include <stdint.h>
#include <stdbool.h>

bool sys_init(void);
void sys_pooling(void);
uint8_t make8(uint64_t val, uint8_t index);
uint32_t make32(uint8_t hh, uint8_t hl, uint8_t lh, uint8_t ll);
uint16_t make16(uint8_t h, uint8_t l);

#endif

