#include "pch.h"
#include "CGRenderState.h"

void CGColor::apply(const CGCamera* camera, CGRenderContext* ctx, int index) const
{
	glColor4f(mColor.r, mColor.g, mColor.b, mColor.a);
}

void CGPointSize::apply(const CGCamera* camera, CGRenderContext* ctx, int index) const
{
	glPointSize(mPointSize);
}

void CGLineWidth::apply(const CGCamera* camera, CGRenderContext* ctx, int index) const
{
	glLineWidth(mLineWidth);
}

void CGLineStipple::apply(const CGCamera* camera, CGRenderContext* ctx, int index) const
{
	glLineStipple(mFactor, mPattern);
}

void CGPolygonMode::apply(const CGCamera* camera, CGRenderContext* ctx, int index) const
{
	if (mFrontFace == mBackFace) {
		glPolygonMode(GL_FRONT_AND_BACK, (GLenum)mFrontFace);
	}
	else {
		glPolygonMode(GL_FRONT, (GLenum)mFrontFace);
		glPolygonMode(GL_BACK, (GLenum)mBackFace);
	}
}

void CGRenderStateSet::setRenderState(std::shared_ptr<CGRenderState> renderstate, int index)
{
	if (renderstate) {
		for (unsigned i = 0; i < mRenderStates.size(); ++i) {
			if (mRenderStates[i].mRS->type() == renderstate->type() && mRenderStates[i].mIndex == index) {
				mRenderStates[i].mRS = renderstate;
				//mRenderStates[i].mIndex = index;
				return;
			}
		}
		mRenderStates.push_back(CGRenderStateSlot(renderstate, index));
	}
}
CGRenderState* CGRenderStateSet::renderState(ERenderState type, int index)
{
	for (unsigned i = 0; i < mRenderStates.size(); ++i)
		if (mRenderStates[i].mRS->type() == type && mRenderStates[i].mIndex == index)
			return mRenderStates[i].mRS.get();
	return nullptr;
}
const CGRenderState* CGRenderStateSet::renderState(ERenderState type, int index) const
{
	for (unsigned i = 0; i < mRenderStates.size(); ++i)
		if (mRenderStates[i].mRS->type() == type && mRenderStates[i].mIndex == index)
			return mRenderStates[i].mRS.get();
	return nullptr;
}
void CGRenderStateSet::eraseRenderState(ERenderState type, int index)
{
	for (unsigned i = 0; i < mRenderStates.size(); ++i) {
		if (mRenderStates[i].mRS->type() == type && (index == mRenderStates[i].mIndex || index == -1)) {
			mRenderStates.erase(mRenderStates.begin() + i);
			if (index == -1)
				continue;
			else
				return;
		}
	}
}

void CGRenderStateSet::apply(const CGCamera* camera, CGRenderContext* ctx)
{
	for (auto itr = mModes.begin(); itr != mModes.end(); ++itr)
	{
		if (itr->second) {
			glEnable(itr->first);
		}
		else {
			glDisable(itr->first);
		}
	}
	for (auto itr = mRenderStates.begin(); itr != mRenderStates.end(); ++itr) {
		itr->apply(camera, ctx);
	}
}
