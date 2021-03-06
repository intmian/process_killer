// Setting.cpp: 实现文件
//
#include "stdafx.h"
#include "process_killer.h"
#include "Setting.h"
#include "afxdialogex.h"
#include "Resource.h"
#include <string>
#include <fstream>
using namespace std;
// Setting 对话框
int timeSetting = 30;
int timeSettingPrepare = 30;
IMPLEMENT_DYNAMIC(Setting, CDialogEx)

Setting::Setting(CWnd* pParent /*=nullptr*/)
	: CDialogEx(setting_, pParent)
{
}

Setting::~Setting()
{
}

void Setting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	CString str;
	str.Format(_T("%d"), timeSetting);
	GetDlgItem(dlgTime)->SetWindowTextW(str);
}


BEGIN_MESSAGE_MAP(Setting, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Setting::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Setting::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Setting::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Setting::OnBnClickedButton4)
END_MESSAGE_MAP()


// Setting 消息处理程序


void Setting::OnBnClickedButton1()
{
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(str);
	if (_ttoi(str) != 0)
	{
		timeSettingPrepare = _ttoi(str);
		GetDlgItem(dlgTime)->SetWindowTextW(str); 

		CString strP;
		string strPro;
		char buffer[20];
		_itoa_s(timeSettingPrepare, buffer, 10);
		GetDlgItem(IDC_EDIT1)->GetWindowTextW(strP);
		string timestr(buffer);
		strPro = CT2A(strP);
		ofstream out("setting", ios::out);
		out << timestr << " " << strPro << "                                                ";  // 覆盖掉可能存在的值
		// 为了避免非预期的退出，在此存储

		CDialogEx::OnCancel();
	}
	else
	{
		CDialogEx::OnCancel();
		MessageBoxA(NULL, "时间不能为0", "警告", MB_OK);
	}
}


void Setting::OnBnClickedButton2()  // 点击开机自启动
{
	HKEY hKey;
	wchar_t *strRegPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

	//1、找到系统的启动项  
	if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) ///打开启动项       
	{
		//2、得到本程序自身的全路径
		TCHAR strExeFullDir[MAX_PATH];
		GetModuleFileName(NULL, strExeFullDir, MAX_PATH);

		//3、判断注册表项是否已经存在
		TCHAR strDir[MAX_PATH] = {};
		DWORD nLength = MAX_PATH;
		long result = RegGetValue(hKey, nullptr, L"process_killer", RRF_RT_REG_SZ, 0, strDir, &nLength);

		//4、已经存在
		if (result != ERROR_SUCCESS || _tcscmp(strExeFullDir, strDir) != 0)
		{
			//5、添加一个子Key,并设置值，"GISRestart"是应用程序名字（不加后缀.exe） 
			RegSetValueEx(hKey, L"process_killer", 0, REG_SZ, (LPBYTE)strExeFullDir, (lstrlen(strExeFullDir) + 1) * sizeof(TCHAR));

			//6、关闭注册表
			RegCloseKey(hKey);
		}
		MessageBox(L"已设置开机自启");
	}
	else
	{
		MessageBox(L"系统参数异常，无法实现开机自启或已经开机自启动");
	}
}


void Setting::OnBnClickedButton3()
{
	HKEY hKey;
	wchar_t *strRegPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

	//1、找到系统的启动项  
	if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
	{
		//2、删除值
		RegDeleteValue(hKey, L"process_killer");

		//3、关闭注册表
		RegCloseKey(hKey);
		MessageBox(L"已关闭开机自启");
	}
	else
	{
		MessageBox(L"无法找到开机自启项，可能已被关闭，或未曾开启");
	}
}


void Setting::OnBnClickedButton4()
{
	CDialogEx::OnCancel();
}
