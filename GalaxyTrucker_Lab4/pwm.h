/*
 * pwm.h
 *
 *  Created on: Feb 9, 2021
 *      Author: adamvitti
 */

#ifndef PWM_H_
#define PWM_H_

#include "msp.h"

/*  MATH FOR TICKS: Where divider = 1
 * (3*10^6)/(2^2) = 750000 |||| 750000*(25*10^-3) = 18750 ticks ==> 0x493E in hex
 */
#define TICKS (0x493E)

void config_pwm_timer(void);

void start_pwm(void);

void stop_pwm(void);

void config_pwm_gpio(void);

void config_switch_interrupt(void);


#endif /* PWM_H_ */
