// CONFIG_SEQUENCEdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TDC_FVT4.h"
#include "CONFIG_SEQUENCEdlg.h"
#include "afxdialogex.h"
#include "IniFile.h"
#include "File_Check.h"

#define SEQUENCE_CONFIG _T(".\\Config\\Sequence.ini")

CIniFile sq_ini;
File_Check sq_filecheck;

// CCONFIG_SEQUENCEdlg 对话框

IMPLEMENT_DYNAMIC(CCONFIG_SEQUENCEdlg, CDialogEx)

CCONFIG_SEQUENCEdlg::CCONFIG_SEQUENCEdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_SEQUENCE, pParent)
	, config_test_environment_check(FALSE)
	, config_equipment_check(FALSE)
	, config_fw_flash(FALSE)
	, config_bluetooth_check(FALSE)
	, config_rfid_check(FALSE)
	, config_button_check(FALSE)
	, config_charging_check(FALSE)
	, config_lcd_check(FALSE)
	, config_buzz_check(FALSE)
	, config_distance_calibration(FALSE)
	, config_distance_measurement(FALSE)
	, config_pressure_calibration(FALSE)
	, config_pressure_measurement(FALSE)
{

}

CCONFIG_SEQUENCEdlg::~CCONFIG_SEQUENCEdlg()
{
}

void CCONFIG_SEQUENCEdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_TEST_ENVIRONMENT_CHECK, config_test_environment_check);
	DDX_Radio(pDX, IDC_EQUIPMENT_CHECK, config_equipment_check);
	DDX_Radio(pDX, IDC_FW_FLASH, config_fw_flash);
	DDX_Radio(pDX, IDC_BLUETOOTH_CHECK, config_bluetooth_check);
	DDX_Radio(pDX, IDC_RFID_CHECK, config_rfid_check);
	DDX_Radio(pDX, IDC_BUTTON_CHECK, config_button_check);
	DDX_Radio(pDX, IDC_CHARGING_CHECK, config_charging_check);
	DDX_Radio(pDX, IDC_LCD_CHECK, config_lcd_check);
	DDX_Radio(pDX, IDC_BUZZ_CHECK, config_buzz_check);
	DDX_Radio(pDX, IDC_DISTANCE_CALIBRATION, config_distance_calibration);
	DDX_Radio(pDX, IDC_DISTANCE_MEASUREMENT, config_distance_measurement);
	DDX_Radio(pDX, IDC_PRESSURE_CALIBRATION, config_pressure_calibration);
	DDX_Radio(pDX, IDC_PRESSURE_MEASUREMENT, config_pressure_measurement);
}


BEGIN_MESSAGE_MAP(CCONFIG_SEQUENCEdlg, CDialogEx)
	ON_BN_CLICKED(IDC_TEST_ENVIRONMENT_CHECK, &CCONFIG_SEQUENCEdlg::OnBnClickedTestEnvironmentCheck)
	ON_BN_CLICKED(IDC_EQUIPMENT_CHECK, &CCONFIG_SEQUENCEdlg::OnBnClickedEquipmentCheck)
	ON_BN_CLICKED(IDC_FW_FLASH, &CCONFIG_SEQUENCEdlg::OnBnClickedFwFlash)
	ON_BN_CLICKED(IDC_BLUETOOTH_CHECK, &CCONFIG_SEQUENCEdlg::OnBnClickedBluetoothCheck)
	ON_BN_CLICKED(IDC_RFID_CHECK, &CCONFIG_SEQUENCEdlg::OnBnClickedRfidCheck)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CCONFIG_SEQUENCEdlg::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_CHARGING_CHECK, &CCONFIG_SEQUENCEdlg::OnBnClickedChargingCheck)
	ON_BN_CLICKED(IDC_LCD_CHECK, &CCONFIG_SEQUENCEdlg::OnBnClickedLcdCheck)
	ON_BN_CLICKED(IDC_BUZZ_CHECK, &CCONFIG_SEQUENCEdlg::OnBnClickedBuzzCheck)
	ON_BN_CLICKED(IDC_DISTANCE_CALIBRATION, &CCONFIG_SEQUENCEdlg::OnBnClickedDistanceCalibration)
	ON_BN_CLICKED(IDC_DISTANCE_MEASUREMENT, &CCONFIG_SEQUENCEdlg::OnBnClickedDistanceMeasurement)
	ON_BN_CLICKED(IDC_PRESSURE_CALIBRATION, &CCONFIG_SEQUENCEdlg::OnBnClickedPressureCalibration)
	ON_BN_CLICKED(IDC_PRESSURE_MEASUREMENT, &CCONFIG_SEQUENCEdlg::OnBnClickedPressureMeasurement)
	ON_BN_CLICKED(IDC_RADIO2, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO4, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO6, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO8, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO10, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio10)
	ON_BN_CLICKED(IDC_RADIO12, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_RADIO14, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio14)
	ON_BN_CLICKED(IDC_RADIO16, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio16)
	ON_BN_CLICKED(IDC_RADIO18, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio18)
	ON_BN_CLICKED(IDC_RADIO20, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio20)
	ON_BN_CLICKED(IDC_RADIO22, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio22)
	ON_BN_CLICKED(IDC_RADIO24, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio24)
	ON_BN_CLICKED(IDC_RADIO26, &CCONFIG_SEQUENCEdlg::OnBnClickedRadio26)
	ON_BN_CLICKED(IDOK, &CCONFIG_SEQUENCEdlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CCONFIG_SEQUENCEdlg 消息处理程序


void CCONFIG_SEQUENCEdlg::OnBnClickedTestEnvironmentCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	config_test_environment_check = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedEquipmentCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	config_equipment_check = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedFwFlash()
{
	// TODO: 在此添加控件通知处理程序代码
	config_fw_flash = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedBluetoothCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	config_bluetooth_check = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRfidCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	config_rfid_check = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedButtonCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	config_button_check = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedChargingCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	config_charging_check = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedLcdCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	config_lcd_check = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedBuzzCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	config_buzz_check = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedDistanceCalibration()
{
	// TODO: 在此添加控件通知处理程序代码
	config_distance_calibration = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedDistanceMeasurement()
{
	// TODO: 在此添加控件通知处理程序代码
	config_distance_measurement = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedPressureCalibration()
{
	// TODO: 在此添加控件通知处理程序代码
	config_pressure_calibration = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedPressureMeasurement()
{
	// TODO: 在此添加控件通知处理程序代码
	config_pressure_measurement = TRUE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	config_test_environment_check = FALSE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	config_equipment_check = FALSE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio6()
{
	// TODO: 在此添加控件通知处理程序代码
	config_fw_flash = FALSE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio8()
{
	// TODO: 在此添加控件通知处理程序代码
	config_bluetooth_check = FALSE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio10()
{
	// TODO: 在此添加控件通知处理程序代码
	config_rfid_check = FALSE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio12()
{
	// TODO: 在此添加控件通知处理程序代码
	config_button_check = FALSE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio14()
{
	// TODO: 在此添加控件通知处理程序代码
	config_charging_check = FALSE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio16()
{
	// TODO: 在此添加控件通知处理程序代码
	config_lcd_check = FALSE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio18()
{
	// TODO: 在此添加控件通知处理程序代码
	config_buzz_check = FALSE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio20()
{
	// TODO: 在此添加控件通知处理程序代码
	config_distance_calibration = FALSE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio22()
{
	// TODO: 在此添加控件通知处理程序代码
	config_distance_measurement = FALSE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio24()
{
	// TODO: 在此添加控件通知处理程序代码
	config_pressure_calibration = FALSE;
}


void CCONFIG_SEQUENCEdlg::OnBnClickedRadio26()
{
	// TODO: 在此添加控件通知处理程序代码
	config_pressure_measurement = FALSE;
}


BOOL CCONFIG_SEQUENCEdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	BOOL Ini_File_Check_Result = sq_filecheck.IsFileExist(SEQUENCE_CONFIG);
	if (Ini_File_Check_Result == FALSE) {
		CString msg;
		//CString exe_path;
		//exe_path.Format("%s",GetModuleFileName());
		msg.Format(_T("No Found Configuration File: %s!\nDo You Want to Creat This File?\nPress 'YES' to Creat New INI File. Press 'NO' to Cancel and Exit."), SEQUENCE_CONFIG);
		int msg_feedback = AfxMessageBox(msg, MB_YESNO | MB_ICONSTOP);
		if (msg_feedback == IDYES) {
			sq_ini.SetFileName(SEQUENCE_CONFIG);
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("Test_Environment_Check"), _T("0"));
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("Equipment_Check"), _T("0"));
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("FW_Flash"), _T("0"));
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("BlueTooth_Check"), _T("0"));
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("RFID_Check"), _T("0"));
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("Button_Check"), _T("0"));
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("Charging_Check"), _T("0"));
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("LCD_Check"), _T("0"));
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("Buzz_Check"), _T("0"));
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("Distance_Calibration"), _T("0"));
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("Distance_Measurement"), _T("0"));
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("Pressure_Calibration"), _T("0"));
			sq_ini.SetProfileString(_T("SEQUENCE"), _T("Pressure_Measurement"), _T("0"));

		}
		if (msg_feedback == IDNO) {
			EndDialog(IDD_CONFIG_SEQUENCE);
			//return FALSE;
		}

	}
	sq_ini.SetFileName(SEQUENCE_CONFIG);
	config_test_environment_check = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("Test_Environment_Check"));
	config_equipment_check = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("Equipment_Check"));
	config_fw_flash = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("FW_Flash"));
	config_bluetooth_check = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("BlueTooth_Check"));
	config_rfid_check = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("RFID_Check"));
	config_button_check = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("Button_Check"));
	config_charging_check = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("Charging_Check"));
	config_lcd_check = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("LCD_Check"));
	config_buzz_check = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("Buzz_Check"));
	config_distance_calibration = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("Distance_Calibration"));
	config_distance_measurement = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("Distance_Measurement"));
	config_pressure_calibration = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("Pressure_Calibration"));
	config_pressure_measurement = sq_ini.GetProfileIntW(_T("SEQUENCE"), _T("Pressure_Measurement"));

	if (config_test_environment_check == TRUE) {
		((CButton *)GetDlgItem(IDC_TEST_ENVIRONMENT_CHECK))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_TEST_ENVIRONMENT_CHECK))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(TRUE);
	}

	if (config_equipment_check == TRUE) {
		((CButton *)GetDlgItem(IDC_EQUIPMENT_CHECK))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_EQUIPMENT_CHECK))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO4))->SetCheck(TRUE);
	}

	if (config_fw_flash == TRUE) {
		((CButton *)GetDlgItem(IDC_FW_FLASH))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO6))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_FW_FLASH))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO6))->SetCheck(TRUE);
	}

	if (config_bluetooth_check == TRUE) {
		((CButton *)GetDlgItem(IDC_BLUETOOTH_CHECK))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO8))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_BLUETOOTH_CHECK))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO8))->SetCheck(TRUE);
	}

	if (config_rfid_check == TRUE) {
		((CButton *)GetDlgItem(IDC_RFID_CHECK))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO10))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_RFID_CHECK))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO10))->SetCheck(TRUE);
	}

	if (config_button_check == TRUE) {
		((CButton *)GetDlgItem(IDC_BUTTON_CHECK))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO12))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_BUTTON_CHECK))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO12))->SetCheck(TRUE);
	}

	if (config_charging_check == TRUE) {
		((CButton *)GetDlgItem(IDC_CHARGING_CHECK))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO14))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_CHARGING_CHECK))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO14))->SetCheck(TRUE);
	}

	if (config_lcd_check == TRUE) {
		((CButton *)GetDlgItem(IDC_LCD_CHECK))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO16))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_LCD_CHECK))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO16))->SetCheck(TRUE);
	}

	if (config_buzz_check == TRUE) {
		((CButton *)GetDlgItem(IDC_BUZZ_CHECK))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO18))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_BUZZ_CHECK))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO18))->SetCheck(TRUE);
	}

	if (config_distance_calibration == TRUE) {
		((CButton *)GetDlgItem(IDC_DISTANCE_CALIBRATION))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO20))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_DISTANCE_CALIBRATION))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO20))->SetCheck(TRUE);
	}

	if (config_distance_measurement == TRUE) {
		((CButton *)GetDlgItem(IDC_DISTANCE_MEASUREMENT))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO22))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_DISTANCE_MEASUREMENT))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO22))->SetCheck(TRUE);
	}

	if (config_pressure_calibration == TRUE) {
		((CButton *)GetDlgItem(IDC_PRESSURE_CALIBRATION))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO24))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_PRESSURE_CALIBRATION))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO24))->SetCheck(TRUE);
	}

	if (config_pressure_measurement == TRUE) {
		((CButton *)GetDlgItem(IDC_PRESSURE_MEASUREMENT))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO26))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_PRESSURE_MEASUREMENT))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO26))->SetCheck(TRUE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CCONFIG_SEQUENCEdlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	config_test_environment_check = ((CButton *)GetDlgItem(IDC_TEST_ENVIRONMENT_CHECK))->GetCheck();
	config_equipment_check = ((CButton *)GetDlgItem(IDC_EQUIPMENT_CHECK))->GetCheck();
	config_fw_flash = ((CButton *)GetDlgItem(IDC_FW_FLASH))->GetCheck();
	config_bluetooth_check = ((CButton *)GetDlgItem(IDC_BLUETOOTH_CHECK))->GetCheck();
	config_rfid_check = ((CButton *)GetDlgItem(IDC_RFID_CHECK))->GetCheck();
	config_button_check = ((CButton *)GetDlgItem(IDC_BUTTON_CHECK))->GetCheck();
	config_charging_check = ((CButton *)GetDlgItem(IDC_CHARGING_CHECK))->GetCheck();
	config_lcd_check = ((CButton *)GetDlgItem(IDC_LCD_CHECK))->GetCheck();
	config_buzz_check = ((CButton *)GetDlgItem(IDC_BUZZ_CHECK))->GetCheck();
	config_distance_calibration = ((CButton *)GetDlgItem(IDC_DISTANCE_CALIBRATION))->GetCheck();
	config_distance_measurement = ((CButton *)GetDlgItem(IDC_DISTANCE_MEASUREMENT))->GetCheck();
	config_pressure_calibration = ((CButton *)GetDlgItem(IDC_PRESSURE_CALIBRATION))->GetCheck();
	config_pressure_measurement = ((CButton *)GetDlgItem(IDC_PRESSURE_MEASUREMENT))->GetCheck();

	sq_ini.SetFileName(SEQUENCE_CONFIG);
	int ini_config_write_result_0 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("Test_Environment_Check"), config_test_environment_check);
	int ini_config_write_result_1 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("Equipment_Check"), config_equipment_check);
	int ini_config_write_result_2 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("FW_Flash"), config_fw_flash);
	int ini_config_write_result_3 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("BlueTooth_Check"), config_bluetooth_check);
	int ini_config_write_result_4 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("RFID_Check"), config_rfid_check);
	int ini_config_write_result_5 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("Button_Check"), config_button_check);
	int ini_config_write_result_6 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("Charging_Check"), config_charging_check);
	int ini_config_write_result_7 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("LCD_Check"), config_lcd_check);
	int ini_config_write_result_8 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("Buzz_Check"), config_buzz_check);
	int ini_config_write_result_9 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("Distance_Calibration"), config_distance_calibration);
	int ini_config_write_result_10 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("Distance_Measurement"), config_distance_measurement);
	int ini_config_write_result_11 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("Pressure_Calibration"), config_pressure_calibration);
	int ini_config_write_result_12 = sq_ini.SetProfileInt(_T("SEQUENCE"), _T("Pressure_Measurement"), config_pressure_measurement);

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
		(ini_config_write_result_12 == 0)) {
		AfxMessageBox(_T("Configuration File Write Error."), MB_OK | MB_ICONSTOP);
	}
	else {
		AfxMessageBox(_T("Configuration File Write Success."), MB_OK | MB_ICONINFORMATION);
	}
}
