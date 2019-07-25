#include "exti.h"
#include "delay.h"
#include "delay.h"
#define kaiguan 1
void EXTI_Init(void)
{ 
  delay_init(180);
  #if(kaiguan)
  //初始化端口时钟
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  
  //初始化端口
  GPIO_InitTypeDef GPIO_Init_struct;
  GPIO_Init_struct.Mode = GPIO_MODE_IT_RISING;//上升沿触发
  GPIO_Init_struct.Pull = GPIO_PULLDOWN;//下拉
  GPIO_Init_struct.Pin = GPIO_PIN_0;
  GPIO_Init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//超高速
  HAL_GPIO_Init(GPIOA,&GPIO_Init_struct);
  
  GPIO_Init_struct.Mode = GPIO_MODE_IT_FALLING;//下降沿触发
  GPIO_Init_struct.Pull = GPIO_PULLUP;//上拉
  GPIO_Init_struct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
  GPIO_Init_struct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;//超高速
  HAL_GPIO_Init(GPIOH,&GPIO_Init_struct);
  
  GPIO_Init_struct.Pin = GPIO_PIN_13;
  HAL_GPIO_Init(GPIOC,&GPIO_Init_struct);
  
  //设置中断优先级和使能中断：
  HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
  
  HAL_NVIC_SetPriority(EXTI0_IRQn,2,1);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
  
  HAL_NVIC_SetPriority(EXTI2_IRQn,2,2);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);
  
  HAL_NVIC_SetPriority(EXTI3_IRQn,2,3);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);
  
  #else
  GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //开启GPIOA时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();               //开启GPIOC时钟
    __HAL_RCC_GPIOH_CLK_ENABLE();               //开启GPIOH时钟
    
    GPIO_Initure.Pin=GPIO_PIN_0;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //上升沿触发
    GPIO_Initure.Pull=GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_13;               //PC13
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3;     //PH2,3
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
    
    //中断线0-PA0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //使能中断线0
    
    //中断线2-PH2
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);       //抢占优先级为2，子优先级为1
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);             //使能中断线2
    
    //中断线3-PH3
    HAL_NVIC_SetPriority(EXTI3_IRQn,2,2);       //抢占优先级为2，子优先级为2
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);             //使能中断线2
    
    //中断线13-PC13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,3);   //抢占优先级为2，子优先级为3
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);         //使能中断线13  
    #endif
}

void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler
  (GPIO_PIN_0);
}

void EXTI2_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}

void EXTI3_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  #if(0)
  GPIOB->ODR = 0x00;
  #else
  delay_ms(200);//消抖
  switch (GPIO_Pin)
  {
    case GPIO_PIN_2 :  GPIOB->ODR = ~(GPIOB->ODR&0x00);  break; //KEY1
    case GPIO_PIN_3 :  GPIOB->ODR = ~(GPIOB->ODR&0x01);  break; //KEY0
    case GPIO_PIN_13:  GPIOB->ODR = ~(GPIOB->ODR&0x02);  break; //KEY2
    case GPIO_PIN_0 :  GPIOB->ODR = ~(GPIOB->ODR&0x03);  break; //KEY_UP
  }
  #endif
}




