/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */


#define PL1 PORTDbits.RD4
#define PL2 PORTDbits.RD5
#define LD1 PORTDbits.RD6
#define LD2 PORTDbits.RD7
#define PERIOD 200 //ms

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    char c = 0; //flash duration
    volatile unsigned short timer_delay = 0;    // Timer software

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */

    while(1)
    {
        if (!timer_delay)
        {
            timer_delay=PERIOD; //ms
            if (PL1 && PL2) //push buttons are not pressed
            {
                if (c & 0x02) //changes every 2 PERIOD
                {
                    LD1 = 1;
                    LD2 = 0;
                }
                else
                {
                    LD1 = 0;
                    LD2 = 1;
                }   
            }
            else //PL1 and/or PL2 are pressed
            {
                LD1 = 0;
                LD2 = 0;
                if (!PL1)
                {
                    if (c & 0x01) LD1 = 1; //faster rate, 1 PERIOD
                    else LD1 = 0;
                }
                if (!PL2)
                {
                    if (c & 0x01) LD2 = 1;
                    else LD2 = 0;
                }
            }
            c++;
            if (4 == c) c=0; //c ranges from 0 to 3
        }
    }
}

