
// TDC_FVT4Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "TDC_FVT4.h"
#include "TDC_FVT4Dlg.h"
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
//#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAIN_CONFIG _T(".//Config//Main.ini")



CIniFile fvt4dlg_ini;
CMenu menu;
CGet_Config get_config;
CTest_Sequence seq;
CSerialPort serial;
CSTLinkV2 stlink;
CTestBench testbench;
File_Check fc;

char T_command[] = { 0x23,0x30,0x31,0x30,0x30,0x0D };
char P_command[] = { 0x23,0x30,0x32,0x30,0x30,0x0D };


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnConfigMain();
	afx_msg void OnHelpAbout();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_CONFIG_MAIN, &CAboutDlg::OnConfigMain)
	ON_COMMAND(ID_HELP_ABOUT, &CAboutDlg::OnHelpAbout)
END_MESSAGE_MAP()


// CTDCFVT4Dlg 对话框



CTDCFVT4Dlg::CTDCFVT4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TDC_FVT4_DIALOG, pParent)
	, c_edittitle(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTDCFVT4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BMP_TITLE, bmp_title);
	DDX_Control(pDX, IDC_START, eButtonStart);
	DDX_Control(pDX, IDC_STOP, eButtonStop);
	DDX_Text(pDX, IDC_TITLE, c_edittitle);
	DDX_Control(pDX, IDC_TITLE, eEditTitle);
	DDX_Control(pDX, IDC_RUNNING_STATUS, eEditRunningStatus);
	DDX_Control(pDX, IDC_PROGRESS, eProgressBar);
	DDX_Control(pDX, IDC_LOG, eEditLog);
	DDX_Control(pDX, IDC_TEST_TOTAL_QTY, eEditTestTotalQTY);
	DDX_Control(pDX, IDC_TEST_PASS_QTY, eEditTestPassQTY);
	DDX_Control(pDX, IDC_TEST_FAIL_QTY, eEditTestFailQTY);
	DDX_Control(pDX, IDC_TEST_FPY, eEditTestFPY);
//	DDX_Control(pDX, IDC_REPEATED_CYCLE, eEditRepeatedCycle);
//	DDX_Control(pDX, IDC_STATIC13, eStaticRepeatedCycle);
	DDX_Control(pDX, IDC_STATIC3, eStaticSerialNo);
	DDX_Control(pDX, IDC_STATIC8, eStaticTestTotal);
	DDX_Control(pDX, IDC_STATIC9, eStaticTestPass);
	DDX_Control(pDX, IDC_STATIC10, eStaticTestFail);
	DDX_Control(pDX, IDC_STATIC11, eStaticTestFPY);
	DDX_Control(pDX, IDC_SN, eEditSerialNo);
}

BEGIN_MESSAGE_MAP(CTDCFVT4Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_CONFIG_MAIN, &CTDCFVT4Dlg::OnConfigMain)
	ON_COMMAND(ID_CONFIG_EQUIPMENT, &CTDCFVT4Dlg::OnConfigEquipment)
	ON_COMMAND(ID_CONFIG_SEQUENCE, &CTDCFVT4Dlg::OnConfigSequence)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_START, &CTDCFVT4Dlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CTDCFVT4Dlg::OnBnClickedStop)
	ON_MESSAGE(WM_COMM_RXSTR, &CTDCFVT4Dlg::OnReceiveStr)
	ON_MESSAGE(WM_UPDATE_TESTRESULT,&CTDCFVT4Dlg::OnReceiveTestResult)
//	ON_BN_CLICKED(IDC_BUTTON1, &CTDCFVT4Dlg::OnBnClickedButton1)
//ON_BN_CLICKED(IDC_OK, &CTDCFVT4Dlg::OnBnClickedOk)
ON_COMMAND(ID_MAINTENANCE_TESTBENCH, &CTDCFVT4Dlg::OnMaintenanceTestbench)
ON_COMMAND(ID_HELP_ABOUT, &CTDCFVT4Dlg::OnHelpAbout)
ON_COMMAND(ID_HELP_USERMANUAL, &CTDCFVT4Dlg::OnHelpUsermanual)
END_MESSAGE_MAP()


// CTDCFVT4Dlg 消息处理程序

BOOL CTDCFVT4Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	AfxOleInit();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//CMenu menu;作为全局变量放到最前面方便更新

	//显示系统菜单栏 William
	menu.LoadMenuW(IDR_MENU1);
	this->SetMenu(&menu);
	menu.Detach();
	//显示系统菜单栏 William
	

	//在标题的图片控件上显示KICKMAKER图标
	//CBitmap bitmap; // CBitmap对象，用于加载位图
	//HBITMAP hBmp;   // 保存CBitmap加载的位图的句柄
	//bitmap.LoadBitmapW(IDB_BMP_KICKMAKER);    // 将位图IDB_BITMAP1加载到bitmap
	//hBmp = (HBITMAP)bitmap.GetSafeHandle(); // 获取bitmap加载位图的句柄
	//bmp_title.ModifyStyle(0, SS_BITMAP | SS_REALSIZECONTROL);
	//bmp_title.SetBitmap(hBmp);   // 设置图片空间m_pictureControl的位图为IDB_BITMAP1
	//CDialog::UpdateWindow();
	HICON m_IconStartBtn = AfxGetApp()->LoadIcon(IDI_ICO_START);
	HICON m_IconStopBtn = AfxGetApp()->LoadIcon(IDI_ICO_STOP);
	eButtonStart.SetIcon(m_IconStartBtn);
	eButtonStop.SetIcon(m_IconStopBtn);


	CFont *l_pFont;//创建新的字体
	l_pFont = new CFont;
	l_pFont->CreateFont(22,                          // 字体高度 32
		0,                           // 字体宽度
		0,                           // 字体倾斜角
		0,                           // 字体倾斜角
		FW_DONTCARE,                   // 字体的粗细
		FALSE,                       // 字体是否为斜体
		FALSE,                       // 字体是否有下划线
		0,                           // 字体是否有删除线
		ANSI_CHARSET,                // 字体使用的字符集
		OUT_DEFAULT_PRECIS,          // 指定如何选择合适的字体
		CLIP_DEFAULT_PRECIS,         // 确定裁剪的精度
		DEFAULT_QUALITY,             // 怎么样跟选择的字体相符合
		DEFAULT_PITCH | FF_SWISS,    // 间距标志和属性标志
		_T("微软雅黑"));          // 字体的名称 微软雅黑, Time New Roman, MS Shell Dlg

							  //MS Shell Dlg

	CFont *m_pFont;//创建新的字体
	m_pFont = new CFont;
	m_pFont->CreateFont(14,                          // 字体高度 32
		0,                           // 字体宽度
		0,                           // 字体倾斜角
		0,                           // 字体倾斜角
		FW_DONTCARE,                   // 字体的粗细 
									   /*
									   #define FW_DONTCARE         0
									   #define FW_THIN             100
									   #define FW_EXTRALIGHT       200
									   #define FW_LIGHT            300
									   #define FW_NORMAL           400
									   #define FW_MEDIUM           500
									   #define FW_SEMIBOLD         600
									   #define FW_BOLD             700
									   #define FW_EXTRABOLD        800
									   #define FW_HEAVY            900
									   */
		FALSE,                       // 字体是否为斜体
		FALSE,                       // 字体是否有下划线
		0,                           // 字体是否有删除线
		ANSI_CHARSET,                // 字体使用的字符集
		OUT_DEFAULT_PRECIS,          // 指定如何选择合适的字体
		CLIP_DEFAULT_PRECIS,         // 确定裁剪的精度
		DEFAULT_QUALITY,             // 怎么样跟选择的字体相符合
		DEFAULT_PITCH | FF_SWISS,    // 间距标志和属性标志
		_T("微软雅黑"));          // 字体的名称

	CFont *s_pFont;//创建新的字体
	s_pFont = new CFont;
	s_pFont->CreateFont(14,                          // 字体高度 32
		0,                           // 字体宽度
		0,                           // 字体倾斜角
		0,                           // 字体倾斜角
		FW_DONTCARE,                   // 字体的粗细
		FALSE,                       // 字体是否为斜体
		FALSE,                       // 字体是否有下划线
		0,                           // 字体是否有删除线
		ANSI_CHARSET,                // 字体使用的字符集
		OUT_DEFAULT_PRECIS,          // 指定如何选择合适的字体
		CLIP_DEFAULT_PRECIS,         // 确定裁剪的精度
		DEFAULT_QUALITY,             // 怎么样跟选择的字体相符合
		DEFAULT_PITCH | FF_SWISS,    // 间距标志和属性标志
		_T("微软雅黑"));       // 字体的名称



	eButtonStart.SetFont(l_pFont);
	eButtonStop.SetFont(l_pFont);
	eStaticSerialNo.SetFont(l_pFont);
	eEditSerialNo.SetFont(l_pFont);
	eEditTitle.SetFont(l_pFont);
	eStaticTestTotal.SetFont(s_pFont);
	eStaticTestPass.SetFont(s_pFont);
	eStaticTestFail.SetFont(s_pFont);
	eStaticTestFPY.SetFont(s_pFont);
	eEditTestTotalQTY.SetFont(s_pFont);
	eEditTestPassQTY.SetFont(s_pFont);
	eEditTestFailQTY.SetFont(s_pFont);
	eEditTestFPY.SetFont(s_pFont);
	eEditLog.SetFont(s_pFont);
	eEditRunningStatus.SetFont(l_pFont);
	sRunningStatus_Result = _T("WAITING");
	sRunningStatus_Sub = _T("WAITING Serial No. Input...");
	//sRunningStatus_Title = (sRunningStatus_Result + _T(" - ") + sRunningStatus_Sub);
	//eEditRunningStatus.SetWindowTextW(sRunningStatus_Title);
	RunningStatusUpdate();

	fvt4dlg_ini.SetFileName(MAIN_CONFIG);
	CString main_title;
	CString test_name;
	CString software_version;
	fvt4dlg_ini.GetProfileStringW(_T("MAIN"), _T("Test_Name"), test_name);
	fvt4dlg_ini.GetProfileStringW(_T("MAIN"), _T("Software_Revision"), software_version);
	main_title.Format(_T("%s - %s"),test_name, software_version);
	eEditTitle.SetWindowTextW(main_title);
	//IDC_RUNNING_STATUS 字符居中
	//CRect rect;
	//GetDlgItem(IDC_RUNNING_STATUS)->GetClientRect(&rect);
	//::OffsetRect(&rect, 0, 15);
	//::SendMessageA(((CComboBox*)GetDlgItem(IDC_RUNNING_STATUS))->m_hWnd, EM_SETRECT, 0, (LPARAM)&rect);

	//eEditLog .SetWindowTextW(_T("Sample Log FIles.\r\nHellow Kickmaker."));

	eEditTestTotalQTY.SetWindowTextW(_T("NULL"));
	eEditTestPassQTY.SetWindowTextW(_T("NULL"));
	eEditTestFailQTY.SetWindowTextW(_T("NULL"));
	eEditTestFPY.SetWindowTextW(_T("NULL"));
	get_config.config_file_name_define();
	get_config.get_main_config(get_config.main_file_name);
	get_config.get_equipment_config(get_config.equipment_file_name);
	get_config.get_sequence_config(get_config.sequence_file_name);
	get_config.get_testbench_config(get_config.testbench_file_name);
	get_config.get_limit_config(get_config.limit_file_name);
	eButtonStop.EnableWindow(0);
	GetDlgItem(IDC_SN)->SetFocus();
	eEditSerialNo.SetLimitText(get_config.MAIN_Barcode_Length);

	//进度条
	eProgressBar.SetRange(0, 100);
	eProgressBar.SetStep(1);
	eProgressBar.SetPos(0);


	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTDCFVT4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTDCFVT4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTDCFVT4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CTDCFVT4Dlg::OnReceiveStr(WPARAM str, LPARAM commInfo)
{
	struct serialPortInfo
	{
		UINT portNr;//串口号
		DWORD bytesRead;//读取的字节数
	}*pCommInfo;
	pCommInfo = (serialPortInfo*)commInfo;
	CString str1((char*)str);
	Serial_Port_Read_Result = str1;
	//LogUpdate(Serial_Port_Read_Result);
	CString running_status;
	GetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	if (running_status.Find(_T("Pressure_Calibration")) >= 0) {

		/*
		Pressure_Calibration_Running_Status = 0;   //0 = Running 1 = Pass 2 = Fail
		if (str1.GetLength() == 10) {
			Serial_Port_Read_Result.Delete(0, 1);
			Serial_Port_Read_Result = Serial_Port_Read_Result.GetBufferSetLength(Serial_Port_Read_Result.GetLength() - 2);
			serial_port_value_float = double(_tstof(Serial_Port_Read_Result));
			if (serial_port_value_float > (get_config.Limit_Pressure_Calibration_Calibration1 - 0.1)) {
				if (serial_port_value_float < (get_config.Limit_Pressure_Calibration_Calibration1 + 0.1)) {
					LogUpdate(_T("Pressure Value meet 4bar."));
					//测试TDC气压 4bar
					float TDC_Pressure_Value = TDC_Get_Pressure();
					CString temp_str0;
					temp_str0.Format(_T("Pressure Sensor Value:%.3f"),serial_port_value_float);
					LogUpdate(temp_str0);
					temp_str0.Format(_T("TDC Pressure Value:   %.3f"), TDC_Pressure_Value);
					LogUpdate(temp_str0);
					int TDC_Pressure_Value_Int = int(TDC_Pressure_Value * 100);
					int Reference_Pressure_Value_Int = int(serial_port_value_float * 100);
					Pressure_Calibration_Result[0] = TDC_Pressure_Value_Int;
					Pressure_Calibration_Result[2] = Reference_Pressure_Value_Int;
				}
			}

			if (serial_port_value_float > (get_config.Limit_Pressure_Calibration_Calibration2 - 0.1)) {
				LogUpdate(_T("Pressure Value meet 12bar."));
				//MySleep(5000);
				//测试TDC气压 12bar

				float TDC_Pressure_Value = TDC_Get_Pressure();
				CString temp_str0;
				temp_str0.Format(_T("Pressure Sensor Value:%.3f"), serial_port_value_float);
				LogUpdate(temp_str0);
				temp_str0.Format(_T("TDC Pressure Value:   %.3f"), TDC_Pressure_Value);
				LogUpdate(temp_str0);
				int TDC_Pressure_Value_Int = int(TDC_Pressure_Value * 100);
				int Reference_Pressure_Value_Int = int(serial_port_value_float * 100);
				Pressure_Calibration_Result[1] = TDC_Pressure_Value_Int;
				Pressure_Calibration_Result[3] = Reference_Pressure_Value_Int;

				Pressure_Calibration_Running_Status = 1;   //0 = Running 1 = Pass 2 = Fail
				return TRUE;
			}
			//int serial_open_result = Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
			//if (serial_open_result != 0) {
			//	LogUpdate(_T("Cannot Open Pressure Gauge Serial Port."));
			//	Pressure_Calibration_Running_Status = 2;
			//	return TRUE;
			//}
			serial.WriteToPort(P_command, 6);
			//LogUpdate(_T("Inflator Running..."));
			CString temp_text;
			temp_text.Format(_T("Get Double Float Value From Serial Port: %.3f."), serial_port_value_float);
			LogUpdate(temp_text);
			return TRUE;

		}
		else {
			//LogUpdate(_T("Receive Error, Need Correct it."));
			if (str_count > 0) {
				MySleep(20);
				Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
				serial.WriteToPort(P_command, 6);
				//LogUpdate(_T("Receive Error, Correct It."));
				str_count = 0;
				return TRUE;
			}
			str_count++;
		}
		*/

		CString temp_text;
		int pressure_calibration_result = 0;
		Pressure_Calibration_Running_Status = 0;   //0 = Running 1 = Pass 2 = Fail
		//LogUpdate(Serial_Port_Read_Result);
		if (str1.GetLength() == 10) {
			Serial_Port_Read_Result.Delete(0, 1);
			Serial_Port_Read_Result = Serial_Port_Read_Result.GetBufferSetLength(Serial_Port_Read_Result.GetLength() - 2);
			serial_port_value_float = float(_tstof(Serial_Port_Read_Result));
			Pressure_Calibration_Running_Status = 1;
			return TRUE;
		}
		else {
			//LogUpdate(_T("Receive Error, Need Correct it."));
			if (str_count > 0) {
				MySleep(20);
				//serial.WriteToPort(T_command, 6);
				//LogUpdate(_T("Receive Error, Correct It."));
				str_count = 0;
				Pressure_Calibration_Running_Status = 1;
				return TRUE;
			}
			str_count++;
			Pressure_Calibration_Running_Status = 1;
		}
	}

	if (running_status.Find(_T("Pressure_Measurement")) >= 0) {
		CString temp_text;
		int pressure_measurement_result = 0;
		Pressure_Measurement_Running_Status = 0;   //0 = Running 1 = Pass 2 = Fail
		LogUpdate(Serial_Port_Read_Result);
		if (str1.GetLength() == 10) {
			Serial_Port_Read_Result.Delete(0, 1);
			Serial_Port_Read_Result = Serial_Port_Read_Result.GetBufferSetLength(Serial_Port_Read_Result.GetLength() - 2);
			serial_port_value_float = float(_tstof(Serial_Port_Read_Result));
			Pressure_Measurement_Running_Status = 1;
			return TRUE;
		}
		else {
			//LogUpdate(_T("Receive Error, Need Correct it."));
			if (str_count > 0) {
				MySleep(20);
				//serial.WriteToPort(T_command, 6);
				//LogUpdate(_T("Receive Error, Correct It."));
				str_count = 0;
				Pressure_Measurement_Running_Status = 1;
				return TRUE;
			}
			str_count++;
			Pressure_Measurement_Running_Status = 1;
		}
	}

	if (running_status.Find(_T("Distance_Calibration")) >= 0) {
		CString temp_text;
		int distance_calibration_result = 0;
		Distance_Calibration_Running_Status = 0;   //0 = Running 1 = Pass 2 = Fail
		//LogUpdate(Serial_Port_Read_Result);
		if (str1.GetLength() == 10) {
			Serial_Port_Read_Result.Delete(0, 1);
			Serial_Port_Read_Result = Serial_Port_Read_Result.GetBufferSetLength(Serial_Port_Read_Result.GetLength() - 2);
			serial_port_value_float = float(_tstof(Serial_Port_Read_Result)) + (float(get_config.Limit_Distance_Calibration_Zero_Position_Offset * 1.0) / 100);
			Serial_Port_Value_Int = serial_port_value_float * 100;
			Distance_Calibration_Running_Status = 1;
			return TRUE;
		}			
		else {
			Serial_Command:
			//LogUpdate(_T("Receive Error, Need Correct it."));
			if (str_count > 0) {
				MySleep(20);
				//serial.WriteToPort(T_command, 6);
				//LogUpdate(_T("Receive Error, Correct It."));
				str_count = 0;
				return TRUE;
			}
			str_count++;
			Distance_Calibration_Running_Status = 1;
		}

	}

	if (running_status.Find(_T("Distance_Measurement")) >= 0) {
		CString temp_text;
		int distance_measurement_result = 0;
		Distance_Measurement_Running_Status = 0;   //0 = Running 1 = Pass 2 = Fail
		//LogUpdate(Serial_Port_Read_Result);
		if (str1.GetLength() == 10) {
			Serial_Port_Read_Result.Delete(0, 1);
			Serial_Port_Read_Result = Serial_Port_Read_Result.GetBufferSetLength(Serial_Port_Read_Result.GetLength() - 2);
			serial_port_value_float = float(_tstof(Serial_Port_Read_Result)) + (float(get_config.Limit_Distance_Measurement_Zero_Position_Offset  * 1.0) / 100);
			Serial_Port_Value_Int = serial_port_value_float * 100;
			Distance_Measurement_Running_Status = 1;
			return TRUE;
		}
		else {
			//LogUpdate(_T("Receive Error, Need Correct it."));
			if (str_count > 0) {
				MySleep(20);
				//serial.WriteToPort(T_command, 6);
				//LogUpdate(_T("Receive Error, Correct It."));
				str_count = 0;
				return TRUE;
			}
			str_count++;
			Distance_Measurement_Running_Status = 1;
		}
	}

	if (running_status.Find(_T("BlueTooth_Check")) >= 0) {
		BT_Serial_Feedback_Status = 0;
		BT_Feedback = BT_Feedback + Serial_Port_Read_Result;
		serial_receive_str_count++;
		return TRUE;
	}

	if (running_status.Find(_T("TDC_BT_TRANSMISSION")) >= 0) {
		TDC_Feedback = TDC_Feedback + Serial_Port_Read_Result;
		return TRUE;
	}
	return TRUE;
	
}

LRESULT CTDCFVT4Dlg::OnReceiveTestResult(WPARAM test_result, LPARAM test_step)
{
	if ((test_result >= 0) && (test_result <= 20)) {
		if (test_result == 0) {
			//serial.ClosePort();
			sRunningStatus_Result = _T("PASS");
			sRunningStatus_Sub = _T("All Step Test Pass.");
			test_pass++;
			LogUpdate(_T("All Step Test Pass."));
			RunningStatusUpdate();
			FPY_Update();
			FPY_cal();
			CTime Finally_Test_End_Time =TimeStamp();
			CString Finally_Test_End_Time_Text = Finally_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
			CString temp_str;
			temp_str.Format(_T("Finally End Time:%s"), Finally_Test_End_Time_Text);
			LogUpdate(temp_str);
			Log_File_Finally_Update(_T("P"), Finally_Test_End_Time_Text);
			eButtonStop.EnableWindow(1);
			GetDlgItem(IDC_STOP)->SetFocus();
		}
		else if (test_result == -1) {
			//serial.ClosePort();
			sRunningStatus_Result = _T("FAIL");
			sRunningStatus_Sub = _T("Manual Stop Test");
			test_fail++;
			LogUpdate(_T("Manual Stop Test."));
			CTime Finally_Test_End_Time = TimeStamp();
			CString Finally_Test_End_Time_Text = Finally_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
			CString temp_str;
			temp_str.Format(_T("Finally End Time:%s"), Finally_Test_End_Time_Text);
			LogUpdate(temp_str);
			Log_File_Finally_Update(_T("F"), Finally_Test_End_Time_Text);
		}
		else {
			//serial.ClosePort();
			test_fail++;
			LogUpdate(_T("Test Fail."));
			sRunningStatus_Result = _T("FAIL");
			RunningStatusUpdate();
			FPY_Update();
			FPY_cal();
			CTime Finally_Test_End_Time = TimeStamp();
			CString Finally_Test_End_Time_Text = Finally_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
			CString temp_str;
			temp_str.Format(_T("Finally End Time:%s"), Finally_Test_End_Time_Text);
			LogUpdate(temp_str);
			Log_File_Finally_Update(_T("F"), Finally_Test_End_Time_Text);
			eButtonStop.EnableWindow(1);
			GetDlgItem(IDC_STOP)->SetFocus();
		}
	}	
	processbar_value = processbar_value + test_step;
	eProgressBar.SetPos(processbar_value);


	return LRESULT();
}



void CAboutDlg::OnConfigMain()
{
	// TODO: 在此添加命令处理程序代码
}


void CTDCFVT4Dlg::OnConfigMain()
{
	// TODO: 在此添加命令处理程序代码
	CTDC_FVT4_CONFIG_MAINdlg  ConfigMainDlg;
	ConfigMainDlg.DoModal();
}


void CTDCFVT4Dlg::OnConfigEquipment()
{
	// TODO: 在此添加命令处理程序代码
	CCONFIG_EQUIPMENTdlg ConfigEquipmentDlg;
	ConfigEquipmentDlg.DoModal();
}


void CTDCFVT4Dlg::OnConfigSequence()
{
	// TODO: 在此添加命令处理程序代码
	CCONFIG_SEQUENCEdlg ConfigSequenceDlg;
	ConfigSequenceDlg.DoModal();
}


HBRUSH CTDCFVT4Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	if (pWnd->GetDlgCtrlID() == IDC_LOG)
	{
		pDC->SetTextColor(GREEN_REF);   //设置字体颜色
		pDC->SetBkMode(TRANSPARENT); //设置字体背景为透明
		//pDC->SetBkColor(YELLOW_REF);				 // TODO: Return a different brush if the default is not desired
		return (HBRUSH)::GetStockObject(BLACK_BRUSH);   // 设置背景色
	}
	if (pWnd->GetDlgCtrlID() == IDC_RUNNING_STATUS) {
		pDC->SetTextColor(BLACK_REF);   //设置字体颜色
		pDC->SetBkMode(TRANSPARENT); //设置字体背景为透明
		pDC->SetBkColor(YELLOW_REF); //设置字体背景为透明
	}

	if (pWnd->GetDlgCtrlID() == IDC_START) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH B = CreateSolidBrush(GREEN_REF);
		return (HBRUSH)B;
	}

	if (pWnd->GetDlgCtrlID() == IDC_STOP) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH B = CreateSolidBrush(RED_REF);
		return (HBRUSH)B;
	}
	CString sCurrent_Running_Status;
	GetDlgItemTextW(IDC_RUNNING_STATUS, sCurrent_Running_Status);
	if (pWnd->GetDlgCtrlID() == IDC_RUNNING_STATUS) {
		pDC->SetBkMode(TRANSPARENT);
		int u_ColorRef = RGB(255, 255, 255);
		if (sCurrent_Running_Status.Find(_T("PASS")) != -1) {
			u_ColorRef = GREEN_REF;
		}
		else if (sCurrent_Running_Status.Find(_T("FAIL")) != -1) {
			u_ColorRef = RED_REF;
		}
		else if (sCurrent_Running_Status.Find(_T("RUNNING")) != -1) {
			u_ColorRef = YELLOW_REF;
		}
		else if (sRunningStatus_Result.Find(_T("WAITING")) != -1) {
			u_ColorRef = BLUE_REF;
		}
		HBRUSH B = CreateSolidBrush(u_ColorRef);
		//Invalidate(TRUE);
		return (HBRUSH)B;		
	}

	if (pWnd->GetDlgCtrlID() == IDC_TEST_PASS_QTY) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH B = CreateSolidBrush(FPY_cal());
		return (HBRUSH)B;
	}

	if (pWnd->GetDlgCtrlID() == IDC_TEST_TOTAL_QTY) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH B = CreateSolidBrush(FPY_cal());
		return (HBRUSH)B;
	}

	if (pWnd->GetDlgCtrlID() == IDC_TEST_FAIL_QTY) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH B = CreateSolidBrush(FPY_cal());
		return (HBRUSH)B;
	}

	if (pWnd->GetDlgCtrlID() == IDC_TEST_FPY) {
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH B = CreateSolidBrush(FPY_cal());
		return (HBRUSH)B;
	}


	//else

	return hbr;
}



void CTDCFVT4Dlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialog::OnOK();
	processbar_value = 0;
	eButtonStart.EnableWindow(0);
	eEditSerialNo.EnableWindow(0);
	eButtonStop.EnableWindow(0);

	get_config.config_file_name_define();
	get_config.get_main_config(get_config.main_file_name);
	get_config.get_equipment_config(get_config.equipment_file_name);
	get_config.get_sequence_config(get_config.sequence_file_name);
	get_config.get_testbench_config(get_config.testbench_file_name);
	get_config.get_limit_config(get_config.limit_file_name);

	Test_Start_Time = TimeStamp();
	Test_Start_Time_Text = Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	eEditSerialNo.GetWindowTextW(Serial_No);
	CString First_Str = _T("Get Serial No:") + Serial_No + _T("\r\n");
	eEditLog.SetWindowTextW(First_Str);
	sRunningStatus_Result = _T("RUNNING");
	sRunningStatus_Sub = _T("Get Serial No.");
	RunningStatusUpdate();

	if (Serial_No.GetLength() == get_config.MAIN_Barcode_Length) {
		Log_File_Name_First = Serial_No + _T("-") + Test_Start_Time_Text;
		Log_Expanded_Name = _T(".log");
		Log_File_Name = Log_File_Name_First + Log_Expanded_Name;
		Log_File_Name_Full = get_config.MAIN_Trace_Path + _T("\\") + Log_File_Name;
		Log_File_Name_Full_Copy = get_config.MAIN_Trace_Path_Copy + _T("\\") + Log_File_Name;
		log_file.Open(Log_File_Name_Full, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL);
		log_file.Close();
		log_file.Open(Log_File_Name_Full_Copy, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL);
		log_file.Close();
		Log_Title();
		LogUpdate(_T("[Serial_No_Check]"));
		CString sn_str;
		sn_str.Format(_T("SerialNo. is: %s\r\nSerial No Check : Pass"), Serial_No);
		LogUpdate(sn_str);
		m_pTestSequence = AfxBeginThread((AFX_THREADPROC)TestThread, this);
		MySleep(5000);
	}
	else {
		sRunningStatus_Result = _T("FAIL");
		eEditLog.SetSel(-1, -1);
		eEditLog.ReplaceSel(_T("Wrong SN Format.\r\n"));
		eButtonStop.EnableWindow(1);
		RunningStatusUpdate();
	}
}


void CTDCFVT4Dlg::OnBnClickedStop()
{
	eEditLog.SetWindowTextW(_T(""));
	eEditSerialNo.SetWindowTextW(_T(""));
	sRunningStatus_Result = _T("WAITING");
	sRunningStatus_Sub = _T("Waiting for SN Scan...");
	RunningStatusUpdate();
	eProgressBar.SetPos(0);
	eButtonStart.EnableWindow(1);
	eEditSerialNo.EnableWindow(1);
	eButtonStop.EnableWindow(0);
	GetDlgItem(IDC_SN)->SetFocus();
}

void CTDCFVT4Dlg::RunningStatusUpdate()
{
	sRunningStatus_Title = sRunningStatus_Result + _T("\r\n") + sRunningStatus_Sub;
	SetDlgItemInt(IDC_RUNNING_STATUS, 0);
	SetDlgItemTextW(IDC_RUNNING_STATUS, sRunningStatus_Title);
}

void CTDCFVT4Dlg::FPY_Update()
{
	test_total = test_pass + test_fail;
	test_fpy = float(test_pass) / float(test_total);
	CString test_total_text, test_pass_text, test_fail_text, test_fpy_text;
	test_total_text.Format(_T("%d"), test_total);
	test_pass_text.Format(_T("%d"), test_pass);
	test_fail_text.Format(_T("%d"), test_fail);
	test_fpy_text.Format(_T("%.2f%%"), test_fpy*100);
	SetDlgItemTextW(IDC_TEST_TOTAL_QTY, test_total_text);
	SetDlgItemTextW(IDC_TEST_PASS_QTY, test_pass_text);
	SetDlgItemTextW(IDC_TEST_FAIL_QTY, test_fail_text);
	SetDlgItemTextW(IDC_TEST_FPY, test_fpy_text);
}

int CTDCFVT4Dlg::FPY_cal()
{
	int color_ref = RGB(0,0,0);
	CString fpy_text;
	GetDlgItemTextW(IDC_TEST_FPY, fpy_text);
	int find_result = fpy_text.Find(_T("NULL"));
	if (find_result != -1) {
		color_ref = WHITE_REF;
		return color_ref;
	}
	else {
		float current_fpy = _tstof(fpy_text);
		fvt4dlg_ini.SetFileName(MAIN_CONFIG);
		if (current_fpy >= get_config.FPY_Target_High_Limit) {
			color_ref = GREEN_REF;
		}
		else if (current_fpy <= get_config.FPY_Target_Low_Limit)
		{
			color_ref = RED_REF;
		}
		else {
			color_ref = YELLOW_REF;
		}
		return color_ref;
	}

}

void CTDCFVT4Dlg::LogUpdate(CString str)
{
	CString stemp;
	stemp = str + _T("\r\n");

	int sLength_Log = eEditLog.GetLimitText();
	int sLength_string = stemp.GetLength();
	eEditLog.SetLimitText((sLength_Log + sLength_string + 10));
	int nLen = eEditLog.SendMessage(WM_GETTEXTLENGTH);
	eEditLog.SetSel(nLen, nLen, FALSE);
	eEditLog.ReplaceSel(stemp);
	nLen = eEditLog.SendMessage(WM_GETTEXTLENGTH);
	eEditLog.SetSel(nLen, nLen, FALSE);

	log_file.Open(Log_File_Name_Full, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL);
	log_file.SeekToEnd();
	log_file.WriteString(stemp);
	log_file.Close();

	log_file.Open(Log_File_Name_Full_Copy, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate, NULL);
	log_file.SeekToEnd();
	log_file.WriteString(stemp);
	log_file.Close();

}

CTime CTDCFVT4Dlg::TimeStamp()
{
	CTime Currenttime = CTime::GetCurrentTime();
	//CString m_strTime = time.Format("%c%2H:%2M:%2S");
	//CString m_strTime = Currenttime.Format(_T("%Y.%m.%d %H.%M.%S"));
	return Currenttime;
}

void CTDCFVT4Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTDCFVT4Dlg::OnBnClickedOk()
{
	CDialog::OnOK();
	// TODO: 在此添加控件通知处理程序代码
}

int CTDCFVT4Dlg::Serial_Open(CString port_str, int SelBaudRate)
{
	//serial.ClosePort();
	int SelPortNO;
	port_str.Delete(0, 3);
	SelPortNO = _tstoi(port_str);
	if (serial.InitPort(this->GetSafeHwnd(), SelPortNO, SelBaudRate))
	{
		serial.StartMonitoring();
		return 0;
	}
	else
	{
		AfxMessageBox(_T("串口已被占用！"));
		return 1;
	}
}

bool CTDCFVT4Dlg::Serial_Open_Without_Monitor(CString port_str, int SelBaudRate)
{
	int SelPortNO;
	port_str.Delete(0, 3);
	SelPortNO = _tstoi(port_str);
	if (serial.InitPort(this->GetSafeHwnd(), SelPortNO, SelBaudRate))
	{
		//serial.StartMonitoring();
		return TRUE;
	}
	else
	{
		AfxMessageBox(_T("串口已被占用！"));
		return FALSE;
	}
}

float CTDCFVT4Dlg::TDC_Get_Distance()
{
	CString running_status, distance_value_str, temp_str;
	Serial_Port_Read_Result = _T("");
	float TDC_Value;
	TDC_Feedback = _T("");
	GetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	SetDlgItemTextW(IDC_RUNNING_STATUS, _T("RUNNING\r\nTDC_BT_TRANSMISSION"));
	int Open_Result = Serial_Open(get_config.BlueTooth_Serial_Port, get_config.BlueTooth_Baud_Rate);
	if (Open_Result !=0 ) {
		LogUpdate(_T("Cannot Open BlueTooth Dongle By Serial RS232."));
	}
	char* command;
	USES_CONVERSION;
	command = T2A(get_config.Limit_Transmission_Command_Get_Distance_Value.GetBuffer(0));
	get_config.Limit_Transmission_Command_Get_Distance_Value.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_Transmission_Command_Get_Distance_Value.GetLength());
	MySleep(1000);
	if (TDC_Feedback.Find(_T("D") >= 0)) {
		TDC_Feedback.Delete(0, 1);
		TDC_Value = _tstof(TDC_Feedback);
	}
	else {
		TDC_Value = 1000;
	}
	SetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	temp_str.Format(_T("Get TDC Distance Value: %.3f"), TDC_Value);
	LogUpdate(temp_str);
	return TDC_Value;
}

float CTDCFVT4Dlg::TDC_Get_Pressure()
{
	CString running_status, distance_value_str, temp_str;
	float TDC_Value;
	TDC_Feedback = _T("");
	GetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	SetDlgItemTextW(IDC_RUNNING_STATUS, _T("RUNNING\r\nTDC_BT_TRANSMISSION"));
	int Open_Result = Serial_Open(get_config.BlueTooth_Serial_Port, get_config.BlueTooth_Baud_Rate);
	if (Open_Result != 0) {
		LogUpdate(_T("Cannot Open BlueTooth Dongle By Serial RS232."));
		return 1000;
	}
	char* command;
	USES_CONVERSION;
	command = T2A(get_config.Limit_Transmission_Command_Get_Pressure_Value.GetBuffer(0));
	get_config.Limit_Transmission_Command_Get_Pressure_Value.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_Transmission_Command_Get_Distance_Value.GetLength());
	MySleep(2000);
	if (TDC_Feedback == _T("")) {
		LogUpdate(_T("Cannot get feedback from bluetooth."));
		TDC_Value = 1000;
		return TDC_Value;
	}
	if (TDC_Feedback.Find(_T("U") >= 0)) {
		TDC_Feedback.Delete(0, 1);
		TDC_Feedback.GetBufferSetLength(TDC_Feedback.GetLength() - 1);
		TDC_Value = _tstof(TDC_Feedback);
	}
	else {
		TDC_Value = 1000;
	}
	SetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	temp_str.Format(_T("Get TDC Pressure Value: %.2f"), TDC_Value);
	LogUpdate(temp_str);
	return TDC_Value;
}

CString CTDCFVT4Dlg::TDC_Get_RFID()
{
	CString running_status, temp_str, TDC_Value_Str;
//	float TDC_Value;
	TDC_Feedback = _T("");
	GetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	SetDlgItemTextW(IDC_RUNNING_STATUS, _T("RUNNING\r\nTDC_BT_TRANSMISSION"));
	int Open_Result = Serial_Open(get_config.BlueTooth_Serial_Port, get_config.BlueTooth_Baud_Rate);
	if (Open_Result != 0) {
		LogUpdate(_T("Cannot Open BlueTooth Dongle By Serial RS232."));
	}
	char* command;
	USES_CONVERSION;
	command = T2A(get_config.Limit_Transmission_Command_Get_RFID.GetBuffer(0));
	get_config.Limit_Transmission_Command_Get_RFID.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_Transmission_Command_Get_Distance_Value.GetLength());
	MySleep(10000);
	if (TDC_Feedback.Find(_T("0000")) >= 0) {
		TDC_Feedback.Delete(0, 1);
		TDC_Value_Str = TDC_Feedback;
	}
	else {
		TDC_Value_Str = _T("Error");
	}
	SetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	temp_str.Format(_T("Get TDC RF_ID: %s"), TDC_Value_Str);
	LogUpdate(temp_str);
	return TDC_Value_Str;
}

bool CTDCFVT4Dlg::TDC_Reset()
{
	CString running_status, temp_str, TDC_Value_Str;
//	float TDC_Value;
	bool feedback;
	TDC_Feedback = _T("");
	GetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	SetDlgItemTextW(IDC_RUNNING_STATUS, _T("RUNNIN\r\nTDC_BT_TRANSMISSION"));
	int Open_Result = Serial_Open(get_config.BlueTooth_Serial_Port, get_config.BlueTooth_Baud_Rate);
	if (Open_Result != 0) {
		LogUpdate(_T("Cannot Open BlueTooth Dongle By Serial RS232."));
	}
	char* command;
	USES_CONVERSION;
	command = T2A(get_config.Limit_Transmission_Command_Reset.GetBuffer(0));
	get_config.Limit_Transmission_Command_Reset.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_Transmission_Command_Reset.GetLength());
	MySleep(1000);
	if (TDC_Feedback.Find(_T("OK") >= 0)) {
		feedback = TRUE;
		TDC_Value_Str = _T("PASS");
	}
	else {
		feedback = FALSE;
		TDC_Value_Str = _T("FAIL");
	}
	SetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	temp_str.Format(_T("TDC Reset Result: %s"), TDC_Value_Str);
	LogUpdate(temp_str);
	return feedback;
}

bool CTDCFVT4Dlg::TDC_Zero_Position()
{
	CString running_status, temp_str, TDC_Value_Str;
	//	float TDC_Value;
	bool feedback;
	TDC_Feedback = _T("");
	GetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	SetDlgItemTextW(IDC_RUNNING_STATUS, _T("RUNNING\r\nTDC_BT_TRANSMISSION"));
	int Open_Result = Serial_Open(get_config.BlueTooth_Serial_Port, get_config.BlueTooth_Baud_Rate);
	if (Open_Result != 0) {
		LogUpdate(_T("Cannot Open BlueTooth Dongle By Serial RS232."));
	}
	char* command;
	USES_CONVERSION;
	CString command_zero_position = _T("TESTZ");
	command = T2A(command_zero_position.GetBuffer(0));
	command_zero_position.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_Transmission_Command_Reset.GetLength());
	MySleep(1000);
	if (TDC_Feedback.Find(_T("OK") >= 0)) {
		feedback = TRUE;
		TDC_Value_Str = _T("PASS");
	}
	else {
		feedback = FALSE;
		TDC_Value_Str = _T("FAIL");
	}
	SetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	temp_str.Format(_T("TDC Set Distance Zero Position:%s"), TDC_Value_Str);
	LogUpdate(temp_str);
	return feedback;
}


bool CTDCFVT4Dlg::TDC_15_Position()
{
	CString running_status, temp_str, TDC_Value_Str;
	//	float TDC_Value;
	bool feedback;
	TDC_Feedback = _T("");
	GetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	SetDlgItemTextW(IDC_RUNNING_STATUS, _T("RUNNING\r\nTDC_BT_TRANSMISSION"));
	int Open_Result = Serial_Open(get_config.BlueTooth_Serial_Port, get_config.BlueTooth_Baud_Rate);
	if (Open_Result != 0) {
		LogUpdate(_T("Cannot Open BlueTooth Dongle By Serial RS232."));
	}
	char* command;
	USES_CONVERSION;
	CString command_zero_position = _T("TESTY");
	command = T2A(command_zero_position.GetBuffer(0));
	command_zero_position.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_Transmission_Command_Reset.GetLength());
	MySleep(1000);
	if (TDC_Feedback.Find(_T("OK") >= 0)) {
		feedback = TRUE;
		TDC_Value_Str = _T("PASS");
	}
	else {
		feedback = FALSE;
		TDC_Value_Str = _T("FAIL");
	}
	SetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	temp_str.Format(_T("TDC Set Distance 15 Position:%s"), TDC_Value_Str);
	LogUpdate(temp_str);
	return feedback;
}

bool CTDCFVT4Dlg::TDC_30_Position()
{
	CString running_status, temp_str, TDC_Value_Str;
	//	float TDC_Value;
	bool feedback;
	TDC_Feedback = _T("");
	GetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	SetDlgItemTextW(IDC_RUNNING_STATUS, _T("RUNNING\r\nTDC_BT_TRANSMISSION"));
	int Open_Result = Serial_Open(get_config.BlueTooth_Serial_Port, get_config.BlueTooth_Baud_Rate);
	if (Open_Result != 0) {
		LogUpdate(_T("Cannot Open BlueTooth Dongle By Serial RS232."));
	}
	char* command;
	USES_CONVERSION;
	CString command_zero_position = _T("TESTX");
	command = T2A(command_zero_position.GetBuffer(0));
	command_zero_position.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_Transmission_Command_Reset.GetLength());
	MySleep(1000);
	if (TDC_Feedback.Find(_T("OK") >= 0)) {
		feedback = TRUE;
		TDC_Value_Str = _T("PASS");
	}
	else {
		feedback = FALSE;
		TDC_Value_Str = _T("FAIL");
	}
	SetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	temp_str.Format(_T("TDC Set Distance 30 Position:%s"), TDC_Value_Str);
	LogUpdate(temp_str);
	return feedback;
}

bool CTDCFVT4Dlg::TDC_Position(int Position)
{
	CString running_status, temp_str, TDC_Value_Str;
	//	float TDC_Value;
	bool feedback;
	TDC_Feedback = _T("");
	GetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	SetDlgItemTextW(IDC_RUNNING_STATUS, _T("RUNNING\r\nTDC_BT_TRANSMISSION"));
	int Open_Result = Serial_Open(get_config.BlueTooth_Serial_Port, get_config.BlueTooth_Baud_Rate);
	if (Open_Result != 0) {
		LogUpdate(_T("Cannot Open BlueTooth Dongle By Serial RS232."));
	}
	char* command;
	USES_CONVERSION;
	CString command_zero_position;
	command_zero_position.Format(_T("TEST%i"), Position);
	command = T2A(command_zero_position.GetBuffer(0));
	command_zero_position.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_Transmission_Command_Reset.GetLength());
	MySleep(1000);
	if (TDC_Feedback.Find(_T("OK") >= 0)) {
		feedback = TRUE;
		TDC_Value_Str = _T("PASS");
	}
	else {
		feedback = FALSE;
		TDC_Value_Str = _T("FAIL");
	}
	SetDlgItemTextW(IDC_RUNNING_STATUS, running_status);
	temp_str.Format(_T("TDC Set Distance %i Position Result:%s"), Position, TDC_Value_Str);
	LogUpdate(temp_str);
	return feedback;
}

int CTDCFVT4Dlg::Serial_Measurement(char command[])
{
    serial.WriteToPort(command, 6);
	//MySleep(10);
	while (Serial_Port_Read_Result.GetLength() < 7) {
		MySleep(40);
		LogUpdate(_T("Sleep Time:40ms"));
	}
	Serial_Port_Read_Result.Delete(0, 1);
	Serial_Port_Read_Result = Serial_Port_Read_Result.GetBufferSetLength(Serial_Port_Read_Result.GetLength() - 2);
	serial_port_value_float = float(_tstof(Serial_Port_Read_Result));
	CString temp_text;
	temp_text.Format(_T("Get Double Float Value From Serial Port: %.3f."), serial_port_value_float);
	LogUpdate(temp_text);
    return 0;
}

////////////////////
//名称:专用延时函数
//说明:没有刷新功能
//参数:系统固定延时值的倍数 默认为1倍
//返回值:
//其它:不独占方式
////////////////////
void CTDCFVT4Dlg::SleepEx(int value)
{
	LARGE_INTEGER litmp;
	LONGLONG QPart1, QPart2;
	double dfMinus, dfFreq, dfTim;
	QueryPerformanceFrequency(&litmp);
	dfFreq = (double)litmp.QuadPart; // 获得计数器的时钟频率
	QueryPerformanceCounter(&litmp);
	QPart1 = litmp.QuadPart;
	do {
		//增加消息处理 删除则在此期间不响应任何消息
		MSG msg;
		GetMessage(&msg, NULL, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		QueryPerformanceCounter(&litmp);
		QPart2 = litmp.QuadPart;
		dfMinus = (double)(QPart2 - QPart1);
		dfTim = dfMinus / dfFreq;
	} while (dfTim<0.001 * 1000 / value);
}

UINT CTDCFVT4Dlg::TestThread(LPVOID pParam)
{
	CTDCFVT4Dlg *pDlg = (CTDCFVT4Dlg *)pParam;
	int test_result = 0;
	CString str;
	if (get_config.SEQUENCE_Test_Environment_Check == TRUE) {
		
		pDlg->sRunningStatus_Sub = _T("Test_Environment_Check");
		pDlg->RunningStatusUpdate();
		str = seq.Test_Environment_Check();
		//pDlg->LogUpdate(_T(""));
		pDlg->LogUpdate(str);
		int temp = str.Find(_T("FAIL"));
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 5);
		if (str.Find(_T("FAIL")) == -1) {
			pDlg->LogUpdate(_T("Test_Environment_Check Pass."));
		}
		else {
			pDlg->LogUpdate(_T("Test_Environment_Check Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 1, 0);
			pDlg->Close_Test();
			return 1;
		}
		//pDlg->LogUpdate(_T("Initialize Distance Calibration Result."));
		//for (int i = 0; i < sizeof(Distance_Calibration_Result); i++) {
		//	pDlg->Distance_Calibration_Result[i] = 0x00;
		//}
		//pDlg->LogUpdate(_T("Initialize Pressure Calibration Result."));
		//for (int i = 0; i < sizeof(Pressure_Calibration_Result); i++) {
		//	pDlg->Pressure_Calibration_Result[i] = 0x00;
		//}
	}

	if (get_config.SEQUENCE_Equipment_Check == TRUE) {
		pDlg->LogUpdate(_T(""));
		pDlg->sRunningStatus_Sub = _T("[Equipment_Check]");
		pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
		pDlg->RunningStatusUpdate();
		CTime Sub_Test_Start_Time = pDlg->TimeStamp();
		CString Sub_Test_Start_Time_Text = Sub_Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
		CString temp_str = _T("Start Time:") + Sub_Test_Start_Time_Text;
		pDlg->LogUpdate(temp_str);
	
		//if (test_result == 0) {
		//	pDlg->LogUpdate(_T("Equipment Check Passed."));
		//}
		//else {
		//	pDlg->LogUpdate(_T("Equipment Check Failed."));
		//	::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 2, 0);
		//	pDlg->Close_Test();
		//	return 2;
		//}
		pDlg->LogUpdate(_T("Check TestBench..."));
		if (testbench.Get_DevHandle() > 0) {
			pDlg->LogUpdate(testbench.testbench_info);
		}
		else {
			pDlg->LogUpdate(_T("Test Bench Check Wrong!"));
			test_result = 1;
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 2, 0);
			pDlg->Close_Test();
			return 2;
		}

		//if (testbench.PWM_InitT(get_config.TestBench_PWM_PWM1 + get_config.TestBench_PWM_PWM2)) {
		//	pDlg->LogUpdate(_T("TestBench PWM Initializtion Pass."));
		//}
		//else {
		//	pDlg->LogUpdate(_T("TestBench PWM Initializtion Fail."));
		//	::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 2, 0);
		//	pDlg->Close_Test();
		//	return 2;
		//}
		//Temp Skip by William Yang
	
		if (testbench.IO_Init(get_config.TestBench_GPIO_GPIO_I2C_0)) {
			pDlg->LogUpdate(_T("TestBench GPIO_I2C_0 Initializtion Pass."));
		}
		else {
			pDlg->LogUpdate(_T("TestBench GPIO_I2C_0 Initializtion Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 2, 0);
			pDlg->Close_Test();
			return 2;
		}
		if (testbench.IO_Init(get_config.TestBench_GPIO_GPIO_I2C_1)) {
			pDlg->LogUpdate(_T("TestBench GPIO_I2C_1 Initializtion Pass."));
		}
		else {
			pDlg->LogUpdate(_T("TestBench GPIO_I2C_1 Initializtion Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 2, 0);
			pDlg->Close_Test();
			return 2;
		}

		if (testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO0)) {
			pDlg->LogUpdate(_T("TestBench Internal IO0 Initializtion Pass."));
		}
		else {
			pDlg->LogUpdate(_T("TestBench Internal IO0 Initializtion Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 2, 0);
			pDlg->Close_Test();
			return 2;
		}
		if (testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1)) {
			pDlg->LogUpdate(_T("TestBench Internal IO1 Initializtion Pass."));
		}
		else {
			pDlg->LogUpdate(_T("TestBench Internal IO1 Initializtion Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 2, 0);
			pDlg->Close_Test();
			return 2;
		}
		if (testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO2)) {
			pDlg->LogUpdate(_T("TestBench Internal IO2 Initializtion Pass."));
		}
		else {
			pDlg->LogUpdate(_T("TestBench Internal IO2 Initializtion Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 2, 0);
			pDlg->Close_Test();
			return 2;
		}
		if (testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO3)) {
			pDlg->LogUpdate(_T("TestBench Internal IO3 Initializtion Pass."));
		}
		else {
			pDlg->LogUpdate(_T("TestBench Internal IO3 Initializtion Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 2, 0);
			pDlg->Close_Test();
			return 2;
		}	
		

		if (get_config.SEQUENCE_FW_Flash == TRUE) {
			if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
				AfxMessageBox(_T("Please manual Push The Power On Key Till Another Remind Window Pop Up.\r\n 请手工按住开机键直到弹出另一个提示窗口"));
			}
			testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO0);
			testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO1);
			CString status;
			pDlg->LogUpdate(_T("Check ST-Link V2..."));
			//::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 5);
			if (stlink.Get_Chip_Info()) {
				status = stlink.Read_exe_Result(_T("Device ID"), 0, 15);
				if (status.Find(_T("0x410")) > -1) {
					pDlg->LogUpdate(status);
					status = stlink.Read_exe_Result(_T("Device family"), 0, 40);
					if (status.Find(_T("STM32F10xx")) > -1) {
						pDlg->LogUpdate(status);
						test_result = 0;
					}
					else {
						pDlg->LogUpdate(_T("Equipment Check Error: Cannot found Device family name."));
						test_result = 1;
						::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 2, 0);
						//pDlg->Close_Test();
						return 2;
					}
				}
				else {
					pDlg->LogUpdate(_T("Equipment Check Error: Cannot found Device Device ID."));
					test_result = 1;
					::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 2, 0);
					//pDlg->Close_Test();
					return 2;
				}
			}
			else {
				pDlg->LogUpdate(_T("Cannot Connect to TDC."));
				test_result = 1;
				//pDlg->Close_Test();
				::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 2, 0);
				return 2;
			}
			testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO0);
			testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1);
			if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
				AfxMessageBox(_T("Please Release The Power On Key.\r\n 请释放开机键!"));
			}
		}



		float inflator_temperature = testbench.DS18B20(get_config.TestBench_INTERNET_DS18B20);
		if (inflator_temperature > 70) {
			inflator_temperature = 30.002;
		}
		//CString temp_str;
		temp_str.Format(_T("Get Temperature From Inflator was:%.3f."), inflator_temperature);
		pDlg->LogUpdate(temp_str);
		//Temp Skip by William
		if ((inflator_temperature > get_config.Limit_Equipment_Check_Inflator_High_Temperature)) {
			pDlg->LogUpdate(_T("Test_Environment Inflator Temperature Failed And Higher than USL."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 1, 0);
			pDlg->Close_Test();
			return 1;
		}
		if ((inflator_temperature < get_config.Limit_Equipment_Check_Inflator_Low_Temperature)) {
			pDlg->LogUpdate(_T("Test_Environment Inflator Temperature Failed And Lower than LSL."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 1, 0);
			pDlg->Close_Test();
			return 1;
		}
		else if ((inflator_temperature < -60)) {
			pDlg->LogUpdate(_T("Test_Environment Inflator Running Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 1, 0);
			pDlg->Close_Test();
			return 1;
		}
		//Equipment Check with Bluetooth Dongle.



		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 5);
		pDlg->LogUpdate(_T("All Equipment Check Pass!"));
		CTime Sub_Test_End_Time = pDlg->TimeStamp();
		CString Sub_Test_End_Time_Text = Sub_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
		temp_str.Format(_T("End Time:%s"), Sub_Test_End_Time_Text);
		pDlg->LogUpdate(temp_str);
		temp_str.Format(_T("Duration: %d"), Sub_Test_End_Time - Sub_Test_Start_Time);
		pDlg->LogUpdate(temp_str);
		//stlink.Get_Chip_Info();
	}

	if (get_config.SEQUENCE_Charging_Check == TRUE) {
		pDlg->sRunningStatus_Sub = _T("[Charging_Check]");
		pDlg->RunningStatusUpdate();
		pDlg->LogUpdate(_T(""));
		pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
		int test_result = pDlg->Charging_Check();
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 5);
		if (test_result == 0) {
			pDlg->LogUpdate(_T("Charging_Check Pass."));
		}
		else {
			pDlg->LogUpdate(_T("Charging_Check Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 7, 0);
			pDlg->Close_Test();
			return 7;
		}
	}

	if (get_config.SEQUENCE_FW_Flash == TRUE) {
		pDlg->sRunningStatus_Sub = _T("[FW_Flash]");
		pDlg->RunningStatusUpdate();
		pDlg->LogUpdate(_T(""));
		pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
		int test_result = pDlg->FW_Flash();
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 5);
		if (test_result == 0) {
			pDlg->LogUpdate(_T("FW_Flash Pass."));
		}
		else {
			pDlg->LogUpdate(_T("FW_Flash Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 3, 0);
			pDlg->Close_Test();
			return 3;
		}
	}


	AfxMessageBox(_T("Please Put TDC on RFID Test Fixture. \r\n 请将TDC产品放置在RFID测试架上！"));

	if (get_config.SEQUENCE_BlueTooth_Check == TRUE) {
		pDlg->sRunningStatus_Sub = _T("[BlueTooth_Check]");
		pDlg->RunningStatusUpdate();
		pDlg->LogUpdate(_T(""));
		pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
		int test_result = pDlg->BlueTooth_Check();
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 5);
		if (test_result == 0) {
			pDlg->LogUpdate(_T("BlueTooth_Check Pass."));
		}
		else {
			pDlg->LogUpdate(_T("BlueTooth_Check Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 4, 0);
			pDlg->Close_Test();
			return 4;
		}
	}

	if (get_config.SEQUENCE_RFID_Check == TRUE) {
		pDlg->sRunningStatus_Sub = _T("[RFID_Check]");
		pDlg->RunningStatusUpdate();
		pDlg->LogUpdate(_T(""));
		pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 5);
		int test_result = pDlg->RFID_Check();
		if (test_result == 0) {
			pDlg->LogUpdate(_T("RFID_Check Pass."));
		}
		else {
			pDlg->LogUpdate(_T("RFID_Check Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 5, 0);
			pDlg->Close_Test();
			return 5;
		}
	}

	AfxMessageBox(_T("Please Put TDC on Distance / Pressure Calibration Test Fixture. \r\n 请将TDC产品放置在距离/气压检验测试架上！"));
	/*
	if (get_config.SEQUENCE_Button_Check == TRUE) {
		pDlg->sRunningStatus_Sub = _T("[Button_Check]");
		pDlg->RunningStatusUpdate();
		pDlg->LogUpdate(_T(""));
		pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
		int test_result = pDlg->Button_Check();
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 5);
		if (test_result == 0) {
			pDlg->LogUpdate(_T("Button_Check Pass."));
		}
		else {
			pDlg->LogUpdate(_T("Button_Check Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 6, 0);
			pDlg->Close_Test();
			return 6;
		}
	}
	*/


	/*
	if (get_config.SEQUENCE_LCD_Check == TRUE) {
		pDlg->sRunningStatus_Sub = _T("[LCD_Check]");
		pDlg->RunningStatusUpdate();
		pDlg->LogUpdate(_T(""));
		pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
		int test_result = pDlg->LCD_Check();
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 5);
		if (test_result == 0) {
			pDlg->LogUpdate(_T("LCD_Check Pass."));
		}
		else {
			pDlg->LogUpdate(_T("LCD_Check Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 8, 0);
			pDlg->Close_Test();
			return 8;
		}
	}
	*/

    /*
	if (get_config.SEQUENCE_Buzz_Check == TRUE) {
		pDlg->sRunningStatus_Sub = _T("[Buzz_Check]");
		pDlg->RunningStatusUpdate();
		pDlg->LogUpdate(_T(""));
		pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
		int test_result = pDlg->Buzz_Check();
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 5);
		if (test_result == 0) {
			pDlg->LogUpdate(_T("Buzz_Check Pass."));
		}
		else {
			pDlg->LogUpdate(_T("Buzz_Check Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 9, 0);
			pDlg->Close_Test();
			return 9;
		}
	}
	*/


	if (get_config.SEQUENCE_Pressure_Calibration == TRUE) {
		pDlg->sRunningStatus_Sub = _T("[Pressure_Calibration]");
		pDlg->RunningStatusUpdate();
		pDlg->LogUpdate(_T(""));
		pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
		int test_result = pDlg->Pressure_Calibration();
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 10);
		if (test_result == 0) {
			pDlg->LogUpdate(_T("Pressure_Calibration Pass."));
		}
		else {
			pDlg->LogUpdate(_T("Pressure_Calibration Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 12, 0);
			pDlg->Close_Test();
			return 12;
		}
	}




	if (get_config.SEQUENCE_Pressure_Measurement == TRUE) {
		pDlg->sRunningStatus_Sub = _T("[Pressure_Measurement]");
		pDlg->RunningStatusUpdate();
		pDlg->LogUpdate(_T(""));
		pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
		int test_result = pDlg->Pressure_Measurement();
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 10);
		if (test_result == 0) {
			pDlg->LogUpdate(_T("Pressure_Measurement Pass."));
		}
		else {
			pDlg->LogUpdate(_T("Pressure_Measurement Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 4, 0);
			pDlg->Close_Test();
			return 4;
		}
	}


	if (get_config.SEQUENCE_Distance_Calibration == TRUE) {
		pDlg->sRunningStatus_Sub = _T("[Distance_Calibration]");
		pDlg->RunningStatusUpdate();
		pDlg->LogUpdate(_T(""));
		pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
		int test_result = pDlg->Distance_Calibration();
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 25);
		if (test_result == 0) {
			pDlg->LogUpdate(_T("Distance_Calibration Pass."));
		}
		else {
			pDlg->LogUpdate(_T("Distance_Calibration Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 10, 0);
			pDlg->Close_Test();
			return 10;
		}
	}


	//Write Calibration Result;
	if (get_config.Limit_Distance_Calibration_BT_Upload == 0) {
		if (get_config.SEQUENCE_Distance_Calibration == TRUE) {
			pDlg->sRunningStatus_Sub = _T("[Write_Calibration_Result]");
			pDlg->RunningStatusUpdate();
			pDlg->LogUpdate(_T(""));
			pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
			test_result = pDlg->Write_Calibration_Result();
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 10);
			if (test_result == 0) {
				pDlg->LogUpdate(_T("Write_Calibration_Result Pass."));
			}
			else {
				pDlg->LogUpdate(_T("Write_Calibration_Result Fail."));
				::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 11, 0);
				pDlg->Close_Test();
				return 11;
			}
		}


		if (get_config.SEQUENCE_Distance_Calibration == TRUE) {
			pDlg->sRunningStatus_Sub = _T("[BlueTooth_Check]");
			pDlg->RunningStatusUpdate();
			pDlg->LogUpdate(_T(""));
			pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
			int test_result = pDlg->BlueTooth_Connect();
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 5);
			if (test_result == 0) {
				pDlg->LogUpdate(_T("BlueTooth_Check Pass."));
			}
			else {
				pDlg->LogUpdate(_T("BlueTooth_Check Fail."));
				::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 4, 0);
				pDlg->Close_Test();
				return 4;
			}
		}
	}

	if (get_config.SEQUENCE_Distance_Measurement == TRUE) {
		pDlg->sRunningStatus_Sub = _T("[Distance_Measurement]");
		pDlg->RunningStatusUpdate();
		pDlg->LogUpdate(_T(""));
		pDlg->LogUpdate(pDlg->sRunningStatus_Sub);
		int test_result = pDlg->Distance_Measurement();
		::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 200, 15);
		if (test_result == 0) {
			pDlg->LogUpdate(_T("Distance_Measurement Pass."));
		}
		else {
			pDlg->LogUpdate(_T("Distance_Measurement Fail."));
			::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 11, 0);
			pDlg->Close_Test();
			return 11;
		}
	}
	CTime Test_End_Time = pDlg->TimeStamp();
	CString Test_End_Time_Text = Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	CString temp_str;
	temp_str.Format(_T("End Time:%s"), Test_End_Time_Text);
	pDlg->LogUpdate(temp_str);
	temp_str.Format(_T("Duration: %d"), Test_End_Time - pDlg->Test_Start_Time);
	pDlg->LogUpdate(temp_str);

	::PostMessage(pDlg->m_hWnd, WM_UPDATE_TESTRESULT, 0, 0);
	pDlg->Close_Test();
	return 0;
}

int CTDCFVT4Dlg::Test_Environment_Check()
{
	return 0;
}

int CTDCFVT4Dlg::Equipment_Check()
{
	return 0;
}

int CTDCFVT4Dlg::FW_Flash()
{
	CString temp_str;
	CTime Sub_Test_Start_Time = TimeStamp();
	CString Sub_Test_Start_Time_Text = Sub_Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	temp_str.Format(_T("Start Time:%s"), Sub_Test_Start_Time_Text);
	LogUpdate(temp_str);
	if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
		AfxMessageBox(_T("Please manual Push The Power On Key Till Another Remind Window Pop Up.\r\n 请手工按住开机键直到弹出另一个提示窗口"));
	}
	CString flash_result_str;
	testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO0);
	testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO1);

	MySleep(3000);

	BOOL flash_result_int = stlink.Flash(get_config.Limit_FW_Flash_Test_FW, get_config.Limit_FW_Flash_Wire_Begin_Address, TRUE);
	if (flash_result_int) {  
		LogUpdate(_T("Flash Command Running Successed."));
	}
	else {
		LogUpdate(_T("Flash Command Running Failed."));
	}
	flash_result_str = stlink.Read_exe_Result(_T("Verification"),15,2);
	stlink.Reset();
	//stlink.Run();
	BOOL flash_result = stlink.Run();
	if (flash_result_int) {
		LogUpdate(_T("Reset / Run Running Successed."));
	}
	else {
		LogUpdate(_T("Reset / Run Running Failed."));
	}
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO0);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1);
	if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
		AfxMessageBox(_T("Please Release The Power On Key.\r\n 请释放开机键!"));
	}
	CTime Sub_Test_End_Time = TimeStamp();
	CString Sub_Test_End_Time_Text = Sub_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	temp_str.Format(_T("End Time:%s"), Sub_Test_End_Time_Text);
	LogUpdate(temp_str);
	temp_str.Format(_T("Duration: %d"), Sub_Test_End_Time - Sub_Test_Start_Time);
	LogUpdate(temp_str);
	if (flash_result_str == _T("OK")) {
		return 0;
	}
	else {
		return 1;
	}

}

int CTDCFVT4Dlg::BlueTooth_Check()
{
	if (get_config.Limit_BlueTooth_Manual_Reset == 1) {
		AfxMessageBox(_T("Pleaes PowerOn / Poweroff TDC! \r\n 请将TDC产品重新启动：关机-开机！"));
	}
	CString time_temp_str;
	CTime Sub_Test_Start_Time = TimeStamp();
	CString Sub_Test_Start_Time_Text = Sub_Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("Start Time:%s"), Sub_Test_Start_Time_Text);
	LogUpdate(time_temp_str);
	if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
		AfxMessageBox(_T("Please manual Push The Power On Key Till Another Remind Window Pop Up.\r\n 请手工按住开机键直到弹出另一个提示窗口"));
	}
	testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO1);
	MySleep(3000);
	stlink.Read_8(get_config.Limit_BlueTooth_Slave_BT_Address, get_config.Limit_BlueTooth_Slave_BT_Addrress_Length);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1);
	if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
		AfxMessageBox(_T("Please Release The Power On Key.\r\n 请释放开机键!"));
	}
	
	CString temp_str1, temp_str2,temp_str3,temp_str4;
	temp_str1.Format(_T("%08X"), get_config.Limit_BlueTooth_Slave_BT_Address);
	temp_str2.Format(_T("%08X"), get_config.Limit_BlueTooth_Slave_BT_Address + 0x10);
	CString bt_address_str = _T("");
	bt_address_str = stlink.Get_BT_Address(temp_str1,temp_str2);
	temp_str3.Format(_T("Get Slave (TDC) BT Address: %s"), bt_address_str);
	LogUpdate(temp_str3);
	if (bt_address_str.Find(_T("Error")) >= 0) {
		LogUpdate(_T("Cannot Get Correct BT Address."));
		return 1;
	}
	if (bt_address_str == _T("000000000000")) {
		LogUpdate(_T("Cannot Get Correct BT Address."));
		return 1;
	}

	if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
		AfxMessageBox(_T("Please manual Push The Power On Key Till TDC Power On.\r\n 请手工按住开机键直到产品开机！"));
	}

	testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO1);
	MySleep(3000);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1);


	Slave_BT = bt_address_str;
	Serial_Open(get_config.BlueTooth_Serial_Port, get_config.BlueTooth_Baud_Rate);
	USES_CONVERSION;
	CString temp_str,BT_str,Log_temp;
	char* command;

	//Disconnct Slave BT (TDC)
	
	BT_Feedback = _T("");
	command = T2A(get_config.Limit_BlueTooth_Command_Disconnect.GetBuffer(0));
	get_config.Limit_BlueTooth_Command_Reset.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_BlueTooth_Command_Disconnect.GetLength());
	MySleep(2000);
	if (BT_Feedback.Find(_T("LOST")) < 0) {
		LogUpdate(_T("No Found Any Connection."));
		//return 1;
	}
	else {
		LogUpdate(_T("Disconnect Slave BT Successed."));
	}
	

	//Check BT Dongle Version.
	BT_Feedback = _T("");
	command = T2A(get_config.Limit_BlueTooth_Command_Get_Master_Vers.GetBuffer(0));
	get_config.Limit_BlueTooth_Command_Get_Master_Vers.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_BlueTooth_Command_Get_Master_Vers.GetLength());
	MySleep(5000);
	LogUpdate(BT_Feedback);
	if (BT_Feedback.Find(get_config.Limit_BlueTooth_Master_BT_Vers) < 0) {
		LogUpdate(_T("Cannot Get Master BT Dongle Vers."));
		return 1;
	}
	Log_temp = _T("Get Master BT Dongle Vers:") + BT_Feedback;
	LogUpdate(Log_temp);

	//Reset BT Dongle
	BT_Feedback = _T("");
	command = T2A(get_config.Limit_BlueTooth_Command_Reset.GetBuffer(0));
	get_config.Limit_BlueTooth_Command_Reset.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_BlueTooth_Command_Reset.GetLength());
	MySleep(2000);
	LogUpdate(BT_Feedback);
	if (BT_Feedback.Find(_T("RESET")) < 0) {
		LogUpdate(_T("Cannot Reset BT Dongle."));
		return 1;
	}
	Log_temp = _T("Reset BT Dongle Successed");
	LogUpdate(Log_temp);

	//Connect TDC BT
	BT_Feedback = _T("");
	temp_str = get_config.Limit_BlueTooth_Command_Connect + Slave_BT;
	command = T2A(temp_str.GetBuffer(0));
	temp_str.ReleaseBuffer();
	//if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
	//AfxMessageBox(_T("Please manual Push The Power On Key Till Another Remind Window Pop Up.\r\n 请手工按住开机键直到弹出另一个提示窗口"));
	//}
	testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO1);
	MySleep(2000);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1);
	//if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
	//AfxMessageBox(_T("Please Release The Power On Key.\r\n 请释放开机键!"));
	//}
	serial.WriteToPort(command, temp_str.GetLength());
	MySleep(5000);
	LogUpdate(BT_Feedback);
	if (BT_Feedback.Find(Slave_BT) < 0) {
		LogUpdate(_T("Cannot Connect Slave (TDC)."));
		return 1;
	}
	Log_temp = _T("Connect Slave BT (TDC) Suceesed:\r\n") + BT_Feedback;
	LogUpdate(Log_temp);

	//Get RSSI
	BT_Feedback = _T("");
	serial_receive_str_count = 0;
	command = T2A(get_config.Limit_BlueTooth_Command_Read_RSSI.GetBuffer(0));
	get_config.Limit_BlueTooth_Command_Read_RSSI.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_BlueTooth_Command_Read_RSSI.GetLength());
	MySleep(10000);
	serial.WriteToPort(command, get_config.Limit_BlueTooth_Command_Read_RSSI.GetLength());
	MySleep(2000);
	int RSSI_Value = 0;
	int RSSI_Value_Total = 0;
	int RSSI_Count = 0;

	RSSI_Count = BT_Feedback.Replace(_T("RSSI(dB):"), _T("RSSI(dB):"));
	if (RSSI_Count <= 0) {
		LogUpdate(_T("Read RSSI Value Failed."));
		return 1;
	}
	while (BT_Feedback.Find(_T("RSSI(dB):")) >= 0 ) {
		int RSSI_Feedback_Str_Flag = BT_Feedback.Find(_T("RSSI(dB):"));
		int temp_value = _tstof(BT_Feedback.Mid(RSSI_Feedback_Str_Flag + 9, 4));
		RSSI_Value_Total = RSSI_Value_Total + temp_value;
		BT_Feedback.Delete(0,RSSI_Feedback_Str_Flag + 15);
	}
	RSSI_Value = RSSI_Value_Total / RSSI_Count;
	Log_temp.Format(_T("Read Salve RSSI:%d"), RSSI_Value);
	LogUpdate(Log_temp);
	if (RSSI_Value < get_config.Limit_BlueTooth_RSSI_LSL) {
		LogUpdate(_T("RSSI Value Less Than LSL."));
		return 1;
	}
	else if (RSSI_Value > get_config.Limit_BlueTooth_RSSI_USL) {
		LogUpdate(_T("RSSI Value Over Than USL."));
		return 1;
	}

	//Setting UUID For RX-Receive
	BT_Feedback = _T("");
	CString UUID_str;
	UUID_str.Format(_T("%4X"), get_config.Limit_BlueTooth_UUID_RX);
	temp_str = get_config.Limit_BlueTooth_Command_Set_Receive_UUID + UUID_str;
	command = T2A(temp_str.GetBuffer(0));
	temp_str.ReleaseBuffer();
	serial.WriteToPort(command, temp_str.GetLength());
	MySleep(2000);
	LogUpdate(BT_Feedback);
	if (BT_Feedback.Find(UUID_str) < 0) {
		LogUpdate(_T("Cannot Set Receive RX UUID."));
		return 1;
	}
	Log_temp = _T("Set Receive (RX) UUID:") + BT_Feedback;
	LogUpdate(Log_temp);


	//Setting UUID For TX-Send
	BT_Feedback = _T("");
	UUID_str.Format(_T("%4X"), get_config.Limit_BlueTooth_UUID_TX);
	temp_str = get_config.Limit_BlueTooth_Command_Set_Send_UUID + UUID_str;
	command = T2A(temp_str.GetBuffer(0));
	temp_str.ReleaseBuffer();
	serial.WriteToPort(command, temp_str.GetLength());
	MySleep(2000);
	LogUpdate(BT_Feedback);
	if (BT_Feedback.Find(UUID_str) < 0) {
		LogUpdate(_T("Cannot Set Send TX UUID."));
		return 1;
	}
	Log_temp = _T("Set Send (TX) UUID:") + BT_Feedback;
	LogUpdate(Log_temp);

	//Set TDC To Test Model (BlueTooth Transmission)
	//Serial_Open(get_config.Pressure_Gauge_Serial_Port,get_config.Pressure_Gauge_Baud_Rate);
	//serial.WriteToPort(P_command,6);
	//while (serial_port_value_float > 0.15)
	//{
	//	LogUpdate(_T("Pressure system haven't drop to 0， need release prressure!"));
	//	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO1);
	//	MySleep(5000);
	//	LogUpdate(_T("排气"));
	//	testbench.IO_Init(get_config.TestBench_GPIO_GPIO_I2C_1);

	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO0);
	MySleep(100);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO2);
	MySleep(100);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO1);
	MySleep(10000);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO0);
	MySleep(100);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO2);
	MySleep(100);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO1);


	BT_Feedback = _T("");
	temp_str = _T("TESTC");
	command = T2A(temp_str.GetBuffer(0));
	temp_str.ReleaseBuffer();
	//Serial_Open(get_config.BlueTooth_Serial_Port, get_config.BlueTooth_Baud_Rate);
	serial.WriteToPort(command,temp_str.GetLength());
	MySleep(2000);
	CString temp_bt_str;
	temp_bt_str.Format(_T("Reset Pressure after command %s:%s-%x"), temp_str, BT_Feedback, BT_Feedback);
	LogUpdate(temp_bt_str);
	if (BT_Feedback.Find(_T("OK")) < 0) {
		LogUpdate(_T("Cannot ReSet TDC Pressure Sensor."));
		return 1;
	}
	Log_temp = _T("ReSet TDC Pressure Sensor Successed");
	LogUpdate(Log_temp);
	CTime Sub_Test_End_Time = TimeStamp();
	CString Sub_Test_End_Time_Text = Sub_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("End Time:%s"), Sub_Test_End_Time_Text);
	LogUpdate(time_temp_str);
	time_temp_str.Format(_T("Duration: %d"), Sub_Test_End_Time - Sub_Test_Start_Time);
	LogUpdate(time_temp_str);
	return 0;
}

int CTDCFVT4Dlg::BlueTooth_Connect()
{
	if (get_config.Limit_BlueTooth_Manual_Reset == 1) {
		AfxMessageBox(_T("Pleaes PowerOn / Poweroff TDC! \r\n 请将TDC产品重新启动：关机-开机！"));
	}
	CString time_temp_str;
	CTime Sub_Test_Start_Time = TimeStamp();
	CString Sub_Test_Start_Time_Text = Sub_Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("Start Time:%s"), Sub_Test_Start_Time_Text);
	LogUpdate(time_temp_str);
	
	/*
	if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
		AfxMessageBox(_T("Please manual Push The Power On Key Till Another Remind Window Pop Up.\r\n 请手工按住开机键直到弹出另一个提示窗口"));
	}
	testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO1);
	MySleep(3000);
	stlink.Read_8(get_config.Limit_BlueTooth_Slave_BT_Address, get_config.Limit_BlueTooth_Slave_BT_Addrress_Length);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1);
	if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
		AfxMessageBox(_T("Please Release The Power On Key.\r\n 请释放开机键!"));
	}

	if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
		AfxMessageBox(_T("Please manual Push The Power On Key Till TDC Power On.\r\n 请手工按住开机键直到产品开机！"));
	}

	testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO1);
	MySleep(500);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1);

	
	CString temp_str1, temp_str2, temp_str3, temp_str4;
	temp_str1.Format(_T("%08X"), get_config.Limit_BlueTooth_Slave_BT_Address);
	temp_str2.Format(_T("%08X"), get_config.Limit_BlueTooth_Slave_BT_Address + 0x10);
	CString bt_address_str = _T("");
	bt_address_str = stlink.Get_BT_Address(temp_str1, temp_str2);
	temp_str3.Format(_T("Get Slave (TDC) BT Address: %s"), bt_address_str);
	LogUpdate(temp_str3);
	if (bt_address_str.Find(_T("Error")) >= 0) {
		LogUpdate(_T("Cannot Get Correct BT Address."));
		return 1;
	}
	if (bt_address_str == _T("000000000000")) {
		LogUpdate(_T("Cannot Get Correct BT Address."));
		return 1;
	}
	Slave_BT = bt_address_str;

	*/

	testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO1);
	MySleep(2000);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1);


	Serial_Open(get_config.BlueTooth_Serial_Port, get_config.BlueTooth_Baud_Rate);
	USES_CONVERSION;
	CString temp_str, BT_str, Log_temp;
	char* command;

	//Disconnct Slave BT (TDC)

	BT_Feedback = _T("");
	command = T2A(get_config.Limit_BlueTooth_Command_Disconnect.GetBuffer(0));
	get_config.Limit_BlueTooth_Command_Reset.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_BlueTooth_Command_Disconnect.GetLength());
	MySleep(2000);
	if (BT_Feedback.Find(_T("LOST")) < 0) {
		LogUpdate(_T("No Found Any Connection."));
		//return 1;
	}
	else {
		LogUpdate(_T("Disconnect Slave BT Successed."));
	}


	//Check BT Dongle Version.
	BT_Feedback = _T("");
	command = T2A(get_config.Limit_BlueTooth_Command_Get_Master_Vers.GetBuffer(0));
	get_config.Limit_BlueTooth_Command_Get_Master_Vers.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_BlueTooth_Command_Get_Master_Vers.GetLength());
	MySleep(5000);
	if (BT_Feedback.Find(get_config.Limit_BlueTooth_Master_BT_Vers) < 0) {
		LogUpdate(_T("Cannot Get Master BT Dongle Vers."));
		return 1;
	}
	Log_temp = _T("Get Master BT Dongle Vers:") + BT_Feedback;
	LogUpdate(Log_temp);

	//Reset BT Dongle
	BT_Feedback = _T("");
	command = T2A(get_config.Limit_BlueTooth_Command_Reset.GetBuffer(0));
	get_config.Limit_BlueTooth_Command_Reset.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_BlueTooth_Command_Reset.GetLength());
	MySleep(2000);
	if (BT_Feedback.Find(_T("RESET")) < 0) {
		LogUpdate(_T("Cannot Reset BT Dongle."));
		return 1;
	}
	Log_temp = _T("Reset BT Dongle Successed");
	LogUpdate(Log_temp);

	//Connect TDC BT
	BT_Feedback = _T("");
	temp_str = get_config.Limit_BlueTooth_Command_Connect + Slave_BT;
	command = T2A(temp_str.GetBuffer(0));
	temp_str.ReleaseBuffer();
	//if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
	//AfxMessageBox(_T("Please manual Push The Power On Key Till Another Remind Window Pop Up.\r\n 请手工按住开机键直到弹出另一个提示窗口"));
	//}
	testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO1);
	MySleep(2000);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1);
	//if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
	//AfxMessageBox(_T("Please Release The Power On Key.\r\n 请释放开机键!"));
	//}
	serial.WriteToPort(command, temp_str.GetLength());
	MySleep(5000);
	if (BT_Feedback.Find(Slave_BT) < 0) {
		LogUpdate(_T("Cannot Connect Slave (TDC)."));
		return 1;
	}
	Log_temp = _T("Connect Slave BT (TDC) Suceesed:\r\n") + BT_Feedback;
	LogUpdate(Log_temp);

	//Get RSSI
	/*
	BT_Feedback = _T("");
	serial_receive_str_count = 0;
	command = T2A(get_config.Limit_BlueTooth_Command_Read_RSSI.GetBuffer(0));
	get_config.Limit_BlueTooth_Command_Read_RSSI.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_BlueTooth_Command_Read_RSSI.GetLength());
	MySleep(10000);
	serial.WriteToPort(command, get_config.Limit_BlueTooth_Command_Read_RSSI.GetLength());
	MySleep(1500);
	int RSSI_Value = 0;
	int RSSI_Value_Total = 0;
	int RSSI_Count = 0;

	RSSI_Count = BT_Feedback.Replace(_T("RSSI(dB):"), _T("RSSI(dB):"));
	if (RSSI_Count <= 0) {
		LogUpdate(_T("Read RSSI Value Failed."));
		return 1;
	}
	while (BT_Feedback.Find(_T("RSSI(dB):")) >= 0) {
		int RSSI_Feedback_Str_Flag = BT_Feedback.Find(_T("RSSI(dB):"));
		int temp_value = _tstof(BT_Feedback.Mid(RSSI_Feedback_Str_Flag + 9, 4));
		RSSI_Value_Total = RSSI_Value_Total + temp_value;
		BT_Feedback.Delete(0, RSSI_Feedback_Str_Flag + 15);
	}
	RSSI_Value = RSSI_Value_Total / RSSI_Count;
	Log_temp.Format(_T("Read Salve RSSI:%d"), RSSI_Value);
	LogUpdate(Log_temp);
	if (RSSI_Value < get_config.Limit_BlueTooth_RSSI_LSL) {
		LogUpdate(_T("RSSI Value Less Than LSL."));
		return 1;
	}
	else if (RSSI_Value > get_config.Limit_BlueTooth_RSSI_USL) {
		LogUpdate(_T("RSSI Value Over Than USL."));
		return 1;
	}
	*/

	//Setting UUID For RX-Receive
	BT_Feedback = _T("");
	CString UUID_str;
	UUID_str.Format(_T("%4X"), get_config.Limit_BlueTooth_UUID_RX);
	temp_str = get_config.Limit_BlueTooth_Command_Set_Receive_UUID + UUID_str;
	command = T2A(temp_str.GetBuffer(0));
	temp_str.ReleaseBuffer();
	serial.WriteToPort(command, temp_str.GetLength());
	MySleep(2000);
	if (BT_Feedback.Find(UUID_str) < 0) {
		LogUpdate(_T("Cannot Set Receive RX UUID."));
		return 1;
	}
	Log_temp = _T("Set Receive (RX) UUID:") + BT_Feedback;
	LogUpdate(Log_temp);


	//Setting UUID For TX-Send
	BT_Feedback = _T("");
	UUID_str.Format(_T("%4X"), get_config.Limit_BlueTooth_UUID_TX);
	temp_str = get_config.Limit_BlueTooth_Command_Set_Send_UUID + UUID_str;
	command = T2A(temp_str.GetBuffer(0));
	temp_str.ReleaseBuffer();
	serial.WriteToPort(command, temp_str.GetLength());
	MySleep(2000);
	if (BT_Feedback.Find(UUID_str) < 0) {
		LogUpdate(_T("Cannot Set Send TX UUID."));
		return 1;
	}
	Log_temp = _T("Set Send (TX) UUID:") + BT_Feedback;
	LogUpdate(Log_temp);

	//Set TDC To Test Model (BlueTooth Transmission)
	BT_Feedback = _T("");
	temp_str = get_config.Limit_Transmission_Command_Transmission;
	command = T2A(temp_str.GetBuffer(0));
	temp_str.ReleaseBuffer();
	serial.WriteToPort(command, get_config.Limit_Transmission_Command_Transmission.GetLength());
	MySleep(2000);
	if (BT_Feedback.Find(_T("Hello Testbench")) < 0) {
		LogUpdate(_T("Cannot Set TDC To Transmission Model."));
		return 1;
	}
	Log_temp = _T("Set TDC To Transmission Model Successed");
	LogUpdate(Log_temp);
	CTime Sub_Test_End_Time = TimeStamp();
	CString Sub_Test_End_Time_Text = Sub_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("End Time:%s"), Sub_Test_End_Time_Text);
	LogUpdate(time_temp_str);
	time_temp_str.Format(_T("Duration: %d"), Sub_Test_End_Time - Sub_Test_Start_Time);
	LogUpdate(time_temp_str);
	return 0;
}

int CTDCFVT4Dlg::RFID_Check()
{
	CString temp_str;
	CTime Sub_Test_Start_Time = TimeStamp();
	CString Sub_Test_Start_Time_Text = Sub_Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	temp_str.Format(_T("Start Time:%s"), Sub_Test_Start_Time_Text);
	LogUpdate(temp_str);
	CString TDC_RFID_Feedback = TDC_Get_RFID();
	if ((TDC_RFID_Feedback.Find(_T("Error")) >= 0)) {
		LogUpdate(_T("Cannot Get Correct RFID!"));
		return 1;			
	}
	if ((TDC_RFID_Feedback.Find(get_config.Limit_RFID_Check_RFID) >= 0)) {
		CString temp_str;
		temp_str.Format(_T("Get Correct RFID Value: %s"), TDC_RFID_Feedback);
		LogUpdate(temp_str);
		CTime Sub_Test_End_Time = TimeStamp();
		CString Sub_Test_End_Time_Text = Sub_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
		temp_str.Format(_T("End Time:%s"), Sub_Test_End_Time_Text);
		LogUpdate(temp_str);
		temp_str.Format(_T("Duration: %d"), Sub_Test_End_Time - Sub_Test_Start_Time);
		LogUpdate(temp_str);
		return 0;
	}
	else {
		CString temp_str;
		temp_str.Format(_T("Get Wrong RFID Value: %s"), TDC_RFID_Feedback);
		LogUpdate(temp_str);
		return 1;
	}

}

int CTDCFVT4Dlg::Button_Check()
{
	return 0;
}

int CTDCFVT4Dlg::Charging_Check()
{
	CString temp_str;
	CTime Sub_Test_Start_Time = TimeStamp();
	CString Sub_Test_Start_Time_Text = Sub_Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	temp_str.Format(_T("Start Time:%s"), Sub_Test_Start_Time_Text);
	LogUpdate(temp_str);
	bool IO_result = testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO0);
	if (IO_result = FALSE) {
		LogUpdate(_T("Cannot Open Internal IO."));
		return 1;
	}
	float bench_voltage_Result = testbench.ADC_Measurement(get_config.TestBench_ADC_ADC_I2C_Address, get_config.TestBench_ADC_ADC1);
	float charging_voltage_Result = testbench.ADC_Measurement(get_config.TestBench_ADC_ADC_I2C_Address, get_config.TestBench_ADC_ADC2);
	float current_Result = testbench.ADC_Current_Measurement(get_config.TestBench_ADC_ADC_I2C_Address, get_config.TestBench_ADC_ADC3);
	float current_value = ((current_Result - 0.5 * bench_voltage_Result)) / 185 * 1000 + 200; //200MA offset.
	//double current_value = (charging_voltage_Result - bench_voltage_Result); // 1000;
	CString reference_voltage;
	reference_voltage.Format(_T("Reference Voltage = %.3fV"), bench_voltage_Result / 1000);
	CString Charging_Current;
	Charging_Current.Format(_T("Charging Current = %.3fmA"), current_value);
	CString Charging_Voltage;
	Charging_Voltage.Format(_T("Charging Voltage = %.3fV"), charging_voltage_Result / 1000);
	LogUpdate(reference_voltage);
	LogUpdate(Charging_Voltage);
	LogUpdate(Charging_Current);
	if ((charging_voltage_Result >= get_config.Limit_Charging_Check_Charging_Voltage_Min) && (charging_voltage_Result <= get_config.Limit_Charging_Check_Charging_Voltage_Max)) {
		LogUpdate(_T("Charging Voltage Check Pass."));
	}
	else {
		LogUpdate(_T("Charging Voltage Check Failed."));
		return 1;
	}

	if ((current_value >= get_config.Limit_Charging_Check_Charging_Current_Min) && (current_value <= get_config.Limit_Charging_Check_Charging_Current_Max)) {
		LogUpdate(_T("Charging Current Check Pass."));
	}
	else {
		LogUpdate(_T("Charging Current Check Failed."));
		return 1;
	}
	IO_result = testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1);
	if (IO_result = FALSE) {
		LogUpdate(_T("Cannot Close Internal IO."));
		return 1;
	}
	CTime Sub_Test_End_Time = TimeStamp();
	CString Sub_Test_End_Time_Text = Sub_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	temp_str.Format(_T("End Time:%s"), Sub_Test_End_Time_Text);
	LogUpdate(temp_str);
	temp_str.Format(_T("Duration: %d"), Sub_Test_End_Time - Sub_Test_Start_Time);
	LogUpdate(temp_str);
	return 0;
}

int CTDCFVT4Dlg::LCD_Check()
{
	return 0;
}

int CTDCFVT4Dlg::Buzz_Check()
{
	return 0;
}


int CTDCFVT4Dlg::Pressure_Measurement()
{
	CString time_temp_str;
	CTime Sub_Test_Start_Time = TimeStamp();
	CString Sub_Test_Start_Time_Text = Sub_Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("Start Time:%s"), Sub_Test_Start_Time_Text);
	LogUpdate(time_temp_str);
	//充气泵电磁阀开
	serial_port_value_float = 0.0;
	Pressure_Measurement_Running_Status = 0;
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO0);
	MySleep(100);
	LogUpdate(_T("充气泵电磁阀开"));

	//TDC电磁阀开
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO2);
	MySleep(100);
	LogUpdate(_T("TDC电磁阀开"));

	//充气泵启动
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
	MySleep(100);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
	LogUpdate(_T("充气泵启动"));

	int Pressure_Measurement_Status = 0;
	Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
	serial.WriteToPort(P_command, 6);
	bool result;

	for (int i = 1; i <= 12; i = i + 2) {
		while (Pressure_Measurement_Running_Status == 0)
		{
			LogUpdate(_T("Waiting 10ms..."));
			MySleep(10);
			Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
			serial.WriteToPort(P_command, 6);
		}

		//float pressure_abs = abs(serial_port_value_float - reference_value);
		while (serial_port_value_float <= i) {
			testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
			MySleep(100);
			testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
			LogUpdate(_T("充气泵启动"));
			Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
			serial.WriteToPort(P_command, 6);
		}
		CString temp_str;
		temp_str.Format(_T("Inflator Running meet %d bar."), i);
		LogUpdate(temp_str);
		testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
		MySleep(100);
		testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
		LogUpdate(_T("充气泵停止"));
		MySleep(5000);
		Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
		serial.WriteToPort(P_command, 6);
		MySleep(1000);
		float TDC_Pressure_Value = TDC_Get_Pressure();
		
		if (TDC_Pressure_Value < 0.8) {
			//fMySleep(3000);
			TDC_Pressure_Value = TDC_Get_Pressure();
		}		
	
		/*
		float *TDC_Pressure_Value_Arry = new float[get_config.Limit_Pressure_Measurement_Max_Measurement_Times];
		TDC_Pressure_Value;
		for (int i = 0; i < get_config.Limit_Pressure_Measurement_Max_Measurement_Times; i++) {
			float TDC_Pressure_Value = TDC_Get_Pressure();
			//while (int(TDC_Pressure_Value * 100) == int(serial_port_value_float * 100)) {
			//	MySleep(1000);
			//	TDC_Pressure_Value = TDC_Get_Pressure();
				//TDC_Pressure_Value_Arry[i] = TDC_Pressure_Value;
			//}
			//CString temp_str;
			//temp_str.Format(_T("Test %d time value was %.3f."),i, &TDC_Pressure_Value_Arry[i]);
			//LogUpdate(temp_str);
			TDC_Pressure_Value_Arry[i] = TDC_Pressure_Value;
		}
		float total_value = 0.0;
		float min_value = 10000.0;
		float max_value = 0.0;

		for (int i = 0; i < get_config.Limit_Pressure_Measurement_Max_Measurement_Times; i++) {
			//min_value = TDC_Pressure_Value_Arry[i];
			total_value = total_value + TDC_Pressure_Value_Arry[i];
			if (TDC_Pressure_Value_Arry[i] > max_value) {
				max_value = TDC_Pressure_Value_Arry[i];
			}
			else {
				max_value = max_value;
			}
			if (TDC_Pressure_Value_Arry[i] < min_value) {
				min_value = TDC_Pressure_Value_Arry[i];
			}
			else {
				min_value = min_value;
			}
		}
		//CString temp_str;
		//temp_str.Format(_T("Max value was %.3f."), i, max_value);
		//LogUpdate(temp_str);
		//temp_str.Format(_T("Max value was %.3f."), i, min_value);
		//LogUpdate(temp_str);

		TDC_Pressure_Value = (total_value - min_value - max_value) / (get_config.Limit_Pressure_Measurement_Max_Measurement_Times - 2);
		*/

		temp_str.Format(_T("Pressure sensor float value was : %.3f."), serial_port_value_float);
		LogUpdate(temp_str);
		temp_str.Format(_T("TDC Pressure    float value was : %.3f."), TDC_Pressure_Value);
		LogUpdate(temp_str);
		int Reference_Pressure_Value_int = serial_port_value_float * 100;
		int TDC_Pressure_Value_int = TDC_Pressure_Value * 100;
		int Gap_Value = abs(TDC_Pressure_Value_int - Reference_Pressure_Value_int);
		if (Gap_Value > get_config.Limit_Pressure_Measurement_Measurement_Tolorance) {
			temp_str.Format(_T("Pressure Value at %d bar gap %d (*100) out of limit:%d"),i, Gap_Value, get_config.Limit_Pressure_Measurement_Measurement_Tolorance);
			LogUpdate(temp_str);
			return 1;
		}
		temp_str.Format(_T("Pressure Value at %d bar gap %d (*100) was OK."), i, Gap_Value);
		LogUpdate(temp_str);
		Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
		serial.WriteToPort(P_command, 6);
		
		if (i <= 12) {
			testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
			MySleep(100);
			testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
			LogUpdate(_T("充气泵启动"));
			Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
			serial.WriteToPort(P_command, 6);
		}
		Pressure_Measurement_Status++;
	}
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
	MySleep(100);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
	LogUpdate(_T("充气泵停止"));

	//排气
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO1);
	MySleep(5000);
	LogUpdate(_T("排气"));
	testbench.IO_Init(get_config.TestBench_GPIO_GPIO_I2C_1);
	CTime Sub_Test_End_Time = TimeStamp();
	CString Sub_Test_End_Time_Text = Sub_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("End Time:%s"), Sub_Test_End_Time_Text);
	LogUpdate(time_temp_str);
	time_temp_str.Format(_T("Duration: %d"), Sub_Test_End_Time - Sub_Test_Start_Time);
	LogUpdate(time_temp_str);
	if (Pressure_Measurement_Status == 6) {
		LogUpdate(_T("Pressure Measurement Result Pass."));
		return 0;
	}
	else {
		LogUpdate(_T("Pressure Measurement Result Failed."));
		return 1;
	}
}


int CTDCFVT4Dlg::Distance_Calibration()
{
	CString time_temp_str;
	CTime Sub_Test_Start_Time = TimeStamp();
	CString Sub_Test_Start_Time_Text = Sub_Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("Start Time:%s"), Sub_Test_Start_Time_Text);
	LogUpdate(time_temp_str);
	Distance_Calibration_Running_Count = 0;
	int seial_open_result;
	//Move_To_Zero_Position();
	//Move_Release();
	//Step_Motor_Move_Right();
	Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
	serial.WriteToPort(T_command, 6);
	//MySleep(10000);
	LogUpdate(_T("Step Motor Running..."));
	bool result;
	for (int i = get_config.Limit_Distance_Calibration_Distance_Begin; i <= get_config.Limit_Distance_Calibration_Distance_End; i = i + get_config.Limit_Distance_Calibration_Distance_Increase) {
		while (Distance_Calibration_Running_Status == 0)
		{
			//LogUpdate(_T("Waiting 10ms..."));
			MySleep(10);
			Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
			serial.WriteToPort(T_command, 6);
		}
		//if (i == 0) {
		//bool temp_compare_result_0 = (serial_port_value_float >= (i + 0.1));
		//bool temp_compare_result_1 = (serial_port_value_float <= (i - 0.1));
		//while (((serial_port_value_float >= (i + 0.1)) || (serial_port_value_float <= (i - 0.1)))) {
		while (((Serial_Port_Value_Int >= (i *100 + 5)) || (Serial_Port_Value_Int <= (i * 100 - 5)))) {

			if (i == 0) {
				if ((Serial_Port_Value_Int >= (i * 100 + 1))) {
					result = Step_Motor_Move_Right();
					//MySleep(10);
					//Step_Motor_Move_Stop();
					Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
					serial.WriteToPort(T_command, 6);
					//LogUpdate(_T("Move Right..."));
				}

				if ((Serial_Port_Value_Int <= i * 100)) {
					result = Step_Motor_Move_Left();
					//MySleep(10);
					Step_Motor_Move_Stop();
					Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
					serial.WriteToPort(T_command, 6);
					//LogUpdate(_T("Move Left..."));
				}
			}
			else {
				if ((Serial_Port_Value_Int >= (i * 100 + 50))) {
					result = Step_Motor_Move_Right();
					MySleep(200);
					Step_Motor_Move_Stop();
					Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
					serial.WriteToPort(T_command, 6);
					//LogUpdate(_T("Move Right Fast..."));
				}

				if ((Serial_Port_Value_Int >= (i * 100  + 5)) && (Serial_Port_Value_Int <= (i * 100 + 50))) {
					result = Step_Motor_Move_Right();
					MySleep(50);
					Step_Motor_Move_Stop();
					Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
					serial.WriteToPort(T_command, 6);
					//LogUpdate(_T("Move Right Slow..."));
				}
				if ((Serial_Port_Value_Int <= (i * 100 - 50))) {
					result = Step_Motor_Move_Left();
					MySleep(200);
					//Step_Motor_Move_Stop();
					Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
					serial.WriteToPort(T_command, 6);
					//LogUpdate(_T("Move Left Fast..."));
				}
				if ((Serial_Port_Value_Int <= (i * 100 - 5)) && (Serial_Port_Value_Int >= (i * 100 - 50))) {
					result = Step_Motor_Move_Left();
					//MySleep(50);
					//Step_Motor_Move_Stop();
					Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
					serial.WriteToPort(T_command, 6);
					//LogUpdate(_T("Move Left Slow..."));
				}
			}
		}
		result = Step_Motor_Move_Stop();
		if (!result) {
			return 1;
		}
		CString temp_str;
		temp_str.Format(_T("Step Motor Move To %d position."), i);
		LogUpdate(temp_str);
		CString temp_str_position;
		
		if (get_config.Limit_Distance_Calibration_BT_Upload == 1) {
			if (i == 0) {
				bool zeor_position_result = TDC_Zero_Position();
				//bool zeor_position_result = TDC_Position(i);
				if (!zeor_position_result) {
					temp_str_position.Format(_T("Calibration TDC Distance at %i Postion Failed."), i);
					LogUpdate(temp_str_position);
					return 1;
				}
				temp_str_position.Format(_T("Calibration TDC Distance at %i Postion Passed."), i);
				LogUpdate(temp_str_position);
			}
			//bool zeor_position_result = TDC_Zero_Position();
			//bool zeor_position_result = TDC_Position(i);
			//if (!zeor_position_result) {
			//	temp_str_position.Format(_T("Calibration TDC Distance at %i Postion Failed."),i);
			//	LogUpdate(temp_str_position);
			//	return 1;
			//}
			//temp_str_position.Format(_T("Calibration TDC Distance at %i Postion Passed."), i);
			//LogUpdate(temp_str_position);
		}

		if (i == 0) {
			bool zeor_position_result = TDC_Zero_Position();
			//bool zeor_position_result = TDC_Position(i);
			if (!zeor_position_result) {
				temp_str_position.Format(_T("Calibration TDC Distance at %i Postion Failed."), i);
				LogUpdate(temp_str_position);
				return 1;
			}
			temp_str_position.Format(_T("Calibration TDC Distance at %i Postion Passed."), i);
			LogUpdate(temp_str_position);
		}

		MySleep(1000);
		Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
		serial.WriteToPort(T_command, 6);
		temp_str.Format(_T("Get Distance Gauge Value: %.3f"), serial_port_value_float);
		LogUpdate(temp_str);

		float *TDC_Distance_Value_Arry = new float[get_config.Limit_Distance_Calibration_Max_Measurement_Times];
		float TDC_Distance_Value;
		for (int i = 0; i < get_config.Limit_Distance_Calibration_Max_Measurement_Times; i++) {
			float TDC_Distance_Value = TDC_Get_Distance();
			//while (int(TDC_Distance_Value * 100) == int(serial_port_value_float * 100)) {
			//	MySleep(1000);
			//	TDC_Distance_Value = TDC_Get_Distance();
				//TDC_Distance_Value_Arry[i] = TDC_Distance_Value;
			//}
			//CString temp_str;
			//temp_str.Format(_T("Test %d time value was %.3f."),i, &TDC_Distance_Value_Arry[i]);
			//LogUpdate(temp_str);
			TDC_Distance_Value_Arry[i] = TDC_Distance_Value;
		}
		float total_value = 0.0;
		float min_value = 10000.0;
		float max_value = 0.0;

		for (int i = 0; i < get_config.Limit_Distance_Calibration_Max_Measurement_Times; i++) {
			//min_value = TDC_Distance_Value_Arry[i];
			total_value = total_value + TDC_Distance_Value_Arry[i];
			if (TDC_Distance_Value_Arry[i] > max_value) {
				max_value = TDC_Distance_Value_Arry[i];
			}
			else {
				max_value = max_value;
			}
			if (TDC_Distance_Value_Arry[i] < min_value) {
				min_value = TDC_Distance_Value_Arry[i];
			}
			else {
				min_value = min_value;
			}
		}
		//CString temp_str;
		//temp_str.Format(_T("Max value was %.3f."), i, max_value);
		//LogUpdate(temp_str);
		//temp_str.Format(_T("Max value was %.3f."), i, min_value);
		//LogUpdate(temp_str);

		TDC_Distance_Value = (total_value - min_value - max_value) / (get_config.Limit_Distance_Calibration_Max_Measurement_Times - 2);
		//TDC_Distance_Value = TDC_Distance_Value_int / 100;
		//temp_str.Format(_T("Int TDC Distance value was %d, float value was: %.3f."),i, TDC_Distance_Value_int, TDC_Distance_Value);
		//LogUpdate(temp_str);

		//seial_open_result = Serial_Open(get_config.BlueTooth_Serial_Port, get_config.BlueTooth_Baud_Rate);
		//if (seial_open_result !=0 ) {
		//	LogUpdate(_T("Cannot Open BT Serial Port."));
		//}
		Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
		serial.WriteToPort(T_command, 6);
		temp_str.Format(_T("Distance sensor float value was : %.3f."), serial_port_value_float);
		LogUpdate(temp_str);
		temp_str.Format(_T("TDC Distance    float value was : %.3f."), TDC_Distance_Value);
		LogUpdate(temp_str);
		if (i == 0) {
			LogUpdate(_T("Adjust 0 Position Value."));
			//TDC_Distance_Value = TDC_Distance_Value + serial_port_value_float;
			serial_port_value_float = 0.0;
			TDC_Distance_Value = 0.0;
			temp_str.Format(_T("Distance sensor float value after calculate was : %.3f."), serial_port_value_float);
			LogUpdate(temp_str);
			temp_str.Format(_T("TDC Distance    float value after calculate was : %.3f."), TDC_Distance_Value);
			LogUpdate(temp_str);
		}
		int Distance_Sensor_Value_Int = int (serial_port_value_float * 100);
		int TDC_Value_Int = int(TDC_Distance_Value * 100);
		Distance_Calibration_Result[i] = TDC_Value_Int;
		Distance_Calibration_Result[i + 31] = Distance_Sensor_Value_Int;
		Distance_Calibration_Running_Count++;
	}

	Step_Motor_Move_Stop();
	//serial.ClosePort();
	Step_Motor_Move_Right();
	MySleep(3000);
	Step_Motor_Move_Stop();
	CTime Sub_Test_End_Time = TimeStamp();
	CString Sub_Test_End_Time_Text = Sub_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("End Time:%s"), Sub_Test_End_Time_Text);
	LogUpdate(time_temp_str);
	time_temp_str.Format(_T("Duration: %d"), Sub_Test_End_Time - Sub_Test_Start_Time);
	LogUpdate(time_temp_str);
	if (Distance_Calibration_Running_Count >= get_config.Limit_Distance_Calibration_Calibration_Point) {
		LogUpdate(_T("Distance Calibration Passed."));
		return 0;
	}
	else {
		LogUpdate(_T("Distance Calibration Failed."));
		return 1;
	}
}

int CTDCFVT4Dlg::Distance_Measurement()
{
	CString time_temp_str;
	CTime Sub_Test_Start_Time = TimeStamp();
	CString Sub_Test_Start_Time_Text = Sub_Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("Start Time:%s"), Sub_Test_Start_Time_Text);
	LogUpdate(time_temp_str);
	Distance_Measurement_Running_Count = 0;
	int seial_open_result;
	//Move_To_Zero_Position();
	//Move_Release();
	//Step_Motor_Move_Right();
	Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
	serial.WriteToPort(T_command, 6);
	//MySleep(10000);
	LogUpdate(_T("Step Motor Running..."));
	bool result;
	for (int i = get_config.Limit_Distance_Measurement_Distance_Begin; i >= get_config.Limit_Distance_Measurement_Distance_End; i = i - get_config.Limit_Distance_Measurement_Distance_Increase) {
		while (Distance_Measurement_Running_Status == 0)
		{
			LogUpdate(_T("Waiting 10ms..."));
			MySleep(10);
			Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
			serial.WriteToPort(T_command, 6);
		}
		//if (i == 0) {
		//bool temp_compare_result_0 = (serial_port_value_float >= (i + 0.1));
		//bool temp_compare_result_1 = (serial_port_value_float <= (i - 0.1));
		//while (((serial_port_value_float >= (i + 0.1)) || (serial_port_value_float <= (i - 0.1)))) {
		while (((Serial_Port_Value_Int >= (i * 100 + 50)) || (Serial_Port_Value_Int <= (i * 100 - 50)))) {

			if (i == 29) {
				if ((Serial_Port_Value_Int >= (i * 100 + 50))) {
					result = Step_Motor_Move_Right();
					//MySleep(400);
					//Step_Motor_Move_Stop();
					Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
					serial.WriteToPort(T_command, 6);
					//LogUpdate(_T("Move Right..."));
				}
				if ((Serial_Port_Value_Int <= (i * 100 - 50))) {
					result = Step_Motor_Move_Left();
					//MySleep(100);
					//Step_Motor_Move_Stop();
					Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
					serial.WriteToPort(T_command, 6);
					//LogUpdate(_T("Move Left..."));
				}
			}
			else {
				if ((Serial_Port_Value_Int >= (i * 100 + 50))) {
					result = Step_Motor_Move_Right();
					//MySleep(400);
					//Step_Motor_Move_Stop();
					Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
					serial.WriteToPort(T_command, 6);
					//LogUpdate(_T("Move Right..."));
				}
				if ((Serial_Port_Value_Int <= (i * 100 - 50))) {
					result = Step_Motor_Move_Left();
					//MySleep(400);
					//Step_Motor_Move_Stop();
					Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
					serial.WriteToPort(T_command, 6);
					//LogUpdate(_T("Move Left..."));
				}
			}
		}
		result = Step_Motor_Move_Stop();
		if (!result) {
			return 1;
		}
		CString temp_str;
		MySleep(1000);
		Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
		serial.WriteToPort(T_command, 6);

		temp_str.Format(_T("Step Motor Move To %d position."), i);
		LogUpdate(temp_str);
		MySleep(1000);
		float *TDC_Distance_Value_Arry = new float[get_config.Limit_Distance_Calibration_Max_Measurement_Times];
		float TDC_Distance_Value;
		float total_value = 0.0;
		float min_value = 10000.0;
		float max_value = 0.0;
		for (int i = 0; i < get_config.Limit_Distance_Calibration_Max_Measurement_Times; i++) {
			TDC_Distance_Value = TDC_Get_Distance();
			//while (int(TDC_Distance_Value * 100) == int(serial_port_value_float * 100)) {
			//	MySleep(1000);
			//	TDC_Distance_Value = TDC_Get_Distance();
			//}
			TDC_Distance_Value_Arry[i] = TDC_Distance_Value;
		}
		for (int i = 0; i < get_config.Limit_Distance_Calibration_Max_Measurement_Times; i++) {
			//min_value = TDC_Distance_Value_Arry[i];
			total_value = total_value + TDC_Distance_Value_Arry[i];
			if (TDC_Distance_Value_Arry[i] > max_value) {
				max_value = TDC_Distance_Value_Arry[i];
			}
			else {
				max_value = max_value;
			}
			if (TDC_Distance_Value_Arry[i] < min_value) {
				min_value = TDC_Distance_Value_Arry[i];
			}
			else {
				min_value = min_value;
			}
		}
		TDC_Distance_Value = (total_value - min_value - max_value) / (get_config.Limit_Distance_Calibration_Max_Measurement_Times - 2);

		Serial_Open(get_config.Distance_Gauge_Serial_Port, get_config.Distance_Gauge_Baud_Rate);
		serial.WriteToPort(T_command, 6);
		temp_str.Format(_T("Distance sensor float value was : %.3f."), serial_port_value_float);
		LogUpdate(temp_str);
		temp_str.Format(_T("TDC Distance    float value was : %.3f."), TDC_Distance_Value);
		LogUpdate(temp_str);

		int TDC_Distance_Value_Int = TDC_Distance_Value * 100;
		int Reference_Distance_Value_Int = serial_port_value_float * 100;
		int Gap_Value = abs(TDC_Distance_Value_Int - Reference_Distance_Value_Int);
		if (Gap_Value > get_config.Limit_Distance_Measurement_Measurement_Tolorance) {
			temp_str.Format(_T("The gap between TDC and Reference Distance Sensor (*100) was: %d out of Limit %d."), Gap_Value, get_config.Limit_Distance_Measurement_Measurement_Tolorance);
			LogUpdate(temp_str);
			return 1;
		}
		temp_str.Format(_T("The gap between TDC and Reference Distance Sensor (*100) was: %d under Limit %d."), Gap_Value, get_config.Limit_Distance_Measurement_Measurement_Tolorance);
		LogUpdate(temp_str);
		Distance_Measurement_Running_Count++;
	}

	Step_Motor_Move_Stop();
	//serial.ClosePort();
	Step_Motor_Move_Left();
	MySleep(5000);
	Step_Motor_Move_Stop();
	CTime Sub_Test_End_Time = TimeStamp();
	CString Sub_Test_End_Time_Text = Sub_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("End Time:%s"), Sub_Test_End_Time_Text);
	LogUpdate(time_temp_str);
	time_temp_str.Format(_T("Duration: %d"), Sub_Test_End_Time - Sub_Test_Start_Time);
	LogUpdate(time_temp_str);
	//if (Distance_Measurement_Running_Count >= ((get_config.Limit_Distance_Measurement_Distance_Begin - get_config.Limit_Distance_Measurement_Distance_End) / get_config.Limit_Distance_Calibration_Distance_Increase)) {
	//	LogUpdate(_T("Distance Measurement Passed."));
	return 0;
	//}
	//else {
	//	LogUpdate(_T("Distance Measurement Failed."));
	//	return 1;
	//}

}

/*
int CTDCFVT4Dlg::Pressure_Calibration()
{
	//充气泵电磁阀开
	Pressure_Calibration_Running_Status = 0;
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO0);
	MySleep(100);
	LogUpdate(_T("充气泵电磁阀开"));
	
	//TDC电磁阀开
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO2);
	MySleep(100);
	LogUpdate(_T("TDC电磁阀开"));
	
	//充气泵启动
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
	MySleep(100);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
	LogUpdate(_T("充气泵启动"));


	Serial_Open(get_config.Pressure_Gauge_Serial_Port,get_config.Pressure_Gauge_Baud_Rate);
	serial.WriteToPort(P_command, 6);
	while (Pressure_Calibration_Running_Status == 0) {
		MySleep(10);	
	}
	//serial.ClosePort();
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
	MySleep(100);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
	LogUpdate(_T("充气泵停止"));

	//排气
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO1);
	MySleep(5000);
	LogUpdate(_T("排气"));
	testbench.IO_Init(get_config.TestBench_GPIO_GPIO_I2C_1);

	if (Pressure_Calibration_Running_Status == 1) {
		return 0;

	}
	if (Pressure_Calibration_Running_Status == 2) {
		return 1;
	}
}
*/
int CTDCFVT4Dlg::Pressure_Calibration() {
	CString time_temp_str;
	CTime Sub_Test_Start_Time = TimeStamp();
	CString Sub_Test_Start_Time_Text = Sub_Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("Start Time:%s"), Sub_Test_Start_Time_Text);
	LogUpdate(time_temp_str);
	//LogUpdate(_T("Initialize Pressure Calibration Result."));
	//for (int i = 0; i < sizeof(Pressure_Calibration_Result); i++) {
	//	Pressure_Calibration_Result[i] = 0x00;
	//}

	//充气泵电磁阀开
	serial_port_value_float = 0.0;
	Pressure_Calibration_Running_Status = 0;
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO0);
	MySleep(100);
	LogUpdate(_T("充气泵电磁阀开"));

	//TDC电磁阀开
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO2);
	MySleep(100);
	LogUpdate(_T("TDC电磁阀开"));

	//充气泵启动
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
	MySleep(100);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
	LogUpdate(_T("充气泵启动"));
	
	int Pressure_Calibration_Status = 0;
	Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
	serial.WriteToPort(P_command, 6);
	bool result;
	CString temp_str;
	for (int i = 0; i < 2; i++ ) {
		while (Pressure_Calibration_Running_Status == 0)
		{
			LogUpdate(_T("Waiting 10ms..."));
			MySleep(10);
			Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
			serial.WriteToPort(P_command, 6);
		}
		int reference_value;
		//temp_str.Format(_T("Pressure sensor Before float value was : %.3f."), serial_port_value_float);
		//	LogUpdate(temp_str);

		if (i == 0) {
			reference_value = get_config.Limit_Pressure_Calibration_Calibration1;
		} 
		if (i == 1) {
			//serial_port_value_float = serial_port_value_float + 0.4;
			reference_value = get_config.Limit_Pressure_Calibration_Calibration2;
		}
		//float pressure_abs = abs(serial_port_value_float - reference_value);
		while (serial_port_value_float <= reference_value) {
			testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
			MySleep(100);
			testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
			//LogUpdate(_T("充气泵启动"));
			Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
			serial.WriteToPort(P_command, 6);
		}
		temp_str.Format(_T("Inflator Running meet %d bar."), reference_value);
		LogUpdate(temp_str);
		testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
		MySleep(100);
		testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
		LogUpdate(_T("充气泵停止"));
		MySleep(5000);
		Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
		serial.WriteToPort(P_command, 6);
		MySleep(1000);
		//if (i == 0) {
		//	serial_port_value_float = serial_port_value_float + 0.6;
		//}
		//else {
		//	serial_port_value_float = serial_port_value_float + 0.4;
		//}
		float TDC_Pressure_Value = TDC_Get_Pressure();
		if (TDC_Pressure_Value > 999) {
			LogUpdate(_T("Cannot Get Correct Pressure Value!"));
			return 1;
		}
		if (TDC_Pressure_Value < 0.8) {
			//MySleep(3000);
			TDC_Pressure_Value = TDC_Get_Pressure();
		}
		temp_str.Format(_T("Pressure sensor float value was : %.3f."), serial_port_value_float);
		LogUpdate(temp_str);
		temp_str.Format(_T("TDC Pressure    float value was : %.3f."), TDC_Pressure_Value);
		LogUpdate(temp_str);
		Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
		serial.WriteToPort(P_command, 6);
		int Pressure_Sensor_Value_Int = int(serial_port_value_float * 100);
		int TDC_Value_Int = int(TDC_Pressure_Value * 100);
		Pressure_Calibration_Result[i] = TDC_Value_Int;
		Pressure_Calibration_Result[i+2] = Pressure_Sensor_Value_Int;
		if (i < 2) {
			testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
			MySleep(100);
			testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
			LogUpdate(_T("充气泵启动"));
			Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
			serial.WriteToPort(P_command, 6);
		}
		Pressure_Calibration_Status++;
	}

	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
	MySleep(100);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
	LogUpdate(_T("充气泵停止"));

	//排气
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO1);
	MySleep(5000);
	LogUpdate(_T("排气"));
	testbench.IO_Init(get_config.TestBench_GPIO_GPIO_I2C_1);
	CTime Sub_Test_End_Time = TimeStamp();
	CString Sub_Test_End_Time_Text = Sub_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("End Time:%s"), Sub_Test_End_Time_Text);
	LogUpdate(time_temp_str);
	time_temp_str.Format(_T("Duration: %d"), Sub_Test_End_Time - Sub_Test_Start_Time);
	LogUpdate(time_temp_str);
	if (Pressure_Calibration_Status == 2) {
		LogUpdate(_T("Pressure Calibration Result Pass."));
		return 0;
	}
	else {
		LogUpdate(_T("Pressure Calibration Result Failed."));
		return 1;
	}
}

/*
int CTDCFVT4Dlg::Pressure_Measurement()
{
	CString time_temp_str;
	CTime Sub_Test_Start_Time = TimeStamp();
	CString Sub_Test_Start_Time_Text = Sub_Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("Start Time:%s"), Sub_Test_Start_Time_Text);
	LogUpdate(time_temp_str);
	//充气泵电磁阀开
	serial_port_value_float = 0.0;
	Pressure_Measurement_Running_Status = 0;
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO0);
	MySleep(100);
	LogUpdate(_T("充气泵电磁阀开"));

	//TDC电磁阀开
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO2);
	MySleep(100);
	LogUpdate(_T("TDC电磁阀开"));

	//充气泵启动
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
	MySleep(100);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
	LogUpdate(_T("充气泵启动"));

	int Pressure_Measurement_Status = 0;
	Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
	serial.WriteToPort(P_command, 6);
	bool result;

	for (int i = 1; i <= 12; i = i + 2) {
		while (Pressure_Measurement_Running_Status == 0)
		{
			LogUpdate(_T("Waiting 10ms..."));
			MySleep(10);
			Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
			serial.WriteToPort(P_command, 6);
		}

		//float pressure_abs = abs(serial_port_value_float - reference_value);
		while (serial_port_value_float <= i) {
			testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
			MySleep(100);
			testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
			LogUpdate(_T("充气泵启动"));
			Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
			serial.WriteToPort(P_command, 6);
		}
		CString temp_str;
		temp_str.Format(_T("Inflator Running meet %d bar."), i);
		LogUpdate(temp_str);
		testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
		MySleep(100);
		testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
		LogUpdate(_T("充气泵停止"));
		MySleep(5000);
		Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
		serial.WriteToPort(P_command, 6);
		MySleep(1000);
		float TDC_Pressure_Value = TDC_Get_Pressure();
		
		if (TDC_Pressure_Value < 0.8) {
			//fMySleep(3000);
			TDC_Pressure_Value = TDC_Get_Pressure();
		}	

		temp_str.Format(_T("Pressure sensor float value was : %.3f."), serial_port_value_float);
		LogUpdate(temp_str);
		temp_str.Format(_T("TDC Pressure    float value was : %.3f."), TDC_Pressure_Value);
		LogUpdate(temp_str);
		int Reference_Pressure_Value_int = serial_port_value_float * 100;
		int TDC_Pressure_Value_int = TDC_Pressure_Value * 100;
		int Gap_Value = abs(TDC_Pressure_Value_int - Reference_Pressure_Value_int);
		if (Gap_Value > get_config.Limit_Pressure_Measurement_Measurement_Tolorance) {
			temp_str.Format(_T("Pressure Value at %d bar gap %d (*100) out of limit:%d"),i, Gap_Value, get_config.Limit_Pressure_Measurement_Measurement_Tolorance);
			LogUpdate(temp_str);
			return 1;
		}
		temp_str.Format(_T("Pressure Value at %d bar gap %d (*100) was OK."), i, Gap_Value);
		LogUpdate(temp_str);
		Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
		serial.WriteToPort(P_command, 6);
		
		if (i <= 12) {
			testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
			MySleep(100);
			testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO3);
			LogUpdate(_T("充气泵启动"));
			Serial_Open(get_config.Pressure_Gauge_Serial_Port, get_config.Pressure_Gauge_Baud_Rate);
			serial.WriteToPort(P_command, 6);
		}
		Pressure_Measurement_Status++;
	}
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
	MySleep(100);
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO4);
	LogUpdate(_T("充气泵停止"));

	//排气
	testbench.IO_Action(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO1);
	MySleep(5000);
	LogUpdate(_T("排气"));
	testbench.IO_Init(get_config.TestBench_GPIO_GPIO_I2C_1);
	CTime Sub_Test_End_Time = TimeStamp();
	CString Sub_Test_End_Time_Text = Sub_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("End Time:%s"), Sub_Test_End_Time_Text);
	LogUpdate(time_temp_str);
	time_temp_str.Format(_T("Duration: %d"), Sub_Test_End_Time - Sub_Test_Start_Time);
	LogUpdate(time_temp_str);
	if (Pressure_Measurement_Status == 6) {
		LogUpdate(_T("Pressure Measurement Result Pass."));
		return 0;
	}
	else {
		LogUpdate(_T("Pressure Measurement Result Failed."));
		return 1;
	}
}
*/

int CTDCFVT4Dlg::Close_Test()
{
	testbench.IO_Init(get_config.TestBench_GPIO_GPIO_I2C_0);
	testbench.IO_Init(get_config.TestBench_GPIO_GPIO_I2C_1);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO0);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO2);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO3);
	return 0;
}

void CTDCFVT4Dlg::Log_Title()
{
	CString Line1, Line2, Line3, Line4, Line5, Line6, Line7, Line8, Line9, Line10, Line11, Line12, Line13, Line14, Line15,Line16;
	Line1.Format(_T("S%s"), Serial_No);
	LogUpdate(Line1);
	Line2.Format(_T("C%s"), get_config.MAIN_Customer);
	LogUpdate(Line2);
	Line3.Format(_T("T%s"), get_config.MAIN_Test_Station);
	LogUpdate(Line3);
	Line4.Format(_T("F%s"), get_config.MAIN_Factory);
	LogUpdate(Line4);
	Line5.Format(_T("H%s"), get_config.MAIN_Hostname);
	LogUpdate(Line5);
	Line6.Format(_T("P%s"),get_config.MAIN_Production_Name);
	LogUpdate(Line6);
	Line7.Format(_T("A%s"),get_config.MAIN_Assembly_Number);
	LogUpdate(Line7);
	Line8.Format(_T("a%s"), get_config.MAIN_Assembly_Revision);
	LogUpdate(Line8);
	Line9.Format(_T("L%s"), get_config.MAIN_Site);
	LogUpdate(Line9);
	Line10.Format(_T("R%s"), get_config.MAIN_Software_Revision);
	LogUpdate(Line10);
	Line11.Format(_T("W%s"), get_config.MAIN_FW_Revision);
	LogUpdate(Line11);
	Line12.Format(_T("f%s"), get_config.MAIN_Fixture_ID);
	LogUpdate(Line12);
	Line13 = _T("");
	LogUpdate(Line13);
	Line14.Format(_T("[%s"), Test_Start_Time_Text);
	LogUpdate(Line14);
	Line15 = _T("]");
	LogUpdate(Line15);
	Line16 = _T("");
	LogUpdate(Line16);
}

BOOL CTDCFVT4Dlg::m_SetEvent(void)
{
	SetEvent(m_hWakeupEvent);
	return TRUE;
}

bool CTDCFVT4Dlg::Step_Motor_Move_Right()
{
	bool move_result;
		move_result = testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO2);
 	if (!move_result) {
		return FALSE;
	}
//	move_result = testbench.IO_To_Open(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO13);
//	if (!move_result) {
//		return FALSE;
//	}
//	//MySleep(100);
	move_result = testbench.IO_To_Open(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO14);
	if (!move_result) {
		return FALSE;
	}
//	MySleep(500);
	move_result = testbench.IO_To_Close(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO13);
	if (!move_result) {
		return FALSE;
	}
	return TRUE;
}

bool CTDCFVT4Dlg::Step_Motor_Move_Left()
{
	bool move_result;
		move_result = testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO2);
	if (!move_result) {
		return FALSE;
	}
	move_result = testbench.IO_To_Open(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO13);
	if (!move_result) {
		return FALSE;
	}
	//MySleep(100);
//	move_result = testbench.IO_To_Open(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO14);
//	if (!move_result) {
//		return FALSE;
//	}
//	MySleep(500);
	move_result = testbench.IO_To_Close(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO14);
	if (!move_result) {
		return FALSE;
	}
	return TRUE;
}

bool CTDCFVT4Dlg::Step_Motor_Move_Stop()
{
	bool move_result;
	move_result = testbench.IO_To_Open(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO13);
	if (!move_result) {
		return FALSE;
	}
	//MySleep(100);
	move_result = testbench.IO_To_Open(get_config.TestBench_GPIO_GPIO_I2C_1, get_config.TestBench_GPIO_GPIO14);
	if (!move_result) {
		return FALSE;
	}
	return TRUE;
}

bool CTDCFVT4Dlg::Pressure_System_Running(float pressure)
{
	while (serial_port_value_float < (get_config.Limit_Pressure_Calibration_Calibration1 - 0.01))  {

	}
	return false;
}

bool CTDCFVT4Dlg::Move_To_Zero_Position()
{
	bool move_result;
	LogUpdate(_T("Move the step motor to Zero position!"));
	move_result = Step_Motor_Move_Right();
	if (!move_result) {
		return FALSE;
	}
	MySleep(25000);
	move_result = Step_Motor_Move_Stop();
	if (!move_result) {
		return FALSE;
	}
	return TRUE;
}

bool CTDCFVT4Dlg::Move_Release()
{
	bool move_result;
	move_result = Step_Motor_Move_Left();
	if (!move_result) {
		return FALSE;
	}
	MySleep(25000);
	move_result = Step_Motor_Move_Stop();
	if (!move_result) {
		return FALSE;
	}
	return TRUE;
}

void CTDCFVT4Dlg::MySleep(DWORD nMilliseconds)
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

int CTDCFVT4Dlg::read_bin_file(CString bin_file_name)
{
	int size = 0x20000;
	//char temp_bin_read_buffer[0x2000];
	char *temp_bin_read_buffer = new char[size + 1];
	temp_bin_read_buffer[0x20000] = '\0';
	//bin_read_buffer[0x20000] = '\0';
	ifstream f(bin_file_name, ios::binary);
	if (!f)
	{
		AfxMessageBox(_T("Cannot Open Original Bin File."));
		return 1;
	}

	//获得文件的大小  
	f.seekg(0, ios::end);
	long fsize = f.tellg();
	if (fsize != (sizeof(bin_read_buffer))) {
		AfxMessageBox(_T("Wrong Original Bin File."));
		return 2;
	}
	//cout << "Original Bin File Length:" << fsize << endl;

	//让文件的指针跑到文件头  
	f.seekg(0, ios::beg);
	//bin_read_buffer.resize(fsize);

	f.read(temp_bin_read_buffer, fsize);
	for (int i = 0; i < fsize; i++) {
		//unsigned char temp_char = unsigned char(temp_bin_read_buffer[i]);
		//bin_read_buffer[i] = temp_char;
		bin_read_buffer[i] = temp_bin_read_buffer[i];
	}
	//		cout << bin_read_buffer[i] << endl;
	//printf("bin_read_buffer:%X.%X\n",i,bin_read_buffer[i]);
	//temp_bin_read_buffer.ReleaseBuffer();
	f.close();
	return 0;
}

int CTDCFVT4Dlg::Write_Calibration_Result()
{
	CString time_temp_str;
	CTime Sub_Test_Start_Time = TimeStamp();
	CString Sub_Test_Start_Time_Text = Sub_Test_Start_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("Start Time:%s"), Sub_Test_Start_Time_Text);
	LogUpdate(time_temp_str);
	int TDC_Distance_Value_Begin_Address = 0x1C000;
	int Distance_Reference_Value_Begin_Address = 0x1E000;
	int TDC_Pressure_Value_Begin_Address = 0x1D000;
	int Pressure_Reference_Value_Begin_Address = 0x1D100;
	int Value_Address_Length = 4;
	int result = read_bin_file(get_config.Limit_FW_Flash_Original_FW);
	if (result == 1) {
		LogUpdate(_T("Cannot Open Original Bin File."));
		return 1;
	}
	if (result == 2) {
		LogUpdate(_T("Wrong Original Bin File."));
		return 1;
	}
	LogUpdate(_T("Read Original Bin File Successed."));
	//Write Distance Calibration Result
	LogUpdate(_T("Distance Calibration Result Matrix:"));
	LogUpdate(_T("Item |-| REF_D_Value_Dec - REF_D_Value_Hex - REF_D_Value_Flash |-| TDC_D_Value_Dec - TDC_D_Value_Hex - TDC_D_Value_Flash |-| Gap_Value |-| Check_Result "));
	for (int i = 0; i < 31; i++) {
		CString temp_str;
		int Distance_Sensor_Int_Value = Distance_Calibration_Result[i + 31];
		int TDC_Distance_Int_Value = Distance_Calibration_Result[i];
		unsigned char Distance_Sensor_Int_Value_High = Distance_Sensor_Int_Value >> 8;
		unsigned char Distance_Sensor_Int_Value_Low = Distance_Sensor_Int_Value & 0xFF;
		unsigned char TDC_Distance_Int_Value_High = TDC_Distance_Int_Value >> 8;
		unsigned char TDC_Distance_Int_Value_Low = TDC_Distance_Int_Value & 0xFF;

		bin_read_buffer[TDC_Distance_Value_Begin_Address + i * 4] = TDC_Distance_Int_Value_Low;
		bin_read_buffer[TDC_Distance_Value_Begin_Address + i * 4 + 1] = TDC_Distance_Int_Value_High;
		bin_read_buffer[TDC_Distance_Value_Begin_Address + i * 4 + 2] = 0x00;
		bin_read_buffer[TDC_Distance_Value_Begin_Address + i * 4 + 3] = 0x00;
		bin_read_buffer[Distance_Reference_Value_Begin_Address + i * 4] = Distance_Sensor_Int_Value_Low;
		bin_read_buffer[Distance_Reference_Value_Begin_Address + i * 4 + 1] = Distance_Sensor_Int_Value_High;
		bin_read_buffer[Distance_Reference_Value_Begin_Address + i * 4 + 2] = 0x00;
		bin_read_buffer[Distance_Reference_Value_Begin_Address + i * 4 + 3] = 0x00;

		int Gap_Value = abs(TDC_Distance_Int_Value - Distance_Sensor_Int_Value);
		CString Gap_Check_Result;
		if (Gap_Value > get_config.Limit_Distance_Calibration_Distance_Limit_Percentage) {
			Gap_Check_Result = _T("FAILED");
		}
		else {
			Gap_Check_Result = _T("PASSED");
		}
		temp_str.Format(_T("%02d: |-| %04d - 0x%04X - 0x%02X%02X |-| %04d - 0x%04X - 0x%02X%02X |-| %04d |-| %s"), i, Distance_Sensor_Int_Value, Distance_Sensor_Int_Value, Distance_Sensor_Int_Value_Low, Distance_Sensor_Int_Value_High, TDC_Distance_Int_Value, TDC_Distance_Int_Value, TDC_Distance_Int_Value_Low, TDC_Distance_Int_Value_High, Gap_Value,Gap_Check_Result);
		LogUpdate(temp_str);
		//if (Gap_Value == 0) {
		//	LogUpdate(_T("Wrong Calibration Result because the gap value is 0."));
		//	return 1;
		//}
		if (Gap_Value > get_config.Limit_Distance_Calibration_Distance_Limit_Percentage) {
			LogUpdate(_T("Calibration Failed because the value Out of limit."));
			return 1;
		}
	}


	//Write Pressure Calibration Result

	if (get_config.SEQUENCE_Pressure_Calibration == 1) {

		LogUpdate(_T("Pressure Calibration Result Matrix:"));
		LogUpdate(_T("Item |-| REF_P_Value_Dec - REF_P_Value_Hex |-| TDC_P_Value_Dec - TDC_P_Value_Hex - TDC_P_Value_Flash  |-| Gap_Value_Dec |-| Check_Result "));
		//int i = 0;
		for (int i = 0; i < 2; i++) {
			CString temp_str;
			int Pressure_Sensor_Int_Value = Pressure_Calibration_Result[i + 2];
			int TDC_Pressure_Int_Value = Pressure_Calibration_Result[i];
			int Pressure_Gap = abs(TDC_Pressure_Int_Value - Pressure_Sensor_Int_Value);
			unsigned char TDC_Pressure_Int_Value_High = TDC_Pressure_Int_Value >> 8;
			unsigned char TDC_Pressure_Int_Value_Low = TDC_Pressure_Int_Value & 0xFF;
			unsigned char Pressure_Sensor_Int_Value_High = Pressure_Sensor_Int_Value >> 8;
			unsigned char Pressure_Sensor_Int_Value_Low = Pressure_Sensor_Int_Value & 0xFF;
			//unsigned char TDC_Pressure_Int_Value_High = TDC_Pressure_Int_Value >> 8;
			//unsigned char TDC_Pressure_Int_Value_Low = TDC_Pressure_Int_Value & 0xFF;
			CString Gap_Check_Result;
			if (Pressure_Gap > get_config.Limit_Pressure_Calibration_Distance_Limit_Percentage) {
				Gap_Check_Result = _T("FAILED");
			}
			else {
				Gap_Check_Result = _T("Passed");
			}
			bin_read_buffer[TDC_Pressure_Value_Begin_Address + i * 4] = TDC_Pressure_Int_Value_Low;
			bin_read_buffer[TDC_Pressure_Value_Begin_Address + i * 4 + 1] = TDC_Pressure_Int_Value_High;
			bin_read_buffer[TDC_Pressure_Value_Begin_Address + i * 4 + 2] = 0x00;
			bin_read_buffer[TDC_Pressure_Value_Begin_Address + i * 4 + 3] = 0x00;
			bin_read_buffer[Pressure_Reference_Value_Begin_Address + i * 4] = Pressure_Sensor_Int_Value_Low;
			bin_read_buffer[Pressure_Reference_Value_Begin_Address + i * 4 + 1] = Pressure_Sensor_Int_Value_High;
			bin_read_buffer[Pressure_Reference_Value_Begin_Address + i * 4 + 2] = 0x00;
			bin_read_buffer[Pressure_Reference_Value_Begin_Address + i * 4 + 3] = 0x00;

			temp_str.Format(_T("%02d: |-| %04d - 0x%04X - 0x%02X%02X |-| %04d - 0x%04X - 0x%02X%02X |-| %04d |-| %s"), i, Pressure_Sensor_Int_Value, Pressure_Sensor_Int_Value, Pressure_Sensor_Int_Value_Low, Pressure_Sensor_Int_Value_High, TDC_Pressure_Int_Value, TDC_Pressure_Int_Value, TDC_Pressure_Int_Value_Low, TDC_Pressure_Int_Value_High, Pressure_Gap, Gap_Check_Result);
			LogUpdate(temp_str);
			if (TDC_Pressure_Int_Value == 0) {
				LogUpdate(_T("Wrong Calibration Result because the value is 0."));
				return 1;
			}
			if (Pressure_Gap >get_config.Limit_Pressure_Calibration_Distance_Limit_Percentage) {
				LogUpdate(_T("Calibration Failed because the value Out of limit."));
				return 1;
			}
		}
	}

	
	
	// Write Data To Bin File;
	CString write_bin_file_name = _T(".\\temp\\Full.bin");
	BOOL file_del = fc.File_Del(write_bin_file_name);
	if (!file_del) {
		LogUpdate(_T("Cannot Delete Old Full Bin File."));
		return 1;
	}
	ofstream output_full(write_bin_file_name, ios::out | ios::binary);
	if (!output_full)
	{
		LogUpdate(_T("Cannot Write Full Bin File."));
		return 1;
	}
	output_full.write((char *)bin_read_buffer, sizeof(bin_read_buffer));
	output_full.close();
	LogUpdate(_T("Write Temp Full Bin File Successed."));

	// Write Full Bin File To TDC By ST-Link;
	LogUpdate(_T("Begin To Write Finally Customer Firmware!"));
	if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
		AfxMessageBox(_T("Please manual Push The Power On Key Till Another Remind Window Pop Up.\r\n 请手工按住开机键直到弹出另一个提示窗口"));
	}
	CString flash_result_str;
	testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO0);
	testbench.Internet_IO_Open(get_config.TestBench_INTERNET_GPIO1);
	MySleep(3000);
	BOOL flash_result_int = stlink.Flash(write_bin_file_name, get_config.Limit_FW_Flash_Wire_Begin_Address, TRUE);
	if (flash_result_int) {
		LogUpdate(_T("Flash Command Running Successed."));
	}
	else {
		LogUpdate(_T("Flash Command Running Failed."));
		return 1;
	}
	flash_result_str = stlink.Read_exe_Result(_T("Verification"), 15, 2);
	BOOL flash_result = stlink.Reset();
	if (flash_result_int) {
		LogUpdate(_T("MCU Reset Successed."));
	}
	else {
		LogUpdate(_T("MCU Rest Failed."));
	}
	flash_result_int = stlink.Run();
	if (flash_result_int) {
		LogUpdate(_T("MCU Running Successed."));
	}
	else {
		LogUpdate(_T("MCU Running Failed."));
		return 1;
	}
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO0);
	testbench.Internet_IO_Init(get_config.TestBench_INTERNET_GPIO1);
	//stlink.Run();
	if (get_config.Limit_FW_Flash_Manual_Power_On == 1) {
		AfxMessageBox(_T("Please Release The Power On Key.\r\n 请释放开机键!"));
	}
	CTime Sub_Test_End_Time = TimeStamp();
	CString Sub_Test_End_Time_Text = Sub_Test_End_Time.Format(_T("%Y.%m.%d %H.%M.%S"));
	time_temp_str.Format(_T("End Time:%s"), Sub_Test_End_Time_Text);
	LogUpdate(time_temp_str);
	time_temp_str.Format(_T("Duration: %d"), Sub_Test_End_Time - Sub_Test_Start_Time);
	LogUpdate(time_temp_str);
	if (flash_result_str != _T("OK")) {
		LogUpdate(_T("STLink Flash Command Running Failed."));
		return 1;
	}
	else {
		return 0;
	}
}


void CTDCFVT4Dlg::OnMaintenanceTestbench()
{
	CMaintenanceTestBenchDlg  MaintenanceTestBench;
	MaintenanceTestBench.DoModal();
	// TODO: 在此添加命令处理程序代码
}


void CAboutDlg::OnHelpAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
	// TODO: 在此添加命令处理程序代码
}


void CTDCFVT4Dlg::OnHelpAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
	// TODO: 在此添加命令处理程序代码
}


void CTDCFVT4Dlg::OnHelpUsermanual()
{
	//CString path;
	//char path[MAX_PATH];
	//GetCurrentDirectory(MAX_PATH, GetModuleFileNameExA(path));
	CString strPath = _T(".\\Document");
	strPath += "\\TDC FVT4 Test Station Setup Manual Ver1.0.pdf";
	ShellExecute(NULL, _T("Open"), strPath, NULL, NULL, SW_SHOW);
	// TODO: 在此添加命令处理程序代码
}

void CTDCFVT4Dlg::Log_File_Finally_Update(CString test_result, CString time)
{
	CString str,test_result_str,time_str;
	test_result_str.Format(_T("T%s\r\n"), test_result);
	time_str.Format(_T("]%s\r\n"), time);
	CStdioFile logfile_read,logfile_write;
	DWORD dwPos_result = 0;
	DWORD dwPos_time = 0;
	LPCTSTR pszSrc_result = _T("T");
	LPCTSTR pszSrc_time = _T("]");
	logfile_read.Open(Log_File_Name_Full, CFile::modeRead);
	int line = 0;
	while (logfile_read.ReadString(str))
	{
		if (line == 2) {
			dwPos_result = (DWORD)logfile_read.GetPosition() - (_tcslen(pszSrc_result) + _tcslen(_T("\r\n")));
		}
		if (line == 14) {
			dwPos_time = (DWORD)logfile_read.GetPosition() - (_tcslen(pszSrc_time) + _tcslen(_T("\r\n")));
			break;
		}
		line++;
	}
	logfile_read.Close();
	logfile_write.Open(Log_File_Name_Full, CFile::modeWrite);
	logfile_write.Seek(dwPos_result,CFile::begin);
	logfile_write.WriteString(test_result_str);
	logfile_write.Seek(dwPos_time, CFile::begin);
	logfile_write.WriteString(time_str);
	logfile_write.Close();
	logfile_write.Open(Log_File_Name_Full_Copy, CFile::modeWrite);
	logfile_write.Seek(dwPos_result, CFile::begin);
	logfile_write.WriteString(test_result_str);
	logfile_write.Seek(dwPos_time, CFile::begin);
	logfile_write.WriteString(time_str);
	logfile_write.Close();
}
