#pragma once
#include "CGObject.h"
#include <vector>
//预声明（本文件中只用到相关类指针，为避免交叉包含）
class CGNode;
class CGCamera;
class CGRenderContext;
class CGGroup;
class CGTransform;
class CGGeode;
class CGRenderable;
class CGGeometry;
class CGNode : public CGObject
{
	DECLARE_SERIAL(CGNode)
public:
	CGNode();
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//绘制对象（在派生类中重写）
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual CGNode* asNode() { return this; }
	virtual const CGNode* asNode() const { return this; }
	virtual CGGroup* asGroup() { return 0; }
	virtual const CGGroup* asGroup() const { return 0; }
	virtual CGTransform* asTransform() { return 0; }
	virtual const CGTransform * asTransform() const { return 0; }
	virtual CGRenderable* asRenderable() { return 0; }
	virtual const CGRenderable* asRenderable() const { return 0; }
	virtual CGGeode* asGeode() { return 0; }
	virtual const CGGeode* asGeode() const { return 0; }
	virtual CGGeometry* asGeometry() { return 0; }
	virtual const CGGeometry* asGeometry() const { return 0; }
	void SetUpdateCallback(std::shared_ptr<CGCallback> uc) { mUpdateCallback = uc; }
	inline CGCallback* GetUpdateCallback() { return mUpdateCallback.get(); }
protected:
	virtual ~CGNode();
	std::shared_ptr<CGCallback> mUpdateCallback = nullptr;
	friend class CGGroup;
	friend class CGRenderable;
};