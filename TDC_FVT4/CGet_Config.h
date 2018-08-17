#pragma once
//#include "TDC_FVT4Dlg.h"
class CGet_Config : 
	public CDialogEx
{
public:

	CString main_file_name;
	CString equipment_file_name;
	CString sequence_file_name;
	CString testbench_file_name;
	CString limit_file_name;

	//Main.ini 中的参数
	//[MAIN]
	CString MAIN_Test_Name;
	CString MAIN_Software_Revision;
	CString MAIN_Trace_Path;
	CString MAIN_Trace_Path_Copy;
	CString MAIN_Customer;
	CString MAIN_Production_Name;
	int MAIN_Barcode_Length;
	CString MAIN_Factory;
	CString MAIN_Assembly_Number;
	CString MAIN_Assembly_Revision;
	CString MAIN_Site;
	CString MAIN_Production_Line;
	CString MAIN_FW_Revision;
	CString MAIN_Test_Station;
	CString MAIN_Hostname;
	CString MAIN_Fixture_ID;

	//[Repeated_Status]
	bool Repeated_Status_Repeated_Test;
	int Repeated_Status_Repeated_Cycle;

	//[FPY_Target]
	int FPY_Target_High_Limit;
	int FPY_Target_Low_Limit;

	//Equipment.ini 中的参数
	//[Product_Communication]
	CString Product_Communication_Equipment_Name;
	CString Product_Communication_Communication_Type;
	int Product_Communication_PID;
	int Product_Communication_VID;

	//[Distance_Gauge]
	CString Distance_Gauge_Equipment_Name;
	CString Distance_Gauge_Communication_Type;
	CString Distance_Gauge_Serial_Port;
	int Distance_Gauge_Baud_Rate;
	CString Distance_Gauge_Slave_ID;

	//[Pressure_Gauge]
	CString Pressure_Gauge_Equipment_Name;
	CString Pressure_Gauge_Communication_Type;
	CString Pressure_Gauge_Serial_Port;
	int Pressure_Gauge_Baud_Rate;
	CString Pressure_Gauge_Slave_ID;

	//[BLUETOOTH]
	CString BlueTooth_Equipment_Name;
	CString BlueTooth_Communication_Type;
	CString BlueTooth_Serial_Port;
	int BlueTooth_Baud_Rate;

	//Sequence.ini  中的参数
	//[SEQUENCE]
	bool SEQUENCE_Test_Environment_Check;
	bool SEQUENCE_Equipment_Check;
	bool SEQUENCE_FW_Flash;
	bool SEQUENCE_BlueTooth_Check;
	bool SEQUENCE_RFID_Check;
	bool SEQUENCE_Button_Check;
	bool SEQUENCE_Charging_Check;
	bool SEQUENCE_LCD_Check;
	bool SEQUENCE_Buzz_Check;
	bool SEQUENCE_Distance_Calibration;
	bool SEQUENCE_Distance_Measurement;
	bool SEQUENCE_Pressure_Calibration;
	bool SEQUENCE_Pressure_Measurement;

	//TestBench.ini  中的参数


	CString TestBench_Main_Equipment_Name;
	CString	TestBench_Main_Communication_Type;
	CString	TestBench_Main_Firmware_Build_Date;
	CString	TestBench_Main_Firmware_Version;
	CString TestBench_Main_Hardware_Version;
	int TestBench_Main_Product_Serial_Number;
	int TestBench_Main_I2C_Channel;
	int TestBench_Main_UART_Channel;

	int TestBench_PWM_PWM0;
	int	TestBench_PWM_PWM1;
	int	TestBench_PWM_PWM2;
	int	TestBench_PWM_PWM3;
	int TestBench_PWM_PWM4;
	int TestBench_PWM_PWM5;
	int TestBench_PWM_PWM6;
	int TestBench_PWM_PWM7;

	//PWM Config
	int TestBench_PWM_Polarity;
	int TestBench_PWM_Precision;
	int TestBench_PWM_Prescaler;
	int TestBench_PWM_Pulse;

	//I2C IO Module Slave Address I2C_GIIO_0: GPIO0-7 I2C_GIIO_1: GPIO8-16
	int TestBench_GPIO_GPIO_I2C_0;
	int TestBench_GPIO_GPIO_I2C_1;

	//GPIO Address
	int TestBench_GPIO_GPIO0;
	int TestBench_GPIO_GPIO1;
	int TestBench_GPIO_GPIO2;
	int TestBench_GPIO_GPIO3;
	int TestBench_GPIO_GPIO4;
	int TestBench_GPIO_GPIO5;
	int TestBench_GPIO_GPIO6;
	int TestBench_GPIO_GPIO7;
	int TestBench_GPIO_GPIO8;
	int TestBench_GPIO_GPIO9;
	int TestBench_GPIO_GPIO10;
	int TestBench_GPIO_GPIO11;
	int TestBench_GPIO_GPIO12;
	int TestBench_GPIO_GPIO13;
	int TestBench_GPIO_GPIO14;
	int TestBench_GPIO_GPIO15;

	int TestBench_ADC_ADC_I2C_Address;
	int	TestBench_ADC_ADC0;
	int	TestBench_ADC_ADC1;
	int	TestBench_ADC_ADC2;
	int	TestBench_ADC_ADC3;

	CString TestBench_RF_Equipment_Name;
	CString	TestBench_RF_Communication_Type;
	int	TestBench_RF_Baud_Rate;

	int TestBench_INTERNET_GPIO0;
	int TestBench_INTERNET_GPIO1;
	int TestBench_INTERNET_GPIO2;
	int TestBench_INTERNET_GPIO3;
	int TestBench_INTERNET_UART;
	int TestBench_INTERNET_DS18B20;


	//Limit.ini 中的参数

	int Limit_Equipment_Check_Inflator_Low_Temperature;
	int Limit_Equipment_Check_Inflator_High_Temperature;


	CString Limit_FW_Flash_Original_FW;
	CString Limit_FW_Flash_Test_FW;
	int		Limit_FW_Flash_Wire_Begin_Address;
	int		Limit_FW_Flash_Write_Length;
	int     Limit_FW_Flash_Manual_Power_On;

	CString Limit_BlueTooth_Master_BT_Name;
	int Limit_BlueTooth_Master_BT_Address;
	CString Limit_BlueTooth_Master_BT_Vers;
	CString Limit_BlueTooth_Slave_BT_Name;
	int Limit_BlueTooth_Slave_BT_Address;
	int Limit_BlueTooth_Slave_BT_Addrress_Length;
	CString Limit_BlueTooth_Command_Get_Master_Address;
	CString Limit_BlueTooth_Command_Get_Master_Name;
	CString Limit_BlueTooth_Command_Get_Master_Vers;
	CString Limit_BlueTooth_Command_Connect;
	CString Limit_BlueTooth_Command_Disconnect;
	CString Limit_BlueTooth_Command_Find_All_UUID;
	CString Limit_BlueTooth_Command_Set_Send_UUID;
	CString Limit_BlueTooth_Command_Set_Receive_UUID;
	CString Limit_BlueTooth_Command_Reset;
	CString Limit_BlueTooth_Command_Read_RSSI;
	int Limit_BlueTooth_UUID_TX;
	int Limit_BlueTooth_UUID_RX;
	int Limit_BlueTooth_RSSI_LSL;
	int	Limit_BlueTooth_RSSI_USL;
	int Limit_BlueTooth_Manual_Reset;

	int Limit_RFID_Check_RFID_Address;
	CString	Limit_RFID_Check_RFID;

	int Limit_Button_Check_OK_Key_Address;
	int	Limit_Button_Check_Model_Key_Address;

	int Limit_Charging_Check_Charging_Current_Max;
	int Limit_Charging_Check_Charging_Current_Min;
	int Limit_Charging_Check_Charging_Voltage_Max;
	int Limit_Charging_Check_Charging_Voltage_Min;

	int Limit_LCD_Check_LCD_All_On;

	int Limit_Buzz_Check_Buzz_On;

	int Limit_Distance_Calibration_Calibration_Point;
	int	Limit_Distance_Calibration_Distance_Limit_Percentage;
	int	Limit_Distance_Calibration_Calibration_Address;
	int Limit_Distance_Calibration_Zero_Position_Offset;
	int Limit_Distance_Calibration_Max_Measurement_Times;
	int Limit_Distance_Calibration_Distance_Begin;
	int Limit_Distance_Calibration_Distance_End;
	int Limit_Distance_Calibration_Distance_Increase;
	int Limit_Distance_Calibration_BT_Upload;


	int Limit_Distance_Measurement_Distance_Read_Address;
	int Limit_Distance_Measurement_Measurement_Tolorance;
	int Limit_Distance_Measurement_Zero_Position_Offset;
	int Limit_Distance_Measurement_Distance_Begin;
	int Limit_Distance_Measurement_Distance_End;
	int Limit_Distance_Measurement_Distance_Increase;

	int Limit_Pressure_Calibration_Calibration_Point;
	int	Limit_Pressure_Calibration_Calibration1;
	int	Limit_Pressure_Calibration_Calibration2;
	int	Limit_Pressure_Calibration_Distance_Limit_Percentage;
	int	Limit_Pressure_Calibration_Calibration_Address;

	int 	Limit_Pressure_Measurement_Pressure_Read_Address;
	int 	Limit_Pressure_Measurement_Measurement_Tolorance;
	int Limit_Pressure_Measurement_Max_Measurement_Times;

	CString Limit_Transmission_Command_Transmission;
	CString Limit_Transmission_Command_Get_Distance_Value;
	CString Limit_Transmission_Command_Get_Pressure_Value;
	CString Limit_Transmission_Command_Get_RFID;
	CString Limit_Transmission_Command_Reset;
	CString Limit_Transmission_Command_Distance_Calibration;
	CString Limit_Transmission_Command_Pressure_Calibration;
	CString Limit_Transmission_Command_Buzz_On;

	void get_main_config(CString config_file);
	void get_equipment_config(CString config_file);
	void get_sequence_config(CString config_file);
	void get_testbench_config(CString config_file);
	void get_limit_config(CString config_file);
	void config_file_name_define();

	CGet_Config();
	~CGet_Config();
};

