#ifndef _PWM_H
#define _PWM_H

#include "stm32f4xx.h"

//-----------------------------------------------------------------------
void c_led(void); // RGB_LED
//-----------------------------------------------------------------------
void c_timer(uint16_t); // TIMER
//-----------------------------------------------------------------------
void c_nvic(void); // NVIC
//-----------------------------------------------------------------------
void c_pwm(void); // PWN
//-----------------------------------------------------------------------
void c_button(void); // BUTTON L & R
//-----------------------------------------------------------------------

#endif
