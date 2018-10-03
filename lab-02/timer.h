#ifndef _TIMER_H_
#define _TIMER_H_

void timer2_ctc_init(void);

void timer_pwm_init(void);

void one_timer_pulse(void);

void two_timer_pulse(void);

uint8_t simple_ramp(uint8_t);

void count(void);

#endif // _TIMER_H_
