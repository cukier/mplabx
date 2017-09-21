#ifndef EXT_EEPROM_H
#define	EXT_EEPROM_H

#define EEPROM_ADDR			0xA0
#define EEPROM_SIZE			32768
#define EEPROM_PAGE_SIZE	64

#include <stdint.h>
#include <stdbool.h>

void ext_eeprom_init(void);
bool ext_eeprom_ready(void);
bool ext_eeprom_read(uint16_t address, uint8_t *data, uint16_t i_size);
bool ext_eeprom_write(uint16_t address, uint8_t *data, uint16_t i_size);

#endif

