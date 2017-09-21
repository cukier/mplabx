#ifndef HEART_BEAT_H
#define	HEART_BEAT_H

#include "sys.h"
#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include <stdbool.h>

void hb_init(void);
void hb_beat(uint32_t ms);

#endif	/* XC_HEADER_TEMPLATE_H */

