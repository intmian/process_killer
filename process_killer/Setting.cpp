// Setting.cpp: 实现文件
//

#include "stdafx.h"
#include "process_killer.h"
#include "Setting.h"
#include "afxdialogex.h"
#include "Resource.h"
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
		CDialogEx::OnCancel();
	}
	else
	{
		CDialogEx::OnCancel();
		MessageBoxA(NULL, "时间不能为0", "警告", MB_OK);
	}
}
