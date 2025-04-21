#pragma once
#include "CGNode.h"
class CGRenderContext;//Ԥ����
class CGCamera; //Ԥ����
class CGRenderable : public CGNode
{
	DECLARE_SERIAL(CGRenderable)
public:
	CGRenderable();
	virtual ~CGRenderable();
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//���ƶ���������������д��
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual CGRenderable * asRenderable() { return this; }
	virtual const CGRenderable* asRenderable() const { return this; }
protected:
};