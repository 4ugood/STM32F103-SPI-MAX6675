#include "u_led.h"	  
/**
 * ����: LED IO��ʼ��
*/
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOD, ENABLE);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOB, &GPIO_InitStructure);
 GPIO_SetBits(GPIOB,GPIO_Pin_5);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
 GPIO_Init(GPIOD, &GPIO_InitStructure);
 GPIO_SetBits(GPIOD,GPIO_Pin_2);
}
