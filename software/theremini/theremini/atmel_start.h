#ifndef ATMEL_START_H_INCLUDED
#define ATMEL_START_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "include/driver_init.h"
#include "include/atmel_start_pins.h"

#include "touch.h"

typedef enum {
	MODE_SPOOLING,
	MODE_HAZARDS,
	MODE_FLICKER,
	MODE_RANDOM,
	MODE_REVERSE_SPOOLING
} RUNMODE;

typedef struct {
	bool touched;
	bool latched;
} KEYPRESS;

typedef enum {
	KEY_D = 0,
	KEY_C = 1,
	KEY_Z = 2,
	KEY_I = 3,
	KEY_A = 4,
	KEY_NONE = 5
} CAPKEY;

CAPKEY lastKey;

/**
 * Initializes MCU, drivers and middleware in the project
 **/
void atmel_start_init(void);

#ifdef __cplusplus
}
#endif
#endif
