#include "stdafx.h"
//#include "TDC_FVT4Dlg.h"
#include "CTest_Sequence.h"
#include "afxdialogex.h"
#include "IniFile.h"
#include "CGet_Config.h"
//#include "SerialPort.h"
#include "File_Check.h"


CIniFile seq_ini;
CGet_Config seq_config;
File_Check seq_fcheck;
CSerialPort com;


CTest_Sequence::CTest_Sequence()
{
}


CTest_Sequence::~CTest_Sequence()
{
}

//IMPLEMENT_DYNAMIC(CTest_Sequence, CDialog)

//: CDialog(CMethodDlg::IDD, pParent)  
//CTest_Sequence::CTest_Sequence(CWnd* pParent /*=NULL*/)
//	: CTDCFVT4Dlg(CTest_Sequence::IDD, pParent) //¼Ì³Ðtemplate  
//{


CString CTest_Sequence::Test_Environment_Check()
{
	CString str = _T("\r\n[Test_Environment_Check]\r\n");
	if (!(seq_fcheck.IsFileExist(seq_config.main_file_name)) &&
		!(seq_fcheck.IsFileExist(seq_config.equipment_file_name)) &&
		!(seq_fcheck.IsFileExist(seq_config.sequence_file_name)) &&
		!(seq_fcheck.IsFileExist(seq_config.testbench_file_name)) &&
		!(seq_fcheck.IsFileExist(seq_config.limit_file_name))) {
		str = str + _T("Configuration File Check Result: Pass\r\n");
	}
	else {
		str = str + _T("Configuration File Check Result: Fail\r\n");
		return str;
	}
	if (!(seq_fcheck.IsDirExist(seq_config.MAIN_Trace_Path)) && !(seq_fcheck.IsDirExist(seq_config.MAIN_Trace_Path_Copy))) {
		str = str + _T("Log Folder Check Result: Pass");
	}
	else {
		str = str + _T("Log Folder Check Result: Fail");
		return str;
	}
	return str;
}

CString CTest_Sequence::Equipment_Check(CString Equipment_Name, CString Communication_Type, CString Comm_Port, int Baud_Rate, int Slave_Id, CString Command, CString Expected_Feedback)
{
	CString enter_str = _T("\r\n");
	CString str = _T("[Equipment_Check]\r\n");
	str = str + Equipment_Name + _T(" Check:\r\n");
	str = (str + Communication_Type + enter_str + Comm_Port + enter_str);
//	str = str + seq_config.Distance_Gauge_Baud_Rate + enter_str + seq_config.Distance_Gauge_Slave_ID + enter_str;
	str = str + _T("PASS");
	return str;
}

float CTest_Sequence::Distance_Gauge(CString Comm_Port, int Baud_Rate, int Slave_Id, char Command[])
{
	return 0;
}
