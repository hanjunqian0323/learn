#ifndef _EXTI_H_
#define _EXTI_H_

#include "sys.h"

#define KEY_UP HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)
#define KEY0 HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_3)
#define KEY1 HAL_GPIO_ReadPin(GPIOH,GPIO_PIN_2)
#define KEY2 HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)


void EXTI_Init(void);


typedef unsigned char u8;
#endif

