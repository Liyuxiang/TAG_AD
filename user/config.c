/*
* Copyright (c) 2015,郑州联睿电子科技有限公司
* All rights reserved.
* 
* 文件名称：config.c
* 文件标识：#pragma location 
* 摘    要：全局设备信息
* 
* 当前版本：0.1
* 作    者：何雪锋
* 完成日期：2015.02.24
*/

#include "stdint.h"
//#include "config.h"
#define LOC_FRQ_A       0xA000  //刷新频率为0.1HZ
#define LOC_FRQ_B       0x5000  //刷新频率为0.2HZ
#define LOC_FRQ_C       0x2000  //刷新频率为0.5HZ
#define LOC_FRQ_D       0x8000  //刷新频率为1HZ
#define LOC_FRQ_E       0x4000  //刷新频率为2HZ
#define LOC_FRQ_F       0x199A  //刷新频率为5HZ
#define LOC_FRQ_G       0x0CCD  //刷新频率为10HZ
#define LOC_FRQ_H       0x0666  //刷新频率为20HZ
#define LOC_FRQ_I       0x028F  //刷新频率为50HZ
#define LOC_FRQ_J       0x0148  //刷新频率为100HZ

//#pragma location=0x1000
//const uint16_t LOC_CFG_ADDR   = 0x0010;
//#pragma location=0x1002
//const uint16_t LOC_CFG_PANID  = 0x0001;
//uint64_t LOC_CFG_EUI    = 0x0000000000000010;

const uint16_t LOC_CFG_ADDR @ 0x1000    = 0x0011;
//const uint16_t LOC_CFG_PANID @ 0x1002   = 0x0001;
const uint16_t LOC_CFG_FRQ @ 0x1004     = LOC_FRQ_G;            //刷新频率
//const uint64_t LOC_CFG_EUI @ 0x1006     = 0x0000000000000010;
