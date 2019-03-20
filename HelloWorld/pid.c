/**
 *  pid.c
 *  Created on: 2019.3.16
 *  Author: llr
 */

#include "pid.h"

// 角度环PID参数值
float Kp_A =6.7;
float Ki_A = 0;
float Kd_A =18.0;

// 速度环PID参数值
float Kp_P =15;
float Ki_P = 0;
float Kd_P =0.075;

float Kp_L =15;
float Ki_L = 0;
float Kd_L =0.075;

extern float pwm_duty;


/**
 * 位置式PID
 * 角度环
 * @param SetPoint  目标位置
 * @param Nowpoint  当前位置
 * @return 输出PID值
 */
float PIDAngle(float SetSpeed,float NowSpeed)
{
    float Speed=0;
    static float Error_always;
    static float LastError;
    //误差值计算
    float Error         =  SetSpeed - NowSpeed;
    float d_Error       =  Error - LastError;

    LastError     =  Error;
    Error_always +=  Error;

    //PID限幅
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
 * 增量式PID
 * 速度环
 * @param SetPoint
 * @param NowPoint
 * @return 输出PWM值
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
 * 位置环
 * @param SetSpeed
 * @param NowSpeed
 * @return 输出PWM值
 */
float PIDSpeed(float SetSpeed, float NowSpeed)//位置环
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
