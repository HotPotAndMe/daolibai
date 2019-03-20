/**
 * pid.h
 * Created on: 2019.3.17
 * Author: llr
 */

#ifndef PID_H_
#define PID_H_

extern float Kp_A;
extern float Kd_A;
extern float Ki_A;
extern float Kp_P;
extern float Kd_P;
extern float Ki_P;
extern float Kp_L;
extern float Kd_L;
extern float Ki_L;

extern float PIDAngle(float SetSpeed,float NowSpeed);
extern float PIDSpeed2(float SetSpeed,float NowSpeed);
extern float PIDSpeed(float SetSpeed, float NowSpeed);


#endif
