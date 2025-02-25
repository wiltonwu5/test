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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//ʹ��USART4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��GPIOCʱ�� 
	 
	//USART4_TX   GPIOC.10
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  	//USART4_RX	  GPIOC.11��ʼ��
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PA10
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOA.10 
  
   	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = 115200;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  	USART_Init(UART4, &USART_InitStructure); //��ʼ������4
  	USART_Cmd(UART4, ENABLE); 
	
 	while(1)
	{
		USART_SendData(UART4, uart_sent_counter++);//�򴮿�1�������� 	
		delay_ms(1000);	
		if(uart_sent_counter == 0x3A) uart_sent_counter = 0x30;
	}	 
}
