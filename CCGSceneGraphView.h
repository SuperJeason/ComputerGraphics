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

// CCGSceneGraphView.h: CCGSceneGraphView 类的接口
//


#pragma once
#include "glIncludes.h"
#include "CCGRenderContext.h"

class CCG2022111073冯杰Doc;

class CCGSceneGraphView : public CTreeView, public CCGRenderContext
{
protected: // 仅从序列化创建
	CCGSceneGraphView();
	DECLARE_DYNCREATE(CCGSceneGraphView)

protected:
	GLFWwindow* m_glfwWindow = nullptr;
	HWND m_hWndGL = nullptr;
	bool m_bGLInitialized = false;

// 特性
public:
	CCG2022111073冯杰Doc* GetDocument();



protected:
	bool InitGLFW(); //初始化GLFW
	void RenderScene(); //渲染函数
// 操作
public:

// 重写
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CCGSceneGraphView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CCGSceneGraphView.cpp 中的调试版本
inline CCG2022111073冯杰Doc* CCGSceneGraphView::GetDocument()
   { return reinterpret_cast<CCG2022111073冯杰Doc*>(m_pDocument); }
#endif

