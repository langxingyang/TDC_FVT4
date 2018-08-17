#include "stdafx.h"
#include "CSTLinkV2.h"
#include "File_Check.h"
#include "cmdLine.h"

File_Check ff_check;
cmdLine cmd;

BOOL CSTLinkV2::Get_Chip_Info()
{
	int exec_result = system(".\\bin\\ST-LINK_CLI.exe -c>.\\temp\\stlink.tmp");
	//int exec_result = WinExec(("\".\\bin\\ST-LINK_CLI.exe -c>.\\temp\\stlink.tmp\""), SW_HIDE);
	/*
	HINSTANCE ShellExecute(
		HWND hwnd, //父窗口句柄 
		LPCTSTR lpOperation, //操作, 打开方式 "edit","explore","open","find","print","NULL" 
		LPCTSTR lpFile, //文件名,前面可加路径 
		LPCTSTR lpParameters, //参数 
		LPCTSTR lpDirectory, //默认文件夹 
		INT nShowCmd //显示方式 
	);*/
	//HINSTANCE exec_result = ShellExecute(NULL, _T("open"), _T(".\\bin\\ST-LINK_CLI.exe -c>.\\temp\\stlink.tmp"), NULL, NULL, SW_SHOW);
	if (int(exec_result) == 0) { //ERROR_PATH_NOT_FOUND	
		return TRUE;
	}
	else {
		AfxMessageBox(_T("ST - LINK_CLI.exe Execulte Failed."));
		return FALSE;
	}

	//return CString();
}

BOOL CSTLinkV2::Read_8(int address, int length)
{
	BOOL file_del = ff_check.File_Del(_T(".\\temp\\stlink.tmp"));
	if (!file_del) {
		return FALSE;
	}
	char command[MAX_PATH];
	sprintf_s(command,sizeof(command),(".\\bin\\ST-LINK_CLI.exe -r8 %08x %04x >.\\temp\\stlink.tmp"),address,length);
	int exec_result = system(command);
	if (int(exec_result) == 0) { //ERROR_PATH_NOT_FOUND	
		return TRUE;
	}
	else {
		AfxMessageBox(_T("ST - LINK_CLI.exe Execulte Failed."));
		return FALSE;
	}
}

BOOL CSTLinkV2::Write_8(int address, DWORD data)
{
	BOOL file_del = ff_check.File_Del(_T(".\\temp\\stlink.tmp"));
	if (!file_del) {
		return FALSE;
	}
	char command[MAX_PATH];
	sprintf_s(command, sizeof(command), (".\\bin\\ST-LINK_CLI.exe -w8 %08x %04x>.\\temp\\stlink.tmp"), address, data);
	int exec_result = system(command);
	if (int(exec_result) == 0) { //ERROR_PATH_NOT_FOUND	
		return TRUE;
	}
	else {
		AfxMessageBox(_T("ST - LINK_CLI.exe Execulte Failed."));
		return FALSE;
	}
}

BOOL CSTLinkV2::Run()
{
	BOOL file_del = ff_check.File_Del(_T(".\\temp\\stlink.tmp"));
	if (!file_del) {
		return FALSE;
	}
	char command[MAX_PATH];
	sprintf_s(command, sizeof(command), (".\\bin\\ST-LINK_CLI.exe -c -Run"));
	int exec_result = system(command);
	if (int(exec_result) == 0) {
		return TRUE;
	}
	else {
		AfxMessageBox(_T("ST - LINK_CLI.exe Execulte Failed."));
		return FALSE;
	}
}

BOOL CSTLinkV2::Flash(CString bin_file, int address, BOOL verify)
{
	char* bin_file_c;
	USES_CONVERSION;
	//进行转换
	bin_file_c = T2A(bin_file.GetBuffer(0));
	bin_file.ReleaseBuffer();

	BOOL file_del = ff_check.File_Del(_T(".\\temp\\stlink.tmp"));
	if (!file_del) {
		return FALSE;
	}
	char command[MAX_PATH];
	int exec_result;
	sprintf_s(command, sizeof(command), ("\".\\bin\\ST-LINK_CLI.exe -ME\""));
	exec_result = system(command);
	if (int(exec_result) == 0) {
		//return TRUE;
	}
	else {
		AfxMessageBox(_T("ST-LINK_CLI.exe Execulte Failed."));
		return FALSE;
	}
	if (verify == TRUE) {
		sprintf_s(command, sizeof(command), ("\".\\bin\\ST-LINK_CLI.exe -c -P %s 0x%08x -V after_programming >.\\temp\\stlink.tmp\""), bin_file_c,address);
	}
	else {
		sprintf_s(command, sizeof(command), (".\\bin\\ST-LINK_CLI.exe -c -P %s 0x%08x >.\\temp\\stlink.tmp"), bin_file_c, address);
	}
	//int exec_result = WinExec(command,SW_HIDE);
	exec_result = system(command);
	//exec_result = exec_result + system(".\\bin\\ST-LINK_CLI.exe -Rst");
	if (int(exec_result) == 0) {
		return TRUE;
	}
	else {
		AfxMessageBox(_T("ST-LINK_CLI.exe Execulte Failed."));
		return FALSE;
	}
}
CString CSTLinkV2::Read_exe_Result(CString identify, int flag, int length)
{
	CStdioFile file;
	CString strLine, strtemp;
	if (!file.Open(_T(".\\temp\\stlink.tmp"), CFile::modeRead))return _T("Error"); ;//打开*.TXT这个文件，打开形式为读取 
	while (file.ReadString(strLine))
	{
		if (strLine.Find(identify) > -1) {
			CString feedback = strLine.Mid(flag, length);
			file.Close();
			return feedback;
		}
	}
	file.Close();
	return _T("Error");
}

CString CSTLinkV2::Get_BT_Address(CString identify1, CString identify2)
{
	CStdioFile file;
	CString BT_Address = _T("HHHHHHHHHHHH");
	CString strLine, strtemp;
	if (!file.Open(_T(".\\temp\\stlink.tmp"), CFile::modeRead))return _T("Error"); ;//打开*.TXT这个文件，打开形式为读取 
	while (file.ReadString(strLine))
	{
		if (strLine.Find(identify1) > -1) {
			BT_Address.SetAt(10, strLine[13]);
			BT_Address.SetAt(11, strLine[14]);

			BT_Address.SetAt(8, strLine[29]);
			BT_Address.SetAt(9, strLine[30]);

			BT_Address.SetAt(6, strLine[45]);
			BT_Address.SetAt(7, strLine[46]);

			BT_Address.SetAt(4, strLine[61]);
			BT_Address.SetAt(5, strLine[62]);
		} 
		if (strLine.Find(identify2) > -1) {
			BT_Address.SetAt(2, strLine[13]);
			BT_Address.SetAt(3, strLine[14]);

			BT_Address.SetAt(0, strLine[29]);
			BT_Address.SetAt(1, strLine[30]);
		}
	}
	CString feedback;
	for (int i = 0; i < 12; i++ ) {
		if (BT_Address[i] == 'H') {
			feedback = _T("Error");
			return feedback;
		}
	}
	feedback = BT_Address;
	file.Close();
	
	return feedback;
}



CString CSTLinkV2::WcharToChar(const wchar_t * wp, size_t m_encode)
{
	CString str;
	int len = WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
	char    *m_char = new char[len + 1];
	WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	str = m_char;
	delete m_char;
	return str;
}

BOOL CSTLinkV2::Flash_CMD(CString bin_file, int address, BOOL verify)
{
	CString command;
	if (verify) {
		command.Format(_T(".\\bin\\ST-LINK_CLI.exe -c -P %s 0x%08x -V after_programming"), bin_file, address);
	}
	else {
		command.Format(_T(".\\bin\\ST-LINK_CLI.exe -c -P %s 0x%08x"), bin_file, address);
	}
	std::string command_str;
	command_str = CT2A(command.GetBuffer());
	std::string exec_result = cmd.runCmd(command_str);
	if (exec_result == "NULL") {
		return FALSE;
	}
	if (exec_result.find("SUCCESS") < 0) {
		return FALSE;
	}
	command_str = ".\\bin\\ST-LINK_CLI.exe -Rst";
	exec_result = cmd.runCmd(command_str);
	if (exec_result == "NULL") {
		return FALSE;
	}
	if (exec_result.find("SUCCESS") < 0) {
		return FALSE;
	}
	return TRUE;
}

BOOL CSTLinkV2::Reset()
{
	char command[MAX_PATH];
	sprintf_s(command, sizeof(command), (".\\bin\\ST-LINK_CLI.exe -Rst"));
	int exec_result = system(command);
	if (int(exec_result) == 0) {
		return TRUE;
	}
	else {
		AfxMessageBox(_T("ST - LINK_CLI.exe Execulte Failed."));
		return FALSE;
	}
}


CSTLinkV2::CSTLinkV2()
{
}


CSTLinkV2::~CSTLinkV2()
{
}
