
// TDC_FVT4Dlg.h: 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
//#include <vector>

#define RED_REF  RGB(255,0,0)
#define GREEN_REF  RGB(0,255,0)
#define BLUE_REF RGB(0,255,255)
#define YELLOW_REF RGB(255,255,0)
#define WHITE_REF RGB(255,255,255)
#define BLACK_REF RGB(0,0,0)
#define WM_UPDATE_TESTRESULT (WM_USER + 200)

// CTDCFVT4Dlg 对话框
class CTDCFVT4Dlg : public CDialog
{
// 构造
public:
	CTDCFVT4Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TDC_FVT4_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	static void MySleep(DWORD nMilliseconds);
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnReceiveStr(WPARAM str, LPARAM commInfo);
	afx_msg LRESULT OnReceiveTestResult(WPARAM test_result, LPARAM test_step);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnConfigMain();
	afx_msg void OnConfigEquipment();
	afx_msg void OnConfigSequence();
	// 图片控件以显示公司LOG在标题中
	CStatic bmp_title;
	// 变量 START 
	CButton eButtonStart;
	// 变量 STOP 按键
	CButton eButtonStop;
	// 程序标题
	CString c_edittitle;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	// //标题 控件变量
	CEdit eEditTitle;
	// 运行状态控件变量
	CEdit eEditRunningStatus;
	// 进度条控件变量
	CProgressCtrl eProgressBar;
	// Log控件变量
	CEdit eEditLog;
	// 测试总数控件变量
	CEdit eEditTestTotalQTY;
	// 测试PASS控件变量
	CEdit eEditTestPassQTY;
	// 测试FAIL控件变量
	CEdit eEditTestFailQTY;
	// 测试FPY控件变量
	CEdit eEditTestFPY;
	// 重复测试次数控件变量
//	CEdit eEditRepeatedCycle;
	// 重复次数提示文件控件变量：IDC_STATIC13
//	CStatic eStaticRepeatedCycle;
	// 序列号提示文本控件：ICT_STATIC3
	CStatic eStaticSerialNo;
	// 测试总数文本提示控件变量：IDC_STATIC8
	CStatic eStaticTestTotal;
	// 测试PASS文本提示控件变量：IDC_STATIC9
	CStatic eStaticTestPass;
	// 测试FAIL文本提示控件变量：IDC_STATIC10
	CStatic eStaticTestFail;
	// 测试FPY文本提示控件变量：IDC_STATIC11
	CStatic eStaticTestFPY;
	// 序列号输入框控件变量
	CEdit eEditSerialNo;
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	CString sRunningStatus_Title; //运行状态第一行 
	CString sRunningStatus_Sub;//运行状态第二行
	CString sRunningStatus_Result;
	int test_total = 0;
	int test_pass = 0;
	int test_fail = 0;
	float test_fpy = 0;

	afx_msg void RunningStatusUpdate();
	afx_msg void FPY_Update();
	afx_msg int FPY_cal();
	afx_msg void LogUpdate(CString str);
	afx_msg CTime TimeStamp();
	//afx_msg int Test_Sequence();

	CStdioFile log_file;

	CString Log_File_Name_First;
	CString Log_Expanded_Name;
	CString Log_File_Name;
	CString Log_File_Name_Full;
	CString Log_File_Name_Full_Copy;
	CString Serial_No;
	CString Test_Start_Time_Text;
	CString Current_Time_Text;
	CTime Test_Start_Time;
	CTime Current_Time;
	CString Serial_Port_Read_Result;
	double serial_port_value_float;
	int Serial_Port_Value_Int;
	CString BT_Feedback;
	CString Slave_BT;
	int serial_receive_str_count;



private:
	CTDCFVT4Dlg * dlg;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg int Serial_Open(CString port_str, int SelBaudRate);
	afx_msg int Serial_Measurement(char command[]);
	void SleepEx(int value = 10);

	//测试线程 全局变量
	CWinThread *m_pTestSequence;
	HANDLE m_hWakeupEvent;
	static UINT TestThread(LPVOID pParam);


	//定义测试步骤
	afx_msg int Test_Environment_Check();
	afx_msg int Equipment_Check();
	afx_msg int FW_Flash();
	afx_msg int BlueTooth_Check();
	afx_msg int BlueTooth_Connect();
	afx_msg int RFID_Check();
	afx_msg int Button_Check();
	afx_msg int Charging_Check();
	afx_msg int LCD_Check();
	afx_msg int Buzz_Check();
	afx_msg int Distance_Calibration();
	afx_msg int Distance_Measurement();
	afx_msg int Pressure_Calibration();
	afx_msg int Pressure_Measurement();
	afx_msg int Write_Calibration_Result();
	afx_msg int Close_Test();
	afx_msg void Log_Title();
	BOOL m_SetEvent(void);
	int processbar_value;
	int Pressure_Calibration_Running_Status; //0 = Running 1 = Pass 2 = Fail
	int Pressure_Measurement_Running_Status; //0 = Running 1 = Pass 2 = Fail
	int Distance_Calibration_Running_Status; //0 = Running 1 = Pass 2 = Fail
	int Distance_Measurement_Running_Status; //0 = Running 1 = Pass 2 = Fail
	int Distance_Calibration_Running_Count = 0;
	int Distance_Measurement_Running_Count = 0;
	int str_count = 0 ;
	int BT_Serial_Feedback_Status;
	CString TDC_Feedback;


	//胎纹深度传感器校验-步进马达控制
	afx_msg bool Step_Motor_Move_Left();
	afx_msg bool Step_Motor_Move_Right();
	afx_msg bool Step_Motor_Move_Stop();
	afx_msg bool Pressure_System_Running(float pressure);
	afx_msg bool Move_To_Zero_Position();
	bool CTDCFVT4Dlg::Move_Release();
	bool CTDCFVT4Dlg::Serial_Open_Without_Monitor(CString port_str, int SelBaudRate);
	int CTDCFVT4Dlg::read_bin_file(CString bin_file_name);
	unsigned char bin_read_buffer[0x20000];
	
	afx_msg float TDC_Get_Distance();
	afx_msg float TDC_Get_Pressure();
	afx_msg CString TDC_Get_RFID();
	afx_msg bool TDC_Reset();
	afx_msg bool TDC_Zero_Position();
	afx_msg bool TDC_15_Position();
	afx_msg bool TDC_30_Position();
	afx_msg bool TDC_Position(int Position);
	afx_msg void OnMaintenanceTestbench();
	int Distance_Calibration_Result[62];
	int Pressure_Calibration_Result[4];
	afx_msg void OnHelpAbout();
	afx_msg void OnHelpUsermanual();
	afx_msg void Log_File_Finally_Update(CString test_result, CString time);
};
//};



