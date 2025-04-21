#pragma once
#include "CGTransform.h"
class CGCamera : public CGTransform
{
	DECLARE_SERIAL(CGCamera)
public:
	CGCamera();
	virtual ~CGCamera();
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//mode=0为正交投影（三维），mode=1为透视投影，mode=2或其他为正交投影（二维）
	virtual void Projection(int mode);
	int ProjectionMode() { return mProjectionMode; }
	void SetProjectionMode(int mode) { if (mode >= 0 && mode <= 2) mProjectionMode = mode; }
protected:
	int mProjectionMode = 0;
};