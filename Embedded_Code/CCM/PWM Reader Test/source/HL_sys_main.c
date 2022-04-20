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
#include "HL_het.h"
#include "HL_gio.h"
#include "HL_sys_core.h"
#include "HL_rti.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
    hetSIGNAL_t signal1, signal2;
    int flag = 0;
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    hetInit();
    gioInit();
    rtiInit();

    signal1.duty = 25;
    signal1.period = 10000;

    signal2.duty = 25;
    signal2.period = 10000;

    pwmSetSignal(hetRAM1, pwm0, signal1);
    pwmSetSignal(hetRAM1, pwm1, signal2);
    gioSetBit(hetPORT1, 16, 1);

    rtiEnableNotification(rtiREG1, rtiNOTIFICATION_COMPARE0);
    _enable_interrupt_();

    rtiStartCounter(rtiREG1, rtiCOUNTER_BLOCK0);


    while(1);
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void rtiNotification(rtiBASE_t *rtiREG, uint32 notification)
{
    /*if(flag == 0)
    {
        signal1.duty = 75;
        signal2.duty = 75;
        pwmSetSignal(hetRAM1, pwm0, signal1);
        pwmSetSignal(hetRAM1, pwm1, signal2);
        flag = 1;
    }
    else
    {
        signal1.duty = 25;
        signal2.duty = 25;
        pwmSetSignal(hetRAM1, pwm0, signal1);
        pwmSetSignal(hetRAM1, pwm1, signal2);
        flag = 0;
    }*/

    if(flag == 0)
    {
        gioSetBit(hetPORT1, 16, 0);

        pwmSetDuty(hetRAM1, pwm0, 75);
        pwmSetDuty(hetRAM1, pwm1, 75);
        flag = 1;
    }
    else
    {
        pwmSetDuty(hetRAM1, pwm0, 25);
        pwmSetDuty(hetRAM1, pwm1, 25);
        gioSetBit(hetPORT1, 16, 1);
        flag = 0;
    }


}
/* USER CODE END */