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

// CG2022111073冯杰Doc.h: CCG2022111073冯杰Doc 类的接口
//


#pragma once
#include <memory>
class CGScene;
class CGRenderContext;
class CGNode;
class CGGroup;
class CCGSceneGraphView;
class CCG2022111073冯杰Doc : public CDocument
{
protected: // 仅从序列化创建
	CCG2022111073冯杰Doc() noexcept;
	DECLARE_DYNCREATE(CCG2022111073冯杰Doc)

public:
	std::shared_ptr<CGScene> mScene = nullptr;
// 操作
public:
	bool RenderScene(CGRenderContext* pRC);
	bool AddRenderable(std::shared_ptr<CGNode> r);
	CCGSceneGraphView* GetSceneGraphView();
	void InstToSceneTree(CTreeCtrl* pTree);//实列节点加入场景树
	void InstToSceneTree(CTreeCtrl* pTree, HTREEITEM hInst, CGNode* node);
	void OnSelectSceneTreeItem(CTreeCtrl* pTree, HTREEITEM hItem); //场景树中选中节点

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CCG2022111073冯杰Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CGGroup* mSelectedGroup = nullptr;
	HTREEITEM mSelectedItem = nullptr;
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnDraw2dLineseg();
	afx_msg void OnUpdateDraw2dLineseg(CCmdUI* pCmdUI);
	afx_msg void OnDraw2dPolygon();
	afx_msg void OnUpdateDraw2dPolygon(CCmdUI* pCmdUI);
	afx_msg void OnTranslateLeft();
	afx_msg void OnTranslateRight();
	afx_msg void OnTranslateUp();
	afx_msg void OnTranslateDown();
};
