#pragma once
#include "afxwin.h"


// CTDC_FVT4_CONFIG_MAINdlg �Ի���

class CTDC_FVT4_CONFIG_MAINdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTDC_FVT4_CONFIG_MAINdlg)

public:
	CTDC_FVT4_CONFIG_MAINdlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTDC_FVT4_CONFIG_MAINdlg();

	virtual void OnFinalRelease();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
public:
	// �����ļ�Main.ini�еĲ���ֵTest_Name
	CString config_main_test_name;
	// �����ļ�main.ini�еĲ���Software_Revisionֵ
	CString config_main_software_revision;
	// �����ļ�main.ini�еĲ���Trace_Pathֵ
	CString config_main_trace_path;
	// �����ļ�main.ini�еĲ���Trace_Path_Copyֵ
	CString config_main_trace_path_copy;
	// �����ļ�main.ini�еĲ���Customerֵ
	CString config_main_customer;
	// �����ļ�main.ini�еĲ���Product_Nameֵ
	CString config_main_product_name;
	// �����ļ�main.ini�еĲ���Barcode_Lengthֵ,Min 1,Max 20
	int config_main_barcode_length;
	// �����ļ�main.ini�еĲ���Factoryֵ
	CString config_main_factory;
	// �����ļ�main.ini�еĲ���Assembly_Numberֵ
	CString config_main_assembly_number;
	// �����ļ�main.ini�еĲ���Assembly_Revisionֵ
	CString config_main_assembly_revision;
	// �����ļ�main.ini�еĲ���Siteֵ
	CString config_main_site;
	// �����ļ�main.ini�еĲ���Production_Lineֵ
	CString config_production_line;
	// �����ļ�main.ini�еĲ���FW_Revisionֵ
	CString config_main_fw_revision;
	// �����ļ�main.ini�еĲ���Test_Stationֵ
	CString config_main_test_station;
	// �����ļ�main.ini�еĲ���Hostnameֵ
	CString config_main_hostname;
	// �����ļ�main.ini�еĲ���Fixtureidֵ
	CString config_main_fixtureid;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSave();
	// �ظ����Դ�����1-10000
	int iRepeatedCycle;
	// �ظ����� ENABLE/DISABLE ��������
	BOOL bRadioRepeatedEnable;
	afx_msg void OnBnClickedRepeatedEnable();
	afx_msg void OnBnClickedRepeatedDisable();

};
