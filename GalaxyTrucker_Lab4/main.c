#include "msp.h"


/**
 * main.c
 */
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    stop_pwm();
    config_switch_interrupt();
    config_pwm_timer();
    config_pwm_gpio();
    start_pwm();
}
