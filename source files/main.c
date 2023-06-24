/*
 * File:   main.c
 * Author: edenc
 *
 * Created on 24 June, 2023, 8:04 AM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000
#include<PIC16f877a.h>
int count;
int COUNT=0;
int generate_delay_value(int sec)
{
    int cnt=sec*20;
    return cnt;
}
void Timer_Interrupt_config(void)
{
    PIR1bits.TMR1IF=0;
    PIE1bits.TMR1IE=1;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
}
void Timer_config(void)
{
    TMR1=15535;
//    TMR1=0;
    T1CONbits.T1CKPS0=0;
    T1CONbits.T1CKPS1=0;
    T1CONbits.TMR1CS=0;
    T1CONbits.TMR1ON=1;
}
void Timer_off(void)
{
    T1CONbits.TMR1ON=0;
}
void main(void) {
    TRISB=0x00;
    PORTB=0x02;
    count=generate_delay_value(1);//Enter the number of seconds after which delay is to be generated
    Timer_config();
    Timer_Interrupt_config();
    while(1)
    {
        
    }
    return;
}
void __interrupt() ISR(void)
{
    COUNT++;
    if(PIR1bits.TMR1IF==1)
    {
//        PORTB^=0x02;
        if(COUNT==count)
        {   /*Include your program that is to be executed at the end of the
            interrupt statement*/
            PORTB^=0x02;
            Timer_off();
        }
        
    }
    TMR1=15535;
    PIR1bits.TMR1IF=0;
}
