#ifndef __RELAY_H
#define __RELAY_H	

#include "sys.h"
/************************************************
 EX-CM3-A
 �̵�������
 ����֧�֣�18034701190
 �Ա����̣�http://iotedu.taobao.com 
 ���ߣ�EXIOT
************************************************/  

#define RELAY1 	1				//A11
#define RELAY2 	2				//A12

#define CLOSE 	0			//�̵����պ�
#define BREAK 	1			//�̵����Ͽ�

void RELAY_Init(void);
void Relay_Control(u8 relay,u8 state);
#endif
