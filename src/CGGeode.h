#pragma once
#include "CGGroup.h"

class CGRenderable;
class CGGeode : public CGGroup
{
	DECLARE_SERIAL(CGGeode)
public:
	CGGeode();
	virtual ~CGGeode();
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//绘制对象（在派生类中重写）
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual CGGeode* asGeode() { return this; }
	virtual const CGGeode * asGeode() const { return this; }
	//作为实例叶子节点，显示下级为模型节点
	unsigned int GetNumRenderables() const;
	CGRenderable* GetRenderable(unsigned int i);
	const CGRenderable* GetRenderable(unsigned int i) const;
	unsigned int GetRenderableIndex(const CGRenderable* renderable) const;
	bool ContainsRenderable(const CGRenderable* renderable) const;
	virtual bool InsertChild(unsigned int index, std::shared_ptr<CGNode>& child);
};