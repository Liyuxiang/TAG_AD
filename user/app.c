/*
* Copyright (c) 2015,郑州联睿电子科技有限公司
* All rights reserved.
* 
* 文件名称：app.c
* 文件标识：
* 摘    要：
* 
* 当前版本：0.1
* 作    者：何雪锋
* 完成日期：2015.02.24
*/


#include <msp430g2755.h>
#include "bsp.h"
#include "uwb.h"

double AD_value;

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;	// 关闭看门狗
  __enable_interrupt();
  //电路板初始化
  BSP_Init();
  
  UWB_Init();                   //初始化超宽带相关信息
  
  BSP_SysStart();               //启动程序
  
  while(1)
  {
    LPM3;
    //if(Key_IN & Key_CLR)
      if(Key_Alarm_Down)
    {
//        //唤醒程序
//        BSP_WakeDWT();
//        
//        //发送程序
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