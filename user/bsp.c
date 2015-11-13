/*
* Copyright (c) 2015,֣������ӿƼ����޹�˾
* All rights reserved.
* 
* �ļ����ƣ�bsp.c
* �ļ���ʶ��
* ժ    Ҫ��
* 
* ��ǰ�汾��0.1
* ��    �ߣ���ѩ��
* ������ڣ�2015.02.24
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
*                                      �ֲ���������
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                              static void Set_DCO(unsigned int delta)
*
* ��     �� : ����DCO����
*
* ������� : 
*       delta:DCO���Ƶ��
*
* ������� : none
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
* ��     �� : ����DWT�˿�
*
* ������� : none
*
* ������� : none
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

	UCA0BR0		 = 0x06;	//����Ϊ����
	UCA0CTL1	&= ~UCSWRST;
}

static void Set_KeyPort(void)
{
  Key_DIR &= ~(Key_CLR | Key_Alarm);  //������ʼ������
  Key_OUT &= ~(Key_CLR | Key_Alarm);
  Key_REN |= Key_CLR | Key_Alarm;
  
  
  P4DIR |= BIT6 | BIT7;        //LED��ʼ������
  P4OUT |= BIT7;
  P4OUT |= BIT6;
}

static void Set_ADC()
{
    P4DIR |= bat_ctrl;
    P4OUT &=~bat_ctrl;
//    P4DIR |= bat_ver;
//    P4SEL |= bat_ver;
//����ADCת������
    ADC10CTL0 &= ~ENC;          //����ʹ�ܿ��� ** ADC10ʹ�ܹرգ��޸ļĴ������� **ֻ��ENC=0ʱADC10CTL1�����ݲ��ܱ��޸ġ�
    ADC10CTL0 |= ADC10ON;       //ADC10ģ�鿪�� ** ADC10����
    ADC10CTL0 |= ADC10SHT_2;    //�����ͱ���ʱ������λ ** 16��ADC10CLK���� 
    ADC10CTL0 |= ADC10SR;       //����������λ ** �ο�������֧�ָߴ�50 ksps�Ĳ����ٶ�
//    ADC10CTL0 |= REFOUT;        //�ο�Դ�������λ ** �ο�Դ�������
//    ADC10CTL0 |= MSC;           //���ز�����ת�� ** SHI�źŵĵ�һ�������ش���������ʱ�������ǽ�һ���Ĳ�����ת��ֻ����ǰһ�ε�ת�����ʱ�Ž��С�
    ADC10CTL0 |= SREF_1;        //��׼Դѡ�� ** VR+=VREF+ VR-=Vss,ѡ���ڲ��ο�
    ADC10CTL0 |= REFON;         //�ο�Դ���� ** �ο�Դ����
    ADC10CTL0 |= REF2_5V;       //�ο�Դ��ѹѡ��λ������ʱREFON���뿪�� ** �ο�Դ��ѹ2.5V
//    ADC10CTL0 |= ADC10IE;       //ADC10ģ��ʹ�ܿ��� ** ����ADC10�ж� 
//    ADC10CTL0 |= ADC10IFG;      //�жϱ�־λ ** ���ж�����
//    ADC10CTL1 |= ADC10DF;       //���ݸ�ʽ����Ϊ������ʽ
//    ADC10CTL1 |= ISSH;          //�����źŷ�ת
    ADC10CTL1 |= ADC10DIV_0;    //ʱ�ӷ�Ƶѡ�� ** �޷�Ƶ
    ADC10CTL1 |= ADC10SSEL_0;   //ʱ��Դѡ��  **  ѡ��ADC�ڲ�ʱ��ԴADC10OSC
    ADC10CTL1 |= SHS_0;         //��������Դѡ�� ** ѡ��ADC10SC
    ADC10CTL1 |= CONSEQ_0 ;     //����ģʽѡ��  ** ��ͨ������ת��
    ADC10CTL1 |= INCH_13;       //ͨ��ѡ���ⲿͨ��13 
    ADC10AE1 |= BIT5;           //�����ⲿͨ��13
}

double ADC10_get_data()
{
    ADC_Open();
    Sleep(10);
    ADC10CTL0 |= ENC+ADC10SC;           // ADC10ʹ�ܿ���;��ʼ����
    while((ADC10CTL0 & ADC10IFG)==0);   //�ȴ�ADC10IFG��־��ߣ�ת����ɣ�
    return (2.5*ADC10MEM/1023.0);
    ADC_Close();
}


/*
*********************************************************************************************************
*                                      ȫ�ֺ�������
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                   void BSP_Init(void)
*
* ��     �� : ��·��ʼ��
*
* ������� : none
*
* ������� : none
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
  
  __delay_cycles(721000);			//�ȴ������ȶ�
  Set_DCO(2930);                                //����DC0����Ϊ12M
  

  Set_DWTPort();                                //����dw1000�˿�
  
  Set_KeyPort();
  Set_ADC();
  //Set_Timer();
  //��������ʱ��
}



/*
*********************************************************************************************************
*                                void Sleep(uint16_t value)
*
* ��     �� : 100us�ӳ�
*
* ������� : none
*
* ������� : none
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
* ��     �� : ��·��ʼ��
*
* ������� : none
*
* ������� : none
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
* ��     �� : ��λDW1000
*
* ������� : none
*
* ������� : none
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
* ��     �� : ����DW1000
*
* ������� : none
*
* ������� : 
*       LOCA_OK��        ���ѳɹ�
*       LOCA_FAULT��     ����ʧ��
*********************************************************************************************************
*/
void BSP_WakeDWT(void)
{
  P1OUT |= 0x02;
  //�ȴ�500us
  Sleep(5);
  P1OUT &= ~0x02;
  //�ȴ�4ms
  Sleep(29);
}

/*
*********************************************************************************************************
*                                 void BSP_ChangeSPIRate(SPIRate spirate)
*
* ��     �� : ����SPI������
*
* ������� : none
*
* ������� : value ��������
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
* ��     �� : ����SPI������
*
* ������� : none
*
* ������� : value ��������
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
*                                      �жϺ�������
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                 __interrupt void TA1_TAIFG_ISR(void)
*
* ��     �� : ���ڻ���ʱ����ض�ʱ
*
* ������� : none
*
* ������� : none
*
*********************************************************************************************************
*/
#pragma vector  = TIMER1_A1_VECTOR
__interrupt void TA1_TAIFG_ISR(void)
{
    //����жϣ��رն�ʱ��
    switch(__even_in_range(TA1IV,10))
    {
        case 2:               //TACCR1 CCIFG
          break;
        case 4:               //TACCR2 CCIFG
          break;
        case 10:              //TAIFG
        // TA1CTL      = TASSEL1;
        TA1CTL      &= ~MC_1; 
        //�˳��͹���
        LPM3_EXIT;
          break;
    }
}

/*
*********************************************************************************************************
*                                 __interrupt void TA1_TAIFG_ISR(void)
*
* ��     �� : ���ڻ���ʱ����ض�ʱ
*
* ������� : none
*
* ������� : none
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
        //�˳��͹���
        LPM3_EXIT;
        break;
  }
}

