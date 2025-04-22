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

// CG2022111073冯杰Doc.cpp: CCG2022111073冯杰Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2022111073冯杰.h"
#endif

#include "CG2022111073冯杰Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CG2022111073冯杰View.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CGTransform.h"
#include "CGGeode.h"
#include "CGLineSegment.h"
#include "CCGRenderContext.h"
#include "UIEventHandler.h"
#include "CGDraw2DLineSeg.h"
#include "CGPolylineSegment.h"
#include "CGDraw2DPolylineSegment.h"

// CCG2022111073冯杰Doc

IMPLEMENT_DYNCREATE(CCG2022111073冯杰Doc, CDocument)

BEGIN_MESSAGE_MAP(CCG2022111073冯杰Doc, CDocument)
	ON_COMMAND(ID_DRAW2d_LINESEG, &CCG2022111073冯杰Doc::OnDraw2dLineseg)
	ON_UPDATE_COMMAND_UI(ID_DRAW2d_LINESEG, &CCG2022111073冯杰Doc::OnUpdateDraw2dLineseg)
	ON_COMMAND(ID_DRAW2D_POLYGON, &CCG2022111073冯杰Doc::OnDraw2dPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW2D_POLYGON, &CCG2022111073冯杰Doc::OnUpdateDraw2dPolygon)
END_MESSAGE_MAP()


// CCG2022111073冯杰Doc 构造/析构

CCG2022111073冯杰Doc::CCG2022111073冯杰Doc() noexcept
{
	// TODO: 在此添加一次性构造代码
	mScene = std::make_shared<CGScene>();
	mScene->SetMainCamera(std::make_shared<CGCamera>());
	auto e = std::make_shared<CGGeode>();
	auto line = std::make_shared<CGLineSegment>(glm::dvec3(100, 100, 0), glm::dvec3(400, 300, 0));
	e->AddChild(line);
	auto g = std::make_shared<CGTransform>();
	g->AddChild(e);
	mScene->SetSceneData(g);

}

CCG2022111073冯杰Doc::~CCG2022111073冯杰Doc()
{
}

BOOL CCG2022111073冯杰Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCG2022111073冯杰Doc 序列化

void CCG2022111073冯杰Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCG2022111073冯杰Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCG2022111073冯杰Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCG2022111073冯杰Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCG2022111073冯杰Doc 诊断

#ifdef _DEBUG
void CCG2022111073冯杰Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCG2022111073冯杰Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCG2022111073冯杰Doc 命令

void CCG2022111073冯杰Doc::OnDraw2dLineseg()
{
	// TODO: 在此添加命令处理程序代码
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGDraw2DLineSeg(view->glfwWindow())); //创建绘制直线段的命令对象
	}
}
void CCG2022111073冯杰Doc::OnUpdateDraw2dLineseg(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() ==EventType::Draw2DLineSeg);
}

bool CCG2022111073冯杰Doc::RenderScene(CGRenderContext* pRC)
{
	if (pRC == nullptr)
		return false;
	if (mScene == nullptr)
		return false;
	CGCamera* pCamera = mScene->GetMainCamera();
	if (pCamera == nullptr)
		return false;
	return mScene->Render(pRC, pCamera);
}
bool CCG2022111073冯杰Doc::AddRenderable(std::shared_ptr<CGNode> r)
{
	if (mScene == nullptr)
		return false;
	CGGroup* g = mScene->GetSceneData()->asGroup();
	if (g) {
		g->AddChild(r);
		return true;
	}
	return false;
}
void CCG2022111073冯杰Doc::OnDraw2dPolygon()
{
	// TODO: 在此添加命令处理程序代码
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGDraw2DPolylineSegment(view->glfwWindow())); //创建绘制折线的命令对象
	}
}

void CCG2022111073冯杰Doc::OnUpdateDraw2dPolygon(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}
