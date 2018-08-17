#pragma once


// CCONFIG_SEQUENCEdlg 对话框

class CCONFIG_SEQUENCEdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCONFIG_SEQUENCEdlg)

public:
	CCONFIG_SEQUENCEdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCONFIG_SEQUENCEdlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_SEQUENCE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// Config For Test Environment Check Enable/Disable
	BOOL config_test_environment_check;
	// Config For Equipment Check Enable/Disable
	BOOL config_equipment_check;
	// Config For FW_Flash Enable/Disable
	BOOL config_fw_flash;
	// Config ForBlueTooth Check Enable/Disable
	BOOL config_bluetooth_check;
	// Config For RFID Check Enable/Disable
	BOOL config_rfid_check;
	// Config For Button Check Enable/Disable
	BOOL config_button_check;
	// Config For Charging Check Enable/Disable
	BOOL config_charging_check;
	// Config For LCD Check Enable/Disable
	BOOL config_lcd_check;
	// Config For Buzz Check Enable/Disable
	BOOL config_buzz_check;
	// Config For Distance Calibration Enable/Disable
	BOOL config_distance_calibration;
	// Config For Distance Measurement Enable/Disable
	BOOL config_distance_measurement;
	// Config For Pressure Calibration Enable/Disable
	BOOL config_pressure_calibration;
	// Config For Pressure Measurement Enable/Disable
	BOOL config_pressure_measurement;
	afx_msg void OnBnClickedTestEnvironmentCheck();
	afx_msg void OnBnClickedEquipmentCheck();
	afx_msg void OnBnClickedFwFlash();
	afx_msg void OnBnClickedBluetoothCheck();
	afx_msg void OnBnClickedRfidCheck();
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnBnClickedChargingCheck();
	afx_msg void OnBnClickedLcdCheck();
	afx_msg void OnBnClickedBuzzCheck();
	afx_msg void OnBnClickedDistanceCalibration();
	afx_msg void OnBnClickedDistanceMeasurement();
	afx_msg void OnBnClickedPressureCalibration();
	afx_msg void OnBnClickedPressureMeasurement();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio10();
	afx_msg void OnBnClickedRadio12();
	afx_msg void OnBnClickedRadio14();
	afx_msg void OnBnClickedRadio16();
	afx_msg void OnBnClickedRadio18();
	afx_msg void OnBnClickedRadio20();
	afx_msg void OnBnClickedRadio22();
	afx_msg void OnBnClickedRadio24();
	afx_msg void OnBnClickedRadio26();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
