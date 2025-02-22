#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
/************************************************
EX-CM3-A
��������
����֧�֣�18034701190
�Ա����̣�http://iotedu.taobao.com 
���ߣ�EXIOT
************************************************/   

//����������ڽ��ջ�����	
u8 USART1_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART2_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 USART3_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u8 RS485_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

//����״̬��������һ֡���ݰ���С��300�ֽڣ�
u16 USART1_RX_STA = 0;       //����״̬���	  
u16 USART2_RX_STA = 0;       //����״̬���	  
u16 USART3_RX_STA = 0;       //����״̬���	  
u16 RS485_RX_STA = 0;       //����״̬���

//���ڽ��ռ�����
u16 USART1_RX_counter = 0;       //���ռ�����
u16 USART2_RX_counter = 0;       //���ռ����� 
u16 USART3_RX_counter = 0;       //���ռ����� 
u16 UART4_RX_counter = 0;       //���ռ�����


//����USART1���ú�������ʼ����
void USART1_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ�ӣ�TX1:A9;RX1:A10��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         		 					//USART1 TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 					//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);		    		 							//A�˿�
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	         	 					//USART1 RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   				//���ÿ�©����
	GPIO_Init(GPIOA, &GPIO_InitStructure);		         	 						//A�˿�
 
	USART_InitStructure.USART_BaudRate = bound;											//������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//����λ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//ֹͣλ1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;							//����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   	//������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
 
	USART_Init(USART1, &USART_InitStructure);												//��ʼ��USART1
	USART1_RX_LEN = 0;
	USART1_RX_STA = 0;
	USART1_RX_counter = 0;
	//USART1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                  //��������ж�
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);									//����IDLE�ж�

	USART_Cmd(USART1, ENABLE); 																			//ʹ��USART1	
} 


//����USART2���ú�������ʼ����
void USART2_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART2	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ�ӣ�TX2:A2;RX2:A3��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	         		 					//USART1 TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 					//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);		    		 							//A�˿�
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	         	 					//USART1 RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   				//���ÿ�©����
	GPIO_Init(GPIOA, &GPIO_InitStructure);		         	 						//A�˿�
 
	USART_InitStructure.USART_BaudRate = bound;											//������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//����λ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//ֹͣλ1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;							//����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   	//������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
 
	USART_Init(USART2, &USART_InitStructure);												//��ʼ��USART2
 
	//USART2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                  //��������ж�
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);									//����IDLE�ж�

	USART_Cmd(USART2, ENABLE); 																			//ʹ��USART2	
}  

//����USART3���ú�������ʼ����
void USART3_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	//ʹ��USART3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//ʹ��GPIOBʱ�ӣ�TX3:B10;RX3:B11��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	         		 					//USART3 TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 					//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);		    		 							//A�˿�
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	         	 					//USART3 RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   				//���ÿ�©����
	GPIO_Init(GPIOB, &GPIO_InitStructure);		         	 						//A�˿�
 
	USART_InitStructure.USART_BaudRate = bound;											//������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//����λ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//ֹͣλ1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;							//����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   	//������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
 
	USART_Init(USART3, &USART_InitStructure);												//��ʼ��USART3
 
	//USART2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);                  //��������ж�
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);									//����IDLE�ж�

	USART_Cmd(USART3, ENABLE); 																			//ʹ��USART3
}

//����UART4���ú�������ʼ����
void UART4_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//ʹ��UART4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��GPIOBʱ�ӣ�TX4:C10;RX4:C11��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	         		 					//USART4 TX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    		 					//�����������
	GPIO_Init(GPIOC, &GPIO_InitStructure);		    		 							//A�˿�
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	         	 					//USART4 RX
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   				//���ÿ�©����
	GPIO_Init(GPIOC, &GPIO_InitStructure);		         	 						//C�˿�
 
	USART_InitStructure.USART_BaudRate = bound;											//������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;			//����λ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//ֹͣλ1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;							//����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   	//������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
 
	USART_Init(UART4, &USART_InitStructure);												//��ʼ��USART4
 
	//USART2 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

  USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);                  //��������ж�
	USART_ITConfig(UART4, USART_IT_IDLE, ENABLE);									//����IDLE�ж�

	USART_Cmd(UART4, ENABLE); 																			//ʹ��USART3	
}

//RS485��ʼ��
void RS485_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ�ӣ�A8��
	
	//RS485������������������ã�A8
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);//RS485Ϊ����ģʽ	
	
	UART4_init(bound);	
}
/**********************************************************
����1�����жϺ���
***********************************************************/
void USART1_IRQHandler(void)                	//����1�жϷ������
{
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //
	{
		USART1_RX_BUF[USART1_RX_counter] = USART_ReceiveData(USART1);	//��ȡ���յ�������	
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		USART1_RX_counter++;
  }	
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)  //
	{
		USART1_RX_LEN = USART1_RX_counter;
		USART1_RX_STA = 1;//��ȷ���յ�һ������
		USART1->SR;
		USART1->DR;
		USART1_RX_counter = 0;
  } 	
}

/**********************************************************
����2�����жϺ���
***********************************************************/
void USART2_IRQHandler(void)                	//����2�жϷ������
{
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //
	{
		USART2_RX_BUF[USART2_RX_counter] = USART_ReceiveData(USART2);	//��ȡ���յ�������	
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		USART2_RX_counter++;
  }	
	if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)  //
	{
		USART2_RX_LEN = USART2_RX_counter;
		USART2->SR;
		USART2->DR;
		USART2_RX_counter = 0;
		USART2_RX_STA = 1;//��ȷ���յ�һ������
  } 	
}

/**********************************************************
����3�����жϺ���
***********************************************************/
void USART3_IRQHandler(void)                	//����3�жϷ������
{
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //
	{
		USART3_RX_BUF[USART3_RX_counter] = USART_ReceiveData(USART3);	//��ȡ���յ�������	
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		USART3_RX_counter++;
  }	
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)  //
	{
		USART3_RX_LEN = USART3_RX_counter;
		USART3->SR;
		USART3->DR;
		USART3_RX_counter = 0;
		USART3_RX_STA = 1;//��ȷ���յ�һ������
  } 	
}

/**********************************************************
����4�����жϺ���
***********************************************************/
void UART4_IRQHandler(void)                	//����4�жϷ������
{
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //
	{
		RS485_RX_BUF[UART4_RX_counter] = USART_ReceiveData(UART4);	//��ȡ���յ�������
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
		UART4_RX_counter++;
  }	
	if(USART_GetITStatus(UART4, USART_IT_IDLE) != RESET)  //
	{
		RS485_RX_LEN = UART4_RX_counter;
		UART4->SR;
		UART4->DR;
		UART4_RX_counter = 0;
		RS485_RX_STA = 1;//��ȷ���յ�һ������
  } 	
}

/**********************************************************
����1���ͺ���
***********************************************************/
void USART1_Send_Byte(u8 Data) //����һ���ֽ�
{
	USART_SendData(USART1,Data);
	while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
}

void USART1_Send_String(u8 *Data) //�����ַ���
{
	USART_ClearFlag(USART1, USART_FLAG_TC );
	while(*Data)
	USART1_Send_Byte(*Data++);
}

void USART1_Send_BUF(u8 *buf,u8 len) //�������ݰ�
{
	u8 i;
	USART_ClearFlag(USART1, USART_FLAG_TC );
	for(i = 0;i < len;i++)
	{
			USART1_Send_Byte(*(buf+i));
	}
}

/**********************************************************
����2���ͺ���
***********************************************************/
void USART2_Send_Byte(u8 Data) //����һ���ֽ�
{
	USART_SendData(USART2,Data);
	while( USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET );
}

void USART2_Send_String(u8 *Data) //�����ַ���
{
	USART_ClearFlag(USART2, USART_FLAG_TC);
	while(*Data)
	USART2_Send_Byte(*Data++);
}

void USART2_Send_BUF(u8 *buf,u8 len) //�������ݰ�
{
	u8 i;
	USART_ClearFlag(USART2, USART_FLAG_TC );
	for(i = 0;i < len;i++)
	{
			USART2_Send_Byte(*(buf+i));
	}
}

/**********************************************************
����3���ͺ���
***********************************************************/
void USART3_Send_Byte(u8 Data) //����һ���ֽ�
{
	USART_SendData(USART3,Data);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET );
}

void USART3_Send_String(u8 *Data) //�����ַ���
{
	USART_ClearFlag(USART3, USART_FLAG_TC );
	while(*Data)
	USART3_Send_Byte(*Data++);
}

void USART3_Send_BUF(u8 *buf,u8 len) //�������ݰ�
{
	u8 i;
	USART_ClearFlag(USART3, USART_FLAG_TC );
	for(i = 0;i < len;i++)
	{
			USART3_Send_Byte(*(buf+i));
	}
}

/**********************************************************
����4���ͺ���
***********************************************************/
void UART4_Send_Byte(u8 Data) //����һ���ֽ�
{
	//GPIO_SetBits(GPIOA,GPIO_Pin_8);//RS485Ϊ����ģʽ	
	USART_SendData(UART4,Data);
	while( USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET );
}

void UART4_Send_String(u8 *Data) //�����ַ���
{
	USART_ClearFlag(UART4, USART_FLAG_TC );
	while(*Data)
	UART4_Send_Byte(*Data++);
}

void UART4_Send_BUF(u8 *buf,u8 len) //�������ݰ�
{
	u8 i;
	USART_ClearFlag(UART4, USART_FLAG_TC );
	for(i = 0;i < len;i++)
	{
			UART4_Send_Byte(*(buf+i));
	}
}

//RS485�ӿڷ��ͺ���
void RS485_Send_Byte(u8 Data) //����һ���ֽ�
{
	RS485_TX_MODE;//RS485Ϊ����ģʽ	
	USART_SendData(UART4,Data);
	while( USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET );
	RS485_RX_MODE;//RS485Ϊ����ģʽ	
}

void RS485_Send_String(u8 *Data) //�����ַ���
{
	RS485_TX_MODE;//RS485Ϊ����ģʽ	
	USART_ClearFlag(UART4, USART_FLAG_TC );
	while(*Data)
	UART4_Send_Byte(*Data++);
	RS485_RX_MODE;//RS485Ϊ����ģʽ	
}

void RS485_Send_BUF(u8 *buf,u8 len) //�������ݰ�
{
	u8 i;
	RS485_TX_MODE;//RS485Ϊ����ģʽ	
	USART_ClearFlag(UART4, USART_FLAG_TC );
	for(i = 0;i < len;i++)
	{
			UART4_Send_Byte(*(buf+i));
	}
	RS485_RX_MODE;//RS485Ϊ����ģʽ	
}

#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
