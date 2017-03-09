#ifndef EXT_EEPROM_H
#define	EXT_EEPROM_H

#define EEPROM_ADDR			0xA0
#define EEPROM_SIZE			32768
#define EEPROM_PAGE_SIZE	64

#include <stdint.h>
#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    void init_ext_eeprom(void);
    bool read_ext_eeprom(uint16_t address, uint8_t *data, uint16_t i_size);
    bool write_ext_eeprom(uint16_t address, uint8_t *data, uint16_t i_size);
    
#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

