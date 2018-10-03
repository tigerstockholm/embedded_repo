#include <avr/io.h>

#include <util/delay.h>

#include "serial.h"

#include "led.h"

void blinky(void){

	DDRB=0x01;

	while(1){
	
		PORTB=0b01;
		_delay_ms(500);

		PORTB=0b00;
		_delay_ms(500);
	}

}
