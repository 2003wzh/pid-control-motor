#include "stm32f10x.h"                  // Device header

/**
  * ��    ������ʱ����ʱ��ʼ��
  * ��    ������
  * �� �� ֵ����
  */
void Timer_Init(void)
{
	/*����ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//����TIM2��ʱ��
	
	TIM_InternalClockConfig(TIM2);//����TIM2Ϊ�ڲ�ʱ��
	
	/*ʱ����Ԫ��ʼ��*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;              //����ṹ�����
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //ʱ�ӷ�Ƶ��ѡ�񲻷�Ƶ���˲������������˲���ʱ�ӣ���Ӱ��ʱ����Ԫ����
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //������ģʽ��ѡ�����ϼ���
	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1;                //�������ڣ���ARR��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;             //Ԥ��Ƶ������PSC��ֵ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //�ظ����������߼���ʱ���Ż��õ�
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);             //���ṹ���������TIM_TimeBaseInit������TIM3��ʱ����Ԫ
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);                            //�����ʱ�����±�־
	
	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);                       //�򿪸����ж���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                 //����
	
	NVIC_InitTypeDef NVIC_InitStructure;                            //��Щ�Ǵ��жϵģ���Ӧ�ö��ҾͲ�д��
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}
