#ifndef __MOTOR1_H
#define __MOTOR1_H

#define MOTOR_RCC RCC_APB2Periph_GPIOA
#define MOTOR_PROT GPIOA
#define MOTOR_A1 GPIO_Pin_6
#define MOTOR_A2 GPIO_Pin_7



void PWM_Init(uint16_t arr,uint16_t psc);

#endif
