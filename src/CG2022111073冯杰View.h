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

// CG2022111073冯杰View.h: CCG2022111073冯杰View 类的接口
//

#pragma once
#include "glIncludes.h"
#include "CCGRenderContext.h"
#include "CG2022111073冯杰Doc.h"
#include <memory>
#include<string>
class CGNode;

class CCG2022111073冯杰View : public CView, public CCGRenderContext
{
protected: // 仅从序列化创建
	CCG2022111073冯杰View() noexcept;
	DECLARE_DYNCREATE(CCG2022111073冯杰View)


protected:
	GLFWwindow* m_glfwWindow = nullptr;
	HWND m_hWndGL = nullptr;
	bool m_bGLInitialized = false;
	// 特性
public:
	CCG2022111073冯杰Doc* GetDocument() const;
	GLFWwindow* glfwWindow() const { return m_glfwWindow; }
	void ShowPrompt(const std::string& str); //状态栏上显示提示信息
	void ShowCoord(double x, double y); //状态栏上显示坐标信息
	//根据视口坐标获取对应场景坐标（二维）-调用文档类默认相机的转换函数
	glm::dvec3 DCS2WCS(const glm::dvec3& p); //设备坐标转世界坐标
	glm::dvec3 WCS2DCS(const glm::dvec3& p); //世界坐标转设备坐标
	bool AddRenderable(std::shared_ptr<CGNode> r) const;


protected:
	bool InitGLFW(); //初始化GLFW
	void RenderScene(); //渲染函数
	// 操作
public:

	// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	// 实现
public:
	virtual ~CCG2022111073冯杰View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	UINT mTimer = 0; //定时器
public:
	UINT toggleFrameTimer(); //触发/关闭定时器
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // CG2022111073冯杰View.cpp 中的调试版本
inline CCG2022111073冯杰Doc* CCG2022111073冯杰View::GetDocument() const
{
	return reinterpret_cast<CCG2022111073冯杰Doc*>(m_pDocument);
}
#endif

