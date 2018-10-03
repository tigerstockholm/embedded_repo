#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <stdlib.h>

#include "led.h"
#include "serial.h"
#include "timer.h"
#include "adc.h"

volatile uint8_t global_value;
volatile uint8_t button_clicks;
uint8_t counter = 0;

void button(void);

ISR(TIMER2_COMPA_vect) {

	button();

	switch(button_clicks) {

		case 1:
			OCR0A = simple_ramp();
			break;
		case 2:
			ADCSRA |= (1 << ADSC);
			break;
		case 3:
			if(counter == 100) {
				OCR0A = 0;
			}
			else if(counter == 200) {
				OCR0A = 255;
				counter = 0;
			}
			counter++;
			break;
		case 4:
			OCR0A = 0;
			break;
	}
}

ISR(ADC_vect) {

	global_value = ADCH;
	OCR0A = global_value;
}

void button(void) {

	static uint8_t state = 0;

	if ((PIND & (1 << PIND2)) == 4 && state == 0) {
		state = 1;
	} else if ((PIND & (1 << PIND2)) == 0 && state == 1) {
		button_clicks++;
		state = 0;
		if (button_clicks == 5) {
			button_clicks = 1;
		}
	}
}

void main (void) {

	LED_init();
	timer_init();
	adc_init();

	sei();

	while (1) {
		;
	}
}

