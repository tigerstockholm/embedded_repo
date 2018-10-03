#include <avr/io.h>

#include "adc.h"

void adc_init(void){

	DDRD |= (0 << DDD2);

	ADCSRA |= (1 << ADEN | 1 << ADIE | 1 << ADPS1 | 1 << ADPS0);
	ADMUX |= (0 << MUX3 | 0 << MUX2 | 0 << MUX1 | 0 << MUX0);
	ADMUX |= (1 << ADLAR | 1 << REFS0);
}
