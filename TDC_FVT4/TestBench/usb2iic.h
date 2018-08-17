/**
  ******************************************************************************
  * @file    usb2iic.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   usb2iic��غ������������Ͷ���.
  ******************************************************************************
  * @attention
  *
  *<center><a href="http:\\www.usbxyz.com">http://www.usbxyz.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
#ifndef __USB2IIC_H_
#define __USB2IIC_H_

#include <stdint.h>
#ifndef OS_UNIX
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif

//�����ʼ��IIC����������
typedef struct _IIC_CONFIG{
  unsigned int    ClockSpeedHz; //IICʱ��Ƶ��:��λΪHz
  unsigned short  OwnAddr;      //USB2XXXΪ�ӻ�ʱ�Լ��ĵ�ַ
  unsigned char   Master;       //����ѡ�����:0-�ӻ���1-����
  unsigned char   AddrBits;     //�ӻ���ַģʽ��7-7bitģʽ��10-10bitģʽ
  unsigned char   EnablePu;     //ʹ������оƬ�ڲ��������裬����ʹ�ܣ���I2C�����ϱ������������
}IIC_CONFIG,*PIIC_CONFIG;

//���庯�����ش������
#define IIC_SUCCESS             (0)   //����ִ�гɹ�
#define IIC_ERR_NOT_SUPPORT     (-1)  //��������֧�ָú���
#define IIC_ERR_USB_WRITE_FAIL  (-2)  //USBд����ʧ��
#define IIC_ERR_USB_READ_FAIL   (-3)  //USB������ʧ��
#define IIC_ERR_CMD_FAIL        (-4)  //����ִ��ʧ��
#define IIC_ERR_PARA_ERROR      (-5)  //�����������
//����IIC�������ش������
#define IIC_ERROR_SUCCESS     0   //�����ɹ�
#define IIC_ERROR_CHANNEL     1   //��ͨ����֧�ָú���
#define IIC_ERROR_BUSY        2   //����æ
#define IIC_ERROR_START_FAILD 3   //��������ʧ��
#define IIC_ERROR_TIMEOUT     4   //��ʱ
#define IIC_ERROR_NACK        5   //�ӻ���Ӧ��
#define IIC_ERROR_PEC         6   //PECУ��ʧ��
#ifdef __cplusplus
extern "C"
{
#endif

int WINAPI IIC_Init(int DevHandle,int IICIndex, PIIC_CONFIG pConfig);
int WINAPI IIC_GetSlaveAddr(int DevHandle,int IICIndex,short *pSlaveAddr);
int WINAPI IIC_WriteBytes(int DevHandle,int IICIndex,short SlaveAddr,unsigned char *pWriteData,int WriteLen,int TimeOutMs);
int WINAPI IIC_ReadBytes(int DevHandle,int IICIndex,short SlaveAddr,unsigned char *pReadData,int ReadLen,int TimeOutMs);
int WINAPI IIC_WriteReadBytes(int DevHandle,int IICIndex,short SlaveAddr,unsigned char *pWriteData,int WriteLen,unsigned char *pReadData,int ReadLen,int TimeOutMs);
int WINAPI IIC_SlaveWriteBytes(int DevHandle,int IICIndex,unsigned char *pWriteData,int WriteLen,int TimeOutMs);
int WINAPI IIC_SlaveReadBytes(int DevHandle,int IICIndex,unsigned char *pReadData,int TimeOutMs);
int WINAPI IIC_SlaveWriteRemain(int DevHandle,int IICIndex);

int WINAPI IIC_WriteBytesOfEvent(int DevHandle,int IICIndex,short SlaveAddr,unsigned char *pWriteData,int WriteLen,int EventPin,unsigned char EventType,int TimeOutOfEventMs);
int WINAPI IIC_ReadBytesOfEvent(int DevHandle,int IICIndex,short SlaveAddr,unsigned char *pReadData,int ReadLen,int EventPin,unsigned char EventType,int TimeOutOfEventMs);
int WINAPI IIC_WriteReadBytesOfEvent(int DevHandle,int IICIndex,short SlaveAddr,unsigned char *pWriteData,int WriteLen,unsigned char *pReadData,int ReadLen,int EventPin,unsigned char EventType,int TimeOutOfEventMs);

int WINAPI SMBUS_Init(int DevHandle,int IICIndex,int ClockSpeedHz,unsigned char EnablePu);
int WINAPI SMBUS_QuickCommand(int DevHandle,int IICIndex,short SlaveAddr,unsigned char WriteReadFlag);
int WINAPI SMBUS_WriteByte(int DevHandle,int IICIndex,short SlaveAddr,unsigned char Data,unsigned char WithPEC);
int WINAPI SMBUS_ReadByte(int DevHandle,int IICIndex,short SlaveAddr,unsigned char *pData,unsigned char WithPEC);
int WINAPI SMBUS_WriteByteProtocol(int DevHandle,int IICIndex,short SlaveAddr,unsigned char CommandCode, unsigned char Data,unsigned char WithPEC);
int WINAPI SMBUS_WriteWordProtocol(int DevHandle,int IICIndex,short SlaveAddr,unsigned char CommandCode, unsigned short Data,unsigned char WithPEC);
int WINAPI SMBUS_ReadByteProtocol(int DevHandle,int IICIndex,short SlaveAddr,unsigned char CommandCode, unsigned char *pData,unsigned char WithPEC);
int WINAPI SMBUS_ReadWordProtocol(int DevHandle,int IICIndex,short SlaveAddr,unsigned char CommandCode, unsigned short *pData,unsigned char WithPEC);
int WINAPI SMBUS_ProcessCall(int DevHandle,int IICIndex,short SlaveAddr,unsigned char CommandCode, unsigned short WriteData, unsigned short *pReadData,unsigned char WithPEC);
int WINAPI SMBUS_BlockWrite(int DevHandle,int IICIndex,short SlaveAddr,unsigned char CommandCode, unsigned char *pWriteData,int WriteCount,unsigned char WithPEC);
int WINAPI SMBUS_BlockRead(int DevHandle,int IICIndex,short SlaveAddr,unsigned char CommandCode, unsigned char *pReadData,int *pReadCount,unsigned char WithPEC);
int WINAPI SMBUS_BlockProcessCall(int DevHandle,int IICIndex,short SlaveAddr,unsigned char CommandCode, unsigned char *pWriteData,int WriteCount, unsigned char *pReadData,int *pReadCount,unsigned char WithPEC);

#ifdef __cplusplus
}
#endif
#endif
