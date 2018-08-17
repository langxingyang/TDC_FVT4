/**
  ******************************************************************************
  * @file    usb2uart.h
  * $Author: wdluo $
  * $Revision: 447 $
  * $Date:: 2013-06-29 18:24:57 +0800 #$
  * @brief   usb2uart��غ������������Ͷ���.
  ******************************************************************************
  * @attention
  *
  *<center><a href="http:\\www.usbxyz.com">http://www.usbxyz.com</a></center>
  *<center>All Rights Reserved</center></h3>
  * 
  ******************************************************************************
  */
#ifndef __USB2UART_H_
#define __USB2UART_H_

#include <stdint.h>
#ifndef OS_UNIX
#include <Windows.h>
#else
#include <unistd.h>
#ifndef WINAPI
#define WINAPI
#endif
#endif

//�����ʼ��UART��ʼ����������
typedef struct _UART_CONFIG{
  unsigned int  BaudRate;     //������
  unsigned char WordLength;   //����λ��0-8bit,1-9bit
  unsigned char StopBits;     //ֹͣλ��0-1bit,1-0.5bit,2-2bit,3-1.5bit
  unsigned char Parity;       //��żУ�飬0-No,4-Even,6-Odd
  unsigned char TEPolarity;   //TE������ƣ�0x80-���TE�źţ��ҵ͵�ƽ��Ч��0x81-���TE�źţ��Ҹߵ�ƽ��Ч��0x00�����TE�ź�
}UART_CONFIG,*PUART_CONFIG;

//���庯�����ش������
#define UART_SUCCESS             (0)   //����ִ�гɹ�
#define UART_ERR_NOT_SUPPORT     (-1)  //��������֧�ָú���
#define UART_ERR_USB_WRITE_FAIL  (-2)  //USBд����ʧ��
#define UART_ERR_USB_READ_FAIL   (-3)  //USB������ʧ��
#define UART_ERR_CMD_FAIL        (-4)  //����ִ��ʧ��
//����λ��
#define UART_WORD_LENGTH_8BIT     0
#define UART_WORD_LENGTH_9BIT     1
//ֹͣλ
#define UART_STOP_BITS_1          0
#define UART_STOP_BITS_05         1
#define UART_STOP_BITS_2          2
#define UART_STOP_BITS_15         3
//��żУ��λ
#define UART_PARITY_NO            0
#define UART_PARITY_EVEN          4
#define UART_PARITY_ODD           6
//TE�����ź����
#define UART_TE_DISEN             0x00
#define UART_TE_EN_LOW            0x80
#define UART_TE_EN_HIGH           0x81

#ifdef __cplusplus
extern "C"
{
#endif

int WINAPI UART_Init(int DevHandle, unsigned char Channel, PUART_CONFIG pConfig);
int WINAPI UART_WriteBytes(int DevHandle,unsigned char Channel,unsigned char *pWriteData,int DataSize);
int WINAPI UART_WriteBytesAsync(int DevHandle,unsigned char Channel,unsigned char *pWriteData,int DataSize);
int WINAPI UART_ReadBytes(int DevHandle,unsigned char Channel,unsigned char *pReadData,int TimeOutMs);

#ifdef __cplusplus
}
#endif
#endif
