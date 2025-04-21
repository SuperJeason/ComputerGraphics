#pragma once
#include "CGGroup.h"
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
};