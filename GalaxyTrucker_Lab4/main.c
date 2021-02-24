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


void PORT2_IRQHandler(void) {
    __NVIC_DisableIRQ(PORT1_IRQn);

    if (P1->IFG & BIT1) {
        P1->IFG &= ~BIT1;
    }

    while(!(P1->IN & BIT1)) {
        stop_pwm();
        TIMER_A0->R = 0;
    }

    config_pwm_timer();
    start_pwm();

    __NVIC_EnableIRQ(PORT1_IRQn);

}

