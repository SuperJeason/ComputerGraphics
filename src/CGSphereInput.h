#pragma once
#include "afxdialogex.h"


// CGSphereInput 对话框

class CGSphereInput : public CDialogEx
{
	DECLARE_DYNAMIC(CGSphereInput)

public:
	CGSphereInput(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGSphereInput();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUT_SLICE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString mValueSlice;
	virtual BOOL OnInitDialog();
	CString mTitle;
	CString mValueStack;
};
