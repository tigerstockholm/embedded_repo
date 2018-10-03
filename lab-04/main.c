#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "serial.h"
#include "timer.h"

char name[] = "TIGERKLO";
char name2[] = "FREDRIK ";

uint8_t buf[256];

uint8_t len = (sizeof( name ) -1);
uint8_t len2 = (sizeof( name2 ) -1);

uint8_t write_addr = 0x00;
uint8_t write_addr2 = 0x08;

void main (void) {

	i2c_init();
	uart_init();

	sei();

	uint8_t full_name = len + len2;

	eeprom_write_page(write_addr2, (sizeof(name) - 1), name);

	eeprom_write_page(write_addr, (sizeof(name2) - 1), name2);

	eeprom_sequential_read(buf, write_addr, full_name);

	for(uint8_t i=0 ; i < full_name ; i++) {

		printf_P(PSTR("%02x : "), buf[i], buf[i]);
		printf_P(PSTR("%02x\n"), write_addr++);

	}

	while (1) {

		;

	}
}

