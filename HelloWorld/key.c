/*
 * key.c
 *
 *  Created on: 2018年5月8日
 *      Author: wanyu
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/pin_map.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"
#include "driverlib/fpu.h"
#include "driverlib/qei.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/hw_gpio.h"

#include "key.h"

/************************按键初始化和检测******************/
void key_init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK ) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR ) |= GPIO_PIN_0;
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

int key_detection_PF4()                         //按键按下返回1
{
    uint8_t ReadPin;
    ReadPin = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
    if((ReadPin&GPIO_PIN_4) != GPIO_PIN_4)
    {
        SysCtlDelay(20*(SysCtlClockGet()/3000));
        ReadPin = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4);
        if((ReadPin&GPIO_PIN_4) != GPIO_PIN_4)
        {
            while(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4));
            return 1;
        }
    }
}
int key_detection_PF0()                        //按键按下返回1
{
    uint8_t ReadPin;
    ReadPin = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
    if((ReadPin&GPIO_PIN_0) != GPIO_PIN_0)
    {
        SysCtlDelay(20*(SysCtlClockGet()/3000));
        ReadPin = GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0);
        if((ReadPin&GPIO_PIN_0) != GPIO_PIN_0)
        {
            while(!GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0));
            return 1;
        }
    }
}
/*************************************************************/
