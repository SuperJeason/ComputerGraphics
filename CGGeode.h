#pragma once
#include "CGGroup.h"
class CGGeode : public CGGroup
{
	DECLARE_SERIAL(CGGeode)
public:
	CGGeode();
	virtual ~CGGeode();
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//���ƶ���������������д��
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual CGGeode* asGeode() { return this; }
	virtual const CGGeode * asGeode() const { return this; }
};