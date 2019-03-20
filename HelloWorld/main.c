/**
 *  pid.c
 *  Created on: 2019.3.17
 *  Author: llr
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
#include "inc/hw_ints.h"
#include "driverlib/adc.h"
#include "drivers/oled.h"
#include "inc/hw_i2c.h"
#include "inc/hw_timer.h"
#include "driverlib/timer.h"

#include "led.h"
#include "key.h"
#include "uart.h"
#include "adc.h"
#include "PWM_Model.h"
#include "QEI_Model.h"
#include "pid.h"

//����
uint8_t count,count1;      //PF4��PF0����״̬����

//��������ֵ
double  Velocity;                //�ٶ�
double  Angle;                   //�Ƕ�

//����
void delay_ms(uint16_t x);
void init_all();
void Timer_config();
void Timer0BIntHandler();

int main(void)
{
    while(1)
    {
 /*************************��������*******************************/
        if(key_detection_PF4()==1)               //����PF4��������ģʽ�����ڵ���ģʽ
        {
            count=count+1;
            if(count>4)
            {
               count=0;
            }
        }
        if(key_detection_PF0()==1)               //����PF0��������ģʽ�����ڿ�����ǰģʽ
        {
            count1=count1+1;
            if(count1>4)
            {
               count1=0;
            }
        }

/*********************ģʽ0����״̬****************************/
        if(count==0)                                        //ģʽ0��none
       {
           none_led();
       }


/***************ģʽ1���ڸ˰ڶ�����-60��-60��*****************/
        if(count==1)
        {
            TimerDisable(TIMER0_BASE, TIMER_B);
            red_led();                                   //ָʾ��������ʾ
            if(count1==1)
            {
                 PWMOUTSet(25);
                 delay_ms(400);
                 PWMOUTSet(0);
                 delay_ms(20);
                 PWMOUTSet(-25);
                 delay_ms(400);
                 PWMOUTSet(-0);
                 delay_ms(20);
            }
        }


/*******************ģʽ2���´�λ��������Բ���˶�***************/
        if(count==2)
        {
            TimerDisable(TIMER0_BASE, TIMER_B);
            int j;
            PWMOUTSet(0);
            blue_led();
            if(count1==2)
            {
                for(j=0;j<2;j++)
                {
                   PWMOUTSet(85);
                   delay_ms(330);
                   PWMOUTSet(0);
                   delay_ms(10);
                   PWMOUTSet(-85);
                   delay_ms(330);
                   PWMOUTSet(-0);
                  delay_ms(10);
                }
                for(j=0;j<40;j++)
                {
                  PWMOUTSet(-80);
                  delay_ms(190);
                  PWMOUTSet(-0);
                  delay_ms(20);
                  PWMOUTSet(80);
                  delay_ms(190);
                  PWMOUTSet(0);
                  delay_ms(20);
                }
            }
        }


/****************ģʽ3������165����ڣ����ֵ���*************/
        if(count==3)
        {
            green_led();
            TimerEnable(TIMER0_BASE, TIMER_B);
        }



/********ģʽ4���´�λ����ڣ����ֵ�����³���Բ���*******/
        if(count==4)
        {
            if(count1==4)
            {
            purple_led();
//            if(count1==4)
//            {
//               PWMOUTSet(80);
//               delay_ms(250);
//               PWMOUTSet(0);
//               delay_ms(200);
//               PWMOUTSet(-80);
//               delay_ms(250);
//               PWMOUTSet(-0);
//               delay_ms(5000);
//            }
            }
        }

    }
}



/*
 * ��ʱ����
 */
void delay_ms(uint16_t x)
{
    SysCtlDelay(x*(SysCtlClockGet()/3000));
}

/*
 * ϵͳ���ó�ʼ��
 */
void init_all()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL
                      |SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);//80Mhz
        FPULazyStackingEnable();
        FPUEnable();
        led_init();
        key_init();
        ADC_Init();
        OLED_I2CInit();
        delay_ms(100);
        OLED_ClearScreen();
        ConfigureUART0();
        ConfigureUART1();
        PWM_Config();
        QEI_Config();
        Timer_config();
        IntMasterEnable();
}

/*
 * ��ʱ����ʼ��
 */
void Timer_config()
{
               SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
               TimerClockSourceSet(TIMER0_BASE, TIMER_CLOCK_SYSTEM);
               TimerPrescaleSet(TIMER0_BASE, TIMER_B, 8-1);
               TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC);
               //TimerLoadSet(TIMER0_BASE, TIMER_B, ((SysCtlClockGet() / (TimerPrescaleGet(TIMER0_BASE, TIMER_B) + 1)) / 100) - 1);
               TimerLoadSet(TIMER0_BASE, TIMER_B, 50000);
               IntMasterEnable();
               TimerIntEnable(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
               IntEnable(INT_TIMER0B);
               TimerIntRegister(TIMER0_BASE, TIMER_B, Timer0BIntHandler);
               TimerDisable(TIMER0_BASE, TIMER_B);
}
/*
 * ��ʱ���жϺ���
 */
void Timer0BIntHandler(void)
{
    //��ʱ����״̬
    uint32_t ui32Status = TimerIntStatus(TIMER0_BASE, true);
    TimerIntClear(TIMER0_BASE, ui32Status);

    //��ȡ����������
    QEIIntDisable(QEI0_BASE,QEI_INTDIR | QEI_INTTIMER);
    if(qei_data_array[0].velocity>0)
    {
        Velocity = (int)(qei_data_array[0].velocity*0.3462+0.5); //x��/s
    }
    else
    {
        Velocity = (int)(qei_data_array[0].velocity*0.3462-0.5); //x��/s
    }
    QEIIntEnable(QEI0_BASE,QEI_INTDIR | QEI_INTTIMER);

    //��ȡ�Ƕ�
    Angle = getangle();
    if(Angle<0)
    {
          Angle=180+(Angle+180);
                 Angle=(int)(Angle*100)/100;
    }

    //PID����
    if(count==3)
    {
       if(count1==3)
       {
            float pwm_duty=0;
            OLED_DisplayChar(100,40,'3');
            if(Angle>=110&&Angle<=250)
            {

                //�ﵽ�Ƕȸ���ֹͣ
                if(Angle<182&&Angle>178)
                {
                    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 1);
                    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, 1);
                    pwm_duty=0;
                }

                //����PID
                float ral_1,ral_2;
                ral_1=PIDAngle(179,Angle);
                ral_2=PIDSpeed2(0,Velocity);
                pwm_duty=(ral_1+ral_2);
                if (pwm_duty>=80)
                   pwm_duty = 80;
                if (pwm_duty<=-80)
                   pwm_duty = -80;

                //������
                PWMOUTSet((int)(pwm_duty));
            }
            else
            {
               PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, 1);
               PWMPulseWidthSet(PWM0_BASE, PWM_OUT_3, 1);
            }
       }
   }
}
