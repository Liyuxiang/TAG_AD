/*
* Copyright (c) 2015,֣������ӿƼ����޹�˾
* All rights reserved.
* 
* �ļ����ƣ�config.c
* �ļ���ʶ��#pragma location 
* ժ    Ҫ��ȫ���豸��Ϣ
* 
* ��ǰ�汾��0.1
* ��    �ߣ���ѩ��
* ������ڣ�2015.02.24
*/

#include "stdint.h"
//#include "config.h"
#define LOC_FRQ_A       0xA000  //ˢ��Ƶ��Ϊ0.1HZ
#define LOC_FRQ_B       0x5000  //ˢ��Ƶ��Ϊ0.2HZ
#define LOC_FRQ_C       0x2000  //ˢ��Ƶ��Ϊ0.5HZ
#define LOC_FRQ_D       0x8000  //ˢ��Ƶ��Ϊ1HZ
#define LOC_FRQ_E       0x4000  //ˢ��Ƶ��Ϊ2HZ
#define LOC_FRQ_F       0x199A  //ˢ��Ƶ��Ϊ5HZ
#define LOC_FRQ_G       0x0CCD  //ˢ��Ƶ��Ϊ10HZ
#define LOC_FRQ_H       0x0666  //ˢ��Ƶ��Ϊ20HZ
#define LOC_FRQ_I       0x028F  //ˢ��Ƶ��Ϊ50HZ
#define LOC_FRQ_J       0x0148  //ˢ��Ƶ��Ϊ100HZ

//#pragma location=0x1000
//const uint16_t LOC_CFG_ADDR   = 0x0010;
//#pragma location=0x1002
//const uint16_t LOC_CFG_PANID  = 0x0001;
//uint64_t LOC_CFG_EUI    = 0x0000000000000010;

const uint16_t LOC_CFG_ADDR @ 0x1000    = 0x0011;
//const uint16_t LOC_CFG_PANID @ 0x1002   = 0x0001;
const uint16_t LOC_CFG_FRQ @ 0x1004     = LOC_FRQ_G;            //ˢ��Ƶ��
//const uint64_t LOC_CFG_EUI @ 0x1006     = 0x0000000000000010;
