#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 


#define USART_REC_LEN  			300  	//�����������ֽ��� 300

#define RS485_TX_MODE 	GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define RS485_RX_MODE		GPIO_ResetBits(GPIOA,GPIO_Pin_8)
	  	
//����������ڽ��ջ�����	
extern u8 USART1_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u8 USART2_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u8 USART3_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u8 RS485_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.

//����״̬��������һ֡���ݰ���С��200�ֽڣ�
extern u16 USART1_RX_STA ;       //����״̬���	  
extern u16 USART2_RX_STA ;       //����״̬���	  
extern u16 USART3_RX_STA;       //����״̬���	  
extern u16 RS485_RX_STA;       //����״̬���	

//�������ݰ�����
extern u16 USART1_RX_LEN;       //��Ч���ݰ�����
extern u16 USART2_RX_LEN;       //��Ч���ݰ�����
extern u16 USART3_RX_LEN;       //��Ч���ݰ�����
extern u16 RS485_RX_LEN;       //��Ч���ݰ�����

//����봮���жϽ��գ��벻Ҫע�����º궨��
//����USART1���ú�������ʼ����
void USART1_init(u32 bound);
void USART2_init(u32 bound);
void USART3_init(u32 bound);
void UART4_init(u32 bound);
void RS485_init(u32 bound);
/**********************************************************
���ڷ��ͺ���
***********************************************************/
void USART1_Send_Byte(u8 Data) ;
void USART1_Send_String(u8 *Data);
void USART1_Send_BUF(u8 *buf,u8 len) ;
void USART2_Send_Byte(u8 Data);
void USART2_Send_String(u8 *Data);
void USART2_Send_BUF(u8 *buf,u8 len);
void USART3_Send_Byte(u8 Data);
void USART3_Send_String(u8 *Data);
void USART3_Send_BUF(u8 *buf,u8 len);
void UART4_Send_Byte(u8 Data);
void UART4_Send_String(u8 *Data);
void UART4_Send_BUF(u8 *buf,u8 len);
void RS485_Send_Byte(u8 Data);
void RS485_Send_String(u8 *Data);
void RS485_Send_BUF(u8 *buf,u8 len);
#endif


