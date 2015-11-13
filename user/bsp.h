/*
* Copyright (c) 2015,郑州联睿电子科技有限公司
* All rights reserved.
* 
* 文件名称：bsp.h
* 文件标识：
* 摘    要：
* 
* 当前版本：0.1
* 作    者：何雪锋
* 完成日期：2015.02.24
*/

#ifndef _BSP_H_
#define _BSP_H_

#include "stdint.h"

#define  SPI_SLOW	    0x06
#define  SPI_FAST	    0X01

#define  Key_DIR                P2DIR          
#define  Key_OUT                P2OUT
#define  Key_REN                P2REN
#define  Key_CLR                BIT1
#define  Key_Alarm              BIT2
#define  Key_CLR_Down           (P2IN & BIT1)
#define  Key_Alarm_Down         (P2IN & BIT2)

#define  bat_ver                BIT4
#define  bat_ctrl               BIT5
#define  Open_adc               P4DIR |= bat_ctrl;
#define  Close_adc              P4DIR &= ~bat_ver;

#define  LED_green_on           P4OUT &=~BIT7; P4OUT |=BIT6;
#define  LED_red_on             P4OUT &=~BIT6; P4OUT |=BIT7;
#define  LED_off                P4OUT |=BIT7;  P4OUT |=BIT6;
void Sleep(uint16_t value);

void BSP_Init(void);                    //电路板初始化

void BSP_DWTIntEnable(void);            //使能DW1000中断

void BSP_SysStart(void);                //启动系统程序

void BSP_ResetDWT(void);                //复位DW1000

void BSP_WakeDWT(void);                 //唤醒DW1000

void BSP_ChangeSPIRate(uint8_t value);  //更改SPI频率

void BSP_Rand(void);

double ADC10_get_data();        //获取AD转换值

#endif
