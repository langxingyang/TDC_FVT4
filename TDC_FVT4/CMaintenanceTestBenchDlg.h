#pragma once


// CMaintenanceTestBenchDlg 对话框

class CMaintenanceTestBenchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMaintenanceTestBenchDlg)

public:
	CMaintenanceTestBenchDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMaintenanceTestBenchDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTBENCH };
#endif

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg LRESULT OnReceiveStr(WPARAM str, LPARAM commInfo);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void CMaintenanceTestBenchDlg::MySleep(DWORD nMilliseconds);
	CString Serial_Port_Read_Result;
	bool serial_read_enable;
	// FW 文件名
	CString FW_File_Name;
	// 烧录按钮控件
	CButton Flash_Button;
	// 步进电机左移动按键
	CButton Move_Left_Button;
	// 步进电机右移按键
	CButton Move_Right_Button;
	// 步进电机停止按键
	CButton Move_Stop_Button;
	// 充气泵电磁阀按键
	CButton Inflator_Relay_Button;
	// TDC产品电磁阀按键
	CButton TDC_Relay_Button;
	// 放气电磁阀按键
	CButton Release_Relay_Button;
	// 充气泵启动按键
	CButton Inflator_Start_Button;
	// 充气泵停止按键
	CButton Inflator_Stop_Button;
	// 充电继电器按键
	CButton Charging_Relay_Button;
	// TDC "ON" 键继电器按键
	CButton Key_On_Relay_Button;
	// 位移传感器监控打开按键
	CButton Distance_Monitor_Button;
	// 气压传感器监控打开按键
	CButton Pressure_Monitor_Button;
	// 位移传感器监控字符控件
	CEdit Distance_Gauge;
	// 气压传感器监控字符控件
	CEdit Pressure_Gauge;
	afx_msg void OnBnClickedFlash();
	// 固件文件手动输入框
	CMFCEditBrowseCtrl FW_FileName_Control;
	afx_msg void OnBnClickedMoveleft();
	afx_msg void OnBnClickedMoveright();
	afx_msg void OnBnClickedMovestop();
	afx_msg void OnBnClickedInflatorrelay();
	afx_msg void OnBnClickedTdcrelay();
	afx_msg void OnBnClickedReleaserelay();
	afx_msg void OnBnClickedInflatorstart();
	afx_msg void OnBnClickedInflatorstop();
	afx_msg void OnBnClickedCharging();
	afx_msg void OnBnClickedKeyon();
	afx_msg void OnBnClickedDon();
	afx_msg void OnBnClickedDoff();
	afx_msg void OnBnClickedPon();
	afx_msg void OnBnClickedPoff();
	bool CMaintenanceTestBenchDlg::Serial_Open(CString port_str, int SelBaudRate);
	// 位移传感器监控停止按键
	CButton DOFF_Button;
	// 气压传感器监控停止按键
	CButton POFF_Button;
};
