/*
* Copyright (c) 2015,֣������ӿƼ����޹�˾
* All rights reserved.
* 
* �ļ����ƣ�uwb.c
* �ļ���ʶ��
* ժ    Ҫ������������Ϣ
* 
* ��ǰ�汾��0.1
* ��    �ߣ���ѩ��
* ������ڣ�2015.02.24
*/

#include "locadef.h"
#include "uwb_def.h"
#include "deca_device_api.h"
#include "deca_regs.h"
#include "uwb_msg.h"
#include "bsp.h"
#include "config.h"


const uint8_t	dwt_pgdelay[8] = {0x00,0xC9,0xC2,0xC5,0x95,0xC0,0x00,0x93};
const uint32_t	dwt_manualpwr[2][8] = {
	{0x00000000,0x7B7B7B7B,0x7B7B7B7B,0x75757575,0x3F3F3F3F,0x4E4E4E4E,0x00000000,0x98989898},      //����3db
	{0x00000000,0x6D6D6D6D,0x6D6D6D6D,0x91919191,0x7A7A7A7A,0x8B8B8B8B,0x00000000,0xB1B1B1B1}};

FrameLoc msgbuf;

/*
*********************************************************************************************************
*                                      �ֲ���������
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                             
*                               static loca_status dwt_init(void)
*
* ��     �� : ��ʼ��DW1000
*
* ������� :none 
*  
*
* ������� :DW1000״̬
*
*********************************************************************************************************
*/
static loca_status dwt_init(void)
{
  volatile uint32_t devid;
  
  BSP_ResetDWT();                       //��λDW1000
  
  BSP_ChangeSPIRate(SPI_SLOW);
  
  devid = dwt_readdevid();
  if (DWT_DEVICE_ID != devid)
  {
    BSP_WakeDWT();
    devid = dwt_readdevid();
    if (DWT_DEVICE_ID != devid)
      return LOCA_FAULT;
  }
  
  //dw1000_intenable();
  BSP_ChangeSPIRate(SPI_FAST);
  return LOCA_OK;
}


/*
*********************************************************************************************************
*
*  loca_status dwt_config(eCHAN channel, ePRF prf, ePLEN PreambleLength, eCODE code, uint8_t nsSFD, DataRate db)
*
* ��     �� : ����DW1000
*
* ������� : 
*       channel��DW1000ͨ��
        prf��
        PreambleLength��
        code��
        nsSFD��
        db��
*
* ������� : DW1000״̬
*********************************************************************************************************
*/
static loca_status dwt_config(eCHAN channel, ePRF prf, ePLEN PreambleLength, eCODE code, uint8_t nsSFD, DataRate db)
{
  dwt_config_t  config;
  dwt_txconfig_t txconfig;
  uint8_t buf[2];
  uint64_t      eui64;
  uint16_t      panid;
  
  eui64 = LOC_CFG_EUI;
  panid = LOC_CFG_PANID;
  
  config.chan   = channel;
  config.prf    = prf;
  
  config.txPreambLength = PreambleLength;
  
  switch (PreambleLength)
  {
  case PLEN_64:
  case PLEN_128:
    config.rxPAC        = DWT_PAC8;
    break;
  case PLEN_256:
  case PLEN_512:
    config.rxPAC	= DWT_PAC16;
    break;
  case PLEN_1024:
    config.rxPAC	= DWT_PAC32;
    break;
  default:
    config.rxPAC	= DWT_PAC64;
    break;
  }
  
  config.rxCode		= code;
  config.txCode		= code;
  config.nsSFD		= nsSFD;
  config.dataRate       = db;
  config.smartPowerEn	= 0;
  config.phrMode	= 0;
  
  txconfig.PGdly        = dwt_pgdelay[channel];
  txconfig.power	= dwt_manualpwr[prf - 1][channel];
  
  BSP_ChangeSPIRate(SPI_SLOW);
  dwt_softreset();
  if (dwt_initialise(DWT_LOADNONE) != DWT_SUCCESS)
  {
    BSP_ChangeSPIRate(SPI_FAST);
    return LOCA_FAULT;
  }
   
  BSP_ChangeSPIRate(SPI_FAST);
  
  if (dwt_readdevid() != DWT_DEVICE_ID)
  {
    return LOCA_FAULT;
  }
  
  buf[0] = 0x10;
  dwt_writetodevice(GPIO_CTRL_ID,0x02,1,&buf[0]);

  buf[0] = 0xf0;
  buf[1] = 0xf0;
  dwt_writetodevice(GPIO_CTRL_ID,0x08,2,&buf[0]);
  
  dwt_configure(&config, 0);
  dwt_xtaltrim(LOC_CFG_XTALRIM);
  dwt_setrxantennadelay(0);
  dwt_settxantennadelay(0);
  dwt_setsmarttxpower(0);
  dwt_configuretxrf(&txconfig);
  
  dwt_enableframefilter(DWT_FF_NOTYPE_EN);
  dwt_seteui((uint8_t *)&eui64);
  dwt_setpanid(panid);
  //����Ӳ���ж�
  //BSP_DWTIntEnable();
  
 // dwt_setinterrupt( DWT_INT_TFRS, 1);
  dwt_setrxmode(DWT_RX_NORMAL,0,0);
  return LOCA_OK;
}

/*
*********************************************************************************************************
*                              static void buf_init(void)
*
* ��     �� : ��ʼ������֡
*
* ������� : none
*
* ������� : none
*********************************************************************************************************
*/
static void buf_init(void)
{
  msgbuf.FrameCtrl      = 0x11;
  msgbuf.Type           = 0x00;
  msgbuf.SeqNum         = 0;
  memcpy(msgbuf.TagID,LOC_CFG_ID, 6);
  //msgbuf.NetPANId       = LOC_CFG_PANID;
 // msgbuf.SourceAddr     = LOC_CFG_ADDR;
  msgbuf.State          = 0;
  msgbuf.Tagmsg         = 0;
  msgbuf.SlotTime       = 0;
  msgbuf.Reserved      = 0;
 // msgbuf.Reserved1      = 0;
}

/*
*********************************************************************************************************
*                                      ȫ�ֺ�������
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                              void UWB_DWTSleep(void)
*
* ��     �� : DW1000����͹���ģʽ
*
* ������� : none
*
* ������� : none
*********************************************************************************************************
*/
void UWB_DWTSleep(void)
{
  dwt_configuresleep(DWT_CONFIG , DWT_WAKE_WK | DWT_SLP_EN);
  dwt_entersleep();
}



/*
*********************************************************************************************************
*                              void UWB_Init(void)
*
* ��     �� : ��ʼ��DW1000
*
* ������� : none
*
* ������� : none
*********************************************************************************************************
*/
void UWB_Init(void)
{
  dwt_init();                   //dw1000��ʼ��
  
  dwt_config(LOC_CFG_CHAN, LOC_CFG_PRF, LOC_CFG_PLEN, LOC_CFG_CODE, LOC_CFG_NSSFD, LOC_CFG_DB);         //����DW1000
  
  //����DW1000����˯��ģʽ
  UWB_DWTSleep();
  
  buf_init();
}

/*
*********************************************************************************************************
*                              void UWB_SendMsg(void)
*
* ��     �� : UWB������Ϣ
*
* ������� : none
*
* ������� : none
*********************************************************************************************************
*/
void UWB_SendMsg(void)
{
  dwt_configuresleep(DWT_CONFIG , DWT_WAKE_WK | DWT_SLP_EN);
  dwt_entersleepaftertx(1);
  
  dwt_writetxdata(sizeof(FrameLoc), (uint8_t *)&msgbuf, 0x00);
  dwt_writetxfctrl(sizeof(FrameLoc), 0x00);
  dwt_starttx(DWT_START_TX_IMMEDIATE);
  msgbuf.SeqNum ++;
}
