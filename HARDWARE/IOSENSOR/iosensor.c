#include "iosensor.h"


//SR602��ʼ��
void IO_SENSOR_INIT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��GPIOBʱ�ӣ�PB2��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	         		 					//
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;   		 					//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);		    		 							//B�˿�
} 
