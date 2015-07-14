#include "stm32f10x_conf.h"
#include "GPIO.h"

void delay(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //自己定义
      while(i--) ;    
   }
}

int main()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin =GPIO_Pin_9|GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_9|GPIO_Pin_10);
    
    while(1)
    {
        PAout(10)=!PAout(10);
        delay(500);
    }
    return 0;
}