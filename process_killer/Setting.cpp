// Setting.cpp: 实现文件
//

#include "stdafx.h"
#include "process_killer.h"
#include "Setting.h"
#include "afxdialogex.h"


// Setting 对话框

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
}


BEGIN_MESSAGE_MAP(Setting, CDialogEx)
END_MESSAGE_MAP()


// Setting 消息处理程序
