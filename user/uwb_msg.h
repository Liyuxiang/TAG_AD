/*
* Copyright (c) 2015,郑州联睿电子科技有限公司
* All rights reserved.
* 
* 文件名称：uwb_msg.h
* 文件标识：
* 摘    要：定义定位信息数据
* 
* 当前版本：1.0
* 作    者：何雪锋
* 完成日期：2015.01.30
*/

#ifndef _UWB_MSG_H_
#define _UWB_MSG_H_
#include <stdint.h>

#define FRAMECTRL_SYNC	0x0BC0
#define FRAMECTRL_LOC	0x83C4

#pragma pack(push,1)
//同步帧
typedef struct 
{
	uint16_t	FrameCtrl;			//帧类型
	uint8_t		SeqNum;				//帧序号
	uint16_t	NetPANId;			//网络PAN ID
	uint16_t	DestinationAddr;	//目标地址
	uint8_t		FrameType;			//类型码
	uint32_t	MasterTimeStamp;	//主机时间戳
	uint8_t		Reserved0;			//保留位
	uint8_t		Reserved1;
	uint16_t	CRCValue;			//CRC校验
}FrameSync,*pFrameSync;

//老版本协议
/*
//定位帧
typedef struct 
{
	uint16_t	FrameCtrl;			//帧类型
	uint8_t		SeqNum;				//序号
	uint16_t	NetPANId;			//网络PAN ID
	uint16_t	SourceAddr;			//标签短地址
	uint8_t		Reserved0;			//保留
	uint8_t		Reserved1;
	uint16_t	CRCValue;			//CRC校验
}FrameLoc, *pFrameLoc;*/

//定位帧
typedef struct
{
	uint8_t		FrameCtrl;			//帧控制字
	uint8_t		Type;				//标签类型
	uint8_t		SeqNum;				//帧序号
	uint8_t		TagID[6];			//标签地址
	uint8_t		State;				//状态值
	uint8_t		Tagmsg;				//标签信息位
	uint16_t	SlotTime;			//时隙号
	uint8_t		Reserved;			//保留字节
	uint16_t	Crc;				//crc校验
}FrameLoc,*pFrameLoc;

#pragma pack(pop)

#endif
