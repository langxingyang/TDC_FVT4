#pragma once
class CSTLinkV2
{
public:
	BOOL CSTLinkV2::Get_Chip_Info();
	BOOL CSTLinkV2::Read_8(int address, int length);
	BOOL CSTLinkV2::Write_8(int address, DWORD data);
	BOOL CSTLinkV2::Run();
	BOOL CSTLinkV2::Flash(CString bin_file, int address, BOOL verify);
	CString CSTLinkV2::Read_exe_Result(CString identify, int flag, int length);
	CString CSTLinkV2::WcharToChar(const wchar_t* wp, size_t m_encode = CP_ACP);
	BOOL CSTLinkV2::Flash_CMD(CString bin_file, int address, BOOL verify);
	CString CSTLinkV2::Get_BT_Address(CString identify1,CString identify2);
	BOOL CSTLinkV2::Reset();






public:
	CSTLinkV2();
	~CSTLinkV2();
};

