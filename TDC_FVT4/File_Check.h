#pragma once
class File_Check
{
public:
	File_Check();
	~File_Check();
	// �ж��ļ��Ƿ����
	BOOL IsFileExist(const CString& csFile);
	// �ж��ļ����Ƿ����
	BOOL IsDirExist(const CString & csDir);
	// �ж��ļ����ļ����Ƿ����
	BOOL IsPathExist(const CString & csPath);
	// ��������(��˵�����һ��)������ע1
	BOOL File_Check::IsPathExist_Fast(const CString & csPath);
	BOOL File_Check::File_Del( CString file_name);
};

