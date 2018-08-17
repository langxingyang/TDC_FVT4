#pragma once


// CCONFIG_EQUIPMENTdlg 对话框

class CCONFIG_EQUIPMENTdlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCONFIG_EQUIPMENTdlg)

public:
	CCONFIG_EQUIPMENTdlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCONFIG_EQUIPMENTdlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIG_EQUIPMENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 配置文件Equipment.ini中的值[Product_Communication] Equipment_Name	
	CString config_equipment_product_communication_equipment_name;
	// 配置文件：Equipment.ini 中 config_equipment_product_communication_equipment_name
	CString config_equipment_product_communication_type;
	// config_equipment_product_pid
	int config_equipment_product_pid;
	// config_equipment_product_vid
	int config_equipment_product_vid;
	// config_equipment_product_pid
	CString config_distance_equipment_name;
	// config_distance_communication_type
	CString config_distance_communication_type;
	// config_distance_serial_port
	CString config_distance_serial_port;
	// config_distance_baud_rate
	int config_distance_baud_rate;
	// config_distance_slave_id
	CString config_distance_slave_id;
	// config_pressure_equipment_name
	CString config_pressure_equipment_name;
	// config_pressure_communication_type
	CString config_pressure_communication_type;
	// config_pressure_serial_port
	CString config_pressure_serial_port;
	// config_pressure_baud_rate
	int config_pressure_baud_rate;
	// config_pressure_slave_id
	CString config_pressure_slave_id;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	// 定义 Equipment - Bluetooth Equipment Name
	CString config_bluetooth_equipment_name;
	// 定义 Equipment - Bluetooth Communication Type
	CString config_bluetooth_communication_type;
	// 定义 Equipment - Bluetooth Serial Port
	CString config_bluetooth_serial_port;
	// 定义 Equipment - Bluetooth baud rate
	int config_bluetooth_baud_rate;
};
