#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#include "timer.h"
#include "led.h"

void main (void) {
	timer2_ctc_init();
	timer_pwm_init();
	LED_init();

	while (1) {

		two_timer_pulse();
	}
}
