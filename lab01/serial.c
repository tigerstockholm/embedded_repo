#include <avr/io.h>

#include <util/delay.h>

#include "serial.h"



#define FOSC 16000000UL // Frekvensen (clock speed)
#define BAUD 38400
#define MYUBRR FOSC/16/BAUD-1 //Beräknar UBBR


void uart_init(void)
{
	unsigned int ubrr=MYUBRR;
	//Sätter baudrate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	//Sätter på sändning och mottagarfunktionen i B-registret
	UCSR0B = (1<<TXEN0) | (1<<RXEN0);
	//Sätter frame format till: 8data. Lämnar tomt för 1-bitstop
	UCSR0C = (3<<UCSZ00);
}

void uart_putchar(char chr){

	//Väntar på tom buffer
	while ( !( UCSR0A & (1<<UDRE0)) );
	//Om char är 'new line' lägger vi till ett 'r' för radbryt
	if(chr=='\n'){
	UDR0= '\r';
	//Väntar på tom buffer igen innan vi går vidare
	while(!(UCSR0A & (1<<UDRE0)) );
	}

	//Stoppar in data i buffern och skickar 
	UDR0=chr;

}

void uart_putstr(const char *str){

while(*str){
	uart_putchar(*str);
	*str++;
	}
}

char uart_getchar(void){

	//Väntar på data 
	while( !(UCSR0A & (1<<RXC0)) );
	return UDR0;

}

void uart_echo(void){

	char rec = uart_getchar();
	uart_putchar(rec);


}


