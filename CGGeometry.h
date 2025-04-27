#pragma once
#include "CGRenderable.h"
class CGGeometry : public CGRenderable
{
	DECLARE_SERIAL(CGGeometry)
public:
	CGGeometry();
	virtual ~CGGeometry();
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//绘制对象（在派生类中重写）
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual void Translate(double tx, double ty) {
		// 空实现（直接写在头文件里）
	}
protected:
};