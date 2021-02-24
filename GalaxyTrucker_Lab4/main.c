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
void PORT1_IRQHandler(void){
    __NVIC_DisableIRQ(PORT1_IRQn); //disable since we're in the interrupt

    if(P1->IFG & BIT1){
        P1->IFG &= ~BIT1;
    }
    while((P1->IN & BIT1) == 0x00){ //RESETS timer while P1.1 is being held
        stop_pwm(); //stops/reset
        TIMER_A0->R = 0; //sets counter register to 0
    }
    //re-initialize timer stuff and begin
    config_pwm_timer();
    start_pwm();

    __NVIC_EnableIRQ(PORT1_IRQn); //enable interrupt since we are about to exit handler
}


void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    stop_pwm();
    config_switch_interrupt();
    config_pwm_timer();
    config_pwm_gpio();
    start_pwm();
}
