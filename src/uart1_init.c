#include "delay.h"
#include "usart.h" 

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
	delay_init();	    	 //��ʱ������ʼ��	  
	uart1_init(115200);					//��ʼ������1	
 	while(1)
	{
		USART_SendData(USART1, uart_sent_counter++);//�򴮿�1�������� 	
		delay_ms(1000);	
		if(uart_sent_counter == 0x3A) uart_sent_counter = 0x30;
	}	 
}
