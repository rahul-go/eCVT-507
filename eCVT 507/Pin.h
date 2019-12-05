#ifndef Pin_h
#define Pin_h

#include <avr/io.h>

struct Pin {
	PORT_t *PORT;
	uint8_t PIN_BM;
};

#endif