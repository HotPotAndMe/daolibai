/*
 * uart.c
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
#include "inc/hw_ints.h"


uint8_t rx_data;
int buffer[9];
double pid=0;
extern double Espeed;;//0
int cmd;
////////////////////
//uint8_t rx_data;
//uint8_t flag=0;
//uint8_t i=0;
//uint8_t num[20];
/******************串口配置和服务函数**********************/
void ConfigureUART0(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 115200 , 16000000);
}

void ConfigureUART1(void)
{
     SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
     GPIOPinConfigure(GPIO_PB0_U1RX );
     GPIOPinConfigure(GPIO_PB1_U1TX);
     GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
     UARTConfigSetExpClk(UART1_BASE,SysCtlClockGet(), 115200,
                                (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                 UART_CONFIG_PAR_NONE));
     IntEnable(INT_UART1);
     UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);

}

void UART1_IntHandler(void)
{
    uint32_t ui32Status;
    int t=0;
    ui32Status = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ui32Status);
    while(UARTCharsAvail(UART1_BASE))
    {
        rx_data = (uint8_t)UARTCharGetNonBlocking(UART1_BASE);
//        UARTprintf("c=%c\n",rx_data);
        if(t==0)
        {
            buffer[0]=rx_data;
            //t=1;
        }
        else if(t==1)
        {
            buffer[1]=rx_data;
            //t=2;
        }
        else
        {
            buffer[t]=rx_data-48;
        }
        t++;
    }
    pid=buffer[2]*100+buffer[3]*10+buffer[4]+buffer[6]*0.1+buffer[7]*0.01+buffer[8]*0.001;

//    UARTprintf("pid:%d\n",(int)(pid*100));
   if(buffer[0] == 'a')
   {
        if(buffer[1] == 'p')
        {
//            Kp=pid;
//            UARTprintf("kp:%d\n",(int)(Kp*100));
//            UARTprintf("ki:%d\n",(int)(Ki*100));
//            UARTprintf("kd:%d\n",(int)(Kd*100));
//            UARTprintf("val_p:%d\n",(int)(val_p*100));
//            UARTprintf("val_i:%d\n",(int)(val_i*100));
//            UARTprintf("val_d:%d\n",(int)(val_d*100));
//            UARTprintf("Espeed:%d\n",(int)(Espeed*100));
        }
        else if(buffer[1]=='i')
        {
//            Ki=pid;
//            UARTprintf("kp:%d\n",(int)(Kp*100));
//            UARTprintf("ki:%d\n",(int)(Ki*100));
//            UARTprintf("kd:%d\n",(int)(Kd*100));
//            UARTprintf("val_p:%d\n",(int)(val_p*100));
//            UARTprintf("val_i:%d\n",(int)(val_i*100));
//            UARTprintf("val_d:%d\n",(int)(val_d*100));
//            UARTprintf("Espeed:%d\n",(int)(Espeed*100));
        }
        else if(buffer[1]=='d')
        {
//            Kd=pid;
//            UARTprintf("kp:%d\n",(int)(Kp*100));
//            UARTprintf("ki:%d\n",(int)(Ki*100));
//            UARTprintf("kd:%d\n",(int)(Kd*100));
//            UARTprintf("val_p:%d\n",(int)(val_p*100));
//            UARTprintf("val_i:%d\n",(int)(val_i*100));
//            UARTprintf("val_d:%d\n",(int)(val_d*100));
//            UARTprintf("Espeed:%d\n",(int)(Espeed*100));
        }
   }
   else if(buffer[0] == 'b')
   {
          if(buffer[1] == 'p')
          {
//              val_p=pid;
//              UARTprintf("kp:%d\n",(int)(Kp*100));
//              UARTprintf("ki:%d\n",(int)(Ki*100));
//              UARTprintf("kd:%d\n",(int)(Kd*100));
//              UARTprintf("val_p:%d\n",(int)(val_p*100));
//              UARTprintf("val_i:%d\n",(int)(val_i*100));
//              UARTprintf("val_d:%d\n",(int)(val_d*100));
//              UARTprintf("Espeed:%d\n",(int)(Espeed*100));
          }
          else if(buffer[1]=='i')
          {
//              val_i=pid;
//              UARTprintf("kp:%d\n",(int)(Kp*100));
//              UARTprintf("ki:%d\n",(int)(Ki*100));
//              UARTprintf("kd:%d\n",(int)(Kd*100));
//              UARTprintf("val_p:%d\n",(int)(val_p*100));
//              UARTprintf("val_i:%d\n",(int)(val_i*100));
//              UARTprintf("val_d:%d\n",(int)(val_d*100));
//              UARTprintf("Espeed:%d\n",(int)(Espeed*100));
          }
          else if(buffer[1]=='d')
          {
//              val_d=pid;
//              UARTprintf("kp:%d\n",(int)(Kp*100));
//              UARTprintf("ki:%d\n",(int)(Ki*100));
//              UARTprintf("kd:%d\n",(int)(Kd*100));
//              UARTprintf("val_p:%d\n",(int)(val_p*100));
//              UARTprintf("val_i:%d\n",(int)(val_i*100));
//              UARTprintf("val_d:%d\n",(int)(val_d*100));
//              UARTprintf("Espeed:%d\n",(int)(Espeed*100));
          }
          else if(buffer[1]=='e')
          {
//                Espeed=pid;
//                UARTprintf("kp:%d\n",(int)(Kp*100));
//                UARTprintf("ki:%d\n",(int)(Ki*100));
//                UARTprintf("kd:%d\n",(int)(Kd*100));
//                UARTprintf("val_p:%d\n",(int)(val_p*100));
//                UARTprintf("val_i:%d\n",(int)(val_i*100));
//                UARTprintf("val_d:%d\n",(int)(val_d*100));
//                UARTprintf("Espeed:%d\n",(int)(Espeed*100));
          }
   }
   else
   {
       ;
   }

    for(t=0;t<9;t++)
    {
        buffer[t] = 0;
    }
}


//void UART1_IntHandler(void)
//{
//    uint32_t ui32Status;
//    int t=0;
//    ui32Status = UARTIntStatus(UART1_BASE, true);
//    UARTIntClear(UART1_BASE, ui32Status);
//    while(UARTCharsAvail(UART1_BASE))
//    {
//        rx_data = (uint8_t)UARTCharGetNonBlocking(UART1_BASE);
////        UARTprintf("c=%c\n",rx_data);
//        if(rx_data=='4')
//        {
//            val_p+=0.1;
//        }
//        else if(rx_data=='1')
//        {
//            val_p-=0.1;
//            UARTprintf("c=1\n");
//        }
//        else if(rx_data=='2')
//        {
//             val_i-=0.1;
//        }
//        else if(rx_data=='5')
//        {
//             val_i-=0.1;
//         }
//        else if(rx_data=='a')
//        {
//              Espeed=200;
//        }
//        else if(rx_data=='b')
//        {
//               Espeed=100;
//        }
//        if(t==0)
//        {
//            buffer[0]=rx_data;
//        }
//        else
//        {
//            buffer[t]=rx_data-48;
//        }
//        t++;
//    }
//    pid=buffer[1]*100+buffer[2]*10+buffer[3]+buffer[5]*0.1+buffer[6]*0.01;
//    UARTprintf("pid:%d\n",(int)(pid*100));
//
//    if(buffer[0] == 'p')
//    {
//        Kp=pid;
//        UARTprintf("kp:%d\n",(int)(Kp*100));
//        UARTprintf("ki:%d\n",(int)(Ki*100));
//        UARTprintf("kd:%d\n",(int)(Kd*100));
//    }
//    else if(buffer[0]=='i')
//    {
//        Ki=pid;
//        UARTprintf("kp:%d\n",(int)(Kp*100));
//        UARTprintf("ki:%d\n",(int)(Ki*100));
//        UARTprintf("kd:%d\n",(int)(Kd*100));
//    }
//    else if(buffer[0]=='d')
//    {
//        Kd=pid;
//        UARTprintf("kp:%d\n",(int)(Kp*100));
//        UARTprintf("ki:%d\n",(int)(Ki*100));
//        UARTprintf("kd:%d\n",(int)(Kd*100));
//    }
//
//
//    for(t=0;t<8;t++)
//    {
//        buffer[t] = 0;
//    }
//}

/*************************************************************/
/*
 void UART1_IntHandler(void)
{
   uint32_t ui32Status;
   ui32Status = UARTIntStatus(UART1_BASE, true);
   UARTIntClear(UART1_BASE,ui32Status);

//   int32_t ui32Data;
//   UARTprintf("%d\n", ui32Data );      //可以用来判断是否进入到中断

 //判断接收数据
   while(UARTCharsAvail(UART2_BASE))
   {
       rx_data = (uint8_t)UARTCharGetNonBlocking(UART2_BASE);  //八位一个字符
       if(rx_data=='r')
       {
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
       }
       else if(rx_data=='b')
       {
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, ~GPIO_PIN_1);
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

       }
       else if(rx_data=='e')
              {
                  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, ~GPIO_PIN_2);

              }
       else{
            //if(rx_data>=48 && rx_data<=57)
           if(rx_data>=43 && rx_data<=57)
              {
                         flag=1;
                         num[i]=rx_data;
                         i++;
                         GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
              }
           else
              {
               if(flag==1)
               {
                   UARTprintf("%s\n", num );
                   flag=0;
                   i=0;
               }
              }
           }
   }

}
*/
//void UART1_IntHandler(void)
//{
//        int t=0;
//        uint32_t ui32Status;
//       ui32Status=UARTIntStatus(UART1_BASE,true);
//       UARTIntClear(UART1_BASE,ui32Status);
//       while(UARTCharsAvail(UART1_BASE))
//       {
//           buffer[t]=(uint8_t)(UARTCharGetNonBlocking(UART1_BASE));
//           t++;
//           cmd=((int)buffer[1]-48)*100+((int)buffer[2]-48)*10+(int)buffer[3]-48;
//
//           if(t>4)
//           {
//              t=0;
//           }
//           UARTprintf("pid:%d\n",cmd);
////           if(buffer[0] == '+')
////           {
////               cmd1=cmd;
////               if(cmd>=90&&cmd<120)  power=2.1;   //5.5--9
////               if(cmd>=120&&cmd<150)  power=2.8;
////               if(cmd>=150&&cmd<260)  power=3.8;
////               if(cmd>=260&&cmd<310)  power=4.6;
////               if(cmd>=310&&cmd<380)  power=5.0;
////               if(cmd>=380&&cmd<=400)  power=5.2;
////               if(cmd>400&&cmd<=450)  power=5.95;
////               duty=cmd1/power;
////               PWMOUTSet(duty);
////           }
////           if(buffer[0] == '-')
////           {
////                cmd1=cmd*(-1);
////                if(cmd>=90&&cmd<120)  power=2.1;   //5.5--9
////                if(cmd>=120&&cmd<150)  power=2.8;
////                if(cmd>=150&&cmd<260)  power=3.8;
////                if(cmd>=260&&cmd<310)  power=4.6;
////                if(cmd>=310&&cmd<380)  power=5.0;
////                if(cmd>=380&&cmd<=400)  power=5.2;
////                if(cmd>400&&cmd<=450)  power=5.95;
////                duty=cmd1/power;
////               PWMOUTSet(duty);
//
//
//       }
//}
