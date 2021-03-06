// CMaintenanceTestBenchDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "TDC_FVT4.h"
//#include "TDC_FVT4Dlg.h"
#include "afxdialogex.h"
#include "TDC_FVT4_CONFIG_MAINdlg.h"
#include "CONFIG_EQUIPMENTdlg.h"
#include "CONFIG_SEQUENCEdlg.h"
#include "CMaintenanceTestBenchDlg.h"
#include "IniFile.h"
#include "CGet_Config.h"
#include "CTest_Sequence.h"
#include "SerialPort.h"
#include "CSTLinkV2.h"
#include "CTestBench.h"
#include "fstream"
#include "File_Check.h"

//#include "stdafx.h"
//#include "TDC_FVT4.h"
//#include "CMaintenanceTestBenchDlg.h"
//#include "afxdialogex.h"
//#include "CGet_Config.h"
//#include "SerialPort.h"
//#include "CSTLinkV2.h"
//#include "CTestBench.h"

CGet_Config config;
CSerialPort rs485;
CSTLinkV2 st;
CTestBench tb;

char Distance_command[] = { 0x23,0x30,0x31,0x30,0x30,0x0D };
char Pressure_command[] = { 0x23,0x30,0x32,0x30,0x30,0x0D };

// CMaintenanceTestBenchDlg 对话框

IMPLEMENT_DYNAMIC(CMaintenanceTestBenchDlg, CDialogEx)

CMaintenanceTestBenchDlg::CMaintenanceTestBenchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTBENCH, pParent)
	, FW_File_Name(_T(""))
{

}

CMaintenanceTestBenchDlg::~CMaintenanceTestBenchDlg()
{
}

void CMaintenanceTestBenchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FWFILEPATH, FW_File_Name);
	DDX_Control(pDX, IDC_FLASH, Flash_Button);
	DDX_Control(pDX, IDC_MOVELEFT, Move_Left_Button);
	DDX_Control(pDX, IDC_MOVERIGHT, Move_Right_Button);
	DDX_Control(pDX, IDC_MOVESTOP, Move_Stop_Button);
	DDX_Control(pDX, IDC_INFLATORRELAY, Inflator_Relay_Button);
	DDX_Control(pDX, IDC_TDCRELAY, TDC_Relay_Button);
	DDX_Control(pDX, IDC_RELEASERELAY, Release_Relay_Button);
	DDX_Control(pDX, IDC_INFLATORSTART, Inflator_Start_Button);
	DDX_Control(pDX, IDC_INFLATORSTOP, Inflator_Stop_Button);
	DDX_Control(pDX, IDC_CHARGING, Charging_Relay_Button);
	DDX_Control(pDX, IDC_KEYON, Key_On_Relay_Button);
	DDX_Control(pDX, IDC_DON, Distance_Monitor_Button);
	DDX_Control(pDX, IDC_PON, Pressure_Monitor_Button);
	DDX_Control(pDX, IDC_DISTANCE_GAUGE, Distance_Gauge);
	DDX_Control(pDX, IDC_PRESSURE_GAUGE, Pressure_Gauge);
	DDX_Control(pDX, IDC_FWFILEPATH, FW_FileName_Control);
	DDX_Control(pDX, IDC_DOFF, DOFF_Button);
	DDX_Control(pDX, IDC_POFF, POFF_Button);
}


BEGIN_MESSAGE_MAP(CMaintenanceTestBenchDlg, CDialogEx)
	ON_BN_CLICKED(IDC_FLASH, &CMaintenanceTestBenchDlg::OnBnClickedFlash)
	ON_BN_CLICKED(IDC_MOVELEFT, &CMaintenanceTestBenchDlg::OnBnClickedMoveleft)
	ON_BN_CLICKED(IDC_MOVERIGHT, &CMaintenanceTestBenchDlg::OnBnClickedMoveright)
	ON_BN_CLICKED(IDC_MOVESTOP, &CMaintenanceTestBenchDlg::OnBnClickedMovestop)
	ON_BN_CLICKED(IDC_INFLATORRELAY, &CMaintenanceTestBenchDlg::OnBnClickedInflatorrelay)
	ON_BN_CLICKED(IDC_TDCRELAY, &CMaintenanceTestBenchDlg::OnBnClickedTdcrelay)
	ON_BN_CLICKED(IDC_RELEASERELAY, &CMaintenanceTestBenchDlg::OnBnClickedReleaserelay)
	ON_BN_CLICKED(IDC_INFLATORSTART, &CMaintenanceTestBenchDlg::OnBnClickedInflatorstart)
	ON_BN_CLICKED(IDC_INFLATORSTOP, &CMaintenanceTestBenchDlg::OnBnClickedInflatorstop)
	ON_BN_CLICKED(IDC_CHARGING, &CMaintenanceTestBenchDlg::OnBnClickedCharging)
	ON_BN_CLICKED(IDC_KEYON, &CMaintenanceTestBenchDlg::OnBnClickedKeyon)
	ON_BN_CLICKED(IDC_DON, &CMaintenanceTestBenchDlg::OnBnClickedDon)
	ON_BN_CLICKED(IDC_DOFF, &CMaintenanceTestBenchDlg::OnBnClickedDoff)
	ON_MESSAGE(WM_COMM_RXSTR, &CMaintenanceTestBenchDlg::OnReceiveStr)
	ON_BN_CLICKED(IDC_PON, &CMaintenanceTestBenchDlg::OnBnClickedPon)
	ON_BN_CLICKED(IDC_POFF, &CMaintenanceTestBenchDlg::OnBnClickedPoff)
END_MESSAGE_MAP()


// CMaintenanceTestBenchDlg 消息处理程序

LRESULT CMaintenanceTestBenchDlg::OnReceiveStr(WPARAM str, LPARAM commInfo)
{
	struct serialPortInfo
	{
		UINT portNr;//串口号
		DWORD bytesRead;//读取的字节数
	}*pCommInfo;
	pCommInfo = (serialPortInfo*)commInfo;
	CString str1((char*)str);
	Serial_Port_Read_Result = str1;
	return TRUE;
}

BOOL CMaintenanceTestBenchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//得到配置参数
	config.config_file_name_define();
	config.get_main_config(config.main_file_name);
	config.get_equipment_config(config.equipment_file_name);
	config.get_sequence_config(config.sequence_file_name);
	config.get_testbench_config(config.testbench_file_name);
	config.get_limit_config(config.limit_file_name);
	//初始化TESTBENCH
	if (tb.Get_DevHandle() <= 0) {
		AfxMessageBox(_T("Cannot Init TestBench!"));
		//return FALSE;
	}
	tb.IO_Init(config.TestBench_GPIO_GPIO_I2C_0);
	tb.IO_Init(config.TestBench_GPIO_GPIO_I2C_1);
	tb.Internet_IO_Init(config.TestBench_INTERNET_GPIO0);
	tb.Internet_IO_Init(config.TestBench_INTERNET_GPIO1);
	tb.Internet_IO_Init(config.TestBench_INTERNET_GPIO2);
	tb.Internet_IO_Init(config.TestBench_INTERNET_GPIO3);
	// TODO:  在此添加额外的初始化


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CMaintenanceTestBenchDlg::MySleep(DWORD nMilliseconds)
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


void CMaintenanceTestBenchDlg::OnBnClickedFlash()
{
	GetDlgItem(IDC_FWFILEPATH)->GetWindowText(FW_File_Name);
	FW_FileName_Control.EnableWindow(0);
	Flash_Button.EnableWindow(0);
	if (FW_File_Name.GetLength() > 0) {

		if (config.Limit_FW_Flash_Manual_Power_On == 1) {
			AfxMessageBox(_T("Please manual Push The Power On Key Till Another Remind Window Pop Up.\r\n 请手工按住开机键直到弹出另一个提示窗口"));
		}
		tb.Internet_IO_Open(config.TestBench_INTERNET_GPIO0);
		tb.Internet_IO_Open(config.TestBench_INTERNET_GPIO1);
		bool flash_result = st.Flash(FW_File_Name,config.Limit_FW_Flash_Wire_Begin_Address,TRUE);
		tb.Internet_IO_Close(config.TestBench_INTERNET_GPIO0);
		tb.Internet_IO_Close(config.TestBench_INTERNET_GPIO1);
		if (config.Limit_FW_Flash_Manual_Power_On == 1) {
			AfxMessageBox(_T("Please Release The Power On Key.\r\n 请释放开机键!"));
		}
		if (flash_result) {
			CString flash_result_str = st.Read_exe_Result(_T("Verification"), 15, 2);
			if (flash_result_str == _T("OK")) {
				AfxMessageBox(_T("Flash PASSED!"));
			}
			else {
				AfxMessageBox(_T("Flash FAILED!"));
			}
		}
		else {
			AfxMessageBox(_T("Flash Execute Failed!"));
		}
	}
	else {
		AfxMessageBox(_T("Wrong FW File Name!"));
	}
	FW_FileName_Control.EnableWindow(1);
	Flash_Button.EnableWindow(1);
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedMoveleft()
{
	Move_Left_Button.EnableWindow(0);
	Move_Right_Button.EnableWindow(0);
	Move_Stop_Button.EnableWindow(1);
	bool move_result;
	move_result = tb.Internet_IO_Init(config.TestBench_INTERNET_GPIO2);
	if (!move_result) {
		AfxMessageBox(_T("Testbench Running Problem!"));
	}
	move_result = tb.IO_To_Open(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO13);
	if (!move_result) {
		AfxMessageBox(_T("Testbench Running Problem!"));
	}
	move_result = tb.IO_To_Close(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO14);
	if (!move_result) {
		AfxMessageBox(_T("Testbench Running Problem!"));
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedMoveright()
{
	Move_Left_Button.EnableWindow(0);
	Move_Right_Button.EnableWindow(0);
	Move_Stop_Button.EnableWindow(1);
	bool move_result;
	move_result = tb.Internet_IO_Open(config.TestBench_INTERNET_GPIO2);
	if (!move_result) {
		AfxMessageBox(_T("Testbench Running Problem!"));
	}
	move_result = tb.IO_To_Open(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO14);
	if (!move_result) {
		AfxMessageBox(_T("Testbench Running Problem!"));
	}
	//	MySleep(500);
	move_result = tb.IO_To_Close(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO13);
	if (!move_result) {
		AfxMessageBox(_T("Testbench Running Problem!"));
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedMovestop()
{
	Move_Left_Button.EnableWindow(1);
	Move_Right_Button.EnableWindow(1);
	Move_Stop_Button.EnableWindow(0);
	bool move_result;
	move_result = tb.Internet_IO_Init(config.TestBench_INTERNET_GPIO2);
	if (!move_result) {
		AfxMessageBox(_T("Testbench Running Problem!"));
	}
	move_result = tb.IO_To_Open(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO13);
	if (!move_result) {
		AfxMessageBox(_T("Testbench Running Problem!"));
	}
	move_result = tb.IO_To_Open(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO14);
	if (!move_result) {
		AfxMessageBox(_T("Testbench Running Problem!"));
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedInflatorrelay()
{
	CString status;
	GetDlgItemTextW(IDC_INFLATORRELAY, status);
	tb.IO_Action(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO0);
	if (status == _T("Open")) {
		SetDlgItemTextW(IDC_INFLATORRELAY, _T("Close"));
	}
	else {
		SetDlgItemTextW(IDC_INFLATORRELAY, _T("Open"));
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedTdcrelay()
{
	CString status;
	GetDlgItemTextW(IDC_TDCRELAY, status);
	tb.IO_Action(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO2);
	if (status == _T("Open")) {
		SetDlgItemTextW(IDC_TDCRELAY, _T("Close"));
	}
	else {
		SetDlgItemTextW(IDC_TDCRELAY, _T("Open"));
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedReleaserelay()
{
	CString status;
	GetDlgItemTextW(IDC_RELEASERELAY, status);
	tb.IO_Action(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO1);
	if (status == _T("Open")) {
		SetDlgItemTextW(IDC_RELEASERELAY, _T("Close"));
	}
	else {
		SetDlgItemTextW(IDC_RELEASERELAY, _T("Open"));
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedInflatorstart()
{
	Inflator_Start_Button.EnableWindow(0);
	Inflator_Stop_Button.EnableWindow(1);
	tb.IO_Action(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO3);
	MySleep(100);
	tb.IO_Action(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO3);
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedInflatorstop()
{
	Inflator_Start_Button.EnableWindow(1);
	Inflator_Stop_Button.EnableWindow(0);
	tb.IO_Action(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO4);
	MySleep(100);
	tb.IO_Action(config.TestBench_GPIO_GPIO_I2C_1, config.TestBench_GPIO_GPIO4);

	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedCharging()
{
	CString status;
	GetDlgItemTextW(IDC_CHARGING, status);
	if (status == _T("Open")) {
		bool IO_result = tb.Internet_IO_Open(config.TestBench_INTERNET_GPIO0);
		if (IO_result = FALSE) {
			AfxMessageBox(_T("Testbench Running Problem!"));
		}
		else {
			SetDlgItemTextW(IDC_CHARGING, _T("Close"));
		}		
	}
	else {
		bool IO_result = tb.Internet_IO_Init(config.TestBench_INTERNET_GPIO0);
		if (IO_result = FALSE) {
			AfxMessageBox(_T("Testbench Running Problem!"));
		}
		else {
			SetDlgItemTextW(IDC_CHARGING, _T("Open"));
		}
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedKeyon()
{
	CString status;
	GetDlgItemTextW(IDC_KEYON, status);
	if (status == _T("Open")) {
		bool IO_result = tb.Internet_IO_Open(config.TestBench_INTERNET_GPIO1);
		if (IO_result = FALSE) {
			AfxMessageBox(_T("Testbench Running Problem!"));
		}
		else {
			SetDlgItemTextW(IDC_KEYON, _T("Close"));
		}
	}
	else {
		bool IO_result = tb.Internet_IO_Init(config.TestBench_INTERNET_GPIO1);
		if (IO_result = FALSE) {
			AfxMessageBox(_T("Testbench Running Problem!"));
		}
		else {
			SetDlgItemTextW(IDC_KEYON, _T("Open"));
		}
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedDon()
{
	Serial_Port_Read_Result = _T("");
	Distance_Monitor_Button.EnableWindow(0);
	Pressure_Monitor_Button.EnableWindow(0);
	DOFF_Button.EnableWindow(1);
	POFF_Button.EnableWindow(0);
	serial_read_enable = TRUE;
	while (serial_read_enable) {
		if (Serial_Open(config.Distance_Gauge_Serial_Port, config.Distance_Gauge_Baud_Rate)) {
			rs485.WriteToPort(Distance_command,sizeof(Distance_command));
			while (Serial_Port_Read_Result.GetLength() != 10) {
				MySleep(10);
			}
			Serial_Port_Read_Result.Delete(0, 1);
			Serial_Port_Read_Result = Serial_Port_Read_Result.GetBufferSetLength(Serial_Port_Read_Result.GetLength() - 2);
			Distance_Gauge.SetWindowTextW(Serial_Port_Read_Result);
		}
		else {
			AfxMessageBox(_T("Cannot Open Distance Gauge Serial Port!"));
			serial_read_enable = FALSE;
		}
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedDoff()
{
	Distance_Monitor_Button.EnableWindow(1);
	Pressure_Monitor_Button.EnableWindow(1);
	DOFF_Button.EnableWindow(0);
	POFF_Button.EnableWindow(0);
	serial_read_enable = FALSE;
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedPon()
{
	Serial_Port_Read_Result = _T("");
	Distance_Monitor_Button.EnableWindow(0);
	Pressure_Monitor_Button.EnableWindow(0);
	DOFF_Button.EnableWindow(0);
	POFF_Button.EnableWindow(1);
	serial_read_enable = TRUE;
	while (serial_read_enable) {
		if (Serial_Open(config.Pressure_Gauge_Serial_Port, config.Pressure_Gauge_Baud_Rate)) {
			rs485.WriteToPort(Pressure_command, sizeof(Pressure_command));
			while (Serial_Port_Read_Result.GetLength() != 10) {
				MySleep(10);
			}
			Serial_Port_Read_Result.Delete(0, 1);
			Serial_Port_Read_Result = Serial_Port_Read_Result.GetBufferSetLength(Serial_Port_Read_Result.GetLength() - 2);
			Pressure_Gauge.SetWindowTextW(Serial_Port_Read_Result);
		}
		else {
			AfxMessageBox(_T("Cannot Open Pressure Gauge Serial Port!"));
			serial_read_enable = FALSE;
		}
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CMaintenanceTestBenchDlg::OnBnClickedPoff()
{
	Distance_Monitor_Button.EnableWindow(1);
	Pressure_Monitor_Button.EnableWindow(1);
	DOFF_Button.EnableWindow(0);
	POFF_Button.EnableWindow(0);
	serial_read_enable = FALSE;
	// TODO: 在此添加控件通知处理程序代码
}


bool CMaintenanceTestBenchDlg::Serial_Open(CString port_str, int SelBaudRate)
{
	int SelPortNO;
	port_str.Delete(0, 3);
	SelPortNO = _tstoi(port_str);
	if (rs485.InitPort(this->GetSafeHwnd(), SelPortNO, SelBaudRate))
	{
		rs485.StartMonitoring();
		return TRUE;
	}
	else
	{
		AfxMessageBox(_T("串口已被占用！"));
		return FALSE;
	}
}
