#include "stdafx.h"
#include "File_Check.h"


File_Check::File_Check()
{
}


File_Check::~File_Check()
{
}


// �ж��ļ��Ƿ����
BOOL File_Check::IsFileExist(const CString& csFile)
{
	DWORD dwAttrib = GetFileAttributes(csFile);
	return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}
// �ж��ļ����Ƿ����
BOOL File_Check::IsDirExist(const CString & csDir)
{
	DWORD dwAttrib = GetFileAttributes(csDir);
	return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 != (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}
// �ж��ļ����ļ����Ƿ����
BOOL File_Check::IsPathExist(const CString & csPath)
{
	DWORD dwAttrib = GetFileAttributes(csPath);
	return INVALID_FILE_ATTRIBUTES != dwAttrib;
}

// ��������(��˵�����һ��)
BOOL File_Check::IsPathExist_Fast(const CString & csPath)
{
	WIN32_FILE_ATTRIBUTE_DATA attrs = { 0 };
	return 0 != GetFileAttributesEx(csPath, GetFileExInfoStandard, &attrs);
}

BOOL File_Check::File_Del(CString file_name)
{
	CFile file;
	if (File_Check::IsFileExist(file_name)) {
		try {
			file.Remove(file_name);
		}
		catch (CFileException* pEx)
		{
			TRACE(_T("File %20s cannot be removed\n"), file_name);
			pEx->Delete();
			return FALSE;
		}
	}
	return TRUE;
}
