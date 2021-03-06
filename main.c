/*
 * CANopen main program file.
 *
 * This file is a template for other microcontrollers.
 *
 * @file        main_generic.c
 * @author      Janez Paternoster
 * @copyright   2004 - 2013 Janez Paternoster
 *
 * This file is part of CANopenNode, an opensource CANopen Stack.
 * Project home page is <http://canopennode.sourceforge.net>.
 * For more information on CANopen see <http://www.can-cia.org/>.
 *
 * CANopenNode is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include "CANopen.h"


/* Global variables and objects */
    volatile uint16_t CO_timer1ms = 0U; /* variable increments each millisecond */


/* main ***********************************************************************/
int main (void){
    CO_NMT_reset_cmd_t reset = CO_RESET_NOT;

    /* Configure microcontroller. */


    /* initialize EEPROM */


    /* increase variable each startup. Variable is stored in EEPROM. */
    OD_powerOnCounter++;


    while(reset != CO_RESET_APP){
/* CANopen communication reset - initialize CANopen objects *******************/
        CO_ReturnError_t err;
        uint16_t timer1msPrevious;

        /* disable timer and CAN interrupts */


        /* initialize CANopen */
        err = CO_init();
        if(err != CO_ERROR_NO){
            while(1);
            /* CO_errorReport(CO->em, CO_EM_MEMORY_ALLOCATION_ERROR, CO_EMC_SOFTWARE_INTERNAL, err); */
        }


        /* initialize variables */
        timer1msPrevious = CO_timer1ms;
        reset = CO_RESET_NOT;


        /* Configure Timer interrupt function for execution every 1 millisecond */


        /* Configure CAN transmit and receive interrupt */


        /* start CAN and enable interrupts */
        CO_CANsetNormalMode(ADDR_CAN1);


        while(reset == CO_RESET_NOT){
/* loop for normal program execution ******************************************/
            uint16_t timer1msDiff;

            CO_DISABLE_INTERRUPTS();
            timer1msDiff = CO_timer1ms - timer1msPrevious;
            timer1msPrevious = CO_timer1ms;
            CO_ENABLE_INTERRUPTS();


            /* CANopen process */
            reset = CO_process(CO, timer1msDiff);


            /* Process EEPROM */
        }
    }


/* program exit ***************************************************************/
    CO_DISABLE_INTERRUPTS();


    /* delete objects from memory */
    CO_delete();


    /* reset */
    return 0;
}


/* timer interrupt function executes every millisecond ************************/
void /* interrupt */ CO_TimerInterruptHandler(void){

    /* clear interrupt flag */


    CO_timer1ms++;


    CO_process_RPDO(CO);


    CO_process_TPDO(CO);


    /* verify timer overflow (is flag set again?) */
    if(0){
        CO_errorReport(CO->em, CO_EM_ISR_TIMER_OVERFLOW, CO_EMC_SOFTWARE_INTERNAL, 0U);
    }
}


/* CAN interrupt function *****************************************************/
void /* interrupt */ CO_CAN1InterruptHandler(void){
    CO_CANinterrupt(CO->CANmodule[0]);


    /* clear interrupt flag */
}
