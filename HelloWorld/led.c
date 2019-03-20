/*
 * led.c
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

#include "led.h"

/***************************LED初始化*********************/
void led_init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3|GPIO_PIN_2|GPIO_PIN_1);
}

void none_led()
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0x00);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
}
void red_led()
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
}

void blue_led()
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0x00);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
}

void green_led()
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0x00);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x00);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
}

void purple_led()
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
}
/*************************************************************/

