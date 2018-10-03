#include <avr/io.h>
#include <stdlib.h>
#include "timer.h"

uint8_t counter = 0;
signed int c_value = 255; 

void timer2_ctc_init() {
	TCCR2A |= (1<<WGM21);
	TCNT2 = 0;
	OCR2A = 124;
	TCCR2B |= (1<<CS02)|(1<<CS01)|(1<<CS00);
}

void timer_pwm_init(){

	TCCR0A |= (1<<WGM00)|(1<<WGM01)|(1<<COM0A1);
	TCCR0B |= (1<<CS00)|(1<<CS01);
	OCR0A = 0;
	TCNT0 = 0;
}

void one_timer_pulse(void){

         while(!(TIFR0 & (1<<OCF0A)))
                 ;
         count();
         TIFR0 = (1<<OCF0A);
         if(counter == 5){
                c_value -= 1;
                PORTD ^= (1<<PD6);
                OCR0A = abs(c_value);
                if(c_value == -255){c_value = 255;}
                counter = 0;
         }

}

uint8_t value;
void two_timer_pulse(void){

        while(!(TIFR0 & (1<<OCF0A)))
                ;
        TIFR0 = (1<<OCF0A);
        PORTD ^= (1<<PD6);
        value = OCR0A;
  	OCR0A = simple_ramp(value);

}

int state=0;
uint8_t simple_ramp(uint8_t cycle_v){

	while(!(TIFR2 &(1<<OCF2A)))
		;
	TIFR2 |= (1<<OCF2A);
	if(cycle_v == 0 || cycle_v == 255){
		state = abs(state -1);
	}
	if(state){
	cycle_v += 1;
	return cycle_v;
	}
	cycle_v -=1;
	return cycle_v;

}

void count(void){counter++;}
