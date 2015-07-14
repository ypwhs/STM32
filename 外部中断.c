#include "stm32f10x_conf.h"
#include "GPIO.h"

void delay(u16 time)
{
    u16 i=0;
    while(time--)
    {
      i=12000;  //自己定义
      while(i--);
    }
}

void EXTI2_IRQHandler(void)
{
    PAout(9)=!PAout(9);
    EXTI_ClearITPendingBit(EXTI_Line2);
}
int main()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    //初始化管脚
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  //选择中断优先级分组，此处选择0。使0级抢占式优先级，16级亚优先级  
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;        //相应的通道配置，此处选择中断通道  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //抢占式优先级配置  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //亚优先级配置  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //时能通道  
    NVIC_Init(&NVIC_InitStructure);                             //使用结构体完成配置  
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    PAout(9)=1;
    //初始化PA09输出高电平,灭灯
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD,&GPIO_InitStructure);
    //初始化PD02输入,浮空
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource2);
    //配置中断源
   
    EXTI_DeInit();
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    //配置中断下降沿触发

    while(1)
    {
        delay(500);
    }
    return 0;
}