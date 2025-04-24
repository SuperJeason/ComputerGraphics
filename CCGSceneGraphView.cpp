// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// CCGSceneGraphView.cpp: CCGSceneGraphView 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CG2022111073冯杰.h"

#include "CG2022111073冯杰Doc.h"
#include "CCGSceneGraphView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGSceneGraphView

IMPLEMENT_DYNCREATE(CCGSceneGraphView, CTreeView)

BEGIN_MESSAGE_MAP(CCGSceneGraphView, CTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CCGSceneGraphView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CCGSceneGraphView 构造/析构

CCGSceneGraphView::CCGSceneGraphView()
{
	// TODO: 在此处添加构造代码
}

CCGSceneGraphView::~CCGSceneGraphView()
{
	GetTreeCtrl().DeleteAllItems();
}

BOOL CCGSceneGraphView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式

	return CTreeView::PreCreateWindow(cs);
}

void CCGSceneGraphView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 调用 GetTreeCtrl() 直接访问 TreeView 的树控件，
	//  从而可以用项填充 TreeView。
}


// CCGSceneGraphView 诊断

#ifdef _DEBUG
void CCGSceneGraphView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CCGSceneGraphView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CCG2022111073冯杰Doc* CCGSceneGraphView::GetDocument() // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰Doc)));
	return (CCG2022111073冯杰Doc*)m_pDocument;
}
#endif //_DEBUG


// CCGSceneGraphView 消息处理程序

void CCGSceneGraphView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CCG2022111073冯杰Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	GetTreeCtrl().SetRedraw(TRUE);
}

int CCGSceneGraphView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CTreeCtrl& tree = GetTreeCtrl();
	DWORD dwStyles = tree.GetStyle();
	dwStyles |= TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_HASLINES | TVS_LINESATROOT;// | TVS_CHECKBOXES
	tree.ModifyStyle(0, dwStyles);
	CCG2022111073冯杰Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc) {
		pDoc->InstToSceneTree(&tree);
	}
	return 0;
}

void CCGSceneGraphView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CCG2022111073冯杰Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	mSelectedItem = GetTreeCtrl().GetSelectedItem();
	pDoc->OnSelectSceneTreeItem(&GetTreeCtrl(), mSelectedItem);
	*pResult = 0;
}
