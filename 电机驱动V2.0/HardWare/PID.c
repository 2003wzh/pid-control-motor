#include "stm32f10x.h"                  // Device header
#include "PID.h"
#include "Delay.h"
#include "motor1.h"
#include "usermotor.h"
#include "Encoder.h"
#include "Timer.h"
#include "OLED.h"

extern volatile  int16_t Speed;
volatile uint16_t counter;  // �������������ٶȼ���
extern PID_TypeDef motorPID;
// ��ʼ��PID�ṹ��
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

// ����PID���
float PID_Compute(PID_TypeDef *pid, float target, float current) {
    pid->target = target;
    pid->current = current;

    pid->error = pid->target - pid->current;
    pid->integral += pid->error;  // ����
    pid->derivative = pid->error - pid->prevError;  // ΢��

    // PID�������
    pid->output = (pid->Kp * pid->error) +
                  (pid->Ki * pid->integral) +
                  (pid->Kd * pid->derivative);

    // ������һ�����
    pid->prevError = pid->error;

    return pid->output;
}

void TIM2_IRQHandler(void) {
    static uint16_t k = 0; // ��̬����k�����ڱ�����������
    static int16_t speed[10] = {0};  // ����������ٶ�ֵ�����˲�
    uint16_t i, j, n, sum = 0, temp;
    
     if(TIM_GetITStatus(TIM2, TIM_FLAG_Update) == SET)
    {
		
        speed[k++] = ((float)(Encoder_Get() + counter * 65535)/1040) * 600;
        if(k == 10)
        {
             //ð������
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

             //ȥ����β�����м�8��ֵ��ƽ��ֵ
            for(n = 1; n < 9; n++)
            {
                sum += speed[n];
            }
            temp = (sum / 8);

            // һ�׵�ͨ�˲���ʹ�������������ض�
            Speed = (int16_t)(0.8f * temp) + (int16_t)(0.2f * Speed);
            k = 0;
        }
		// ���㵱ǰת�ٺ�Ŀ��ת��֮���PID���
		float output = PID_Compute(&motorPID, 400, Speed);

		// ���Ƶ���ٶ�
		CAR_GO((int)output);

        counter = 0;  // ���ü�����
        TIM_ClearFlag(TIM2, TIM_FLAG_Update);  // ����жϱ�־
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
