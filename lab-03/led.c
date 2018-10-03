#include <avr/io.h>
#include <stdlib.h>
#include "led.h"

void LED_init() {

	DDRD |= (1 << DDD6);

}

uint8_t ramp_state = 0;
uint8_t cycle = 0;

uint8_t simple_ramp(){

	if (cycle == 0 || cycle == 255) {
		ramp_state = abs(ramp_state -1);
	}

	if (ramp_state) {
		cycle += 1;
		return cycle;
	}

	cycle -=1;
	return cycle;
}
