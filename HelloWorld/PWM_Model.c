/*
 * PWM_Model.c
 *
 *  Created on: 2018年1月29日
 *      Author: bobo
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "PWM_Model.h"

void PWM_Config(void)
{
     SysCtlPWMClockSet(SYSCTL_PWMDIV_8);  //SysClock/8=10M
     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
     SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_PWM0));
    GPIOPinConfigure(GPIO_PB4_M0PWM2);  // Gen 1
    GPIOPinConfigure(GPIO_PB5_M0PWM3);  // Gen 1
    GPIOPinConfigure(GPIO_PE4_M0PWM4);  // Gen 2
    GPIOPinConfigure(GPIO_PE5_M0PWM5);  // Gen 2
    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4|GPIO_PIN_5);
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4|GPIO_PIN_5);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_2,
                    PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenConfigure(PWM0_BASE, PWM_GEN_1,
                    PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, PWMPERIOD);  // sysClock:80M => PWMClock:10M => 10M/PWMPERIOD = 1khz(波形频率)
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1, PWMPERIOD);
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
    PWMOutputState(PWM0_BASE,PWM_OUT_4_BIT | PWM_OUT_5_BIT, true);
    PWMOutputState(PWM0_BASE,PWM_OUT_2_BIT | PWM_OUT_3_BIT, true);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2,1);  //%0  //B4
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3,1);  //%0  //B5
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,1);  //%0  //E4
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5,1);  //%0  //E5
}

//占空比设置
//int32_t Duty ：-10000<Val<10000
//PB6输出的占空比 Val/10000; PB7输出的占空比 自定义
//eg：PWMDutyCycleSet(5000) => PB6占空比为50%
// Val>0 : return true
// Val<0 : return false
//频率 ： 1Khz
bool PWMDutyCycleSet(int32_t Val)
{
    if(Val>=0)
        return true;   //正方向标识
    else
        return false;   //反方向标识
}


/* -100<=Duty<=100 占空比*/
void PWMOUTSet(int Duty1)
{
    int32_t PWMVal1,pwm1;
    PWMVal1 = (int)(Duty1*(PWMPERIOD/100));
    pwm1 = PWMVal1;
    if(pwm1 < 0)
        pwm1 = -PWMVal1;
    else if(pwm1 == 0)
        pwm1 = 1;
    pwm1 = pwm1 > PWMPERIOD ? PWMPERIOD : pwm1 ;
    if(PWMDutyCycleSet(PWMVal1))
   {
       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 1);
       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, (uint32_t)pwm1);
   }
   else
   {
       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2,  (uint32_t)pwm1);
       PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, 1);
   }
}





