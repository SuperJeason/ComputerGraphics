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

// CG2022111073冯杰View.cpp: CCG2022111073冯杰View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2022111073冯杰.h"
#endif
#include "MainFrm.h"
#include "UIEventHandler.h"
#include "CG2022111073冯杰Doc.h"
#include "CG2022111073冯杰View.h"
#include <vector>
#include <utility>
#include "homework1.h"
#include"homework2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CCG2022111073冯杰View

IMPLEMENT_DYNCREATE(CCG2022111073冯杰View, CView)

BEGIN_MESSAGE_MAP(CCG2022111073冯杰View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CCG2022111073冯杰View 构造/析构

CCG2022111073冯杰View::CCG2022111073冯杰View() noexcept
{
	// TODO: 在此处添加构造代码

}

CCG2022111073冯杰View::~CCG2022111073冯杰View()
{
	if (mTimer) KillTimer(mTimer); //关闭定时器
	if (m_glfwWindow) {
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
	}
}

bool CCG2022111073冯杰View::InitGLFW() {
	if (!glfwInit()) {
		AfxMessageBox(_T("GLFW初始化失败"));
		return false;
	}
	// 设置GLFW窗口无边框、透明（避免覆盖MFC控件）
	glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	// 设置OpenGL版本
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //如果使用OpenGL核心模式
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); //如果使用OpenGL兼容模式
	// 创建隐藏的GLFW窗口
	m_glfwWindow = glfwCreateWindow(100, 100, "", NULL, NULL);
	if (!m_glfwWindow) {
		AfxMessageBox(_T("Failed to glfwCreateWindow"));
		glfwTerminate();
		return false;
	}
	// 获取GLFW窗口的HWND并设置为MFC视图的子窗口
	m_hWndGL = glfwGetWin32Window(m_glfwWindow);
	SetWindowLong(m_hWndGL, GWL_STYLE, WS_VISIBLE);
	::SetParent(m_hWndGL, GetSafeHwnd());
	::ShowWindow(m_hWndGL, SW_SHOW);
	// 初始化OpenGL上下文
	glfwMakeContextCurrent(m_glfwWindow);
#if defined(_USE_GLEW)
	glewInit();
#else
	//使用GLAD来加载OpenGL的函数地址
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		AfxMessageBox(_T("Failed to initialize GLAD"));
		return false;
	}
#endif
	// 设置视口
	CRect rect;
	GetClientRect(&rect);
	glViewport(0, 0, rect.Width(), rect.Height());
	m_bGLInitialized = true;

	//设置回调函数用到的指针（this-当前view）
	glfwSetWindowUserPointer(m_glfwWindow, this); //this也是CCGRenderContext*类型
	//设置键盘输入回调
	glfwSetKeyCallback(m_glfwWindow, UIEventHandler::KeyCallback);
	//设置鼠标按键回调
	glfwSetMouseButtonCallback(m_glfwWindow, UIEventHandler::MouseButtonCallback);
	//设置光标移动回调
	glfwSetCursorPosCallback(m_glfwWindow, UIEventHandler::CursorPosCallback);
	//设置鼠标滚轮回调
	glfwSetScrollCallback(m_glfwWindow, UIEventHandler::ScrollCallback);
	return true;
}

std::vector<std::pair<int, int>> generateRegularPolygon(int cx, int cy, float r, int n) {
	const double M_PI = 3.1415926;
	std::vector<std::pair<int, int>> points;
	for (int i = 0; i < n; i++) {
		float angle = 2.0f * M_PI * i / n;  // 计算当前角度（弧度）
		int x = cx + r * cos(angle);      // x 坐标
		int y = cy + r * sin(angle);      // y 坐标
		points.push_back({ x, y });
	}
	return points;
}
void CCG2022111073冯杰View::RenderScene() {
	if (!m_bGLInitialized)
		return;
	//启用渲染环境
	glfwMakeContextCurrent(m_glfwWindow);
	//此处添加自定义OpenGL渲染代码...
	glm::vec3 color(1.0f, 0.0f, 0.0f);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	/*drawTest();*/
	// DDALine(100, 200, 400, 300, glm::vec3(1.0f, 0.0f, 0.0f));

	// 绘制点集合
	// 实验1
	/* drawPoint();
	 drawLine();
	 drawLineStrip();
	 drawLineLoop();
	 drawTriangles();
	 drawTriangStrip();
	 drawTriangFan();
	 drawQuads();
	 drawQuadsStrip();
	 drawPolygon();
	 drawStar(600.0f,400.0f,100.0f,40.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f));
	 drawStar(800.0f, 400.0f, 75.0f, 30.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 1.0f));*/
	 //绘制完毕，交换缓存
	 // 实验2
	 //DDALine(1, 1, 500, 200, glm::vec3(1.0f, 1.0f, 0.0f));
	 //DDALine(1, 500, 600, 100, glm::vec3(1.0f, 1.0f, 0.0f));
	 //DDALine(1, 1, 500, 700, glm::vec3(1.0f, 1.0f, 0.0f));
	 //DDALine(1, 700, 500, 1, glm::vec3(1.0f, 1.0f, 0.0f));
	 // MidLine(1, 1, 500, 200, glm::vec3(1.0f, 1.0f, 0.0f));
	 //MidLine(1, 100, 500, 200, glm::vec3(1.0f, 1.0f, 0.0f));
	 //MidLine(1, 500, 600, 100, glm::vec3(1.0f, 1.0f, 0.0f));
	 //MidLine(1, 150, 500, 700, glm::vec3(1.0f, 1.0f, 0.0f));
	 //MidLine(1, 700, 500, 1, glm::vec3(1.0f, 1.0f, 0.0f));
	 //BresenhamLine(300, 100, 500, 200, glm::vec3(1.0f, 1.0f, 0.0f));
	 //BresenhamLine(200, 500, 600, 100, glm::vec3(1.0f, 1.0f, 0.0f));
	 //BresenhamLine(400, 150, 500, 700, glm::vec3(1.0f, 1.0f, 0.0f));
	 //BresenhamLine(200, 700, 500, 1, glm::vec3(1.0f, 1.0f, 0.0f));
	 // BresenhamLine(1, 200, 500, 1, glm::vec3(1.0f, 1.0f, 0.0f));

	 // 绘制圆心在 (200, 200)、半径为50的绿色圆
	 //CenterCircle(300, 300, 100, glm::vec3(0.0f, 1.0f, 0.0f));
	 //CenterCircle(300, 300, 50, glm::vec3(0.0f, 1.0f, 0.0f));
	 //CenterCircle(300, 300, 200, glm::vec3(0.0f, 1.0f, 0.0f));
	 //CenterCircle(300, 300, 150, glm::vec3(0.0f, 1.0f, 0.0f));
	 //CenterCircle(800, 300, 200, glm::vec3(0.0f, 1.0f, 0.0f));
	 // 绘制圆心在 (200, 200)、半径为50的蓝色圆
	 // BresenhamCircle(200, 200, 50, glm::vec3(0.0f, 0.0f, 1.0f));


	 // 画正多边形
	 //for (int i = 0;i < points.size();++i) {
	 //	if (i== points.size() -1){
	 //		MidLine(points[i].first, points[i].second, points[0].first, points[0].second, glm::vec3(0.0f, 1.0f, 1.0f));
	 //	}
	 //	else {
	 //		MidLine(points[i].first, points[i].second, points[i + 1].first, points[i + 1].second, glm::vec3(0.0f, 1.0f, 1.0f));
	 //	}
	 //}
	 // 画出园内多边形
	 //std::vector<std::pair<int, int>> points1 = generateRegularPolygon(300, 300, 200, 13);
	 //for (auto point1 : points1)
	 //	for (auto point2 : points1) {
	 //		BresenhamLine(point1.first, point1.second, point2.first, point2.second, glm::vec3(0.0f, 1.0f, 1.0f));
	 //	}

	 //std::vector<std::pair<int, int>> points2 = generateRegularPolygon(800, 300, 200, 15);
	 //for (auto point1 : points2)
	 //	for (auto point2 : points2) {
	 //		BresenhamLine(point1.first, point1.second, point2.first, point2.second, glm::vec3(0.0f, 1.0f, 1.0f));
	 //	}


	 //BresenhamCircle(300, 300, 50, glm::vec3(0.0f, 0.0f, 1.0f));
	 //BresenhamCircle(300, 300, 100, glm::vec3(0.0f, 0.0f, 1.0f));
	 //BresenhamCircle(300, 300, 150, glm::vec3(0.0f, 0.0f, 1.0f));
	 //BresenhamCircle(300, 300, 200, glm::vec3(0.0f, 0.0f, 1.0f));
	 //drawArc(600,300,100,50,130, glm::vec3(0.0f, 1.0f, 1.0f));
	 //drawArc(700, 300, 100, 25, 70, glm::vec3(0.0f, 1.0f, 1.0f));
	 //drawArc(800, 400, 100, 195, 270, glm::vec3(0.0f, 1.0f, 1.0f));
	 //drawArc(460, 400, 100, 50, 123, glm::vec3(0.0f, 1.0f, 1.0f));
	 //drawArc(800, 150, 100, 250, 355, glm::vec3(0.0f, 1.0f, 1.0f));

	 // 实验2-2 扫描线填充算法
	 // 扫描线填充1
	 //std::vector<glm::ivec2> vtxs = {
	 //	glm::ivec2(100, 100),  // Vertex 1
	 //	glm::ivec2(200, 150),  // Vertex 2
	 //	glm::ivec2(150, 200),  // Vertex 3
	 //	glm::ivec2(50, 180),   // Vertex 4
	 //	glm::ivec2(20,200),
	 //	glm::ivec2(10,120),
	 //	glm::ivec2(50,120),
	 //};
	 //ScanPolygon(vtxs, glm::vec3(0.0f, 1.0f, 1.0f));

	 //// 扫描线填充2
	 //vtxs = {
	 //	glm::ivec2(600, 100),  // Vertex 1
	 //	glm::ivec2(700, 450),  // Vertex 2
	 //	glm::ivec2(850, 300),  // Vertex 3
	 //	glm::ivec2(990, 480),   // Vertex 4
	 //	glm::ivec2(1000,300),
	 //	glm::ivec2(1000,120),
	 //	glm::ivec2(1100,100),
	 //};
	 //ScanPolygon(vtxs, glm::vec3(0.0f, 1.0f, 1.0f));

	 //// 种子填充算法1
	 //std::vector<glm::ivec2> circlePoints = BresenhamCircleWithPoints(300, 300, 50, glm::vec3(0.0f, 0.0f, 1.0f));
	 //floodFill(300, 300, glm::vec3(0.0f, 1.0f, 1.0f), circlePoints,circlePoints.size());


	 ////// 种子填充算法2
	 //circlePoints = BresenhamCircleWithPoints(500, 300, 50, glm::vec3(0.0f, 0.0f, 1.0f));
	 //floodFill(500, 300, glm::vec3(0.0f, 1.0f, 1.0f), circlePoints, circlePoints.size());

	 // 实验3-1
	CCG2022111073冯杰Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc) {
		pDoc->RenderScene((CGRenderContext*)this);
	}


	glfwSwapBuffers(m_glfwWindow);

}
BOOL CCG2022111073冯杰View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCG2022111073冯杰View 绘图

void CCG2022111073冯杰View::OnDraw(CDC* /*pDC*/)
{
	CCG2022111073冯杰Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	RenderScene();
}

void CCG2022111073冯杰View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCG2022111073冯杰View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCG2022111073冯杰View 诊断

#ifdef _DEBUG
void CCG2022111073冯杰View::AssertValid() const
{
	CView::AssertValid();
}

void CCG2022111073冯杰View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCG2022111073冯杰Doc* CCG2022111073冯杰View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰Doc)));
	return (CCG2022111073冯杰Doc*)m_pDocument;
}
#endif //_DEBUG


// CCG2022111073冯杰View 消息处理程序

int CCG2022111073冯杰View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if (!InitGLFW())
		return -1;
	return 0;
}

void CCG2022111073冯杰View::OnDestroy()
{
	if (m_glfwWindow) {
		glfwDestroyWindow(m_glfwWindow);
		glfwTerminate();
		m_glfwWindow = nullptr;
	}
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

BOOL CCG2022111073冯杰View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	// return __super::OnEraseBkgnd(pDC);
	return TRUE;
}

void CCG2022111073冯杰View::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	if (m_hWndGL) {
		// 调整GLFW子窗口大小与视图客户区匹配
		::SetWindowPos(m_hWndGL, NULL, 0, 0, cx, cy, SWP_NOZORDER);
		glfwMakeContextCurrent(m_glfwWindow);
		//通过文档类操作相机
		CCG2022111073冯杰Doc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (pDoc) {
			pDoc->OnViewResize(cx, cy);
		}
		else {
			//+0
			glViewport(0, 0, cx, cy);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//
			//基本图形生成算法实验部分，假定观察窗口与视口一致。（左下角为原点，右上角为(cx,cy)）
			//使用正交平行投影
			//glOrtho(0, cx, //x范围
			// 0, cy, //y范围
			// -10000.0f, 10000.0f); //z范围（深度）
			//调到屏幕中心
			glOrtho(-cx / 2.0f, cx / 2.0f, //x范围
				-cy / 2.0f, cy / 2.0f, //y范围
				-10000.0f, 10000.0f); //z范围（深度）
			//
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
		}
	} //
}

//状态栏上显示提示信息
void CCG2022111073冯杰View::ShowPrompt(const std::string& str)
{
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
#include <memory>
		class CGNode;
		pMainWnd->ShowPrompt(CString(str.c_str()));
	}
}
//状态栏上显示坐标信息
void CCG2022111073冯杰View::ShowCoord(double x, double y)
{
	CString str;
	glm::dvec3 v = DCS2WCS(glm::dvec3(x, y, 0.0));
	str.Format(_T("视口坐标 (%.0f, %.0f) : 世界坐标 (%.2f, %.2f) "), x, y, v.x, v.y);
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
	if (pMainWnd != nullptr)
	{
		pMainWnd->ShowCoord(str); //显示到状态栏
	}
}
glm::dvec3 CCG2022111073冯杰View::DCS2WCS(const glm::dvec3& p)
{
	//暂时使用屏幕设备坐标
	int w, h;
	glfwGetWindowSize(m_glfwWindow, &w, &h);
	// return glm::dvec3(p.x, double(h) - p.y, 0.0);
	return glm::dvec3(p.x - double(w) / 2, double(h) / 2 - p.y, 0.0);
}
glm::dvec3 CCG2022111073冯杰View::WCS2DCS(const glm::dvec3& p)
{
	//待实现
	return glm::dvec3();
}
bool CCG2022111073冯杰View::AddRenderable(std::shared_ptr<CGNode> r) const
{
	CCG2022111073冯杰Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return false;

	return pDoc->AddRenderable(r);
}


UINT CCG2022111073冯杰View::toggleFrameTimer()
{
	if (!mTimer) {
		mTimer = SetTimer(1, 20, NULL);// 启动50FPS定时器（20毫秒间隔）
	}
	else {
		KillTimer(mTimer);
		mTimer = 0;
	}
	return mTimer;
}


void CCG2022111073冯杰View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == mTimer) {
		RenderScene();
	}

	__super::OnTimer(nIDEvent);
}
