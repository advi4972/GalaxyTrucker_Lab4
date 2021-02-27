#include "msp.h"
#include "pwm.h"


void config_pwm_timer(void){
    TIMER_A0->CTL |= TIMER_A_CTL_IE; //Turns on interrupts for clock
    TIMER_A0->CTL |= TIMER_A_CTL_TASSEL_2; //Chooses SMCLK as input clk
    //SET DIVIDER VALUE
    TIMER_A0->CTL |= TIMER_A_CTL_ID__1 ; //DIVIDE BY MASK FOR ID = 1

    //SET CCR VALUES BASED TO TICKS
    //Creates 80/20 duty cycle for 10us Output to P2.4
    TIMER_A0->CCR[0] = TICKS0 ;//Limit value for clock
    TIMER_A0->CCR[1] = TICKS1 ;

 //Setup TIMER A1
    TIMER_A1->CTL |= TIMER_A_CTL_TASSEL_2; //Chooses SMCLK as input clk
    TIMER_A1->CTL |= TIMER_A_CTL_ID__1 ;


}

void start_pwm(void){
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_OUTMOD_7; //RESETS mode
    TIMER_A0->CCTL[1] &= TIMER_A_CCTLN_OUTMOD_2; //SETS OUTPUT MODE TO TOGGLE/RESET
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_CCIE; //enables interrupt bit CCIE in cctl register
    TIMER_A0->CTL |= TIMER_A_CTL_MC_1; //Sets count mode to "UP"


}

void stop_pwm(void){
    TIMER_A0->CTL &= TIMER_A_CTL_MC__STOP;
}

void config_pwm_gpio(void){
//PIN 2.4
    P2->DIR |= BIT4; //sets p2.4 as output 000010000
    P2->OUT |= BIT4; // sets bit4 to 1

    P2->SEL0 |= BIT4; //0000100000
    P2->SEL1 &= ~BIT4;// 111101111

 //Set up P2.7 as interrupt output for testing purposes
    P2->DIR |= BIT7; //sets p2.4 as output 000010000
    P2->OUT |= BIT7; // sets bit4 to 1

    P2->SEL0 &= ~BIT7; //0000000000
    P2->SEL1 &= ~BIT7;// 0000000000

//PIN 2.5 as input and enable interrupt
    P2->SEL0 &= ~BIT5; //0000100000
    P2->SEL1 &= ~BIT5;// 0000000000
    P2->DIR &= ~BIT5; //sets p2.7 as input 001000000
    P2->REN &= ~BIT5; //no pullup/pulldown
    P2->IES |= BIT5; //Falling edge interrupt trigger
    P2->IFG &= ~BIT5; //Clears initial interrupt flag
    P2->IE |= BIT5; //Enables interrupt functionality for P2.7


 //Set up test LED for toggling within the Port 2 interrupt
    P2->DIR |= BIT0; //sets p2.0 as output 000000001
    P2->OUT &= ~BIT0; // sets bit0 to 0

    P2->SEL0 &= ~BIT0; //0000000000
    P2->SEL1 &= ~BIT0;// 0000000000



}

void config_interrupt(void){
    __NVIC_EnableIRQ(TA0_N_IRQn);
    __NVIC_EnableIRQ(PORT2_IRQn);

}
