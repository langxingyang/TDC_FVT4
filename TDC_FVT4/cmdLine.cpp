#include "stdafx.h"
#include "cmdLine.h"

cmdLine::cmdLine()
{
}

cmdLine::~cmdLine()
{
}


// ����:execmd����ִ�������������洢��result�ַ��������� 
// ����:cmd��ʾҪִ�е�����
// result��ִ�еĽ���洢���ַ�������
// ����ִ�гɹ�����TRUE��ʧ�ܷ���FALSE  
std::string cmdLine::runCmd(std::string& strCmd)
{
	/*
	clock_t startTime = clock();
	clock_t execTime;
	CString logData;
	*/
	//��ȫ����
	SECURITY_ATTRIBUTES sa;
	HANDLE hRead, hWrite;
	std::string strResult;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	strCmd = "cmd /c " + strCmd;//����"cmd /c"��Ϊ����ִ������dir������,ִ���ַ���ָ��������Ȼ���ն�

	//���������ܵ�������DOS�������ͨ��
	if (!CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		return NULL;
	}
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	si.cb = sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError = hWrite;//��������õ��ļ����
	si.hStdOutput = hWrite;//�´������̵ı�׼�������д�ܵ�һ��
	si.wShowWindow = SW_HIDE;//���ش���
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	//ִ��cmd����,���������йܵ���д��cmd����صĴ�
	//if (!CreateProcess(NULL, const_cast <char*>(strCmd.c_str()), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	if (!CreateProcess(NULL, ConvertCharToLPWSTR(strCmd.c_str()), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
	{
		return NULL;
	}
	/*
	execTime = clock();
	int t = execTime - startTime;
	logData.Format("ִ������ %s ��ʱ:%d ms", strCmd.c_str(), t);
	mtmlog.LogOut(logData.GetBuffer(0));
	*/
	/*
	if(WaitForSingleObject(pi.hProcess, INFINITE)==WAIT_FAILED)//��������Ƿ�Ҫ����������ִ����,��ping�Ⱥ�ʱ�϶������.
	{
	return FALSE;
	}
	*/
	CloseHandle(hWrite);//�رչܵ����

	char buffer[4096] = { 0 };
	DWORD bytesRead;

	while (ReadFile(hRead, buffer, 4096, &bytesRead, NULL))//�������ܵ��ж�ȡ����
	{
		strResult += buffer;
		memset(&buffer, 0, 4096);
		Sleep(200);//��ֹ����
	}
	/*
	t = clock() - execTime;
	logData.Format("����ͨ����ȡ��ʱ:%d ms", t);
	mtmlog.LogOut(logData.GetBuffer(0));
	*/
	//mtmlog.LogOut(strResult);
	CloseHandle(hRead);
	return strResult;
}

LPWSTR cmdLine::ConvertCharToLPWSTR(const char * szString)
{
	int dwLen = strlen(szString) + 1;
	int nwLen = MultiByteToWideChar(CP_ACP, 0, szString, dwLen, NULL, 0);//������ʵĳ���
	LPWSTR lpszPath = new WCHAR[dwLen];
	MultiByteToWideChar(CP_ACP, 0, szString, dwLen, lpszPath, nwLen);
	return lpszPath;
}