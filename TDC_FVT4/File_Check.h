#pragma once
class File_Check
{
public:
	File_Check();
	~File_Check();
	// 判断文件是否存在
	BOOL IsFileExist(const CString& csFile);
	// 判断文件夹是否存在
	BOOL IsDirExist(const CString & csDir);
	// 判断文件或文件夹是否存在
	BOOL IsPathExist(const CString & csPath);
	// 变变变变变种(听说会更快一点)，见备注1
	BOOL File_Check::IsPathExist_Fast(const CString & csPath);
	BOOL File_Check::File_Del( CString file_name);
};

