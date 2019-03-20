/**
 *  pid.c
 *  Created on: 2019.3.16
 *  Author: llr
 */

#include "pid.h"

// �ǶȻ�PID����ֵ
float Kp_A =6.7;
float Ki_A = 0;
float Kd_A =18.0;

// �ٶȻ�PID����ֵ
float Kp_P =15;
float Ki_P = 0;
float Kd_P =0.075;

float Kp_L =15;
float Ki_L = 0;
float Kd_L =0.075;

extern float pwm_duty;


/**
 * λ��ʽPID
 * �ǶȻ�
 * @param SetPoint  Ŀ��λ��
 * @param Nowpoint  ��ǰλ��
 * @return ���PIDֵ
 */
float PIDAngle(float SetSpeed,float NowSpeed)
{
    float Speed=0;
    static float Error_always;
    static float LastError;
    //���ֵ����
    float Error         =  SetSpeed - NowSpeed;
    float d_Error       =  Error - LastError;

    LastError     =  Error;
    Error_always +=  Error;

    //PID�޷�
    if(Error_always>55)
    {
      Error_always=55;
    }
    else if(Error_always<-55)
    {
      Error_always=-55;
    }

    Speed = Kp_A * Error +  Ki_A * Error_always +  Kd_A * d_Error;

    if(Speed > 80)
    {
      Speed = 80;
    }
    if(Speed < -80)
    {
      Speed = -80;
    }
    return Speed;
}

/**
 * ����ʽPID
 * �ٶȻ�
 * @param SetPoint
 * @param NowPoint
 * @return ���PWMֵ
 */
float PIDSpeed2(float SetSpeed,float NowSpeed)
{
    float Speed=0;
    static float L_Error;
    static float LL_Error;

    float Error     =  SetSpeed - NowSpeed;
    float d_Error   =  Error - L_Error;
    float dd_Error  =  Error + LL_Error - L_Error*2;
    L_Error   =  Error;
    LL_Error  =  L_Error;

    Speed       =  NowSpeed + Kp_P * d_Error + Ki_P * Error + Kd_P * dd_Error;

    if(Speed > 80)
    {
        Speed = 80;
    }
    if(Speed < -80)
    {
        Speed = -80;
    }

    return Speed;
}

/**
 * λ�û�
 * @param SetSpeed
 * @param NowSpeed
 * @return ���PWMֵ
 */
float PIDSpeed(float SetSpeed, float NowSpeed)//λ�û�
{
    static float Speed_LPF , L_Error;
    float Speed=0;

    float Error      =  SetSpeed - NowSpeed ;

    Speed_LPF *=  0.8;
    Speed_LPF +=  Error*0.2;

    float d_Error    =  Speed_LPF-L_Error;
    L_Error    =  Speed_LPF;

    Speed      =  Kp_L*Speed_LPF + Kd_L * d_Error;

    return Speed;
}
