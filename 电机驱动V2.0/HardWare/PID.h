#ifndef __PID_H
#define __PID_H

#include "stm32f10x.h"  // 根据需要包含的头文件

// PID结构体定义
typedef struct {
    float Kp;         // 比例系数
    float Ki;         // 积分系数
    float Kd;         // 微分系数
    float target;     // 目标值
    float current;    // 当前值（实际值）
    float error;      // 当前误差
    float prevError;  // 上一次的误差
    float integral;   // 积分项累积
    float derivative; // 微分项
    float output;     // 输出值
} PID_TypeDef;

// 函数声明
void PID_Init(PID_TypeDef *pid, float Kp, float Ki, float Kd);
float PID_Compute(PID_TypeDef *pid, float target, float current);

#endif
