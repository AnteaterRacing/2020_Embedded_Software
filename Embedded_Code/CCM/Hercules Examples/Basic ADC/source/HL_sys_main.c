/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
#include "HL_sci.h"
#include "HL_adc.h"
#include "HL_rti.h"
#include "HL_sys_core.h"
#include "stdlib.h"
#include "stdio.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    //Initializations
    sciInit();
    adcInit();
    rtiInit();

    //Set up RIT
    rtiEnableNotification(rtiREG1, rtiNOTIFICATION_COMPARE0);
    _enable_IRQ_interrupt_();


    //Start RIT
    rtiStartCounter(rtiREG1, rtiCOUNTER_BLOCK0);

    //LOOP
    while(1);

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void rtiNotification(rtiBASE_t *rtiREG, uint32 notification)
{
    //Variable Declarations
    adcData_t adc_data;
    adcData_t *adc_data_ptr = &adc_data;
    unsigned int adcValue, charNum;
    unsigned char command[8];

    //Run ADC
    adcStartConversion(adcREG1, adcGROUP1);             //Start ADC conversion
    while(!adcIsConversionComplete(adcREG1, adcGROUP1));  //Wait for conversion to complete
    adcGetData(adcREG1, 1U, adc_data_ptr);              //retrieve the data from the group 1 buffer

    adcValue = (unsigned int)adc_data_ptr->value;
    printf("value: %d\n", adcValue);

    //Send it over serial monitor
    charNum = ltoa(adcValue, (char*)command);               //convert adcValue to string and store it in command
    sciSend(sciREG1, 11, (unsigned char *)"ADC Pin 0: ");   //Send descriptor string over SCI
    sciSend(sciREG1, charNum, command);                     //Send command string (containing ADC value) over SCI
    sciSend(sciREG1, 2, (unsigned char *)"\r\n");           //Send terminating characters


}

/* USER CODE END */
