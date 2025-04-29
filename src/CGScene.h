#pragma once
#include "CGObject.h"
#include <vector>
class CGCamera; //预声明
class CGRenderContext;//预声明
class CGNode; //预声明
class CGScene : public CGObject
{
	DECLARE_SERIAL(CGScene)
public:
	CGScene();
	virtual ~CGScene();
	virtual void Serialize(CArchive& ar) override;
	//渲染场景
	bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	void SetMainCamera(std::shared_ptr<CGCamera> camera) { mCamera = camera; }
	CGCamera* GetMainCamera() { return mCamera.get(); }
	//场景中的图形对象，一般是Group或Transform
	void SetSceneData(std::shared_ptr<CGNode> root);
	CGNode* GetSceneData() { return mRoot.get(); }
protected:
	std::shared_ptr<CGCamera> mCamera = nullptr;//场景主相机
	std::shared_ptr<CGNode> mRoot = nullptr; //场景树根节点
	void DrawWCS(CGCamera* pCamera);
};