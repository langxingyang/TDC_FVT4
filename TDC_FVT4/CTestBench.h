#pragma once

#ifndef __CTestBench_H_
#define __CTestBench_H_

#include ".//TestBench/usb_device.h"
#include ".//TestBench/usb2adc.h"
#include ".//TestBench/usb2gpio.h"
#include ".//TestBench/usb2pwm.h"
#include ".//TestBench/usb2spi.h"
#include ".//TestBench/usb2uart.h" 
#include ".//TestBench/usb2iic.h" 
#include ".//TestBench/usb2ow.h"
#include<vector>
using namespace std;
extern vector<int> read_temp;


#ifdef __cplusplus
extern "C"
{
#endif

//	int Get_DevHandle();
//	BOOL PWM_Driver(int channel_id, int frequence, int duty_cycle);

class CTestBench
{
public:
	int DevHandle;
	int I2Cindex = 0;
	int GPIOAddr_0x20;
	int GPIOAddr_0x21;
	int PWM_Channel;
	int Internal_IO_Address;
	CString testbench_info;
	//定义GPIO地址:I2C_PCF8574模块
	//I2C Slave 地址 0x20
	int I2C_IO_0 = 0x20;
	int  GPIO0_Address = 0x01;
	int  GPIO1_Address = 0x02;
	int  GPIO2_Address = 0x04;
	int  GPIO3_Address = 0x08;
	int  GPIO4_Address = 0x10;
	int  GPIO5_Address = 0x20;
	int  GPIO6_Address = 0x40;
	int  GPIO7_Address = 0x80;

	//定义GPIO地址:I2C_PCF8574模块
	//I2C Slave 地址 0x21
	int I2C_IO_1 = 0x21;
	int  GPIO8_Address = 0x01;
	int  GPIO9_Address = 0x02;
	int  GPIO10_Address = 0x04;
	int  GPIO11_Address = 0x08;
	int  GPIO12_Address = 0x10;
	int  GPIO13_Address = 0x20;
	int  GPIO14_Address = 0x40;
	int  GPIO15_Address = 0x80;

	//定义 PWM 通道地址
	int PWM_Address[8] = { 0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80 };
	
	CTestBench();
	~CTestBench();
	int CTestBench::Get_DevHandle();
	BOOL CTestBench::PWM_InitT(int ChannelMask);
	BOOL CTestBench::PWM_InitT_Close(int ChannelMask);
	BOOL CTestBench::PWM_InitT_Far(int ChannelMask);
	BOOL CTestBench::IO_Init(int SlaveAddr);
	BOOL CTestBench::IO_Action(int SlaveAddr, int io_id);
	BOOL CTestBench::IO_To_Close(int SlaveAddr, int io_id);
	BOOL CTestBench::IO_To_Open(int SlaveAddr, int io_id);
	BOOL CTestBench::IO_Close(int SlaveAddr,int io_id);
	CString CTestBench::CharToWchar(const char* c, size_t m_encode = CP_ACP);
	CString CTestBench::WcharToChar(const wchar_t* wp, size_t m_encode = CP_ACP);
	BOOL CTestBench::PWM_StartT(unsigned char ChannelMask, unsigned int RunTimeUs);
	BOOL CTestBench::PWM_StopT(unsigned char ChannelMask);
	int CTestBench::ADC_Measurement(int SlaveAddr,int channel_id);
	int CTestBench::ADC_Current_Measurement(int SlaveAddr, int channel_id);
	BOOL CTestBench::Close_Dev();
	BOOL CTestBench::Internet_IO_Init(int Internal_IO_ID);
	BOOL CTestBench::Internet_IO_Open(int IO_id);
	BOOL CTestBench::Internet_IO_Close(int IO_id);
	int CTestBench::Internet_IO_Read(int IO_id);
	float CTestBench::DS18B20(int IO_id);
	void CTestBench::MySleep(DWORD nMilliseconds);
	void CTestBench::BitToZero(int& value, int index);

//	BOOL CTestBench::Internet_IO_Action(int IO_id);

};

#ifdef __cplusplus
}
#endif
#endif
