// Setting.cpp: 实现文件
//
#include <string>
#include <fstream>
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
