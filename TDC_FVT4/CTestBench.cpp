#include <stdlib.h>
#include <stdio.h>lib
#include <string.h>
#include "stdafx.h"
//#include <iostream>
//#include <cassert>
//#include <vector>
#include "CTestBench.h"
#include ".//TestBench/usb_device.h"
#include ".//TestBench/usb2adc.h"
#include ".//TestBench/usb2gpio.h"
#include ".//TestBench/usb2pwm.h"
#include ".//TestBench/usb2spi.h"
#include ".//TestBench/usb2uart.h" 
#include ".//TestBench/usb2iic.h" 
#include ".//TestBench/usb2ow.h"

#pragma comment(lib,".//TestBench/USB2XXX.lib")
//#pragma comment(lib,".//TestBench/USB2XXX_OW.lib")

#define GET_FIRMWARE_INFO   1

//定义错误代码
#define NO_USB_CONNECTION -1;
#define USB_OPEN_ERROR -2;

//定义GPIO地址:I2C_PCF8574模块
//I2C Slave 地址 0x20
#define GPIO0 = 0x01;
#define GPIO1 = 0x02;
#define GPIO2 = 0x04;
#define GPIO3 = 0x08;
#define GPIO4 = 0x10;
#define GPIO5 = 0x20;
#define GPIO6 = 0x40;
#define GPIO7 = 0x80;

//定义GPIO地址:I2C_PCF8574模块
//I2C Slave 地址 0x21
#define GPIO8 = 0x01;
#define GPIO9 = 0x02;
#define GPIO10 = 0x04;
#define GPIO11 = 0x08;
#define GPIO12 = 0x10;
#define GPIO13 = 0x20;
#define GPIO14 = 0x40;
#define GPIO15 = 0x80;

#define GPIO_ALL_ON = 0xFF;
#define GPIO_ALL_OFF = 0x00;



CTestBench::CTestBench()
{
}


CTestBench::~CTestBench()
{
}


int CTestBench::Get_DevHandle()
{
	#if GET_FIRMWARE_INFO
	DEVICE_INFO DevInfo;
	#endif
	int DevHandleT[10];
	bool state;
	int ret;
	//扫描查找设备
	ret = USB_ScanDevice(DevHandleT);
	if (ret <= 0) {
		AfxMessageBox(_T("No USB device connected!"));
		return NO_USB_CONNECTION;
	}
	//打开设备
	state = USB_OpenDevice(DevHandleT[0]);
	if (!state) {
		AfxMessageBox(_T("Open USB Device Error!"));
		return USB_OPEN_ERROR;
	}
	#if GET_FIRMWARE_INFO
	char FunctionStr[256] = { 0 };
	//获取固件信息
	state = DEV_GetDeviceInfo(DevHandleT[0], &DevInfo, FunctionStr);
	if (!state) {
		AfxMessageBox(_T("Get device infomation error!"));
		return USB_OPEN_ERROR;
	}
	else {
		CString device_info;
		CString fw_date, fw_version, hardware_version, sn;
		device_info = _T("Product Name: KICKMAKER Test Bench V1.0\r\n");
		device_info = device_info + _T("Firmware Info:\r\n");
		//fw_name.Format(_T("Firmware Name:%s\r\n"), CTestBench::CharToWchar(DevInfo.FirmwareName));
		fw_date.Format(_T("Firmware Build Date:%s\r\n"), CTestBench::CharToWchar(DevInfo.BuildDate));
		fw_version.Format(_T("Firmware Version:v%d.%d.%d\r\n"), (DevInfo.FirmwareVersion >> 24) & 0xFF, (DevInfo.FirmwareVersion >> 16) & 0xFF, DevInfo.FirmwareVersion & 0xFFFF);
		hardware_version.Format(_T("Hardware Version:v%d.%d.%d\r\n"), (DevInfo.HardwareVersion >> 24) & 0xFF, (DevInfo.HardwareVersion >> 16) & 0xFF, DevInfo.HardwareVersion & 0xFFFF);
		sn.Format(_T("Product Serial Number:%d.\r\n"), DevInfo.SerialNumber[2]);
		//fw_function.Format(_T("Firmware Functions:%s\r\n"), CTestBench::CharToWchar(FunctionStr));
		device_info = device_info + fw_date + fw_version + hardware_version + sn ;
		testbench_info = device_info;
		//AfxMessageBox(device_info);
	}
	#endif
	DevHandle = DevHandleT[0];
	//Internal_IO_Address = 0x00;
	//GPIOAddr = 0x00;
	return DevHandleT[0];
}

BOOL CTestBench::PWM_InitT(int ChannelMask)
{
	PWM_CONFIG PWMConfig;
	PWMConfig.ChannelMask = ChannelMask;//初始化所有通道
	for (int i = 0; i<8; i++) {
		PWMConfig.Polarity[i] = 0;//将所有PWM通道都设置为正极性
	}
	for (int i = 0; i<8; i++) {
		PWMConfig.Precision[i] = 5;//将所有通道的占空比调节精度都设置为1%
	}
	for (int i = 0; i<8; i++) {
		PWMConfig.Prescaler[i] = 100;//将所有通道的预分频器都设置为10，则PWM输出频率为200MHz/(PWMConfig.Precision*PWMConfig.Prescaler)
	}
	for (int i = 0; i<8; i++) {
		PWMConfig.Pulse[i] = PWMConfig.Precision[i] * 50 / 100;//将所有通道的占空比都设置为30%
	}
	int ret = PWM_Init(DevHandle, &PWMConfig);
	if (ret != PWM_SUCCESS) {
		AfxMessageBox(_T("Initialize pwm faild!"));
		return FALSE;
	}
	ret = PWM_Stop(DevHandle,0xFF);
	if (ret != PWM_SUCCESS) {
		AfxMessageBox(_T("Initialize pwm faild!"));
		return FALSE;
	}
	else {
		//AfxMessageBox(_T("Initialize pwm sunccess!\n"));
		return TRUE;
	}
}

BOOL CTestBench::PWM_InitT_Close(int ChannelMask)
{
	PWM_CONFIG PWMConfig;
	PWMConfig.ChannelMask = ChannelMask;//初始化所有通道
	for (int i = 0; i<8; i++) {
		PWMConfig.Polarity[i] = 0;//将所有PWM通道都设置为正极性
	}
	for (int i = 0; i<8; i++) {
		PWMConfig.Precision[i] = 20;//将所有通道的占空比调节精度都设置为1%
	}
	for (int i = 0; i<8; i++) {
		PWMConfig.Prescaler[i] = 100;//将所有通道的预分频器都设置为10，则PWM输出频率为200MHz/(PWMConfig.Precision*PWMConfig.Prescaler)
	}
	for (int i = 0; i<8; i++) {
		PWMConfig.Pulse[i] = PWMConfig.Precision[i] * 50 / 100;//将所有通道的占空比都设置为30%
	}
	int ret = PWM_Init(DevHandle, &PWMConfig);
	if (ret != PWM_SUCCESS) {
		AfxMessageBox(_T("Initialize pwm faild!"));
		return FALSE;
	}
	else {
		//AfxMessageBox(_T("Initialize pwm sunccess!\n"));
		return TRUE;
	}
}

BOOL CTestBench::PWM_InitT_Far(int ChannelMask)
{
	PWM_CONFIG PWMConfig;
	PWMConfig.ChannelMask = ChannelMask;//初始化所有通道
	for (int i = 0; i<8; i++) {
		PWMConfig.Polarity[i] = 0;//将所有PWM通道都设置为正极性
	}
	for (int i = 0; i<8; i++) {
		PWMConfig.Precision[i] = 20;//将所有通道的占空比调节精度都设置为1%
	}
	for (int i = 0; i<8; i++) {
		PWMConfig.Prescaler[i] = 100;//将所有通道的预分频器都设置为10，则PWM输出频率为200MHz/(PWMConfig.Precision*PWMConfig.Prescaler)
	}
	for (int i = 0; i<8; i++) {
		PWMConfig.Pulse[i] = PWMConfig.Precision[i] * 50 / 100;//将所有通道的占空比都设置为30%
	}
	int ret = PWM_Init(DevHandle, &PWMConfig);
	if (ret != PWM_SUCCESS) {
		AfxMessageBox(_T("Initialize pwm faild!"));
		return FALSE;
	}
	else {
		//AfxMessageBox(_T("Initialize pwm sunccess!\n"));
		return TRUE;
	}
}

BOOL CTestBench::IO_Init(int SlaveAddr)
{
	IIC_CONFIG I2C_Config;
	I2C_Config.EnablePu = 1;            //使能内部上拉电阻
	I2C_Config.AddrBits = 7;            //7bit地址模式
	I2C_Config.ClockSpeedHz = 100000;   //时钟频率100KHz
	I2C_Config.Master = 1;              //主机模式
	int GPIOAddr = 0x00;
	if (SlaveAddr == 0x20) {
		GPIOAddr_0x20 = 0x00;
		GPIOAddr = GPIOAddr_0x20;
	}
	else {
		GPIOAddr_0x21 = 0x00;
		GPIOAddr = GPIOAddr_0x21;
	}
	int ret = IIC_Init(DevHandle,I2Cindex,&I2C_Config);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("Config I2C IO faild!"));
		return FALSE;
	}
	//unsigned char command[] = { 0x80 };
	//ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, &command[0], sizeof(command), 10);
	//if (ret != IIC_SUCCESS) {
	//	AfxMessageBox(_T("Initialize I2C IO faild!"));
	//	return FALSE;
	//}
	//ret = CTestBench::IO_Action(SlaveAddr, 0xFF);
	//if (ret == FALSE) {
	//	AfxMessageBox(_T("Initialize IO All Channel setting to 0 faild!"));
	//	return FALSE;
	//}
	//else {
	//	return TRUE;
	//}
	unsigned char command[] = { 0x00 };
	ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, command, sizeof(command), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C IO All Open faild!"));
		return FALSE;
	}
	MySleep(1000);
	command[0] = 0xFF;
	ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, command, sizeof(command), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C IO All Close faild!"));
		return FALSE;
	}
	else {
		return TRUE;
	}
}

BOOL CTestBench::IO_Action(int SlaveAddr,int io_id)
{
	//GPIOAddr = 0x00;
	int GPIOAddr = 0xFF;
	unsigned char GPIO_Read_Result[1];
	int ret = IIC_ReadBytes(DevHandle, I2Cindex, SlaveAddr, GPIO_Read_Result, sizeof(GPIO_Read_Result), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C IO Read faild!"));
		return FALSE;
	}
	GPIOAddr = GPIO_Read_Result[0] ^ (1 << (io_id));

	//if (GPIO_Read_Result[0] >= 0x80) {
	//	GPIOAddr = 0x00 + (0x01 << io_id);
	//}
	//else {
	//	GPIOAddr = GPIO_Read_Result[0] + (0x01 << io_id);
	//}
	//if (SlaveAddr == 0x20 ) {
	//	GPIOAddr_0x20 = GPIOAddr_0x20 + 0x01 << io_id;
	//	GPIOAddr = GPIOAddr_0x20;
	//}
	//else {
	//	GPIOAddr_0x20 = GPIOAddr_0x21 + 0x01 << io_id;
	//	GPIOAddr = GPIOAddr_0x21;
	//}

	unsigned char command[] = { GPIOAddr };
	ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, &command[0], sizeof(command), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C IO Open faild!"));
		return FALSE;
	}
	else {
		return TRUE;
	}
}

BOOL CTestBench::IO_To_Open(int SlaveAddr, int io_id)
{
	//GPIOAddr = 0x00;
	int GPIOAddr = 0xFF;
	int sub_address = 0x01 << io_id;
	unsigned char GPIO_Read_Result[1];
	int ret = IIC_ReadBytes(DevHandle, I2Cindex, SlaveAddr, GPIO_Read_Result, sizeof(GPIO_Read_Result), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C IO Read faild!"));
		return FALSE;
	}
	GPIOAddr = GPIO_Read_Result[0] | sub_address;

	unsigned char command[] = { GPIOAddr };
	ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, &command[0], sizeof(command), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C IO Open faild!"));
		return FALSE;
	}
	else {
		return TRUE;
	}
}


BOOL CTestBench::IO_To_Close(int SlaveAddr, int io_id)
{
	//GPIOAddr = 0x00;
	int GPIOAddr = 0xFF;
	unsigned char GPIO_Read_Result[1];
	int ret = IIC_ReadBytes(DevHandle, I2Cindex, SlaveAddr, GPIO_Read_Result, sizeof(GPIO_Read_Result), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C IO Read faild!"));
		return FALSE;
	}
	int sub_address = GPIO_Read_Result[0];
	BitToZero(sub_address, io_id);
	GPIOAddr = sub_address;

	unsigned char command[] = { GPIOAddr };
	ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, &command[0], sizeof(command), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C IO Open faild!"));
		return FALSE;
	}
	else {
		return TRUE;
	}
}




BOOL CTestBench::IO_Close(int SlaveAddr,int io_id)
{
	int GPIOAddr = 0x00;
	unsigned char GPIO_Read_Result[1];
	int ret = IIC_ReadBytes(DevHandle, I2Cindex, SlaveAddr, GPIO_Read_Result, sizeof(GPIO_Read_Result), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C IO Read faild!"));
		return FALSE;
	}
	if ((GPIO_Read_Result[0] >= 0x80) || (GPIO_Read_Result[0] <= 0x01 )) {
		GPIOAddr = 0x80;
	}
	else {
		GPIOAddr = GPIO_Read_Result[0] - (0x01 << io_id);
	}
	//if (SlaveAddr == 0x20) {
	//	GPIOAddr_0x20 = GPIOAddr_0x20 - 0x01 << io_id;
	//	GPIOAddr = GPIOAddr_0x20;
	//}
	//else {
	//	GPIOAddr_0x20 = GPIOAddr_0x21 - 0x01 << io_id;
	//	GPIOAddr = GPIOAddr_0x21;
	//}
	unsigned char command[] = { GPIOAddr };
    ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, &command[0], sizeof(command), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C IO Close faild!"));
		return FALSE;
	}
	else {
		return TRUE;
	}
}

CString CTestBench::CharToWchar(const char* c, size_t m_encode)
{
	CString str;
	int len = MultiByteToWideChar(m_encode, 0, c, strlen(c), NULL, 0);
	wchar_t*    m_wchar = new wchar_t[len + 1];
	MultiByteToWideChar(m_encode, 0, c, strlen(c), m_wchar, len);
	m_wchar[len] = '\0';
	str = m_wchar;
	delete m_wchar;
	return str;
}

CString CTestBench::WcharToChar(const wchar_t* wp, size_t m_encode)
{
	CString str;
	int len = WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
	char    *m_char = new char[len + 1];
	WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	str = m_char;
	delete m_char;
	return str;
}

BOOL CTestBench::PWM_StartT(unsigned char ChannelMask, unsigned int RunTimeUs)
{
	int ret = PWM_Start(DevHandle, ChannelMask, RunTimeUs);
	if (ret != PWM_SUCCESS) {
		AfxMessageBox(_T("PWM Start Running faild!"));
		return FALSE;
	}
	else {
		return TRUE;
	}
}

BOOL CTestBench::PWM_StopT(unsigned char ChannelMask)
{
	int ret = PWM_Stop(DevHandle, ChannelMask);
	if (ret != PWM_SUCCESS) {
		AfxMessageBox(_T("PWM Stop faild!"));
		return FALSE;
	}
	else {
		return TRUE;
	}
}

int CTestBench::ADC_Measurement(int SlaveAddr, int channel_id)
{
	unsigned char command[4][3];
	unsigned char read_result[2];
	int voltage = 0;
	command[0][0] = command[1][0] = command[2][0] = command[3][0] = 0x01;
	command[0][2] = command[1][2] = command[2][2] = command[3][2] = 0x83;
	if (channel_id == 0) {
		command[0][1] = 0xC0;
	}
	else if (channel_id == 1) {
		command[1][1] = 0xD0;
	}
	else if (channel_id == 2) {
		command[2][1] = 0xE0;
	}
	else if (channel_id == 3) {
		command[3][1] = 0xF0;
	}
	else {
		AfxMessageBox(_T("Channel ID out of testbench Configuration."));
		return -100;
	}
	int ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, command[channel_id], sizeof(command[channel_id]), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C ADC Config - Write Config Register faild!"));
		return -100;
	}
	unsigned char command_conversion[2];
	command_conversion[0] = { 0x01 };
	ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, command_conversion, 1, 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C ADC Config - Change to Conversion Register faild!"));
		return -100;
	}
	ret = IIC_ReadBytes(DevHandle, I2Cindex, SlaveAddr, read_result, sizeof(read_result), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C ADC Read Config faild!"));
		return -100;
	}
	if (read_result[1] != 0x83) {
		AfxMessageBox(_T("I2C ADC Read Config faild!"));
		return -100;
	}
	command_conversion[0] = { 0x00 };
	// int read_temp[20];
	//Sleep(1000);
	int x = 0;
	vector<int> read_temp;
	ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, command_conversion, 1, 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C ADC Config - Change to Conversion Register faild!"));
		return -100;
	}
	for (int i = 0; i < 30; i++) {
		//Sleep(100);
		ret = IIC_ReadBytes(DevHandle, I2Cindex, SlaveAddr,read_result, sizeof(read_result), 10);
		if (ret != IIC_SUCCESS) {
			AfxMessageBox(_T("I2C ADC Read Voltage faild!"));
			return -100;
		}

		int register_result = read_result[0] * 0x100 + read_result[1]; //0x40 0.013V offset
		if (register_result > 0x7FFF) {
			register_result = 0;
		}
		int voltage_temp = 6144 * register_result / 0x7FFF;
		if (voltage_temp > 0) {
			read_temp.push_back(voltage_temp);
			x++;
		}
	
		//Sleep(20);
	}
	int sum_read = 0;
	for (int i = 10; i < read_temp.size(); i++) {
		sum_read = sum_read + read_temp[i];
	}
	voltage = sum_read / (read_temp.size() - 10);
	return voltage;
}

int CTestBench::ADC_Current_Measurement(int SlaveAddr, int channel_id)
{
	unsigned char command[4][3];
	unsigned char read_result[2];
	int voltage = 0;
	command[0][0] = command[1][0] = command[2][0] = command[3][0] = 0x01;
	command[0][2] = command[1][2] = command[2][2] = command[3][2] = 0x83;
	if (channel_id == 0) {
		command[0][1] = 0xC2;
	}
	else if (channel_id == 1) {
		command[1][1] = 0xD2;
	}
	else if (channel_id == 2) {
		command[2][1] = 0xE2;
	}
	else if (channel_id == 3) {
		command[3][1] = 0xF2;
	}
	else {
		AfxMessageBox(_T("Channel ID out of testbench Configuration."));
		return -100;
	}
	int ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, command[channel_id], sizeof(command[channel_id]), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C ADC Config - Write Config Register faild!"));
		return -100;
	}
	unsigned char command_conversion[2];
	command_conversion[0] = { 0x01 };
	ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, command_conversion, 1, 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C ADC Config - Change to Conversion Register faild!"));
		return -100;
	}
	ret = IIC_ReadBytes(DevHandle, I2Cindex, SlaveAddr, read_result, sizeof(read_result), 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C ADC Read Config faild!"));
		return -100;
	}
	if (read_result[1] != 0x83) {
		AfxMessageBox(_T("I2C ADC Read Config faild!"));
		return -100;
	}
	command_conversion[0] = { 0x00 };
	// int read_temp[20];
	//Sleep(1000);
	int x = 0;
	vector<int> read_temp;
	ret = IIC_WriteBytes(DevHandle, I2Cindex, SlaveAddr, command_conversion, 1, 10);
	if (ret != IIC_SUCCESS) {
		AfxMessageBox(_T("I2C ADC Config - Change to Conversion Register faild!"));
		return -100;
	}
	for (int i = 0; i < 30; i++) {
		//Sleep(100);
		ret = IIC_ReadBytes(DevHandle, I2Cindex, SlaveAddr, read_result, sizeof(read_result), 10);
		if (ret != IIC_SUCCESS) {
			AfxMessageBox(_T("I2C ADC Read Voltage faild!"));
			return -100;
		}

		int register_result = read_result[0] * 0x100 + read_result[1]; //0x40 0.013V offset
		if (register_result > 0x7FFF) {
			register_result = 0;
		}
		int voltage_temp = 4096 * register_result / 0x7FFF;
		if (voltage_temp > 0) {
			read_temp.push_back(voltage_temp);
			x++;
		}

		//Sleep(20);
	}
	int sum_read = 0;
	for (int i = 10; i < read_temp.size(); i++) {
		sum_read = sum_read + read_temp[i];
	}
	voltage = sum_read / (read_temp.size() - 10);
	return voltage;
}

BOOL CTestBench::Close_Dev()
{
	USB_CloseDevice(DevHandle);
	return TRUE;
}

BOOL CTestBench::Internet_IO_Init(int Internal_IO_ID)
{
	Internal_IO_Address = 0x00;
	int ret = GPIO_SetOutput(DevHandle, 0x1 << Internal_IO_ID, GPIO_PUPD_UP);
	if (ret != GPIO_SUCCESS) {
		return FALSE;
	}
	ret = GPIO_Write(DevHandle, 0x1 << Internal_IO_ID, 0x00);
	if (ret == GPIO_SUCCESS) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

BOOL CTestBench::Internet_IO_Open(int IO_id)
{
	int IO_Port = 0x1 << IO_id;
	Internal_IO_Address = Internal_IO_Address + IO_Port;
	int ret = GPIO_Write(DevHandle, Internal_IO_Address, IO_Port);
	if (ret == GPIO_SUCCESS) {
		return TRUE;
	}
	else {
		return FALSE;
	}
	
}

BOOL CTestBench::Internet_IO_Close(int IO_id)
{
	int IO_Port = 0x1 << IO_id;
	Internal_IO_Address = Internal_IO_Address - IO_Port;
	int ret = GPIO_Write(DevHandle, Internal_IO_Address, 0x0000);
	if (ret == GPIO_SUCCESS) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

int CTestBench::Internet_IO_Read(int IO_id)
{
	return TRUE;
}

float CTestBench::DS18B20(int IO_id)
{
	uint8_t WriteDataBuffer[64];
	uint8_t ReadDataBuffer[64];
//	DEVICE_INFO DevInfo;
//	bool state;
	int ret;
	int OW_Channel_id = 0x01 << IO_id;
	ret = OW_Init(DevHandle, OW_Channel_id, 500, 1);
	if (ret != OW_SUCCESS) {
		AfxMessageBox(_T("DS18B20 Init faild!"));
		return -100;
	}
	//while (1)
	//{
		WriteDataBuffer[0] = 0xCC;
		WriteDataBuffer[1] = 0x44;
		OW_Reset(DevHandle, OW_Channel_id);
		ret = OW_WriteBytes(DevHandle, OW_Channel_id, WriteDataBuffer, 2);
		if (ret != OW_SUCCESS) {
			AfxMessageBox(_T("DS18B20 Write faild!"));
			return -100;
		}
		Sleep(200);
		WriteDataBuffer[0] = 0xCC;
		WriteDataBuffer[1] = 0xBE;
		ret = OW_Reset(DevHandle, OW_Channel_id);
		if (ret != OW_SUCCESS) {
			AfxMessageBox(_T("DS18B20 Reset faild!"));
			return -100;
		}
		ret = OW_WriteReadBytes(DevHandle, OW_Channel_id, WriteDataBuffer, 2, ReadDataBuffer, 2, 100);
		if (ret != OW_SUCCESS) {
			AfxMessageBox(_T("DS18B20 Write-Read faild!"));
			return -100;
		}
		int16_t tmp = (ReadDataBuffer[1] << 8) | ReadDataBuffer[0];
		float temperature = (float)tmp * 0.0625;
		printf("t = %04X\n", tmp);
		printf("temperature = %0.3f\n", temperature);
		//Sleep(1000);
	//}
	return temperature;
}

void CTestBench::MySleep(DWORD nMilliseconds)
{
	HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	LARGE_INTEGER liDuring;
	liDuring.QuadPart = -(__int64)nMilliseconds * 10000; //单位是100纳秒

	if (hTimer == NULL)
		RaiseException(EXCEPTION_INVALID_HANDLE, 0, 0, 0);

	SetWaitableTimer(hTimer, &liDuring, 0, 0, 0, 0);

	for (;;) {
		DWORD dwRet = MsgWaitForMultipleObjects(1, &hTimer, FALSE, INFINITE, QS_ALLEVENTS);
		if (dwRet == WAIT_OBJECT_0)
			break;
		else if (dwRet == WAIT_OBJECT_0 + 1) {
			MSG msg;
			while (PeekMessage(&msg, 0, 0, 0, PM_NOREMOVE) != 0) {
				if (AfxGetThread()->PumpMessage() == 0) {
					AfxPostQuitMessage(0);
					break;
				}
			}
		}
	}

	CloseHandle(hTimer);

}


void CTestBench::BitToZero(int& value, int index)
{
	int bit = 1 << index;
	int nMark = 0;
	nMark = (~nMark) ^ bit;
	value &= nMark;
}

