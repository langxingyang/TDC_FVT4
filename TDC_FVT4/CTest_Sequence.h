#pragma once
#include "SerialPort.h"

using namespace std;
using namespace itas109;

class CTest_Sequence //:public CTDCFVT4Dlg
{
	//DECLARE_DYNAMIC(CTest_Sequence)
public:
	//enum { IDD = IDD_METHODDLG };
	//CTest_Sequence(CWnd* pParent = NULL);
	CTest_Sequence();
	~CTest_Sequence();
	CString Test_Environment_Check();
	CString Equipment_Check(CString Equipment_Name,CString Communication_Type, CString Comm_Port, int Baud_Rate, int Slave_Id, CString Command, CString Expected_Feedback);
	int	FW_Flash();
	int	BlueTooth_Check();
	int	RFID_Check();
	int	Button_Check();
	int	Charging_Check();
	int	LCD_Check();
	int	Buzz_Check();
	int	Distance_Calibration();
	int	Distance_Measurement();
	int	Pressure_Calibration();
	int	Pressure_Measurement();
	float CTest_Sequence::Distance_Gauge(CString Comm_Port, int Baud_Rate, int Slave_Id, char Command[]);
};

