/*
 * File:   sick.c
 * Author: cuki
 *
 * Created on 13 de Março de 2017, 10:16
 */

#include "sick.h"
#include "serial.h"
#include <libpic30.h>
#include <stdlib.h>

#define EXIT_SUCESS		0
#define EXIT_ERROR		0xFF
#define DSF60_ADDRESS	0x40
#define BUFFER_MAX		0x80
#define ENCODER_EN		PIN_C2

typedef enum electrical_interface_e {
    DSF60_TTL, DSF60_HTL
} electrical_interface_t;

typedef enum pulse_width_electrical_e {
    DSF60_90_DEGREES,
    DSF60_180_DEGREES_CHANNEL_B,
    DSF60_180_DEGREES_CHANNEL_A,
    DSF60_270_DEGREES
} pulse_width_electrical_t;

typedef enum pulse_width_mechanical_e {
    DSF60_45_DEGREES_MECHANICAL, DSF60_270_DEGREES_MECHANICAL,
} pulse_width_mechanical_t;

typedef struct dsf60_str {
    pulse_width_electrical_t pulse_width_electrical;
    char serial_number[10];
    char firmware_version[11];
    char firmware_date[9];
    char part_number[17];
    char encoder_type[8];
    char date_code[9];
    uint32_t position;
    uint32_t resolution;
    uint16_t pulse_width_mechanical;
} dsf60_t;

typedef enum dsf60_command_e {
    DSF60_COMMAND_ENCODER_RESET = 0x53,
    DSF60_COMMAND_READ_SERIAL_NUMBER = 0x56,
    DSF60_COMMAND_READ_POSITION = 0x92,
    DSF60_COMMAND_SET_NUMBER_OF_LINES = 0x96,
    DSF60_COMMAND_SET_ELECTRICAL_INTERFACE,
    DSF60_COMMAND_SET_ZERO_PULSE_WIDTH_ELECTRICAL,
    DSF60_COMMAND_ZERO_SET,
    DSF60_COMMAND_READ_ENCODER_TYPE,
    DSF60_COMMAND_SET_ZERO_PULSE_WIDTH_MECHANICAL,
    DSF60_COMMAND_READ_ZERO_PULSE_WIDTH_ELECTRIAL_MECHANICAL,
    DSF60_COMMAND_READ_ELECTRICAL_INTERFACE
} DSF60_command_t;

dsf60_t *dsf60;
#ifdef ENCODER_USE_UART1
uint8_t dsf60_buffer[SERIAL1_BUFFER_SIZE];
#endif
#ifdef ENCODER_USE_UART2
uint8_t dsf60_buffer[SERIAL2_BUFFER_SIZE];
#endif

void DSF60_send_request(uint8_t *req, uint16_t size) {
    uint16_t cont;

    for (cont = 0; cont < size; ++cont) {
#ifdef ENCODER_USE_UART1
        __C30_UART = 1;
        putchar(req[cont]);
#endif
#ifdef ENCODER_USE_UART2
        __C30_UART = 2;
        putchar(req[cont]);
#endif
    }

    return;
}

bool DSF60_init_encoder(void) {
    TRISEbits.TRISE0 = 0;

    //    dsf60_buffer = (uint8_t *) malloc(SERIAL_BUFFER_SIZE * sizeof(uint8_t));
    //    
    //    if (dsf60_buffer == NULL)
    //            return false;

#ifdef ENCODER_USE_UART1
    uart1_init(dsf60_buffer);
#endif

#ifdef ENCODER_USE_UART2
    uart2_init(dsf60_buffer);
#endif

    dsf60 = (dsf60_t *) malloc(sizeof (dsf60_t));

    if (dsf60 == NULL) {
        //        free(dsf60_buffer);
        return false;
    }

    return true;
}

uint8_t DSF60_crc_sum(uint8_t *data, uint16_t size) {
    uint8_t i = 0, ret = 0;

    for (i = 0; i < size; ++i)
        ret ^= data[i];

    return ret;
}

void DSF60_encoder_reset(void) {
    uint8_t *req;

    req = (uint8_t *) malloc(3 * sizeof (uint8_t));
    req[0] = DSF60_ADDRESS;
    req[1] = DSF60_COMMAND_ENCODER_RESET;
    req[2] = DSF60_crc_sum(req, 2);
    DSF60_send_request(req, 3);
    free(req);

    return;
}

void DSF60_read_serial_number(void) {
    uint8_t *req;

    req = (uint8_t *) malloc(3 * sizeof (uint8_t));
    req[0] = DSF60_ADDRESS;
    req[1] = DSF60_COMMAND_READ_SERIAL_NUMBER;
    req[2] = DSF60_crc_sum(req, 2);
    DSF60_send_request(req, 3);
    free(req);

    return;
}

void DSF60_read_position(void) {
    uint8_t *req;

    req = (uint8_t *) malloc(4 * sizeof (uint8_t));
    req[0] = DSF60_ADDRESS;
    req[1] = DSF60_COMMAND_READ_POSITION;
    req[2] = 0x21; //FORMAT
    req[3] = DSF60_crc_sum(req, 3);
    DSF60_send_request(req, 4);
    free(req);

    return;
}

void DSF60_set_number_lines(uint32_t n_lines) {
    uint8_t *req;

    req = (uint8_t *) malloc(7 * sizeof (uint8_t));
    req[0] = DSF60_ADDRESS;
    req[1] = DSF60_COMMAND_SET_NUMBER_OF_LINES;
    req[2] = (uint8_t) ((n_lines & 0x0F00) >> 16);
    req[3] = (uint8_t) ((n_lines & 0x00F0) >> 8);
    req[4] = (uint8_t) ((n_lines & 0x000F));
    req[5] = 0x69; //ACCESS code
    req[6] = DSF60_crc_sum(req, 6);
    DSF60_send_request(req, 7);
    free(req);

    return;
}

void DSF60_set_electrical_interface(uint8_t mode) {
    uint8_t *req;

    req = (uint8_t *) malloc(5 * sizeof (uint8_t));
    req[0] = DSF60_ADDRESS;
    req[1] = DSF60_COMMAND_SET_ELECTRICAL_INTERFACE;
    req[2] = mode;
    req[3] = 0x69; //ACCESS code
    req[4] = DSF60_crc_sum(req, 4);
    DSF60_send_request(req, 5);
    free(req);

    return;
}

void DSF60_set_zero_pulse_width_electrical(uint8_t mode) {
    uint8_t *req;

    req = (uint8_t *) malloc(5 * sizeof (uint8_t));
    req[0] = DSF60_ADDRESS;
    req[1] = DSF60_COMMAND_SET_ZERO_PULSE_WIDTH_ELECTRICAL;
    req[2] = mode;
    req[3] = 0x69; //ACCESS code
    req[4] = DSF60_crc_sum(req, 4);
    DSF60_send_request(req, 5);
    free(req);

    return;
}

void DSF60_zero_set(void) {
    uint8_t *req;

    req = (uint8_t *) malloc(5 * sizeof (uint8_t));
    req[0] = DSF60_ADDRESS;
    req[1] = DSF60_COMMAND_ZERO_SET;
    req[2] = 0x69; //ACCESS code
    req[3] = DSF60_crc_sum(req, 3);
    DSF60_send_request(req, 4);
    free(req);

    return;
}

void DSF60_read_encoder_type(void) {
    uint8_t *req;

    req = (uint8_t *) malloc(3 * sizeof (uint8_t));
    req[0] = DSF60_ADDRESS;
    req[1] = DSF60_COMMAND_READ_ENCODER_TYPE;
    req[2] = DSF60_crc_sum(req, 2);
    DSF60_send_request(req, 3);
    free(req);

    return;
}

void DSF60_set_zero_pulse_width_mechanical(uint16_t degrees) {
    uint8_t *req;

    req = (uint8_t *) malloc(3 * sizeof (uint8_t));
    req[0] = DSF60_ADDRESS;
    req[1] = DSF60_COMMAND_SET_ZERO_PULSE_WIDTH_MECHANICAL;
    req[2] = (uint8_t) ((degrees & 0xF0) >> 8);
    req[3] = (uint8_t) (degrees & 0x0F);
    req[4] = DSF60_crc_sum(req, 4);
    DSF60_send_request(req, 5);
    free(req);

    return;
}

void DSF60_read_zero_pulse_width_electrical_mechanical(void) {
    uint8_t *req;

    req = (uint8_t *) malloc(3 * sizeof (uint8_t));
    req[0] = DSF60_ADDRESS;
    req[1] = DSF60_COMMAND_READ_ZERO_PULSE_WIDTH_ELECTRIAL_MECHANICAL;
    req[2] = DSF60_crc_sum(req, 2);
    DSF60_send_request(req, 3);
    free(req);

    return;
}

void DSF60_read_electrical_interface(void) {
    uint8_t *req;

    req = (uint8_t *) malloc(3 * sizeof (uint8_t));
    req[0] = DSF60_ADDRESS;
    req[1] = DSF60_COMMAND_READ_ELECTRICAL_INTERFACE;
    req[2] = DSF60_crc_sum(req, 2);
    DSF60_send_request(req, 3);
    free(req);

    return;
}

void DSF60_disable_encoder(void) {
    LATEbits.LATE0 = 0;

    return;
}

void DSF60_enable_encoder(void) {
    LATEbits.LATE0 = 1;

    return;
}

uint32_t make32(uint8_t hh, uint8_t hl, uint8_t lh, uint8_t ll) {
    uint32_t ret = 0;

    ret = (uint32_t) hh << 24;
    ret |= (uint32_t) hl << 16;
    ret |= (uint32_t) lh << 8;
    ret |= (uint32_t) ll;

    return ret;
}

uint16_t make16(uint8_t h, uint8_t l) {
    uint16_t ret = 0;

    ret = (uint16_t) h << 8;
    ret |= (uint16_t) l;

    return ret;
}

bool DSF60_make_transaction(DSF60_command_t command, uint32_t arg) {
    uint8_t retries, n, cont, t;
    uint16_t pulse_width_resp;

    retries = 200;
    n = 0;
    pulse_width_resp = 0;
    t = 1;

    //	do {
    //		resp = EXIT_SUCESS;
    //		resp = DSF60_check();
    //		delay_ms(100);
    //
    //		if (!retries)
    //			return false;
    //
    //	} while (resp == EXIT_ERROR && --retries);

    switch (command) {
        case DSF60_COMMAND_ENCODER_RESET:
            DSF60_encoder_reset();
            break;
        case DSF60_COMMAND_READ_SERIAL_NUMBER:
            DSF60_read_serial_number();
            n = 30;
            t = 5;
            break;
        case DSF60_COMMAND_READ_POSITION:
            DSF60_read_position();
            n = 7;
            t = 5;
            break;
        case DSF60_COMMAND_SET_NUMBER_OF_LINES:
            DSF60_set_number_lines(arg);
            n = 3;
            t = 150;
            break;
        case DSF60_COMMAND_SET_ELECTRICAL_INTERFACE:
            DSF60_set_electrical_interface((uint8_t) arg);
            n = 3;
            t = 5;
            break;
        case DSF60_COMMAND_SET_ZERO_PULSE_WIDTH_ELECTRICAL:
            DSF60_set_zero_pulse_width_electrical((uint8_t) arg);
            n = 3;
            t = 80;
            break;
        case DSF60_COMMAND_ZERO_SET:
            DSF60_zero_set();
            n = 3;
            break;
        case DSF60_COMMAND_READ_ENCODER_TYPE:
            DSF60_read_encoder_type();
            n = 37;
            t = 40;
            break;
        case DSF60_COMMAND_SET_ZERO_PULSE_WIDTH_MECHANICAL:
            DSF60_set_zero_pulse_width_mechanical((uint16_t) arg);
            n = 3;
            t = 80;
            break;
        case DSF60_COMMAND_READ_ZERO_PULSE_WIDTH_ELECTRIAL_MECHANICAL:
            DSF60_read_zero_pulse_width_electrical_mechanical();
            n = 5;
            t = 5;
            break;
        case DSF60_COMMAND_READ_ELECTRICAL_INTERFACE:
            DSF60_read_electrical_interface();
            n = 4;
            t = 5;
            break;
        default:
            n = 0;
            break;
    }

    __delay_ms(t);

#ifdef ENCODER_USE_UART1
    if (uart1_get_index() != n) {
        return false;
    }
#endif
#ifdef ENCODER_USE_UART2
    if (uart2_get_index() != n) {
        return false;
    }
#endif

    switch (command) {
        case DSF60_COMMAND_ENCODER_RESET:
            break;
        case DSF60_COMMAND_READ_SERIAL_NUMBER:
            for (cont = 0; cont < 9; ++cont)
                dsf60->serial_number[cont] = dsf60_buffer[cont + 2];

            dsf60->serial_number[cont] = '\0';

            for (cont = 0; cont < 10; ++cont)
                dsf60->firmware_version[cont] = dsf60_buffer[cont + 11];

            dsf60->firmware_version[cont] = '\0';

            for (cont = 0; cont < 8; ++cont)
                dsf60->firmware_date[cont] = dsf60_buffer[cont + 21];

            dsf60->firmware_date[cont] = '\0';
            break;
        case DSF60_COMMAND_READ_POSITION:
            dsf60->position = make32(dsf60_buffer[2], dsf60_buffer[3],
                    dsf60_buffer[4], dsf60_buffer[5]);
            break;
        case DSF60_COMMAND_SET_NUMBER_OF_LINES:
            break;
        case DSF60_COMMAND_SET_ELECTRICAL_INTERFACE:
            break;
        case DSF60_COMMAND_SET_ZERO_PULSE_WIDTH_ELECTRICAL:
            break;
        case DSF60_COMMAND_ZERO_SET:
            break;
        case DSF60_COMMAND_READ_ENCODER_TYPE:
            for (cont = 0; cont < 16; ++cont)
                dsf60->part_number[cont] = dsf60_buffer[cont + 2];

            dsf60->part_number[cont] = '\0';

            for (cont = 0; cont < 7; ++cont)
                dsf60->encoder_type[cont] = dsf60_buffer[cont + 18];

            dsf60->encoder_type[cont] = '\0';

            for (cont = 0; cont < 8; ++cont)
                dsf60->date_code[cont] = dsf60_buffer[cont + 25];

            dsf60->date_code[cont] = '\0';
            dsf60->resolution = make32(0, dsf60_buffer[33], dsf60_buffer[34],
                    dsf60_buffer[35]);
            break;
        case DSF60_COMMAND_SET_ZERO_PULSE_WIDTH_MECHANICAL:
            break;
        case DSF60_COMMAND_READ_ZERO_PULSE_WIDTH_ELECTRIAL_MECHANICAL:
            pulse_width_resp = make16(dsf60_buffer[2], dsf60_buffer[3]);

            if (pulse_width_resp > 1 && pulse_width_resp < 360) {
                dsf60->pulse_width_mechanical = pulse_width_resp;
                dsf60->pulse_width_electrical = 0;
            } else {
                dsf60->pulse_width_mechanical = 0;
                dsf60->pulse_width_electrical &= 0x00FF;

                if ((pulse_width_resp & DSF60_90_DEGREES) == DSF60_90_DEGREES)
                    dsf60->pulse_width_electrical = DSF60_90_DEGREES;
                else if ((pulse_width_resp & DSF60_180_DEGREES_CHANNEL_A)
                        == DSF60_180_DEGREES_CHANNEL_A)
                    dsf60->pulse_width_electrical = DSF60_180_DEGREES_CHANNEL_A;
                else if ((pulse_width_resp & DSF60_180_DEGREES_CHANNEL_B)
                        == DSF60_180_DEGREES_CHANNEL_B)
                    dsf60->pulse_width_electrical = DSF60_180_DEGREES_CHANNEL_B;
                else if ((pulse_width_resp & DSF60_270_DEGREES)
                        == DSF60_270_DEGREES)
                    dsf60->pulse_width_electrical = DSF60_270_DEGREES;
            }

            break;
        case DSF60_COMMAND_READ_ELECTRICAL_INTERFACE:
            if ((dsf60_buffer[2] & 0b0001) == DSF60_TTL)
                dsf60->pulse_width_electrical = DSF60_TTL;
            else
                dsf60->pulse_width_electrical = DSF60_HTL;

            break;
    }

    return true;
}

bool DSF60_reset(void) {
#ifdef ENCODER_USE_UART1
    uart1_get_index();
#endif    
#ifdef ENCODER_USE_UART2
    uart2_get_index();
#endif
    DSF60_disable_encoder();
    __delay_ms(3000);
    DSF60_enable_encoder();
    __delay_ms(20);
    DSF60_read_encoder_type();
    __delay_ms(50);

#ifdef ENCODER_USE_UART1    
    if (uart1_get_index() != 0) {
        return true;
    }
#endif
#ifdef ENCODER_USE_UART2
    if (uart2_get_index() != 0) {
        return true;
    }
#endif
    return false;
}

bool DSF60_check(void) {
    bool encoder_ok;
    uint8_t tries;

    encoder_ok = false;
    tries = 10;
    
    do {
        encoder_ok = DSF60_make_transaction(DSF60_COMMAND_READ_ENCODER_TYPE, 0);

        if (!encoder_ok) {
            __delay_ms(2000);
            encoder_ok = DSF60_reset();
            tries--;
            
            if (!encoder_ok && !tries) {
                return false;
            }
        }
    } while (!encoder_ok);

    return true;
}

uint32_t DSF60_get_position(void) {
    DSF60_make_transaction(DSF60_COMMAND_READ_POSITION, 0);

    return dsf60->position;
}