#include "msp.h"


/**
 * main.c
 */
void TA0_N_IRQHandler(void){
    //__NVIC_DisableIRQ(TA0_N_IRQn); //disable since we're in the interrupt
    __disable_irq();



    if(TIMER_A0->CCTL[1] & BIT0){
        TIMER_A0->CCTL[1] &= ~BIT0;
    }

    //__NVIC_EnableIRQ(PORT1_IRQn); //enable interrupt since we are about to exit handler
    __enable_irq();
}


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    stop_pwm();
    config_switch_interrupt();
    config_pwm_timer();
    config_pwm_gpio();
    start_pwm();
    config_interrupt();
}



