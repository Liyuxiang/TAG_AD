/*
* Copyright (c) 2015,郑州联睿电子科技有限公司
* All rights reserved.
* 
* 文件名称：uwb_def.h
* 文件标识：
* 摘    要：DW1000配置参数定义
* 
* 当前版本：0.1
* 作    者：何雪锋
* 完成日期：2015.02.24
*/

#ifndef _UWB_DEF_H_
#define _UWB_DEF_H_

//dw1000脉冲重复品路
typedef enum tagePRF
{
	PRF_16M = 1,
	PRF_64M = 2
}ePRF;


//DW1000导频长度
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

//dw1000波特率
typedef enum tagDataRate
{
	DATARATE_110K	= 0,
	DATARATE_850K	= 1,
	DATARATE_6M8	= 2
}DataRate;


#endif 