#ifndef ESP_H
#define ESP_H

#include "sys.h"
#include "xc.h"

#include <libpic30.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

void esp_init(void);
void esp_pool(void);

#endif