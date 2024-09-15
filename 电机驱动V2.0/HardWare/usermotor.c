#include "stm32f10x.h"                  // Device header
#include "motor1.h"

#define MOTOR_GO()            {GPIO_ResetBits(MOTOR_PORT, MOTOR_A2);}
#define MOTOR_BACK()          {GPIO_ResetBits(MOTOR_PORT, MOTOR_A1);}

#define MOTOR_PWM_GO(Speed)   {TIM_SetCompare1(TIM3, Speed);}
#define MOTOR_PWM_BACK(Speed) {TIM_SetCompare2(TIM3, Speed);}

void CAR_GO(int Speed){
	GPIO_ResetBits(GPIOA, MOTOR_A2);
	MOTOR_PWM_GO(Speed);
}

void CAR_BACK(int Speed){
	GPIO_ResetBits(GPIOA, MOTOR_A1);
	MOTOR_PWM_BACK(Speed);
}
