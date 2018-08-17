#pragma once
#include "afxwin.h"


// CTDC_FVT4_CONFIG_MAINdlg 对话框

class CTDC_FVT4_CONFIG_MAINdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTDC_FVT4_CONFIG_MAINdlg)

public:
	CTDC_FVT4_CONFIG_MAINdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTDC_FVT4_CONFIG_MAINdlg();

	virtual void OnFinalRelease();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	// 配置文件Main.ini中的参数值Test_Name
	CString config_main_test_name;
	// 配置文件main.ini中的参数Software_Revision值
	CString config_main_software_revision;
	// 配置文件main.ini中的参数Trace_Path值
	CString config_main_trace_path;
	// 配置文件main.ini中的参数Trace_Path_Copy值
	CString config_main_trace_path_copy;
	// 配置文件main.ini中的参数Customer值
	CString config_main_customer;
	// 配置文件main.ini中的参数Product_Name值
	CString config_main_product_name;
	// 配置文件main.ini中的参数Barcode_Length值,Min 1,Max 20
	int config_main_barcode_length;
	// 配置文件main.ini中的参数Factory值
	CString config_main_factory;
	// 配置文件main.ini中的参数Assembly_Number值
	CString config_main_assembly_number;
	// 配置文件main.ini中的参数Assembly_Revision值
	CString config_main_assembly_revision;
	// 配置文件main.ini中的参数Site值
	CString config_main_site;
	// 配置文件main.ini中的参数Production_Line值
	CString config_production_line;
	// 配置文件main.ini中的参数FW_Revision值
	CString config_main_fw_revision;
	// 配置文件main.ini中的参数Test_Station值
	CString config_main_test_station;
	// 配置文件main.ini中的参数Hostname值
	CString config_main_hostname;
	// 配置文件main.ini中的参数Fixtureid值
	CString config_main_fixtureid;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSave();
	// 重复测试次数，1-10000
	int iRepeatedCycle;
	// 重复测试 ENABLE/DISABLE 布尔变量
	BOOL bRadioRepeatedEnable;
	afx_msg void OnBnClickedRepeatedEnable();
	afx_msg void OnBnClickedRepeatedDisable();

};
