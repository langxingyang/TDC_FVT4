// CONFIG_EQUIPMENTdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TDC_FVT4.h"
#include "CONFIG_EQUIPMENTdlg.h"
#include "afxdialogex.h"
#include "IniFile.h"
#include "File_Check.h"

#define EQUIPMENT_CONFIG _T(".\\Config\\Equipment.ini")

CIniFile eq_ini;
File_Check eq_filecheck;

// CCONFIG_EQUIPMENTdlg 对话框

IMPLEMENT_DYNAMIC(CCONFIG_EQUIPMENTdlg, CDialogEx)

CCONFIG_EQUIPMENTdlg::CCONFIG_EQUIPMENTdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_EQUIPMENT, pParent)
	, config_equipment_product_communication_equipment_name(_T(""))
	, config_equipment_product_communication_type(_T(""))
	, config_equipment_product_pid(0)
	, config_equipment_product_vid(0)
	, config_distance_equipment_name(_T(""))
	, config_distance_communication_type(_T(""))
	, config_distance_serial_port(_T(""))
	, config_distance_baud_rate(0)
	, config_distance_slave_id(_T(""))
	, config_pressure_equipment_name(_T(""))
	, config_pressure_communication_type(_T(""))
	, config_pressure_serial_port(_T(""))
	, config_pressure_baud_rate(0)
	, config_pressure_slave_id(_T(""))
	, config_bluetooth_equipment_name(_T(""))
	, config_bluetooth_communication_type(_T(""))
	, config_bluetooth_serial_port(_T(""))
	, config_bluetooth_baud_rate(0)
{

}

CCONFIG_EQUIPMENTdlg::~CCONFIG_EQUIPMENTdlg()
{
}

void CCONFIG_EQUIPMENTdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EQUIPMENT_PRODUCT_COMMUNICATION_EQUIPMENT_NAME, config_equipment_product_communication_equipment_name);
	DDX_CBString(pDX, IDC_EQUIPMENT_PRODUCT_COMMUNICATION_TYPE, config_equipment_product_communication_type);
	DDX_Text(pDX, IDC_EQUIPMENT_PRODUCT_COMMUNICATION_PID, config_equipment_product_pid);
	DDX_Text(pDX, IDC_EQUIPMENT_PRODUCT_COMMUNICATION_VID, config_equipment_product_vid);
	DDX_Text(pDX, IDC_DISTANCE_EQUIPMENT_NAME, config_distance_equipment_name);
	DDX_CBString(pDX, IDC_DISTANCE_COMMUNICATION_TYPE, config_distance_communication_type);
	DDX_CBString(pDX, IDC_DISTANCE_SERIAL_PORT, config_distance_serial_port);
	DDX_Text(pDX, IDC_DISTANCE_BAUD_RATE, config_distance_baud_rate);
	DDX_Text(pDX, IDC_DISTANCE_SLAVE_ID, config_distance_slave_id);
	DDX_Text(pDX, IDC_PRESSURE_EQUIPMENT_NAME, config_pressure_equipment_name);
	DDX_CBString(pDX, IDC_PRESSURE_COMMUNICATION_TYPE, config_pressure_communication_type);
	DDX_CBString(pDX, IDC_PRESSURE_SERIAL_PORT, config_pressure_serial_port);
	DDX_Text(pDX, IDC_PRESSURE_BAUD_RATE, config_pressure_baud_rate);
	DDX_Text(pDX, IDC_PRESSURE_SLAVE_ID, config_pressure_slave_id);
	DDX_Text(pDX, IDC_BLUETOOTH_EQUIPMENT_NAME, config_bluetooth_equipment_name);
	DDX_CBString(pDX, IDC_BLUETOOTH_COMMUNICATION_TYPE, config_bluetooth_communication_type);
	DDX_CBString(pDX, IDC_BLUETOOTH_SERIAL_PORT, config_bluetooth_serial_port);
	DDX_CBIndex(pDX, IDC_BLUETOOTH_BAUD_RATE, config_bluetooth_baud_rate);
}


BEGIN_MESSAGE_MAP(CCONFIG_EQUIPMENTdlg, CDialogEx)
	//ON_COMMAND(ID_CONFIG_EQUIPMENT, &CCONFIG_EQUIPMENTdlg::OnConfigEquipment)
	ON_BN_CLICKED(IDOK, &CCONFIG_EQUIPMENTdlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCONFIG_EQUIPMENTdlg 消息处理程序


//void CCONFIG_EQUIPMENTdlg::OnConfigEquipment()
//{
//	// TODO: 在此添加命令处理程序代码
//}


void CCONFIG_EQUIPMENTdlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	GetDlgItem(IDC_EQUIPMENT_PRODUCT_COMMUNICATION_EQUIPMENT_NAME)->GetWindowText(config_equipment_product_communication_equipment_name);
	GetDlgItem(IDC_EQUIPMENT_PRODUCT_COMMUNICATION_TYPE)->GetWindowText(config_equipment_product_communication_type);
	//GetDlgItem(IDC_EQUIPMENT_PRODUCT_COMMUNICATION_PID)->GetDlgItemInt(config_equipment_product_pid, NULL, FALSE);
	//GetDlgItem(IDC_EQUIPMENT_PRODUCT_COMMUNICATION_VID)->GetDlgItemInt(config_equipment_product_vid, NULL, FALSE);
	config_equipment_product_pid = GetDlgItemInt(IDC_EQUIPMENT_PRODUCT_COMMUNICATION_PID,NULL,FALSE);
	config_equipment_product_vid = GetDlgItemInt(IDC_EQUIPMENT_PRODUCT_COMMUNICATION_VID, NULL, FALSE);

	GetDlgItem(IDC_DISTANCE_EQUIPMENT_NAME)->GetWindowText(config_distance_equipment_name);
	GetDlgItem(IDC_DISTANCE_COMMUNICATION_TYPE)->GetWindowText(config_distance_communication_type);
	GetDlgItem(IDC_DISTANCE_SERIAL_PORT)->GetWindowText(config_distance_serial_port);
	GetDlgItem(IDC_DISTANCE_SLAVE_ID)->GetWindowText(config_distance_slave_id);
	//GetDlgItem(IDC_DISTANCE_BAUD_RATE)->GetDlgItemInt(config_distance_baud_rate, NULL, FALSE);
	//GetDlgItem(IDC_DISTANCE_SLAVE_ID)->GetDlgItemInt(config_distance_slave_id, NULL, FALSE);
	config_distance_baud_rate = GetDlgItemInt(IDC_DISTANCE_BAUD_RATE, NULL, FALSE);
	//config_distance_slave_id = GetDlgItemInt(IDC_DISTANCE_SLAVE_ID, NULL, FALSE);

	GetDlgItem(IDC_PRESSURE_EQUIPMENT_NAME)->GetWindowText(config_pressure_equipment_name);
	GetDlgItem(IDC_PRESSURE_COMMUNICATION_TYPE)->GetWindowText(config_pressure_communication_type);
	GetDlgItem(IDC_PRESSURE_SERIAL_PORT)->GetWindowText(config_pressure_serial_port);
	GetDlgItem(IDC_PRESSURE_SLAVE_ID)->GetWindowText(config_pressure_slave_id);
	//GetDlgItem(IDC_PRESSURE_BAUD_RATE)->GetDlgItemInt(config_pressure_baud_rate, NULL, FALSE);
	//GetDlgItem(IDC_PRESSURE_SLAVE_ID)->GetDlgItemInt(config_pressure_slave_id, NULL, FALSE);
	config_pressure_baud_rate = GetDlgItemInt(IDC_PRESSURE_BAUD_RATE, NULL, FALSE);
	//config_pressure_slave_id = GetDlgItemInt(IDC_PRESSURE_SLAVE_ID, NULL, FALSE);

	GetDlgItem(IDC_BLUETOOTH_EQUIPMENT_NAME)->GetWindowText(config_bluetooth_equipment_name);
	GetDlgItem(IDC_BLUETOOTH_COMMUNICATION_TYPE)->GetWindowText(config_bluetooth_communication_type);
	GetDlgItem(IDC_BLUETOOTH_SERIAL_PORT)->GetWindowText(config_bluetooth_serial_port);
	config_bluetooth_baud_rate = GetDlgItemInt(IDC_BLUETOOTH_BAUD_RATE, NULL, FALSE);

	eq_ini.SetFileName(EQUIPMENT_CONFIG);
	int ini_config_write_result_0 = eq_ini.SetProfileString(_T("Product_Communication"),_T("Equipment_Name"), config_equipment_product_communication_equipment_name);
	int ini_config_write_result_1 = eq_ini.SetProfileString(_T("Product_Communication"), _T("Communication_Type"), config_equipment_product_communication_type);
	int ini_config_write_result_2 = eq_ini.SetProfileInt(_T("Product_Communication"), _T("PID"), config_equipment_product_pid);
	int ini_config_write_result_3 = eq_ini.SetProfileInt(_T("Product_Communication"), _T("VID"), config_equipment_product_vid);

	int ini_config_write_result_4 = eq_ini.SetProfileString(_T("Distance_Gauge"), _T("Equipment_Name"), config_distance_equipment_name);
	int ini_config_write_result_5 = eq_ini.SetProfileString(_T("Distance_Gauge"), _T("Communication_Type"), config_distance_communication_type);
	int ini_config_write_result_6 = eq_ini.SetProfileString(_T("Distance_Gauge"), _T("Serial_Port"), config_distance_serial_port);
	int ini_config_write_result_7 = eq_ini.SetProfileInt(_T("Distance_Gauge"), _T("Baud_Rate"), config_distance_baud_rate);
//	int ini_config_write_result_8 = eq_ini.SetProfileInt(_T("Distance_Gauge"), _T("Slave_ID"), config_distance_slave_id);
	int ini_config_write_result_8 = eq_ini.SetProfileString(_T("Distance_Gauge"), _T("Slave_ID"), config_distance_slave_id);

	int ini_config_write_result_9 = eq_ini.SetProfileString(_T("Pressure_Gauge"), _T("Equipment_Name"), config_pressure_equipment_name);
	int ini_config_write_result_10 = eq_ini.SetProfileString(_T("Pressure_Gauge"), _T("Communication_Type"), config_pressure_communication_type);
	int ini_config_write_result_11 = eq_ini.SetProfileString(_T("Pressure_Gauge"), _T("Serial_Port"), config_pressure_serial_port);
	int ini_config_write_result_12 = eq_ini.SetProfileInt(_T("Pressure_Gauge"), _T("Baud_Rate"), config_pressure_baud_rate);
	//int ini_config_write_result_13 = eq_ini.SetProfileInt(_T("Pressure_Gauge"), _T("Slave_ID"), config_pressure_slave_id);
	int ini_config_write_result_13 = eq_ini.SetProfileString(_T("Pressure_Gauge"), _T("Slave_ID"), config_pressure_slave_id);

	int ini_config_write_result_14 = eq_ini.SetProfileString(_T("BLUETOOTH"), _T("Equipment_Name"), config_bluetooth_equipment_name);
	int ini_config_write_result_15 = eq_ini.SetProfileString(_T("BLUETOOTH"), _T("Communication_Type"), config_bluetooth_communication_type);
	int ini_config_write_result_16 = eq_ini.SetProfileString(_T("BLUETOOTH"), _T("Serial_Port"), config_bluetooth_serial_port);
	int ini_config_write_result_17 = eq_ini.SetProfileInt(_T("BLUETOOTH"), _T("Baud_Rate"), config_bluetooth_baud_rate);


	if ((ini_config_write_result_0 == 0) &&
		(ini_config_write_result_1 == 0) &&
		(ini_config_write_result_2 == 0) &&
		(ini_config_write_result_3 == 0) &&
		(ini_config_write_result_4 == 0) &&
		(ini_config_write_result_5 == 0) &&
		(ini_config_write_result_6 == 0) &&
		(ini_config_write_result_7 == 0) &&
		(ini_config_write_result_8 == 0) &&
		(ini_config_write_result_9 == 0) &&
		(ini_config_write_result_10 == 0) &&
		(ini_config_write_result_11 == 0) &&
		(ini_config_write_result_12 == 0) &&
		(ini_config_write_result_13 == 0) &&
		(ini_config_write_result_14 == 0) &&
		(ini_config_write_result_15 == 0) &&
		(ini_config_write_result_16 == 0) &&
		(ini_config_write_result_17 == 0)) {
		AfxMessageBox(_T("Configuration File Write Error."), MB_OK | MB_ICONSTOP);
	}
	else {
		AfxMessageBox(_T("Configuration File Write Success."), MB_OK | MB_ICONINFORMATION);
	}
}





BOOL CCONFIG_EQUIPMENTdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	BOOL Ini_File_Check_Result = eq_filecheck.IsFileExist(EQUIPMENT_CONFIG);
	if (Ini_File_Check_Result == FALSE) {
		CString msg;
		//CString exe_path;
		//exe_path.Format("%s",GetModuleFileName());
		msg.Format(_T("No Found Configuration File: %s!\nDo You Want to Creat This File?\nPress 'YES' to Creat New INI File. Press 'NO' to Cancel and Exit."), EQUIPMENT_CONFIG);
		int msg_feedback = AfxMessageBox(msg, MB_YESNO | MB_ICONSTOP);
		if (msg_feedback == IDYES) {
			eq_ini.SetFileName(EQUIPMENT_CONFIG);
			//ini.~CIniFile();
			eq_ini.SetProfileString(_T("Product_Communication"), _T("Equipment_Name"), _T("No value"));
			eq_ini.SetProfileString(_T("Product_Communication"), _T("Communication_Type"), _T("No value"));
			eq_ini.SetProfileString(_T("Product_Communication"), _T("PID"), _T("0x????"));
			eq_ini.SetProfileString(_T("Product_Communication"), _T("VID"), _T("0x????"));
			eq_ini.SetProfileString(_T("Distance_Gauge"), _T("Equipment_Name"), _T("No value"));
			eq_ini.SetProfileString(_T("Distance_Gauge"), _T("Communication_Type"), _T("No value"));
			eq_ini.SetProfileString(_T("Distance_Gauge"), _T("Serial_Port"), _T("No value"));
			eq_ini.SetProfileString(_T("Distance_Gauge"), _T("Baud_Rate"), _T("????"));
			eq_ini.SetProfileString(_T("Distance_Gauge"), _T("Slave_ID"), _T("No value"));
			eq_ini.SetProfileString(_T("Pressure_Gauge"), _T("Equipment_Name"), _T("No value"));
			eq_ini.SetProfileString(_T("Pressure_Gauge"), _T("Communication_Type"), _T("No value"));
			eq_ini.SetProfileString(_T("Pressure_Gauge"), _T("Serial_Port"), _T("No value"));
			eq_ini.SetProfileString(_T("Pressure_Gauge"), _T("Baud_Rate"), _T("????"));
			eq_ini.SetProfileString(_T("Pressure_Gauge"), _T("Slave_ID"), _T("No value"));
			eq_ini.SetProfileString(_T("BLUETOOTH"), _T("Equipment_Name"), _T("No value"));
			eq_ini.SetProfileString(_T("BLUETOOTH"), _T("Communication_Type"), _T("No value"));
			eq_ini.SetProfileString(_T("BLUETOOTH"), _T("Serial_Port"), _T("No value"));
			eq_ini.SetProfileString(_T("BLUETOOTH"), _T("Baud_Rate"), _T("????"));
		}
		if (msg_feedback == IDNO) {
			EndDialog(IDD_CONFIG_EQUIPMENT);
			//return FALSE;
		}

	}

	eq_ini.SetFileName(EQUIPMENT_CONFIG);
	eq_ini.GetProfileStringW(_T("Product_Communication"), _T("Equipment_Name"), config_equipment_product_communication_equipment_name);
	eq_ini.GetProfileStringW(_T("Product_Communication"), _T("Communication_Type"), config_equipment_product_communication_type);
	config_equipment_product_pid = eq_ini.GetProfileInt(_T("Product_Communication"), _T("PID"));
	config_equipment_product_vid = eq_ini.GetProfileInt(_T("Product_Communication"), _T("VID"));
	eq_ini.GetProfileStringW(_T("Distance_Gauge"), _T("Equipment_Name"), config_distance_equipment_name);
	eq_ini.GetProfileStringW(_T("Distance_Gauge"), _T("Communication_Type"), config_distance_communication_type);
	eq_ini.GetProfileStringW(_T("Distance_Gauge"), _T("Serial_Port"), config_distance_serial_port);
	config_distance_baud_rate = eq_ini.GetProfileIntW(_T("Distance_Gauge"), _T("Baud_Rate"));
	//config_distance_slave_id  = eq_ini.GetProfileIntW(_T("Distance_Gauge"), _T("Slave_ID"));
	eq_ini.GetProfileStringW(_T("Distance_Gauge"), _T("Slave_ID"), config_distance_slave_id);

	eq_ini.GetProfileStringW(_T("Pressure_Gauge"), _T("Equipment_Name"), config_pressure_equipment_name);
	eq_ini.GetProfileStringW(_T("Pressure_Gauge"), _T("Communication_Type"), config_pressure_communication_type);
	eq_ini.GetProfileStringW(_T("Pressure_Gauge"), _T("Serial_Port"), config_pressure_serial_port);
	config_pressure_baud_rate = eq_ini.GetProfileIntW(_T("Pressure_Gauge"), _T("Baud_Rate"));
	//config_pressure_slave_id = eq_ini.GetProfileIntW(_T("Pressure_Gauge"), _T("Slave_ID"));
	eq_ini.GetProfileStringW(_T("Pressure_Gauge"), _T("Slave_ID"), config_pressure_slave_id);

	eq_ini.GetProfileStringW(_T("BLUETOOTH"), _T("Equipment_Name"), config_bluetooth_equipment_name);
	eq_ini.GetProfileStringW(_T("BLUETOOTH"), _T("Communication_Type"), config_bluetooth_communication_type);
	eq_ini.GetProfileStringW(_T("BLUETOOTH"), _T("Serial_Port"), config_bluetooth_serial_port);
	config_bluetooth_baud_rate = eq_ini.GetProfileIntW(_T("BLUETOOTH"), _T("Baud_Rate"));

	GetDlgItem(IDC_EQUIPMENT_PRODUCT_COMMUNICATION_EQUIPMENT_NAME)->SetWindowText(config_equipment_product_communication_equipment_name);
	GetDlgItem(IDC_EQUIPMENT_PRODUCT_COMMUNICATION_TYPE)->SetWindowText(config_equipment_product_communication_type);
	CString config_equipment_product_pid_text;
	config_equipment_product_pid_text.Format(_T("%d"), config_equipment_product_pid);
	CString config_equipment_product_vid_text;
	config_equipment_product_vid_text.Format(_T("%d"), config_equipment_product_vid);
	GetDlgItem(IDC_EQUIPMENT_PRODUCT_COMMUNICATION_PID)->SetWindowText(config_equipment_product_pid_text);
	GetDlgItem(IDC_EQUIPMENT_PRODUCT_COMMUNICATION_VID)->SetWindowText(config_equipment_product_vid_text);

	GetDlgItem(IDC_DISTANCE_EQUIPMENT_NAME)->SetWindowText(config_distance_equipment_name);
	GetDlgItem(IDC_DISTANCE_COMMUNICATION_TYPE)->SetWindowText(config_distance_communication_type);
	GetDlgItem(IDC_DISTANCE_SERIAL_PORT)->SetWindowText(config_distance_serial_port);
	CString config_distance_baud_rate_text;
	config_distance_baud_rate_text.Format(_T("%d"), config_distance_baud_rate);
	//CString config_distance_slave_id_text;
	//config_distance_slave_id_text.Format(_T("%d"), config_distance_slave_id);
	GetDlgItem(IDC_DISTANCE_BAUD_RATE)->SetWindowText(config_distance_baud_rate_text);
	GetDlgItem(IDC_DISTANCE_SLAVE_ID)->SetWindowText(config_distance_slave_id);

	GetDlgItem(IDC_PRESSURE_EQUIPMENT_NAME)->SetWindowText(config_pressure_equipment_name);
	GetDlgItem(IDC_PRESSURE_COMMUNICATION_TYPE)->SetWindowText(config_pressure_communication_type);
	GetDlgItem(IDC_PRESSURE_SERIAL_PORT)->SetWindowText(config_pressure_serial_port);
	CString config_pressure_baud_rate_text;
	config_pressure_baud_rate_text.Format(_T("%d"), config_pressure_baud_rate);
	//CString config_pressure_slave_id_text;
	//config_pressure_slave_id_text.Format(_T("%d"), config_pressure_slave_id);
	GetDlgItem(IDC_PRESSURE_BAUD_RATE)->SetWindowText(config_pressure_baud_rate_text);
	GetDlgItem(IDC_PRESSURE_SLAVE_ID)->SetWindowText(config_pressure_slave_id);

	GetDlgItem(IDC_BLUETOOTH_EQUIPMENT_NAME)->SetWindowText(config_bluetooth_equipment_name);
	GetDlgItem(IDC_BLUETOOTH_COMMUNICATION_TYPE)->SetWindowText(config_bluetooth_communication_type);
	GetDlgItem(IDC_BLUETOOTH_SERIAL_PORT)->SetWindowText(config_bluetooth_serial_port);
	CString config_bluetooth_baud_rate_text;
	config_bluetooth_baud_rate_text.Format(_T("%d"), config_bluetooth_baud_rate);
	GetDlgItem(IDC_BLUETOOTH_BAUD_RATE)->SetWindowText(config_bluetooth_baud_rate_text);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
