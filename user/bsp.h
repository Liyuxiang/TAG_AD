/*
* Copyright (c) 2015,֣������ӿƼ����޹�˾
* All rights reserved.
* 
* �ļ����ƣ�bsp.h
* �ļ���ʶ��
* ժ    Ҫ��
* 
* ��ǰ�汾��0.1
* ��    �ߣ���ѩ��
* ������ڣ�2015.02.24
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

void BSP_Init(void);                    //��·���ʼ��

void BSP_DWTIntEnable(void);            //ʹ��DW1000�ж�

void BSP_SysStart(void);                //����ϵͳ����

void BSP_ResetDWT(void);                //��λDW1000

void BSP_WakeDWT(void);                 //����DW1000

void BSP_ChangeSPIRate(uint8_t value);  //����SPIƵ��

void BSP_Rand(void);

double ADC10_get_data();        //��ȡADת��ֵ

#endif
