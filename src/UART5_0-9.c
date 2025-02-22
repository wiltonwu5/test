#include "delay.h"
//#include "usart.h" 

u16 uart_sent_counter = 0x30;
	
/************************************************
 EX-TKSϵͳ���ذ�
 ����ʵ�� 
 ����֧�֣�18034701190
 �Ա����̣�http://iotedu.taobao.com 
 ���ߣ�EXIOT
************************************************/
 int main(void)
 {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	delay_init();	    	 //��ʱ������ʼ��	  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//ʹ��USART5
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	//ʹ��GPIOC\GPIODʱ�� 	 
	 
	//USART5_TX   GPIOC.12
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //PC.12
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOC.12
   
  //USART5_RX	  GPIOD.2��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//PD2
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOD.2 
  
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = 115200;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(UART5, &USART_InitStructure); //��ʼ������4
  USART_Cmd(UART5, ENABLE); 
	
 	while(1)
	{
		USART_SendData(UART5, uart_sent_counter++);//�򴮿�1�������� 	
		delay_ms(1000);	
		if(uart_sent_counter == 0x3A) uart_sent_counter = 0x30;
	}	 
}
