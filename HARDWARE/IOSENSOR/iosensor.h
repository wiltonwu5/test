#ifndef __IOSENSOR_H
#define __IOSENSOR_H	 
#include "sys.h"

/************************************************
 ��������չ��
 IO����������
 ����֧�֣�18034701190
 �Ա����̣�http://iotedu.taobao.com 
 ���ߣ�EXIOT
 ************************************************/  
 
 
 
#define READ_IO_SENSOR() GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)
#define IOH 1
#define IOL 0

void IO_SENSOR_INIT(void);  

 #endif
 