#include "delay.h"
//#include "usart.h" 

u16 uart_sent_counter = 0x30;
	
/************************************************
 EX-TKS系统网关板
 串口实验 
 技术支持：18034701190
 淘宝店铺：http://iotedu.taobao.com 
 作者：EXIOT
************************************************/
 int main(void)
 {
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	delay_init();	    	 //延时函数初始化	  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//使能USART4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//使能GPIOC时钟 
	 
	//USART4_TX   GPIOC.10
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //PC.10
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOA.9
   
  	//USART4_RX	  GPIOC.11初始化
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;//PA10
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOA.10 
  
   	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = 115200;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  	USART_Init(UART4, &USART_InitStructure); //初始化串口4
  	USART_Cmd(UART4, ENABLE); 
	
 	while(1)
	{
		USART_SendData(UART4, uart_sent_counter++);//向串口1发送数据 	
		delay_ms(1000);	
		if(uart_sent_counter == 0x3A) uart_sent_counter = 0x30;
	}	 
}
