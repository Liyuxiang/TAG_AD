/*
* Copyright (c) 2015,֣������ӿƼ����޹�˾
* All rights reserved.
* 
* �ļ����ƣ�uwb_def.h
* �ļ���ʶ��
* ժ    Ҫ��DW1000���ò�������
* 
* ��ǰ�汾��0.1
* ��    �ߣ���ѩ��
* ������ڣ�2015.02.24
*/

#ifndef _UWB_DEF_H_
#define _UWB_DEF_H_

//dw1000�����ظ�Ʒ·
typedef enum tagePRF
{
	PRF_16M = 1,
	PRF_64M = 2
}ePRF;


//DW1000��Ƶ����
typedef enum tagePLEN
{
	PLEN_64		= 0x04,
	PLEN_128	= 0x14,
	PLEN_256	= 0x24,
	PLEN_512	= 0x34,
	PLEN_1024	= 0x08,
	PLEN_1536	= 0x18,
	PLEN_2048	= 0x28,
	PLEN_4096	= 0x0C
}ePLEN;

//DW1000 preamble code
typedef enum tageCODE
{
	CODE_1	= 1,
	CODE_2	= 2,
	CODE_3	= 3,
	CODE_4	= 4,
        CODE_5  = 5,
	CODE_6	= 6,
	CODE_7	= 7,
	CODE_8	= 8,
	CODE_9	= 9,
	CODE_10	= 10,
	CODE_11	= 11,
	CODE_12	= 12,
	CODE_17	= 17,
	CODE_18	= 18,
	CODE_19	= 19,
	CODE_20	= 20
}eCODE;

//dw1000������
typedef enum tagDataRate
{
	DATARATE_110K	= 0,
	DATARATE_850K	= 1,
	DATARATE_6M8	= 2
}DataRate;


#endif 