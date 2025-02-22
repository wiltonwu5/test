#include "delay.h"
#include "usart.h" 
#include "led.h"
#include "relay.h"
#include "iosensor.h"



/************************************************
 SR602��ʾ����
 ����֧�֣�18034701190
 �Ա����̣�http://iotedu.taobao.com 
 ���ߣ�EXIOT
************************************************/




//�������ݰ�����
u16 USART1_RX_LEN = 0;       //���ռ�����
u16 USART2_RX_LEN = 0;       //���ռ����� 
u16 USART3_RX_LEN = 0;       //���ռ����� 
u16 RS485_RX_LEN = 0;       //���ռ�����

char alarm[] = {"alarm\n"};


 int main(void)
 {	
	delay_init();	    	 //��ʱ������ʼ��	  
	LED_Init();
	//RELAY_Init();
  USART1_init(9600);
	IO_SENSOR_INIT();
	delay_ms(1000);
	delay_ms(1000);
 	while(1)
	{
		if(READ_IO_SENSOR()==IOH)
		{
			USART1_Send_String("alarm\n");			
			GPIO_TogglePin(GPIOB, GPIO_Pin_4);
		}
		else
		{
			USART1_Send_String("safety\n");
			GPIO_TogglePin(GPIOB, GPIO_Pin_3);
		}
		delay_ms(1000);
	}	 	
}
 

