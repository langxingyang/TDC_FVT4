// TDC_FVT4_CONFIG_MAINdlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TDC_FVT4.h"
#include "TDC_FVT4_CONFIG_MAINdlg.h"
#include "afxdialogex.h"
#include "IniFile.h"
#include "File_Check.h"


//定义全局常量
#define MAIN_CONFIG _T(".\\Config\\Main.ini")


// CTDC_FVT4_CONFIG_MAINdlg 对话框
CIniFile ini;
File_Check filecheck;
//CFileFind finder;

IMPLEMENT_DYNAMIC(CTDC_FVT4_CONFIG_MAINdlg, CDialogEx)

CTDC_FVT4_CONFIG_MAINdlg::CTDC_FVT4_CONFIG_MAINdlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONFIG_MAIN, pParent)
	, config_main_test_name(_T(""))
	, config_main_software_revision(_T(""))
	, config_main_trace_path(_T(""))
	, config_main_trace_path_copy(_T(""))
	, config_main_customer(_T(""))
	, config_main_product_name(_T(""))
	, config_main_barcode_length(0)
	, config_main_factory(_T(""))
	, config_main_assembly_number(_T(""))
	, config_main_site(_T(""))
	, config_production_line(_T(""))
	, config_main_fw_revision(_T(""))
	, config_main_test_station(_T(""))
	, config_main_hostname(_T(""))
	, iRepeatedCycle(0)
	, bRadioRepeatedEnable(FALSE)
	, config_main_fixtureid(_T(""))
{

	EnableAutomation();

}

CTDC_FVT4_CONFIG_MAINdlg::~CTDC_FVT4_CONFIG_MAINdlg()
{
}

void CTDC_FVT4_CONFIG_MAINdlg::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。  基类将自动
	// 删除该对象。  在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CDialogEx::OnFinalRelease();
}

void CTDC_FVT4_CONFIG_MAINdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEST_NAME, config_main_test_name);
	DDV_MaxChars(pDX, config_main_test_name, 256);
	DDX_Text(pDX, IDC_SOFTWARE_REVISION, config_main_software_revision);
	DDX_Text(pDX, IDC_TRACE_PATH, config_main_trace_path);
	DDX_Text(pDX, IDC_TRACE_PATH_COPY, config_main_trace_path_copy);
	DDX_Text(pDX, IDC_CUSTOMER, config_main_customer);
	DDX_Text(pDX, IDC_PRODUCT_NAME, config_main_product_name);
	DDX_Text(pDX, IDC_BARCODE_LENGTH, config_main_barcode_length);
	DDV_MinMaxInt(pDX, config_main_barcode_length, 1, 20);
	DDX_Text(pDX, IDC_FACTORY, config_main_factory);
	DDX_Text(pDX, IDC_ASSEMBLY_NUMBER, config_main_assembly_number);
	DDX_Text(pDX, IDC_ASSEMBLY_REVISION, config_main_assembly_revision);
	DDX_Text(pDX, IDC_SITE, config_main_site);
	DDX_Text(pDX, IDC_LINE, config_production_line);
	DDX_Text(pDX, IDC_FW_REVISION, config_main_fw_revision);
	DDX_Text(pDX, IDC_TEST_Station, config_main_test_station);
	DDX_Text(pDX, IDC_HOSTNAME, config_main_hostname);
	DDX_Text(pDX, IDC_REPEATED_CYCLE, iRepeatedCycle);
	DDV_MinMaxInt(pDX, iRepeatedCycle, 1, 10000);
	DDX_Radio(pDX, IDC_REPEATED_ENABLE, bRadioRepeatedEnable);
	DDX_Text(pDX, IDC_FIXTUREID, config_main_fixtureid);
}


BEGIN_MESSAGE_MAP(CTDC_FVT4_CONFIG_MAINdlg, CDialogEx)
	//ON_COMMAND(ID_CONFIG_MAIN, &CTDC_FVT4_CONFIG_MAINdlg::OnConfigMain)
	ON_BN_CLICKED(IDOK, &CTDC_FVT4_CONFIG_MAINdlg::OnBnClickedOk)
	//ON_BN_CLICKED(ID_SAVE, &CTDC_FVT4_CONFIG_MAINdlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_REPEATED_ENABLE, &CTDC_FVT4_CONFIG_MAINdlg::OnBnClickedRepeatedEnable)
	ON_BN_CLICKED(IDC_REPEATED_DISABLE, &CTDC_FVT4_CONFIG_MAINdlg::OnBnClickedRepeatedDisable)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTDC_FVT4_CONFIG_MAINdlg, CDialogEx)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ITDC_FVT4_CONFIG_MAINdlg 支持
//  以支持来自 VBA 的类型安全绑定。  此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {72C20AC1-1B4D-4BF7-A1CA-FD5E617E1E99}
static const IID IID_ITDC_FVT4_CONFIG_MAINdlg =
{ 0x72C20AC1, 0x1B4D, 0x4BF7, { 0xA1, 0xCA, 0xFD, 0x5E, 0x61, 0x7E, 0x1E, 0x99 } };

BEGIN_INTERFACE_MAP(CTDC_FVT4_CONFIG_MAINdlg, CDialogEx)
	INTERFACE_PART(CTDC_FVT4_CONFIG_MAINdlg, IID_ITDC_FVT4_CONFIG_MAINdlg, Dispatch)
END_INTERFACE_MAP()


// CTDC_FVT4_CONFIG_MAINdlg 消息处理程序

/*
void CTDC_FVT4_CONFIG_MAINdlg::OnConfigMain()
{
	// TODO: 在此添加命令处理程序代码
	CTDC_FVT4_CONFIG_MAINdlg  Config_Main_Dlg;
	Config_Main_Dlg.DoModal();

}
*/


BOOL CTDC_FVT4_CONFIG_MAINdlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	BOOL Ini_File_Check_Result = filecheck.IsFileExist(MAIN_CONFIG);
	if (Ini_File_Check_Result == FALSE) {
		CString msg;
		//CString exe_path;
		//exe_path.Format("%s",GetModuleFileName());
		msg.Format(_T("No Found Configuration File: %s!\nDo You Want to Creat This File?\nPress 'YES' to Creat New INI File. Press 'NO' to Cancel and Exit."), MAIN_CONFIG);
		int msg_feedback = AfxMessageBox(msg, MB_YESNO|MB_ICONSTOP);
		if (msg_feedback == IDYES) {
			ini.SetFileName(MAIN_CONFIG);
			//ini.~CIniFile();
			BOOL write_result = ini.SetProfileString(_T("MAIN"),_T("Test_Name"),_T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Software_Revision"), _T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Trace_Path"), _T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Trace_Path_Copy"), _T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Customer"), _T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Production_Name"), _T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Barcode_Length"), _T("0"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Factory"), _T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Assembly_Number"), _T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Assembly_Revision"), _T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Site"), _T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Production_Line"), _T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("FW_Revision"), _T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Test_Station"), _T("No value"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Hostname"), _T("No value"));
			write_result = ini.SetProfileString(_T("Repeated_Status"), _T("Repeated_Test"), _T("0"));
			write_result = ini.SetProfileString(_T("Repeated_Status"), _T("Repeated_Cycle"), _T("1"));
			write_result = ini.SetProfileString(_T("MAIN"), _T("Fixture_ID"), _T("No value"));

		}
		if (msg_feedback == IDNO) {
			EndDialog(IDD_CONFIG_MAIN);
			//return FALSE;
		}

	} 

	ini.SetFileName(MAIN_CONFIG);
	int ini_config_read_result_0 = ini.GetProfileStringW(_T("MAIN"), _T("Test_Name"), config_main_test_name);
	int ini_config_read_result_1 = ini.GetProfileStringW(_T("MAIN"), _T("Software_Revision"), config_main_software_revision);
	int ini_config_read_result_2 = ini.GetProfileStringW(_T("MAIN"), _T("Trace_Path"), config_main_trace_path);
	int ini_config_read_result_3 = ini.GetProfileStringW(_T("MAIN"), _T("Trace_Path_Copy"), config_main_trace_path_copy);
	int ini_config_read_result_4 = ini.GetProfileStringW(_T("MAIN"), _T("Customer"), config_main_customer);
	int ini_config_read_result_5 = ini.GetProfileStringW(_T("MAIN"), _T("Production_Name"), config_main_product_name);
	int ini_config_read_result_6 = ini.GetProfileStringW(_T("MAIN"), _T("Factory"), config_main_factory);
	int ini_config_read_result_7 = ini.GetProfileStringW(_T("MAIN"), _T("Assembly_Number"), config_main_assembly_number);
	int ini_config_read_result_8 = ini.GetProfileStringW(_T("MAIN"), _T("Assembly_Revision"), config_main_assembly_revision);
	int ini_config_read_result_9 = ini.GetProfileStringW(_T("MAIN"), _T("Site"), config_main_site);
	int ini_config_read_result_10 = ini.GetProfileStringW(_T("MAIN"), _T("Production_Line"), config_production_line);
	int ini_config_read_result_11 = ini.GetProfileStringW(_T("MAIN"), _T("FW_Revision"), config_main_fw_revision);
	int ini_config_read_result_12 = ini.GetProfileStringW(_T("MAIN"), _T("Test_Station"), config_main_test_station);
	int ini_config_read_result_13 = ini.GetProfileStringW(_T("MAIN"), _T("Hostname"), config_main_hostname);
	int ini_config_read_result_14 = ini.GetProfileStringW(_T("MAIN"), _T("Fixture_ID"), config_main_fixtureid);
	config_main_barcode_length = ini.GetProfileInt(_T("MAIN"), _T("Barcode_Length"));
	bRadioRepeatedEnable = ini.GetProfileIntW(_T("Repeated_Status"), _T("Repeated_Test"));
	iRepeatedCycle = ini.GetProfileIntW(_T("Repeated_Status"), _T("Repeated_Cycle"));
	GetDlgItem(IDC_TEST_NAME)->SetWindowText(config_main_test_name);
	GetDlgItem(IDC_SOFTWARE_REVISION)->SetWindowText(config_main_software_revision);
	GetDlgItem(IDC_TRACE_PATH)->SetWindowText(config_main_trace_path);
	GetDlgItem(IDC_TRACE_PATH_COPY)->SetWindowText(config_main_trace_path_copy);
	GetDlgItem(IDC_CUSTOMER)->SetWindowText(config_main_customer);
	GetDlgItem(IDC_PRODUCT_NAME)->SetWindowText(config_main_product_name);
	GetDlgItem(IDC_FACTORY)->SetWindowText(config_main_factory);
	GetDlgItem(IDC_ASSEMBLY_NUMBER)->SetWindowText(config_main_assembly_number);
	GetDlgItem(IDC_ASSEMBLY_REVISION)->SetWindowText(config_main_assembly_revision);
	GetDlgItem(IDC_SITE)->SetWindowText(config_main_site);
	GetDlgItem(IDC_LINE)->SetWindowText(config_production_line);
	GetDlgItem(IDC_FW_REVISION)->SetWindowText(config_main_fw_revision);
	GetDlgItem(IDC_TEST_Station)->SetWindowText(config_main_test_station);
	GetDlgItem(IDC_HOSTNAME)->SetWindowText(config_main_hostname);
	GetDlgItem(IDC_FIXTUREID)->SetWindowText(config_main_fixtureid);
	CString config_main_barcode_length_txt;
	config_main_barcode_length_txt.Format(_T("%d"), config_main_barcode_length);
	GetDlgItem(IDC_BARCODE_LENGTH)->SetWindowText(config_main_barcode_length_txt);
	CString iRepeatedCycle_text;
	iRepeatedCycle_text.Format(_T("%d"), iRepeatedCycle);
	GetDlgItem(IDC_REPEATED_CYCLE)->SetWindowText(iRepeatedCycle_text);

	if (bRadioRepeatedEnable == TRUE) {
		((CButton *)GetDlgItem(IDC_REPEATED_ENABLE))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_REPEATED_DISABLE))->SetCheck(FALSE);
	}
	else {
		((CButton *)GetDlgItem(IDC_REPEATED_ENABLE))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_REPEATED_DISABLE))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_REPEATED_CYCLE))->EnableWindow(0);

	}



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CTDC_FVT4_CONFIG_MAINdlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	//config_main_barcode_length = ini.GetProfileInt(_T("MAIN"), _T("Barcode_Length"));
	GetDlgItem(IDC_TEST_NAME)->GetWindowText(config_main_test_name);
	GetDlgItem(IDC_SOFTWARE_REVISION)->GetWindowText(config_main_software_revision);
	GetDlgItem(IDC_TRACE_PATH)->GetWindowText(config_main_trace_path);
	GetDlgItem(IDC_TRACE_PATH_COPY)->GetWindowText(config_main_trace_path_copy);
	GetDlgItem(IDC_CUSTOMER)->GetWindowText(config_main_customer);
	GetDlgItem(IDC_PRODUCT_NAME)->GetWindowText(config_main_product_name);
	GetDlgItem(IDC_FACTORY)->GetWindowText(config_main_factory);
	GetDlgItem(IDC_ASSEMBLY_NUMBER)->GetWindowText(config_main_assembly_number);
	GetDlgItem(IDC_ASSEMBLY_REVISION)->GetWindowText(config_main_assembly_revision);
	GetDlgItem(IDC_SITE)->GetWindowText(config_main_site);
	GetDlgItem(IDC_LINE)->GetWindowText(config_production_line);
	GetDlgItem(IDC_FW_REVISION)->GetWindowText(config_main_fw_revision);
	GetDlgItem(IDC_TEST_Station)->GetWindowText(config_main_test_station);
	GetDlgItem(IDC_HOSTNAME)->GetWindowText(config_main_hostname);
	GetDlgItem(IDC_FIXTUREID)->GetWindowText(config_main_fixtureid);
	//GetDlgItem(IDC_BARCODE_LENGTH)->GetDlgItemInt(config_main_barcode_length);
	config_main_barcode_length = GetDlgItemInt(IDC_BARCODE_LENGTH , NULL, FALSE);
	bRadioRepeatedEnable = GetDlgItemInt(IDC_REPEATED_ENABLE, NULL, FALSE);
	iRepeatedCycle = GetDlgItemInt(IDC_REPEATED_CYCLE, NULL, FALSE);

	ini.SetFileName(MAIN_CONFIG);
	int ini_config_write_result_0 = ini.SetProfileString(_T("MAIN"), _T("Test_Name"), config_main_test_name);
	int ini_config_write_result_1 = ini.SetProfileString(_T("MAIN"), _T("Software_Revision"), config_main_software_revision);
	int ini_config_write_result_2 = ini.SetProfileString(_T("MAIN"), _T("Trace_Path"), config_main_trace_path);
	int ini_config_write_result_3 = ini.SetProfileString(_T("MAIN"), _T("Trace_Path_Copy"), config_main_trace_path_copy);
	int ini_config_write_result_4 = ini.SetProfileString(_T("MAIN"), _T("Customer"), config_main_customer);
	int ini_config_write_result_5 = ini.SetProfileString(_T("MAIN"), _T("Production_Name"), config_main_product_name);
	int ini_config_write_result_6 = ini.SetProfileString(_T("MAIN"), _T("Factory"), config_main_factory);
	int ini_config_write_result_7 = ini.SetProfileString(_T("MAIN"), _T("Assembly_Number"), config_main_assembly_number);
	int ini_config_write_result_8 = ini.SetProfileString(_T("MAIN"), _T("Assembly_Revision"), config_main_assembly_revision);
	int ini_config_write_result_9 = ini.SetProfileString(_T("MAIN"), _T("Site"), config_main_site);
	int ini_config_write_result_10 = ini.SetProfileString(_T("MAIN"), _T("Production_Line"), config_production_line);
	int ini_config_write_result_11 = ini.SetProfileString(_T("MAIN"), _T("FW_Revision"), config_main_fw_revision);
	int ini_config_write_result_12 = ini.SetProfileString(_T("MAIN"), _T("Test_Station"), config_main_test_station);
	int ini_config_write_result_13 = ini.SetProfileString(_T("MAIN"), _T("Hostname"), config_main_hostname);
	int ini_config_write_result_14 = ini.SetProfileString(_T("MAIN"), _T("Fixture_ID"), config_main_fixtureid);
	//CString config_main_barcode_length_text;
	//config_main_barcode_length_text.Format(_T("%d"), config_main_barcode_length);
	//int ini_config_write_result_14 = ini.SetProfileString(_T("MAIN"), _T("Barcode_Length"), config_main_barcode_length_text
	int ini_config_write_result_15 = ini.SetProfileInt(_T("MAIN"), _T("Barcode_Length"), config_main_barcode_length);
	ini.SetProfileInt(_T("Repeated_Status"), _T("Repeated_Test"), bRadioRepeatedEnable);
	ini.SetProfileInt(_T("Repeated_Status"), _T("Repeated_Cycle"), iRepeatedCycle);

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
		(ini_config_write_result_15 == 0)) {
		AfxMessageBox(_T("Configuration File Write Error."), MB_OK | MB_ICONSTOP);
	}
	else {
		AfxMessageBox(_T("Configuration File Write Success."), MB_OK | MB_ICONINFORMATION);
	}

}


void CTDC_FVT4_CONFIG_MAINdlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	config_main_barcode_length = ini.GetProfileInt(_T("MAIN"), _T("Barcode_Length"));
	GetDlgItem(IDC_TEST_NAME)->GetWindowText(config_main_test_name);
	GetDlgItem(IDC_SOFTWARE_REVISION)->GetWindowText(config_main_software_revision);
	GetDlgItem(IDC_TRACE_PATH)->GetWindowText(config_main_trace_path);
	GetDlgItem(IDC_TRACE_PATH_COPY)->GetWindowText(config_main_trace_path_copy);
	GetDlgItem(IDC_CUSTOMER)->GetWindowText(config_main_customer);
	GetDlgItem(IDC_PRODUCT_NAME)->GetWindowText(config_main_product_name);
	GetDlgItem(IDC_FACTORY)->GetWindowText(config_main_factory);
	GetDlgItem(IDC_ASSEMBLY_NUMBER)->GetWindowText(config_main_assembly_number);
	GetDlgItem(IDC_ASSEMBLY_REVISION)->GetWindowText(config_main_assembly_revision);
	GetDlgItem(IDC_SITE)->GetWindowText(config_main_site);
	GetDlgItem(IDC_LINE)->GetWindowText(config_production_line);
	GetDlgItem(IDC_FW_REVISION)->GetWindowText(config_main_fw_revision);
	GetDlgItem(IDC_TEST_Station)->GetWindowText(config_main_test_station);
	GetDlgItem(IDC_HOSTNAME)->GetWindowText(config_main_hostname);
	GetDlgItem(IDC_FIXTUREID)->GetWindowText(config_main_fixtureid);
	//GetDlgItem(IDC_BARCODE_LENGTH)->GetDlgItemInt(config_main_barcode_length);
	config_main_barcode_length = GetDlgItemInt(IDC_BARCODE_LENGTH, NULL, FALSE);

	ini.SetFileName(MAIN_CONFIG);
	int ini_config_write_result_0 = ini.SetProfileString(_T("MAIN"), _T("Test_Name"), config_main_test_name);
	int ini_config_write_result_1 = ini.SetProfileString(_T("MAIN"), _T("Software_Revision"), config_main_software_revision);
	int ini_config_write_result_2 = ini.SetProfileString(_T("MAIN"), _T("Trace_Path"), config_main_trace_path);
	int ini_config_write_result_3 = ini.SetProfileString(_T("MAIN"), _T("Trace_Path_Copy"), config_main_trace_path_copy);
	int ini_config_write_result_4 = ini.SetProfileString(_T("MAIN"), _T("Customer"), config_main_customer);
	int ini_config_write_result_5 = ini.SetProfileString(_T("MAIN"), _T("Production_Name"), config_main_product_name);
	int ini_config_write_result_6 = ini.SetProfileString(_T("MAIN"), _T("Factory"), config_main_factory);
	int ini_config_write_result_7 = ini.SetProfileString(_T("MAIN"), _T("Assembly_Number"), config_main_assembly_number);
	int ini_config_write_result_8 = ini.SetProfileString(_T("MAIN"), _T("Assembly_Revision"), config_main_assembly_revision);
	int ini_config_write_result_9 = ini.SetProfileString(_T("MAIN"), _T("Site"), config_main_site);
	int ini_config_write_result_10 = ini.SetProfileString(_T("MAIN"), _T("Production_Line"), config_production_line);
	int ini_config_write_result_11 = ini.SetProfileString(_T("MAIN"), _T("FW_Revision"), config_main_fw_revision);
	int ini_config_write_result_12 = ini.SetProfileString(_T("MAIN"), _T("Test_Station"), config_main_test_station);
	int ini_config_write_result_13 = ini.SetProfileString(_T("MAIN"), _T("Hostname"), config_main_hostname);
	int ini_config_write_result_14 = ini.SetProfileString(_T("MAIN"), _T("Fixture_ID"), config_main_fixtureid);
	//CString config_main_barcode_length_text;
	//config_main_barcode_length_text.Format(_T("%d"), config_main_barcode_length);
	//int ini_config_write_result_14 = ini.SetProfileString(_T("MAIN"), _T("Barcode_Length"), config_main_barcode_length_text
	int ini_config_write_result_15 = ini.SetProfileInt(_T("MAIN"), _T("Barcode_Length"), config_main_barcode_length);

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
		(ini_config_write_result_15 == 0)) {
		AfxMessageBox(_T("Configuration File Write Error."), MB_OK | MB_ICONSTOP);
	}
	else {
		AfxMessageBox(_T("Configuration File Write Success."), MB_OK | MB_ICONINFORMATION);
	}
}


void CTDC_FVT4_CONFIG_MAINdlg::OnBnClickedRepeatedEnable()
{
	// TODO: 在此添加控件通知处理程序代码
	bRadioRepeatedEnable = TRUE;
	GetDlgItem(IDC_REPEATED_CYCLE)->EnableWindow(bRadioRepeatedEnable);
}


void CTDC_FVT4_CONFIG_MAINdlg::OnBnClickedRepeatedDisable()
{
	// TODO: 在此添加控件通知处理程序代码
	bRadioRepeatedEnable = FALSE;
	GetDlgItem(IDC_REPEATED_CYCLE)->EnableWindow(bRadioRepeatedEnable);
}
