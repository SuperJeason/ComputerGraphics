#pragma once
#include "CGGroup.h"
class CGTransform : public CGGroup
{
	DECLARE_SERIAL(CGTransform)
public:
	CGTransform();
	virtual ~CGTransform();
	virtual void Serialize(CArchive& ar) override;
	//‰÷»æ≥°æ∞
	bool Render(CGRenderContext * pRC, CGCamera * pCamera);
	virtual CGTransform* asTransform() { return this; }
	virtual const CGTransform* asTransform() const { return this; }
};