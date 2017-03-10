#include "ext_eeprom.h"
#include "i2c.h"
#include <libpic30.h>
#include <stdlib.h>

void init_ext_eeprom(void) {
    I2C1_Initialize();

    return;
}

bool ext_eeprom_ready(void) {
    uint8_t cont;

    cont = UINT8_MAX;

    while (!I2C1_get_ack(EEPROM_ADDR) && cont--) {
        __delay_ms(10);
    }

    if (!cont)
        return false;

    return true;
}

bool read_ext_eeprom(uint16_t address, uint8_t *data, uint16_t i_size) {

    if ((address + i_size) > (uint16_t) EEPROM_SIZE)
        return false;

    if (ext_eeprom_ready()) {
        I2C1_get_data(EEPROM_ADDR, address, data, i_size);
        __delay_ms(10);
    } else {
        return false;
    }

    return true;
}

bool write_ext_eeprom(uint16_t address, uint8_t *data, uint16_t i_size) {
    uint8_t *read_buffer;
    uint16_t cont, acum, end, block_addr, offset;

    if ((!ext_eeprom_ready()) || ((address + i_size) > (uint16_t) EEPROM_SIZE))
        return false;

    if (i_size > EEPROM_PAGE_SIZE)
        end = EEPROM_PAGE_SIZE;
    else
        end = i_size;

    acum = 0;
    block_addr = ((uint16_t) (address / EEPROM_PAGE_SIZE)) * EEPROM_PAGE_SIZE;
    offset = address - block_addr;
    read_buffer = NULL;
    read_buffer = (uint8_t *) malloc(EEPROM_PAGE_SIZE * sizeof(uint8_t));
    
    if (read_buffer == NULL)
        return false;

    do {
        I2C1_get_data(EEPROM_ADDR, block_addr, read_buffer, EEPROM_PAGE_SIZE);

        for (cont = 0; cont < end; ++cont) {
            read_buffer[cont + offset] = data[cont + acum];
        }

        I2C1_send_data(EEPROM_ADDR, block_addr, read_buffer, EEPROM_PAGE_SIZE);
        acum += end - offset;

        if (i_size > (acum + EEPROM_PAGE_SIZE))
            end = EEPROM_PAGE_SIZE;
        else
            end = i_size - acum;

        block_addr += EEPROM_PAGE_SIZE;
        offset = 0;
        __delay_ms(10);
    } while (acum < i_size);

    free(read_buffer);
    return true;
}