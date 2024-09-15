#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "motor1.h"
#include "usermotor.h"
#include "Encoder.h"
#include "Timer.h"
#include "OLED.h"
#include "PID.h"

// 全局变量定义
volatile int16_t Speed;
PID_TypeDef motorPID;

int main(void)
{
    PWM_Init(10000, 0);
    Encoder_Init();
    Timer_Init();
    OLED_Init();
    OLED_ShowString(1,1,"Speed:");
    
	 // 初始化PID控制器
    PID_Init(&motorPID, 7, 0.5, 0.1);
    while(1)
    {
        OLED_ShowSignedNum(1,7,Speed,5);
    }
}

