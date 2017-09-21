/*
 * pivo_mem.h
 *
 *  Created on: 22 de dez de 2016
 *      Author: cuki
 */

#ifndef SRC_PIVO_MEM_H_
#define SRC_PIVO_MEM_H_

#include "sys.h"

#include <stdint.h>
#include <stdbool.h>

#define MB_MAX_SIZE		UINT16_MAX

extern void MEM_init(void);
extern bool MEM_ready(void);
extern uint32_t MEM_get_dword(uint16_t address);
extern bool MEM_set_dword(uint16_t address, uint32_t i_value);
extern uint16_t MEM_get_register(uint16_t address);
extern bool MEM_set_register(uint16_t address, uint16_t value);
extern uint8_t MEM_get_byte(uint16_t address);
extern bool MEM_set_byte(uint16_t address, uint8_t value);
//extern bool MEM_get_bool(uint16_t address);
//extern bool MEM_set_bool(uint16_t address, bool value);
extern bool MEM_get_str(uint16_t address, uint8_t *data, uint16_t i_size);
extern bool MEM_set_str(uint16_t address, uint8_t *data, uint16_t i_size);
extern float MEM_get_mb_float(uint16_t address);
bool MEM_set_mb_float(uint16_t address, float value);
extern bool MEM_get_bit(uint16_t address);
extern void MEM_set_bit(uint16_t address, bool value);

#endif /* SRC_PIVO_MEM_H_ */