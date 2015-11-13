/*
* Copyright (c) 2015,֣������ӿƼ����޹�˾
* All rights reserved.
* 
* �ļ����ƣ�uwb_msg.h
* �ļ���ʶ��
* ժ    Ҫ�����嶨λ��Ϣ����
* 
* ��ǰ�汾��1.0
* ��    �ߣ���ѩ��
* ������ڣ�2015.01.30
*/

#ifndef _UWB_MSG_H_
#define _UWB_MSG_H_
#include <stdint.h>

#define FRAMECTRL_SYNC	0x0BC0
#define FRAMECTRL_LOC	0x83C4

#pragma pack(push,1)
//ͬ��֡
typedef struct 
{
	uint16_t	FrameCtrl;			//֡����
	uint8_t		SeqNum;				//֡���
	uint16_t	NetPANId;			//����PAN ID
	uint16_t	DestinationAddr;	//Ŀ���ַ
	uint8_t		FrameType;			//������
	uint32_t	MasterTimeStamp;	//����ʱ���
	uint8_t		Reserved0;			//����λ
	uint8_t		Reserved1;
	uint16_t	CRCValue;			//CRCУ��
}FrameSync,*pFrameSync;

//�ϰ汾Э��
/*
//��λ֡
typedef struct 
{
	uint16_t	FrameCtrl;			//֡����
	uint8_t		SeqNum;				//���
	uint16_t	NetPANId;			//����PAN ID
	uint16_t	SourceAddr;			//��ǩ�̵�ַ
	uint8_t		Reserved0;			//����
	uint8_t		Reserved1;
	uint16_t	CRCValue;			//CRCУ��
}FrameLoc, *pFrameLoc;*/

//��λ֡
typedef struct
{
	uint8_t		FrameCtrl;			//֡������
	uint8_t		Type;				//��ǩ����
	uint8_t		SeqNum;				//֡���
	uint8_t		TagID[6];			//��ǩ��ַ
	uint8_t		State;				//״ֵ̬
	uint8_t		Tagmsg;				//��ǩ��Ϣλ
	uint16_t	SlotTime;			//ʱ϶��
	uint8_t		Reserved;			//�����ֽ�
	uint16_t	Crc;				//crcУ��
}FrameLoc,*pFrameLoc;

#pragma pack(pop)

#endif
