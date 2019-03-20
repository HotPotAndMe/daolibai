/*
 * PWM_Model.h
 *
 *  Created on: 2018Äê1ÔÂ29ÈÕ
 *      Author: bobo
 */

#ifndef PWM_MODEL_H_
#define PWM_MODEL_H_


#define PWMPERIOD   10000

void PWM_Config(void);
bool PWMDutyCycleSet(int32_t Val);
void PWMOUTSet(int Duty1);



#endif /* PWM_MODEL_H_ */
