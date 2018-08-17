#include "stdafx.h"
#include "CGet_Config.h"
#include "IniFile.h"

#define MAIN_CONFIG _T(".\\Config\\Main.ini")
#define EQUIPMENT_CONFIG _T(".\\Config\\\Equipment.ini")
#define SEQUENCE_CONFIG _T(".\\Config\\Sequence.ini")
#define TESTBENCH_CONFIG _T(".\\Config\\TestBench.ini")
#define LIMIT_CONFIG _T(".\\Config\\Limit.ini")


CIniFile get_ini;

void CGet_Config::get_main_config(CString config_file)
{
	//MAIN Sector
	get_ini.SetFileName(config_file);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Test_Name"), MAIN_Test_Name);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Software_Revision"), MAIN_Software_Revision);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Trace_Path"), MAIN_Trace_Path);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Trace_Path_Copy"), MAIN_Trace_Path_Copy);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Customer"), MAIN_Customer);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Production_Name"), MAIN_Production_Name);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Factory"), MAIN_Factory);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Assembly_Number"), MAIN_Assembly_Number);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Assembly_Revision"), MAIN_Assembly_Revision);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Site"), MAIN_Site);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Production_Line"), MAIN_Production_Line);
	get_ini.GetProfileStringW(_T("MAIN"), _T("FW_Revision"), MAIN_FW_Revision);
	get_ini.GetProfileStringW(_T("MAIN"), _T("FW_Revision"), MAIN_FW_Revision);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Hostname"), MAIN_Hostname);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Fixture_ID"), MAIN_Fixture_ID);
	MAIN_Barcode_Length = get_ini.GetProfileIntW(_T("MAIN"), _T("Barcode_Length"));
	//[Repeated_Status]
	Repeated_Status_Repeated_Test = get_ini.GetProfileIntW(_T("Repeated_Status"), _T("Repeated_Test"));
	Repeated_Status_Repeated_Cycle = get_ini.GetProfileIntW(_T("Repeated_Status"), _T("Repeated_Cycle"));
	//[FPY_Target]
	FPY_Target_High_Limit = get_ini.GetProfileIntW(_T("FPY_Target"), _T("High_Limit"));
	FPY_Target_Low_Limit = get_ini.GetProfileIntW(_T("FPY_Target"), _T("Low_Limit"));

}

void CGet_Config::get_equipment_config(CString config_file)
{
	get_ini.SetFileName(config_file);
	//[Product_Communication]
	get_ini.GetProfileStringW(_T("Product_Communication"), _T("Equipment_Name"), Product_Communication_Equipment_Name);
	get_ini.GetProfileStringW(_T("Product_Communication"), _T("Communication_Type"), Product_Communication_Communication_Type);
	Product_Communication_PID = get_ini.GetProfileIntW(_T("Product_Communication"), _T("PID"));
	Product_Communication_VID = get_ini.GetProfileIntW(_T("Product_Communication"), _T("VID"));

	//[Distance_Gauge]
	get_ini.GetProfileStringW(_T("Distance_Gauge"), _T("Equipment_Name"), Distance_Gauge_Equipment_Name);
	get_ini.GetProfileStringW(_T("Distance_Gauge"), _T("Communication_Type"), Distance_Gauge_Communication_Type);
	get_ini.GetProfileStringW(_T("Distance_Gauge"), _T("Serial_Port"), Distance_Gauge_Serial_Port);
	get_ini.GetProfileStringW(_T("Distance_Gauge"), _T("Slave_ID"), Distance_Gauge_Slave_ID);
	Distance_Gauge_Baud_Rate = get_ini.GetProfileIntW(_T("Distance_Gauge"), _T("Baud_Rate"));
	//Distance_Gauge_Slave_ID = get_ini.GetProfileIntW(_T("Distance_Gauge"), _T("Slave_ID"));

	//[Pressure_Gauge]
	get_ini.GetProfileStringW(_T("Pressure_Gauge"), _T("Equipment_Name"), Pressure_Gauge_Equipment_Name);
	get_ini.GetProfileStringW(_T("Pressure_Gauge"), _T("Communication_Type"), Pressure_Gauge_Communication_Type);
	get_ini.GetProfileStringW(_T("Pressure_Gauge"), _T("Serial_Port"), Pressure_Gauge_Serial_Port);
	get_ini.GetProfileStringW(_T("Pressure_Gauge"), _T("Slave_ID"), Pressure_Gauge_Slave_ID);
	Pressure_Gauge_Baud_Rate = get_ini.GetProfileIntW(_T("Pressure_Gauge"), _T("Baud_Rate"));
	//Pressure_Gauge_Slave_ID = get_ini.GetProfileIntW(_T("Pressure_Gauge"), _T("Slave_ID"));

	//[BLUETOOTH]
	get_ini.GetProfileStringW(_T("BLUETOOTH"), _T("Equipment_Name"), BlueTooth_Equipment_Name);
	get_ini.GetProfileStringW(_T("BLUETOOTH"), _T("Communication_Type"), BlueTooth_Communication_Type);
	get_ini.GetProfileStringW(_T("BLUETOOTH"), _T("Serial_Port"), BlueTooth_Serial_Port);
	BlueTooth_Baud_Rate = get_ini.GetProfileIntW(_T("BLUETOOTH"), _T("Baud_Rate"));
}

void CGet_Config::get_sequence_config(CString config_file)
{
	get_ini.SetFileName(config_file);
	//[SEQUENCE]
	SEQUENCE_Test_Environment_Check = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("Test_Environment_Check"));
	SEQUENCE_Equipment_Check = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("Equipment_Check"));
	SEQUENCE_FW_Flash = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("FW_Flash"));
	SEQUENCE_BlueTooth_Check = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("BlueTooth_Check"));
	SEQUENCE_RFID_Check = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("RFID_Check"));
	SEQUENCE_Button_Check = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("Button_Check"));
	SEQUENCE_Charging_Check = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("Charging_Check"));
	SEQUENCE_LCD_Check = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("LCD_Check"));
	SEQUENCE_Buzz_Check = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("Buzz_Check"));
	SEQUENCE_Distance_Calibration = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("Distance_Calibration"));
	SEQUENCE_Distance_Measurement = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("Distance_Measurement"));
	SEQUENCE_Pressure_Calibration = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("Pressure_Calibration"));
	SEQUENCE_Pressure_Measurement = get_ini.GetProfileIntW(_T("SEQUENCE"), _T("Pressure_Measurement"));
}

void CGet_Config::get_testbench_config(CString config_file)
{
	get_ini.SetFileName(config_file);
	//CGet_Config::TestBench::Main main;
	get_ini.GetProfileStringW(_T("MAIN"), _T("Equipment_Name"), TestBench_Main_Equipment_Name);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Communication_Type"), TestBench_Main_Communication_Type);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Firmware_Build_Date"), TestBench_Main_Firmware_Build_Date);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Firmware_Version"), TestBench_Main_Firmware_Version);
	get_ini.GetProfileStringW(_T("MAIN"), _T("Hardware_Version"), TestBench_Main_Hardware_Version);
	TestBench_Main_Product_Serial_Number = get_ini.GetProfileIntW(_T("MAIN"), _T("Product_Serial_Number"));
	TestBench_Main_I2C_Channel = get_ini.GetProfileIntW(_T("MAIN"), _T("I2C_Channel"));
	TestBench_Main_UART_Channel = get_ini.GetProfileIntW(_T("MAIN"), _T("UART_Channel"));

	//CGet_Config::TestBench::PWM pwm;
	TestBench_PWM_Polarity = get_ini.GetProfileIntW(_T("PWM"), _T("Polarity"));
	TestBench_PWM_Precision = get_ini.GetProfileIntW(_T("PWM"), _T("Precision"));
	TestBench_PWM_Prescaler = get_ini.GetProfileIntW(_T("PWM"), _T("Prescaler"));
	TestBench_PWM_Pulse = get_ini.GetProfileIntW(_T("PWM"), _T("Pulse"));
	TestBench_PWM_PWM0 = get_ini.GetProfileIntW(_T("PWM"), _T("PWM0"));
	TestBench_PWM_PWM1 = get_ini.GetProfileIntW(_T("PWM"), _T("PWM1"));
	TestBench_PWM_PWM2 = get_ini.GetProfileIntW(_T("PWM"), _T("PWM2"));
	TestBench_PWM_PWM3 = get_ini.GetProfileIntW(_T("PWM"), _T("PWM3"));
	TestBench_PWM_PWM4 = get_ini.GetProfileIntW(_T("PWM"), _T("PWM4"));
	TestBench_PWM_PWM5 = get_ini.GetProfileIntW(_T("PWM"), _T("PWM5"));
	TestBench_PWM_PWM6 = get_ini.GetProfileIntW(_T("PWM"), _T("PWM6"));
	TestBench_PWM_PWM7 = get_ini.GetProfileIntW(_T("PWM"), _T("PWM7"));
	
	//CGet_Config::TestBench::GPIO gpio;
	TestBench_GPIO_GPIO_I2C_0 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO_I2C_0"));
	TestBench_GPIO_GPIO_I2C_1 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO_I2C_1"));
	TestBench_GPIO_GPIO0 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO0"));
	TestBench_GPIO_GPIO1 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO1"));
	TestBench_GPIO_GPIO2 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO2"));
	TestBench_GPIO_GPIO3 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO3"));
	TestBench_GPIO_GPIO4 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO4"));
	TestBench_GPIO_GPIO5 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO5"));
	TestBench_GPIO_GPIO6 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO6"));
	TestBench_GPIO_GPIO7 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO7"));
	TestBench_GPIO_GPIO8 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO8"));
	TestBench_GPIO_GPIO9 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO9"));
	TestBench_GPIO_GPIO10 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO10"));
	TestBench_GPIO_GPIO11 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO11"));
	TestBench_GPIO_GPIO12 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO12"));
	TestBench_GPIO_GPIO13 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO13"));
	TestBench_GPIO_GPIO14 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO14"));
	TestBench_GPIO_GPIO15 = get_ini.GetProfileIntW(_T("GPIO"), _T("GPIO15"));

	//CGet_Config::TestBench::ADC adc;
	TestBench_ADC_ADC_I2C_Address = get_ini.GetProfileIntW(_T("ADC"), _T("ADC_I2C_Address"));
	TestBench_ADC_ADC0 = get_ini.GetProfileIntW(_T("ADC"), _T("ADC0"));
	TestBench_ADC_ADC1 = get_ini.GetProfileIntW(_T("ADC"), _T("ADC1"));
	TestBench_ADC_ADC2 = get_ini.GetProfileIntW(_T("ADC"), _T("ADC2"));
	TestBench_ADC_ADC3 = get_ini.GetProfileIntW(_T("ADC"), _T("ADC3"));

	//CGet_Config::TestBench::RF rf;
	get_ini.GetProfileStringW(_T("RF"), _T("Equipment_Name"), TestBench_RF_Equipment_Name);
	get_ini.GetProfileStringW(_T("RF"), _T("Communication_Type"), TestBench_RF_Communication_Type);
	TestBench_RF_Baud_Rate = get_ini.GetProfileIntW(_T("RF"), _T("Baud_Rate"));

	//CGet_Config::TestBench::Internet GPIO;
	TestBench_INTERNET_GPIO0 = get_ini.GetProfileIntW(_T("INTERNET"), _T("GPIO0"));
	TestBench_INTERNET_GPIO1 = get_ini.GetProfileIntW(_T("INTERNET"), _T("GPIO1"));
	TestBench_INTERNET_GPIO2 = get_ini.GetProfileIntW(_T("INTERNET"), _T("GPIO2"));
	TestBench_INTERNET_GPIO3 = get_ini.GetProfileIntW(_T("INTERNET"), _T("GPIO3"));
	TestBench_INTERNET_UART = get_ini.GetProfileIntW(_T("INTERNET"), _T("UART"));
	TestBench_INTERNET_DS18B20 = get_ini.GetProfileIntW(_T("INTERNET"), _T("DS18B20"));
}

void CGet_Config::get_limit_config(CString config_file)
{
	get_ini.SetFileName(config_file);

	Limit_Equipment_Check_Inflator_Low_Temperature = get_ini.GetProfileIntW(_T("Equipment_Check"), _T("Inflator_Low_Temperature"));
	Limit_Equipment_Check_Inflator_High_Temperature = get_ini.GetProfileIntW(_T("Equipment_Check"), _T("Inflator_High_Temperature"));

	get_ini.GetProfileStringW(_T("FW_Flash"), _T("Original_FW"), Limit_FW_Flash_Original_FW);
	get_ini.GetProfileStringW(_T("FW_Flash"), _T("Test_FW"), Limit_FW_Flash_Test_FW);
	Limit_FW_Flash_Wire_Begin_Address = get_ini.GetProfileIntW(_T("FW_Flash"), _T("Wire_Begin_Address"));
	Limit_FW_Flash_Write_Length = get_ini.GetProfileIntW(_T("FW_Flash"), _T("Write_Length"));
	Limit_FW_Flash_Manual_Power_On = get_ini.GetProfileIntW(_T("FW_Flash"), _T("Manual_Power_On"));

	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Master_BT_Name"), Limit_BlueTooth_Master_BT_Name);
	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Master_BT_Vers"), Limit_BlueTooth_Master_BT_Vers);
	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Slave_BT_Name"), Limit_BlueTooth_Slave_BT_Name);
	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Command_Get_Master_Address"), Limit_BlueTooth_Command_Get_Master_Address);
	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Command_Get_Master_Name"), Limit_BlueTooth_Command_Get_Master_Name);
	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Command_Get_Master_Vers"), Limit_BlueTooth_Command_Get_Master_Vers);
	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Command_Connect"), Limit_BlueTooth_Command_Connect);
	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Command_Disconnect"), Limit_BlueTooth_Command_Disconnect);
	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Command_Find_All_UUID"), Limit_BlueTooth_Command_Find_All_UUID);
	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Command_Set_Send_UUID"), Limit_BlueTooth_Command_Set_Send_UUID);
	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Command_Set_Receive_UUID"), Limit_BlueTooth_Command_Set_Receive_UUID);
	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Command_Reset"), Limit_BlueTooth_Command_Reset);
	get_ini.GetProfileStringW(_T("BlueTooth_Check"), _T("Command_Read_RSSI"), Limit_BlueTooth_Command_Read_RSSI);


	get_ini.GetProfileStringW(_T("BlueTooth_TRANSMISSION"), _T("Command_Transmission"), Limit_Transmission_Command_Transmission);
	get_ini.GetProfileStringW(_T("BlueTooth_TRANSMISSION"), _T("Command_Get_Distance_Value"), Limit_Transmission_Command_Get_Distance_Value);
	get_ini.GetProfileStringW(_T("BlueTooth_TRANSMISSION"), _T("Command_Get_Pressure_Value"), Limit_Transmission_Command_Get_Pressure_Value);
	get_ini.GetProfileStringW(_T("BlueTooth_TRANSMISSION"), _T("Command_Get_RFID"), Limit_Transmission_Command_Get_RFID);
	get_ini.GetProfileStringW(_T("BlueTooth_TRANSMISSION"), _T("Command_Reset"), Limit_Transmission_Command_Reset);
	get_ini.GetProfileStringW(_T("BlueTooth_TRANSMISSION"), _T("Command_Distance_Calibration"), Limit_Transmission_Command_Distance_Calibration);
	get_ini.GetProfileStringW(_T("BlueTooth_TRANSMISSION"), _T("Command_Pressure_Calibration"), Limit_Transmission_Command_Pressure_Calibration);
	get_ini.GetProfileStringW(_T("BlueTooth_TRANSMISSION"), _T("Command_Buzz_On"), Limit_Transmission_Command_Buzz_On);


	Limit_BlueTooth_Master_BT_Address = get_ini.GetProfileIntW(_T("BlueTooth_Check"), _T("Master_BT_Address"));;
	Limit_BlueTooth_Slave_BT_Address = get_ini.GetProfileIntW(_T("BlueTooth_Check"), _T("Slave_BT_Address"));;
	Limit_BlueTooth_Slave_BT_Addrress_Length = get_ini.GetProfileIntW(_T("BlueTooth_Check"), _T("Slave_BT_Address_Length"));;
	Limit_BlueTooth_UUID_TX = get_ini.GetProfileIntW(_T("BlueTooth_Check"), _T("UUID_TX"));;
	Limit_BlueTooth_UUID_RX = get_ini.GetProfileIntW(_T("BlueTooth_Check"), _T("UUID_RX"));;
	Limit_BlueTooth_RSSI_LSL = get_ini.GetProfileIntW(_T("BlueTooth_Check"), _T("RSSI_LSL"));;
	Limit_BlueTooth_RSSI_USL = get_ini.GetProfileIntW(_T("BlueTooth_Check"), _T("RSSI_USL"));;
	Limit_BlueTooth_Manual_Reset = get_ini.GetProfileIntW(_T("BlueTooth_Check"), _T("Manual_Reset"));

	Limit_RFID_Check_RFID_Address = get_ini.GetProfileIntW(_T("RFID_Check"), _T("RFID_Address"));
	//Limit_RFID_Check_RFID = get_ini.GetProfileIntW(_T("RFID_Check"), _T("RFID"));
	get_ini.GetProfileStringW(_T("RFID_Check"), _T("RFID"), Limit_RFID_Check_RFID);

	Limit_Button_Check_Model_Key_Address = get_ini.GetProfileIntW(_T("Button_Check"), _T("Model_Key_Address"));
	Limit_Button_Check_OK_Key_Address = get_ini.GetProfileIntW(_T("Button_Check"), _T("OK_Key_Address"));

	Limit_Charging_Check_Charging_Current_Max = get_ini.GetProfileIntW(_T("Charging_Check"), _T("Charging_Current_Max"));
	Limit_Charging_Check_Charging_Current_Min = get_ini.GetProfileIntW(_T("Charging_Check"), _T("Charging_Current_Min"));
	Limit_Charging_Check_Charging_Voltage_Max = get_ini.GetProfileIntW(_T("Charging_Check"), _T("Charging_Voltage_Max"));
	Limit_Charging_Check_Charging_Voltage_Min = get_ini.GetProfileIntW(_T("Charging_Check"), _T("Charging_Voltage_Min"));

	Limit_LCD_Check_LCD_All_On = get_ini.GetProfileIntW(_T("LCD_Check"), _T("LCD_All_On"));

	Limit_Buzz_Check_Buzz_On = get_ini.GetProfileIntW(_T("Buzz_Check"), _T("Buzz_On"));

	Limit_Distance_Calibration_Calibration_Point = get_ini.GetProfileIntW(_T("Distance_Calibration"), _T("Calibration_Point"));
	Limit_Distance_Calibration_Calibration_Address = get_ini.GetProfileIntW(_T("Distance_Calibration"), _T("Calibration_Address"));
	Limit_Distance_Calibration_Distance_Limit_Percentage = get_ini.GetProfileIntW(_T("Distance_Calibration"), _T("Distance_Limit_Percentage"));
	Limit_Distance_Calibration_Zero_Position_Offset = get_ini.GetProfileIntW(_T("Distance_Calibration"), _T("Zero_Position_Offset")); ;
	Limit_Distance_Calibration_Max_Measurement_Times = get_ini.GetProfileIntW(_T("Distance_Calibration"), _T("Max_Measurement_Times"));
	Limit_Distance_Calibration_Distance_Begin = get_ini.GetProfileIntW(_T("Distance_Calibration"), _T("Distance_Begin"));
	Limit_Distance_Calibration_Distance_End = get_ini.GetProfileIntW(_T("Distance_Calibration"), _T("Distance_End"));
	Limit_Distance_Calibration_Distance_Increase = get_ini.GetProfileIntW(_T("Distance_Calibration"), _T("Distance_Increase"));
	Limit_Distance_Calibration_BT_Upload = get_ini.GetProfileIntW(_T("Distance_Calibration"), _T("BT_Upload"));

	Limit_Distance_Measurement_Distance_Read_Address = get_ini.GetProfileIntW(_T("Distance_Measurement"), _T("Distance_Read_Address"));
	Limit_Distance_Measurement_Measurement_Tolorance = get_ini.GetProfileIntW(_T("Distance_Measurement"), _T("Measurement_Tolorance"));
	Limit_Distance_Measurement_Zero_Position_Offset = get_ini.GetProfileIntW(_T("Distance_Measurement"), _T("Zero_Position_Offset"));;
	Limit_Distance_Measurement_Distance_Begin = get_ini.GetProfileIntW(_T("Distance_Measurement"), _T("Distance_Begin"));
	Limit_Distance_Measurement_Distance_End = get_ini.GetProfileIntW(_T("Distance_Measurement"), _T("Distance_End"));
	Limit_Distance_Measurement_Distance_Increase = get_ini.GetProfileIntW(_T("Distance_Measurement"), _T("Distance_Increase"));

	Limit_Pressure_Calibration_Calibration_Point = get_ini.GetProfileIntW(_T("Pressure_Calibration"), _T("Calibration_Point"));
	Limit_Pressure_Calibration_Calibration1 = get_ini.GetProfileIntW(_T("Pressure_Calibration"), _T("Calibration1"));
	Limit_Pressure_Calibration_Calibration2 = get_ini.GetProfileIntW(_T("Pressure_Calibration"), _T("Calibration2"));
	Limit_Pressure_Calibration_Calibration_Address = get_ini.GetProfileIntW(_T("Pressure_Calibration"), _T("Calibration_Address"));
	Limit_Pressure_Calibration_Distance_Limit_Percentage = get_ini.GetProfileIntW(_T("Pressure_Calibration"), _T("Pressure_Limit_Percentage"));

	Limit_Pressure_Measurement_Pressure_Read_Address = get_ini.GetProfileIntW(_T("Pressure_Measurement"), _T("Distance_Read_Address"));
	Limit_Pressure_Measurement_Measurement_Tolorance = get_ini.GetProfileIntW(_T("Pressure_Measurement"), _T("Measurement_Tolorance"));
	Limit_Pressure_Measurement_Max_Measurement_Times = get_ini.GetProfileIntW(_T("Pressure_Measurement"), _T("Max_Measurement_Times"));



}

void CGet_Config::config_file_name_define()
{
	main_file_name = MAIN_CONFIG;
	equipment_file_name = EQUIPMENT_CONFIG;
	sequence_file_name = SEQUENCE_CONFIG;
	testbench_file_name = TESTBENCH_CONFIG;
	limit_file_name = LIMIT_CONFIG;
}

CGet_Config::CGet_Config()
{
}

CGet_Config::~CGet_Config()
{
}
