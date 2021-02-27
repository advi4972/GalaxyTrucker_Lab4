#include "msp.h"
#include "pwm.h"
#include <stdbool.h>
#include <stdio.h>

/**
 * main.c
 */

bool fallingEdge = false;
uint16_t EchoTICKS = 0;
float EchoTime = 0;

void TA0_N_IRQHandler(void){
    //__NVIC_DisableIRQ(TA0_N_IRQn); //disable since we're in the interrupt
    __disable_irq();

    if(fallingEdge == true){ //only execute when falling edge of trig
        TIMER_A1->CTL |= TIMER_A_CTL_MC_2; //Sets count mode to "CONTINUOUS" starts counting

        fallingEdge = false;
    }else{
        fallingEdge = true;
    }

    if(TIMER_A0->CCTL[1] & BIT0){
        P2->OUT = ~(P2->OUT & BIT7); //Test to make sure the interrupt is triggered every 50ms
        TIMER_A0->CCTL[1] &= ~BIT0;
    }

    //__NVIC_EnableIRQ(PORT1_IRQn); //enable interrupt since we are about to exit handler
    __enable_irq();

}

void PORT2_IRQHandler(void){
    __NVIC_DisableIRQ(PORT2_IRQn); //disable since we're in the interrupt

        //STOP TIMER A1 since we've hit falling edge of ECHO signal
        TIMER_A1->CTL &= TIMER_A_CTL_MC__STOP;

        //Read from TIMER_A1->R for the ticks value from end of trig signal to end of ECHO signal!!!
        EchoTICKS = TIMER_A1->R;

        //Reset the R counting register
        TIMER_A1->R = 0000000000000000;

        P2->OUT = ~(P2->OUT & BIT0);

    if(P2->IFG & BIT5){
        P2->IFG &= ~BIT5;
    }

    __NVIC_EnableIRQ(PORT6_IRQn); //enable interrupt since we are about to exit handler
}


float distance = 0.0;

void main(void)
{


    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer

    stop_pwm();
    config_pwm_timer();
    config_pwm_gpio();
    start_pwm();
    config_interrupt();

    while(1){
        EchoTime = EchoTICKS/3000000;
        distance = ((.34)*(EchoTime))/2;
        printf("Distance = %f\n", distance);
    }
}



