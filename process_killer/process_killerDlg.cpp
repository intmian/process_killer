
// process_killerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "process_killer.h"
#include "process_killerDlg.h"
#include "afxdialogex.h"
#include "about.h"
#include "Setting.h"
#include <tlhelp32.h>
#include <Windows.h>
#include <fstream>
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
CProgressCtrl *m_progress = NULL;
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On32771();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CAboutDlg::On32771()
{
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_32771, &CAboutDlg::On32771)
END_MESSAGE_MAP()


// CprocesskillerDlg 对话框



CprocesskillerDlg::CprocesskillerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROCESS_KILLER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CprocesskillerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CprocesskillerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CprocesskillerDlg::OnBnClickedOk)
	ON_COMMAND(ID_32771, &CprocesskillerDlg::On32771)
	ON_BN_CLICKED(IDCANCEL, &CprocesskillerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CprocesskillerDlg::OnBnClickedButton1)
	ON_COMMAND(ID_32774, &CprocesskillerDlg::On32774)
	ON_WM_TIMER()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_PROGRESS1, &CprocesskillerDlg::OnNMCustomdrawProgress1)
END_MESSAGE_MAP()


// CprocesskillerDlg 消息处理程序

BOOL CprocesskillerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_progress = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	m_progress->SetRange(0, 1000);
	m_progress->SetPos(0);
	//额外的初始化代码
	string processNameA;
	int myTime;
	// 读入本地文件并修改
	ifstream localSetting("setting");
	localSetting >> myTime >> processNameA;
	localSetting.close();
	CString processName(processNameA.c_str());
	CString timeStr;
	timeSetting = timeSettingPrepare = myTime;
	timeStr.Format(_T("%d"), myTime);
	GetDlgItem(lats_time)->SetWindowTextW(timeStr);
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(processName);
	checkAndKill(processName);
	this->OnBnClickedOk();  // 响应开机自启动，框架启动自动计时

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CprocesskillerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CprocesskillerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CprocesskillerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CprocesskillerDlg::OnBnClickedOk()
{
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowTextW(str);
	if (str == "")
	{
		MessageBoxA(NULL, "待处理进程名不能为零", "警告", MB_OK);
		return;
	}

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

	SetTimer(1, 1000, NULL);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	GetDlgItem(IDC_EDIT1)->EnableWindow(false);
	GetDlgItem(IDOK)->EnableWindow(false);
	//TODO here start 
}


void CprocesskillerDlg::On32771()
{
	about a;
	a.DoModal();
}


void CprocesskillerDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


void CprocesskillerDlg::OnBnClickedButton1()
{
	GetDlgItem(IDOK)->EnableWindow(true);
	GetDlgItem(IDC_EDIT1)->EnableWindow(true);
	//GetDlgItem(ID_32774)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	KillTimer(1);
}


void CprocesskillerDlg::On32774()
{
	Setting settingDlg;
	settingDlg.DoModal();
}

void checkAndKill(CString processName)
{
	TCHAR m_buf[100];
	_tcscpy_s<100>(m_buf, processName);                            //定义字符串并初始化,c为8长度,最后结尾有'\0',定义一个字符为'x',
	HANDLE handle;                                            //定义CreateToolhelp32Snapshot系统快照句柄
	HANDLE handle1;                                           //定义要结束进程句柄
	handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //获得系统快照句柄
	PROCESSENTRY32 *info;                                     //定义PROCESSENTRY32结构字指
															  //PROCESSENTRY32  结构的 dwSize 成员设置成 sizeof(PROCESSENTRY32)
	info = new PROCESSENTRY32;
	info->dwSize = sizeof(PROCESSENTRY32);
	//调用一次 Process32First 函数，从快照中获取进程列表
	Process32First(handle, info);
	//重复调用 Process32Next，直到函数返回 FALSE 为止
	while (Process32Next(handle, info) != FALSE)
	{
		info->szExeFile; //指向进程名字
						 //strcmp字符串比较函数同要结束相同
		if (wcscmp(m_buf, info->szExeFile) == 0)
		{
			//MessageBox (NULL, info->szExeFile, TEXT ("HelloMsg"), 0);
			//PROCESS_TERMINATE表示为结束操作打开,FALSE=可继承,info->th32ProcessID=进程ID
			handle1 = OpenProcess(PROCESS_TERMINATE, FALSE, info->th32ProcessID);
			//结束进程
			TerminateProcess(handle1, 0);
		}
	}
	CloseHandle(handle);
}


void CprocesskillerDlg::OnTimer(UINT_PTR nIDEvent) // 此处为 定时器
{
	CString latstime_str, time_str, times_str;
	int lasttime_int, time_int, times_int;
	GetDlgItem(lats_time)->GetWindowTextW(latstime_str);
	GetDlgItem(timeDlg)->GetWindowTextW(time_str);
	GetDlgItem(times)->GetWindowTextW(times_str);
	lasttime_int = _ttoi(latstime_str);
	time_int = _ttoi(time_str);
	times_int = _ttoi(times_str);
	time_int++;
	lasttime_int--;
	int pos = (int)((double)lasttime_int / timeSetting * 1000);
	pos = 1000 - pos;
	m_progress->SetPos(pos);
	if (lasttime_int == 0)
	{
		timeSetting = timeSettingPrepare;
		lasttime_int = timeSetting;
		times_int++;
		CString str;
		GetDlgItem(IDC_EDIT1)->GetWindowTextW(str);
		checkAndKill(str);
		
	} 

	latstime_str.Format(_T("%d"), lasttime_int);
	time_str.Format(_T("%d"), time_int);
	times_str.Format(_T("%d"), times_int);
	GetDlgItem(lats_time)->SetWindowTextW(latstime_str);
	GetDlgItem(timeDlg)->SetWindowTextW(time_str);
	GetDlgItem(times)->SetWindowTextW(times_str);

	CDialogEx::OnTimer(nIDEvent);
}


void CprocesskillerDlg::OnNMCustomdrawProgress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}
