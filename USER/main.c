#include "stm32f10x_conf.h"
#include "GPIO.h"

void delay(u16 time)
{
    u16 i=0;
    while(time--)
    {
      i=12000;  //�Լ�����
      while(i--);
    }
}

void EXTI0_IRQHandler(void)
{
    PAout(9)=!PAout(9);
//    delay(10);
    EXTI_ClearITPendingBit(EXTI_Line2);
}
int main()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    //��ʼ���ܽ�
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  //ѡ���ж����ȼ����飬�˴�ѡ��0��ʹ0����ռʽ���ȼ���16�������ȼ�  
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;        //��Ӧ��ͨ�����ã��˴�ѡ���ж�ͨ��  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //��ռʽ���ȼ�����  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //�����ȼ�����  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //ʱ��ͨ��  
    NVIC_Init(&NVIC_InitStructure);                             //ʹ�ýṹ���������  
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    PAout(9)=1;
    //��ʼ��PA09����ߵ�ƽ,���
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    //��ʼ��PD02����
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
    //�����ж�Դ
   
    EXTI_DeInit();
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    //�����ж��½��ش���

    while(1)
    {
        delay(500);
    }
    return 0;
}