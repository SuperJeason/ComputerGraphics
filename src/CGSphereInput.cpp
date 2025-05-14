// CGSphereInput.cpp: 实现文件
//

#include "pch.h"
#include "CG2022111073冯杰.h"
#include "afxdialogex.h"
#include "CGSphereInput.h"


// CGSphereInput 对话框

IMPLEMENT_DYNAMIC(CGSphereInput, CDialogEx)

CGSphereInput::CGSphereInput(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INPUT_SLICE, pParent)
	, mValueSlice(_T(""))
	, mValueStack(_T(""))
{

}

CGSphereInput::~CGSphereInput()
{
}

void CGSphereInput::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT_SLICE, mValueSlice);
	DDX_Text(pDX, IDC_INPUT_STACK, mValueStack);
}


BEGIN_MESSAGE_MAP(CGSphereInput, CDialogEx)
	ON_BN_CLICKED(IDOK, &CGSphereInput::OnBnClickedOk)
END_MESSAGE_MAP()


// CGSphereInput 消息处理程序

void CGSphereInput::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true); //取回输入框中数据到成员变量
	CDialogEx::OnOK();
}

BOOL CGSphereInput::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 在此添加额外的初始化
	if (mTitle.GetLength() > 1)
		this->SetWindowText(mTitle);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
