#pragma once


// Setting 对话框

class Setting : public CDialogEx
{
	DECLARE_DYNAMIC(Setting)

public:
	Setting(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Setting();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = setting_ };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};

extern int timeSetting;
extern int timeSettingPrepare; // 在下一轮会被写入timeSetting
