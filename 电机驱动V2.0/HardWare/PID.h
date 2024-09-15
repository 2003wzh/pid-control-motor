#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"  // ������Ҫ������ͷ�ļ�

// PID�ṹ�嶨��
typedef struct {
    float Kp;         // ����ϵ��
    float Ki;         // ����ϵ��
    float Kd;         // ΢��ϵ��
    float target;     // Ŀ��ֵ
    float current;    // ��ǰֵ��ʵ��ֵ��
    float error;      // ��ǰ���
    float prevError;  // ��һ�ε����
    float integral;   // �������ۻ�
    float derivative; // ΢����
    float output;     // ���ֵ
} PID_TypeDef;

// ��������
void PID_Init(PID_TypeDef *pid, float Kp, float Ki, float Kd);
float PID_Compute(PID_TypeDef *pid, float target, float current);

#endif
