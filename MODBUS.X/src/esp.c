/*
 * esp.c
 *
 *  Created on: 13 de fev de 2017
 *      Author: cuki
 */

#ifndef BUFF_S
#define BUFF_S	512
#endif

#include "esp.h"

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

uint8_t webPage[] = "<h1><u>Krebs - Web Server</u></h1><h2>Porta ";
bool esp_recived;
char esp_buff[BUFF_S];
uint16_t esp_index;

void esp_flush() {
    uint16_t cont;

    esp_index = 0;

    for (cont = 0; cont < BUFF_S; ++cont)
        esp_buff[cont] = 0;

    return;
}

uint8_t esp_find() {
    char ipd[] = "+IPD,";
    char *ptr;
    uint8_t ret = 0;

    ptr = strstr(esp_buff, ipd);

    if (*ptr == '\0')
        return 0xFF;

    ptr += 5;
    ret = *ptr - 48;

    return ret;
}

void esp_webPage(bool input) {
    printf("%s%u</h2>", webPage, input);

    return;
}

void esp_chipSend(uint8_t conId, uint16_t length) {
    printf("AT+CIPSEND=%u,%u\r\n", conId, length);

    return;
}

void esp_close(uint8_t conId) {
    printf("AT+CIPCLOSE=%u\r\n", conId);

    return;
}

void esp_init(void) {
    char str[50], aux[50];
    uint16_t s;

    esp_index = 0;
    esp_recived = false;

    strcpy(aux, "Hello");
    strcat(str, aux);
    strcpy(aux, " World");
    strcat(str, aux);
    s = strlen(str);

    printf("AT+RST\r\n");
    __delay_ms(2500);
    printf("AT+CWMODE=1\r\n");
    __delay_ms(1000);
    printf("AT+CWJAP=\"dlinkesp\",\"\"\r\n");
    __delay_ms(8000);
    printf("AT+CIFSR\r\n");
    __delay_ms(1000);
    printf("AT+CIPMUX=1\r\n");
    __delay_ms(1000);
    printf("AT+CIPSERVER=1,80\r\n");
    __delay_ms(1000);

    return;
}

void esp_pool(void) {
    uint8_t ch_id;

    ch_id = '\0';


    if (esp_recived) {
        esp_recived = false;
        ch_id = esp_find();

        if (ch_id != 0xFF) {
            __delay_ms(500);
            esp_chipSend(ch_id, sizeof (webPage) + 5);
            __delay_ms(500);
            esp_webPage(true);
            __delay_ms(500);
            esp_close(ch_id);
            ch_id = '\0';
        }

        esp_flush();
    }

    return;
}
