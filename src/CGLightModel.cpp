#include "pch.h"
#include "CGLightModel.h"

CGLightModel::CGLightModel()
	: mAmbientColor(0.2f, 0.2f, 0.2f, 1.0f), mLocalViewer(false), mTwoSide(false)
{
}
void CGLightModel::apply(const CGCamera*, CGRenderContext*, int) const
{
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, mLocalViewer ? 1.0f : 0.0f);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, &mAmbientColor.r);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, mTwoSide ? 1.0f : 0.0f);
}