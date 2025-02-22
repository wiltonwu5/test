#include "relay.h"


void RELAY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ�ӣ�A11;A12��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;				 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 	//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 	//IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 			//�����趨������ʼ��GPIOB 
	GPIO_ResetBits(GPIOA,GPIO_Pin_11|GPIO_Pin_12);					//�̵���Ĭ�ϴ��ڳ���״̬
}

//�̵������ƺ���
void Relay_Control(u8 relay,u8 state)
{
	if(relay == RELAY1)
	{
		if(state == CLOSE){
			GPIO_SetBits(GPIOA,GPIO_Pin_11);							//�̵���1�պ�
		}
		else if(state == BREAK){
			GPIO_ResetBits(GPIOA,GPIO_Pin_11);						//�̵���1�Ͽ�
		}	
	}
	else if(relay == RELAY2)
	{
		if(state == CLOSE){
			GPIO_SetBits(GPIOA,GPIO_Pin_12);							//�̵���2�պ�
		}
		else if(state == BREAK){
			GPIO_ResetBits(GPIOA,GPIO_Pin_12);						//�̵���2�Ͽ�
		}
	}
}


