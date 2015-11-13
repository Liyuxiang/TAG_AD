/*
* Copyright (c) 2015,郑州联睿电子科技有限公司
* All rights reserved.
* 
* 文件名称：config.h
* 文件标识：
* 摘    要：配置标签相关参数
* 
* 当前版本：0.1
* 作    者：何雪锋
* 完成日期：2015.02.24
*/


#ifndef _CONFIG_H_
#define _CONFIG_H_

//#define LOC_FRQ_A       0xA000  //刷新频率为0.1HZ
//#define LOC_FRQ_B       0x5000  //刷新频率为0.2HZ
//#define LOC_FRQ_C       0x2000  //刷新频率为0.5HZ
//#define LOC_FRQ_D       0x8000  //刷新频率为1HZ
//#define LOC_FRQ_E       0x4000  //刷新频率为2HZ
//#define LOC_FRQ_F       0x199A  //刷新频率为5HZ
//#define LOC_FRQ_G       0x0CCD  //刷新频率为10HZ
//#define LOC_FRQ_H       0x0666  //刷新频率为20HZ
//#define LOC_FRQ_I       0x028F  //刷新频率为50HZ
//#define LOC_FRQ_J       0x0148  //刷新频率为100HZ

#define LOC_FRQ_A       0x9EB9  //刷新频率为0.1HZ 147
#define LOC_FRQ_B       0x4EB9  //刷新频率为0.2HZ
#define LOC_FRQ_C       0x1EB9  //刷新频率为0.5HZ
#define LOC_FRQ_D       0x7EB9  //刷新频率为1HZ
#define LOC_FRQ_E       0x3EB9  //刷新频率为2HZ
#define LOC_FRQ_F       0x1853  //刷新频率为5HZ
#define LOC_FRQ_G       0x0B86  //刷新频率为10HZ
#define LOC_FRQ_H       0x051F  //刷新频率为20HZ
#define LOC_FRQ_I       0x0148  //刷新频率为50HZ

#define LOC_RAND_MAX    0x028F


#define LOC_CFG_CHAN            CHAN_CTRL_TXCHAN_3
#define LOC_CFG_PRF             PRF_16M
#define LOC_CFG_PLEN            PLEN_256
#define LOC_CFG_CODE            CODE_5
#define LOC_CFG_NSSFD           1
#define LOC_CFG_DB              DATARATE_850K


#define LOC_CFG_XTALRIM         0x09                    //晶振频偏

//const uint16_t LOC_CFG_ADDR @ 0x1000    = 0x0010;
//const uint16_t LOC_CFG_PANID @ 0x1002   = 0x0001;
//const uint64_t LOC_CFG_EUI @ 0x1004     = 0x0000000000000010;

extern const uint16_t LOC_CFG_ADDR @ 0x1000    = 0x0011;
extern const uint16_t LOC_CFG_PANID @ 0x1002   = 0x0001;
extern const uint16_t LOC_CFG_FRQ @ 0x1004     = LOC_FRQ_G;
extern const uint64_t LOC_CFG_EUI @ 0x1006     = 0x0000000000000010;
extern const uint8_t  LOC_CFG_ID[6] @ 0x100e = {0x06,0x05,0x04,0x03,0x02,0x01};


#endif