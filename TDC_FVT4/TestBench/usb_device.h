/**
  ******************************************************************************
  * @file    usb_device.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   USB���ò�����غ������������Ͷ���.
  ******************************************************************************
  * @attention
  *
  *<center><a href="http:\\www.usbxzy.com">http://www.usbxzy.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
#ifndef __USB_DEVICE_H_
#define __USB_DEVICE_H_

#include <stdint.h>
#ifndef OS_UNIX
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif

typedef struct _DEVICE_INFO
{
    char    FirmwareName[32];   //�̼������ַ���
    char    BuildDate[32];      //�̼�����ʱ���ַ���
    int     HardwareVersion;    //Ӳ���汾��
    int     FirmwareVersion;    //�̼��汾��
    int     SerialNumber[3];    //���������к�
    int     Functions;          //��������ǰ�߱��Ĺ���
}DEVICE_INFO,*PDEVICE_INFO;

#ifdef __cplusplus
extern "C"
{
#endif

/**
  * @brief  ��ʼ��USB�豸����ɨ���豸���������������
  * @param  pDevNum ÿ���豸���豸�Ŵ洢��ַ��������Ҫ�豸�ţ����Դ���NULL
  * @retval ɨ�赽���豸����
  */
int  WINAPI USB_ScanDevice(int *pDevHandle);

/**
  * @brief  ���豸���������
  * @param  DevHandle �豸������
  * @retval ���豸��״̬
  */
bool WINAPI USB_OpenDevice(int DevHandle);

/**
  * @brief  �ر��豸
  * @param  DevHandle �豸������
  * @retval �ر��豸��״̬
  */
bool WINAPI USB_CloseDevice(int DevHandle);

/**
  * @brief  ��ȡ�豸��Ϣ�������豸���ƣ��̼��汾�ţ��豸��ţ��豸����˵���ַ�����
  * @param  DevHandle �豸������
  * @param  pDevInfo �豸��Ϣ�洢�ṹ��ָ��
  * @param  pFunctionStr �豸����˵���ַ���
  * @retval ��ȡ�豸��Ϣ��״̬
  */
bool WINAPI DEV_GetDeviceInfo(int DevHandle,PDEVICE_INFO pDevInfo,char *pFunctionStr);

/**
  * @brief  �����û�������
  * @param  DevHandle �豸������
  * @retval �û������ݲ���״̬
  */
bool WINAPI DEV_EraseUserData(int DevHandle);

/**
  * @brief  ���û�����д���û��Զ������ݣ�д������֮ǰ��Ҫ���ò������������ݲ���
  * @param  DevHandle �豸������
  * @param  OffsetAddr ����д��ƫ�Ƶ�ַ����ʼ��ַΪ0x00���û���������Ϊ0x10000�ֽڣ�Ҳ����64KBye
  * @param  pWriteData �û����ݻ������׵�ַ
  * @param  DataLen ��д��������ֽ���
  * @retval д���û��Զ�������״̬
  */
bool WINAPI DEV_WriteUserData(int DevHandle,int OffsetAddr,unsigned char *pWriteData,int DataLen);

/**
  * @brief  ���û��Զ�����������������
  * @param  DevHandle �豸������
  * @param  OffsetAddr ����д��ƫ�Ƶ�ַ����ʼ��ַΪ0x00���û���������Ϊ0x10000�ֽڣ�Ҳ����64KBye
  * @param  pReadData �û����ݻ������׵�ַ
  * @param  DataLen �������������ֽ���
  * @retval �����û��Զ������ݵ�״̬
  */
bool WINAPI DEV_ReadUserData(int DevHandle,int OffsetAddr,unsigned char *pReadData,int DataLen);

/**
  * @brief  ���ÿɱ��ѹ������������ѹֵ
  * @param  DevHandle �豸������
  * @param  PowerLevel �����ѹֵ��0-1.8V��1-3.3V
  * @retval ���������ѹ״̬
  */
bool WINAPI DEV_SetPowerLevel(int DevHandle,char PowerLevel);

#ifdef __cplusplus
}
#endif

#endif

