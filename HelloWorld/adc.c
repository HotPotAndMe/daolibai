/*
 * adc.c
 *
 *  Created on: 2018年5月8日
 *      Author: wanyu
 */
/*
 * adc.c
 *
 *  Created on: 2018年1月30日
 *      Author: 89640
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/fpu.h"
#include "driverlib/adc.h"

#include "adc.h"


int32_t Ch0Value, Ch1Value;
volatile bool  bDataReady ;


void ADC0IntHander(void)
{
    uint32_t ui32AdcValue[2] = {0};
    ADCIntClear(ADC0_BASE, 0);
    ADCSequenceDataGet(ADC0_BASE, 0, ui32AdcValue);
    Ch0Value = ((float)ui32AdcValue[0])*(3300.0/4096.0);
    Ch1Value = ((float)ui32AdcValue[1])*(3300.0/4096.0);
//    UARTprintf("Ch1Value：%d\n", Ch1Value);
    bDataReady = true;
}

void ADC_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0));
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2 |GPIO_PIN_3);
    ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PIOSC | ADC_CLOCK_RATE_FULL, 1);
    ADCReferenceSet(ADC0_BASE, ADC_REF_INT);
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0);
    ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH1 |ADC_CTL_END | ADC_CTL_IE);
    ADCHardwareOversampleConfigure(ADC0_BASE, 64);
    ADCSequenceEnable(ADC0_BASE, 0);
    ADCIntRegister(ADC0_BASE, 0, ADC0IntHander);
    ADCIntEnable(ADC0_BASE, 0);
    IntPrioritySet (INT_ADC0SS0, 0x0);
    IntEnable(INT_SSI0);
}

void ADC_Trig(void)
{
    ADCProcessorTrigger(ADC0_BASE, 0);
}

int getangle()
{
    double angle0;
    ADC_Trig();
    while(true != bDataReady) ;
    bDataReady = false;
    if(Ch1Value>=0 && Ch1Value<=1650 )
    {
        angle0=(Ch1Value*172.5/1650 + 7.5)*(-1);
    }
    else
    {
        angle0=353-(Ch1Value*172.5/1650);
    }
    return angle0;
}


