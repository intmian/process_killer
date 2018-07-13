// about.cpp: 实现文件
//

#include "stdafx.h"
#include "process_killer.h"
#include "about.h"
#include "afxdialogex.h"

// about 对话框

IMPLEMENT_DYNAMIC(about, CDialogEx)

about::about(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ABOUTBOX, pParent)
{

}

about::~about()
{
}

void about::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(about, CDialogEx)
END_MESSAGE_MAP()


// about 消息处理程序
