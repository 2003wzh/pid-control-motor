#include "stm32f10x.h"                  // Device header
#include "PID.h"
#include "Delay.h"
#include "motor1.h"
#include "usermotor.h"
#include "Encoder.h"
#include "Timer.h"
#include "OLED.h"

extern volatile  int16_t Speed;
volatile uint16_t counter;  // 计数器，用于速度计算
extern PID_TypeDef motorPID;
// 初始化PID结构体
void PID_Init(PID_TypeDef *pid, float Kp, float Ki, float Kd) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->target = 0;
    pid->current = 0;
    pid->error = 0;
    pid->prevError = 0;
    pid->integral = 0;
    pid->derivative = 0;
    pid->output = 0;
}

// 计算PID输出
float PID_Compute(PID_TypeDef *pid, float target, float current) {
    pid->target = target;
    pid->current = current;

    pid->error = pid->target - pid->current;
    pid->integral += pid->error;  // 积分
    pid->derivative = pid->error - pid->prevError;  // 微分

    // PID输出计算
    pid->output = (pid->Kp * pid->error) +
                  (pid->Ki * pid->integral) +
                  (pid->Kd * pid->derivative);

    // 更新上一次误差
    pid->prevError = pid->error;

    return pid->output;
}

void TIM2_IRQHandler(void) {
    static uint16_t k = 0; // 静态变量k，用于保存数组索引
    static int16_t speed[10] = {0};  // 保存最近的速度值用于滤波
    uint16_t i, j, n, sum = 0, temp;
    
     if(TIM_GetITStatus(TIM2, TIM_FLAG_Update) == SET)
    {
		
        speed[k++] = ((float)(Encoder_Get() + counter * 65535)/1040) * 600;
        if(k == 10)
        {
             //冒泡排序
            for(i = 0; i < k - 1; i++)
            {
                for(j = 0; j < k - i - 1; j++)
                {
                    if(speed[j] > speed[j+1])
                    {
                        temp = speed[j];
                        speed[j] = speed[j+1];
                        speed[j+1] = temp;
                    }
                }
            }

             //去掉首尾，求中间8个值的平均值
            for(n = 1; n < 9; n++)
            {
                sum += speed[n];
            }
            temp = (sum / 8);

            // 一阶低通滤波，使用整数运算避免截断
            Speed = (int16_t)(0.8f * temp) + (int16_t)(0.2f * Speed);
            k = 0;
        }
		// 计算当前转速和目标转速之间的PID输出
		float output = PID_Compute(&motorPID, 400, Speed);

		// 控制电机速度
		CAR_GO((int)output);

        counter = 0;  // 重置计数器
        TIM_ClearFlag(TIM2, TIM_FLAG_Update);  // 清除中断标志
    }
}

int TIM1_UP_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM1, TIM_FLAG_Update) == SET)
    {
       counter++;
        TIM_ClearFlag(TIM1, TIM_FLAG_Update);
    }
	return 0;
}
