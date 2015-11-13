/*
* Copyright (c) 2015,֣������ӿƼ����޹�˾
* All rights reserved.
* 
* �ļ����ƣ�app.c
* �ļ���ʶ��
* ժ    Ҫ��
* 
* ��ǰ�汾��0.1
* ��    �ߣ���ѩ��
* ������ڣ�2015.02.24
*/


#include <msp430g2755.h>
#include "bsp.h"
#include "uwb.h"

double AD_value;

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;	// �رտ��Ź�
  __enable_interrupt();
  //��·���ʼ��
  BSP_Init();
  
  UWB_Init();                   //��ʼ������������Ϣ
  
  BSP_SysStart();               //��������
  
  while(1)
  {
    LPM3;
    //if(Key_IN & Key_CLR)
      if(Key_Alarm_Down)
    {
//        //���ѳ���
//        BSP_WakeDWT();
//        
//        //���ͳ���
//        UWB_SendMsg();
//        
//        BSP_Rand();
        AD_value = ADC10_get_data();
        LED_green_on;
        //Sleep(1000);
    }
    else 
    {
        LED_red_on;
        //Sleep(1000);
    }
        
  }
  
}