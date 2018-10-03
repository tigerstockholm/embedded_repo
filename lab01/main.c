#include <avr/io.h>

#include "serial.h"

#include "led.h"

#include <util/delay.h>


void main (void) {

	uart_init();
	while(1){
	uart_putstr("Fredrik Tigerklo\n");
	_delay_ms(500);
	UDR0='f';
	uart_echo();
	UDR0='\n';
	}

}

