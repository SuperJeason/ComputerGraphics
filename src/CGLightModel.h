#pragma once
#include "CGRenderState.h"


class CGLightModel : public CGRenderState
{
public:
	CGLightModel();
	virtual ~CGLightModel() = default;
	virtual ERenderState type() const { return ERenderState::RS_LightModel; }
	virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const;
	void setLocalViewer(bool localviewer) { mLocalViewer = localviewer; }
	void setTwoSide(bool twoside) { mTwoSide = twoside; }
	void setAmbientColor(const glm::vec4& ambientcolor) { mAmbientColor = ambientcolor; }
	bool localViewer() const { return mLocalViewer; }
	bool twoSide() const { return mTwoSide; }
	const glm::vec4& ambientColor() const { return mAmbientColor; }
protected:
	glm::vec4 mAmbientColor;//全局环境光
	bool mLocalViewer; //无限远或局部观察（镜面反射角度的计算）
	bool mTwoSide; //双面光照
};