/*
* Copyright (c) 2015,郑州联睿电子科技有限公司
* All rights reserved.
* 
* 文件名称：bsp.c
* 文件标识：
* 摘    要：
* 
* 当前版本：0.1
* 作    者：何雪锋
* 完成日期：2015.02.24
*/
#include <msp430g2755.h>
#include <stdint.h>
#include <stdlib.h>
#include "config.h"
#include "bsp.h"


#define SLEEP_100us_CNT 0x0004
#define SLEEP_1ms_CNT   0x0021

#define ADC_Open()      P4OUT |= bat_ctrl
#define ADC_Close()     P4OUT &=~bat_ctrl

uint16_t timer_cnt;

/*
*********************************************************************************************************
*                                      局部函数定义
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                              static void Set_DCO(unsigned int delta)
*
* 描     述 : 设置DCO晶振
*
* 输入参数 : 
*       delta:DCO输出频率
*
* 输出参数 : none
*********************************************************************************************************
*/
static void Set_DCO(unsigned int Delta)
{
  unsigned int Compare, Oldcapture = 0;

  BCSCTL1 |= DIVA_3;                        // ACLK = LFXT1CLK/8
  TACCTL2 = CM_1 | CCIS_1 | CAP;            // CAP, ACLK
  TACTL = TASSEL_2 | MC_2 | TACLR;          // SMCLK, cont-mode, clear

  while (1)
  {
    while (!(CCIFG & TACCTL2));             // Wait until capture occured
    TACCTL2 &= ~CCIFG;                      // Capture occured, clear flag
    Compare = TACCR2;                       // Get current captured SMCLK
    Compare = Compare - Oldcapture;         // SMCLK difference
    Oldcapture = TACCR2;                    // Save current captured SMCLK

    if (Delta == Compare)
      break;                                // If equal, leave "while(1)"
    else if (Delta < Compare)
    {
      DCOCTL--;                             // DCO is too fast, slow it down
      if (DCOCTL == 0xFF)                   // Did DCO roll under?
        if (BCSCTL1 & 0x0f)
          BCSCTL1--;                        // Select lower RSEL
    }
    else
    {
      DCOCTL++;                             // DCO is too slow, speed it up
      if (DCOCTL == 0x00)                   // Did DCO roll over?
      if ((BCSCTL1 & 0x0f) != 0x0f)
        BCSCTL1++;                        // Sel higher RSEL
      }
  }
  TACCTL2 = 0;                              // Stop TACCR2
  TACTL = 0;                                // Stop Timer_A
  BCSCTL1 &= ~DIVA_3;                       // ACLK = LFXT1CLK
}


/*
*********************************************************************************************************
*                             static void Set_DWT_Port(void)
*
* 描     述 : 设置DWT端口
*
* 输入参数 : none
*
* 输出参数 : none
*********************************************************************************************************
*/
static void Set_DWTPort(void)
{
  	P2DIR	&= ~0x08;

	P2DIR	|= 0x10;
	P2OUT	|= 0x10;

	P1DIR 	|= 0x02;
	P1OUT 	&= ~0x02;

	P3SEL		|= 0x31;

	UCA0CTL1	= UCSWRST;
	UCA0CTL0	|= UCMST | UCMSB | UCSYNC;
	UCA0CTL1	|= UCSSEL_2;

	UCA0BR0		 = 0x06;	//设置为低速
	UCA0CTL1	&= ~UCSWRST;
}

static void Set_KeyPort(void)
{
  Key_DIR &= ~(Key_CLR | Key_Alarm);  //按键初始化配置
  Key_OUT &= ~(Key_CLR | Key_Alarm);
  Key_REN |= Key_CLR | Key_Alarm;
  
  
  P4DIR |= BIT6 | BIT7;        //LED初始化配置
  P4OUT |= BIT7;
  P4OUT |= BIT6;
}

static void Set_ADC()
{
    P4DIR |= bat_ctrl;
    P4OUT &=~bat_ctrl;
//    P4DIR |= bat_ver;
//    P4SEL |= bat_ver;
//配置ADC转换参数
    ADC10CTL0 &= ~ENC;          //采样使能开关 ** ADC10使能关闭，修改寄存器内容 **只有ENC=0时ADC10CTL1的内容才能被修改。
    ADC10CTL0 |= ADC10ON;       //ADC10模块开关 ** ADC10开启
    ADC10CTL0 |= ADC10SHT_2;    //采样和保持时间设置位 ** 16个ADC10CLK周期 
    ADC10CTL0 |= ADC10SR;       //采样率设置位 ** 参考缓冲器支持高达50 ksps的采样速度
//    ADC10CTL0 |= REFOUT;        //参考源输出控制位 ** 参考源输出开启
//    ADC10CTL0 |= MSC;           //多重采样和转换 ** SHI信号的第一个上升沿触发采样定时器，但是进一步的采样和转换只有在前一次的转换完成时才进行。
    ADC10CTL0 |= SREF_1;        //基准源选择 ** VR+=VREF+ VR-=Vss,选择内部参考
    ADC10CTL0 |= REFON;         //参考源开关 ** 参考源开启
    ADC10CTL0 |= REF2_5V;       //参考源电压选择位，更改时REFON必须开启 ** 参考源电压2.5V
//    ADC10CTL0 |= ADC10IE;       //ADC10模块使能开关 ** 允许ADC10中断 
//    ADC10CTL0 |= ADC10IFG;      //中断标志位 ** 有中断请求
//    ADC10CTL1 |= ADC10DF;       //数据格式，打开为补码形式
//    ADC10CTL1 |= ISSH;          //输入信号反转
    ADC10CTL1 |= ADC10DIV_0;    //时钟分频选择 ** 无分频
    ADC10CTL1 |= ADC10SSEL_0;   //时钟源选择  **  选择ADC内部时钟源ADC10OSC
    ADC10CTL1 |= SHS_0;         //采样保持源选择 ** 选择ADC10SC
    ADC10CTL1 |= CONSEQ_0 ;     //工作模式选择  ** 单通道单次转换
    ADC10CTL1 |= INCH_13;       //通道选择外部通道13 
    ADC10AE1 |= BIT5;           //开启外部通道13
}

double ADC10_get_data()
{
    ADC_Open();
    Sleep(10);
    ADC10CTL0 |= ENC+ADC10SC;           // ADC10使能开启;开始采样
    while((ADC10CTL0 & ADC10IFG)==0);   //等待ADC10IFG标志变高（转换完成）
    return (2.5*ADC10MEM/1023.0);
    ADC_Close();
}


/*
*********************************************************************************************************
*                                      全局函数定义
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                   void BSP_Init(void)
*
* 描     述 : 电路初始化
*
* 输入参数 : none
*
* 输出参数 : none
*********************************************************************************************************
*/
void BSP_Init(void)
{
//  P1DIR = 0xF2;
//  P2DIR = 0x21;
//  P3DIR = 0xFF;
//  P4DIR = 0xEF;
  
//  P1OUT = 0x00;
//  P2OUT = 0x00;
//  P3OUT = 0x00;
//  P4OUT = 0xC0;
  
  __delay_cycles(721000);			//等待晶振稳定
  Set_DCO(2930);                                //设置DC0晶振为12M
  

  Set_DWTPort();                                //设置dw1000端口
  
  Set_KeyPort();
  Set_ADC();
  //Set_Timer();
  //设置休眠时钟
}



/*
*********************************************************************************************************
*                                void Sleep(uint16_t value)
*
* 描     述 : 100us延迟
*
* 输入参数 : none
*
* 输出参数 : none
*
*********************************************************************************************************
*/
void Sleep(uint16_t value)
{
  TA1CTL        = TACLR;
  TA1CCR0       = SLEEP_100us_CNT * value;
  TA1CTL        = TASSEL_1 | MC_1 | TAIE; 
  LPM3;

}

/*
*********************************************************************************************************
*                                   void BSP_SysStart(void)
*
* 描     述 : 电路初始化
*
* 输入参数 : none
*
* 输出参数 : none
*********************************************************************************************************
*/
void BSP_SysStart(void)
{
  uint16_t temp;
  
  srand(LOC_CFG_ADDR);
  
  timer_cnt = LOC_CFG_FRQ + (int)(LOC_RAND_MAX * rand()/(RAND_MAX + 1.0));
  
  TA0CTL         = TACLR;
  TA0CCR0        = timer_cnt;
  
  if ((LOC_CFG_FRQ == LOC_FRQ_A) || (LOC_CFG_FRQ == LOC_FRQ_B) || (LOC_CFG_FRQ == LOC_FRQ_C))
    temp = TASSEL_1 | ID_3 | MC_1 | TAIE;
  else
    temp = TASSEL_1 | MC_1 | TAIE;
  
  TA0CTL = temp;
  
}

/*
*********************************************************************************************************
*                                   void BSP_ResetDWT(void)
*
* 描     述 : 复位DW1000
*
* 输入参数 : none
*
* 输出参数 : none
*********************************************************************************************************
*/
void BSP_ResetDWT(void)
{
  P2DIR |= 0x08;
  P2OUT &= ~0x08;
  
  P2DIR &= ~0x08;
}

/*
*********************************************************************************************************
*                                 loca_status BSP_WakeDWT(void)
*
* 描     述 : 唤醒DW1000
*
* 输入参数 : none
*
* 输出参数 : 
*       LOCA_OK：        唤醒成功
*       LOCA_FAULT：     唤醒失败
*********************************************************************************************************
*/
void BSP_WakeDWT(void)
{
  P1OUT |= 0x02;
  //等待500us
  Sleep(5);
  P1OUT &= ~0x02;
  //等待4ms
  Sleep(29);
}

/*
*********************************************************************************************************
*                                 void BSP_ChangeSPIRate(SPIRate spirate)
*
* 描     述 : 更改SPI波特率
*
* 输入参数 : none
*
* 输出参数 : value ：波特率
*
*********************************************************************************************************
*/
void BSP_ChangeSPIRate(uint8_t value)
{
  UCA0BR0       = value;
}

/*
*********************************************************************************************************
*                                 void BSP_ChangeSPIRate(SPIRate spirate)
*
* 描     述 : 更改SPI波特率
*
* 输入参数 : none
*
* 输出参数 : value ：波特率
*
*********************************************************************************************************
*/
void BSP_DWTIntEnable(void)
{
    P1IE	|= 0x01;
    P1IES	&= ~0x01;
    P1IFG	&= ~0x01;
}

void BSP_Rand(void)
{
  timer_cnt = LOC_CFG_FRQ + (int)((double)LOC_RAND_MAX * (double)rand()/(RAND_MAX + 1.0));
}

/*
*********************************************************************************************************
*                                      中断函数定义
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                 __interrupt void TA1_TAIFG_ISR(void)
*
* 描     述 : 用于唤醒时的相关定时
*
* 输入参数 : none
*
* 输出参数 : none
*
*********************************************************************************************************
*/
#pragma vector  = TIMER1_A1_VECTOR
__interrupt void TA1_TAIFG_ISR(void)
{
    //清除中断，关闭定时器
    switch(__even_in_range(TA1IV,10))
    {
        case 2:               //TACCR1 CCIFG
          break;
        case 4:               //TACCR2 CCIFG
          break;
        case 10:              //TAIFG
        // TA1CTL      = TASSEL1;
        TA1CTL      &= ~MC_1; 
        //退出低功耗
        LPM3_EXIT;
          break;
    }
}

/*
*********************************************************************************************************
*                                 __interrupt void TA1_TAIFG_ISR(void)
*
* 描     述 : 用于唤醒时的相关定时
*
* 输入参数 : none
*
* 输出参数 : none
*
*********************************************************************************************************
*/
#pragma vector  = TIMER0_A1_VECTOR
__interrupt void TA0_SYSTIMER(void)
{
  switch(__even_in_range(TAIV,10))
  {
      case 2:               //TACCR1 CCIFG
        break;
      case 4:               //TACCR2 CCIFG
        break;
      case 10:              //TAIFG
        TA0CCR0        = timer_cnt;
        //退出低功耗
        LPM3_EXIT;
        break;
  }
}

