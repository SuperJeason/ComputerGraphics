#pragma once
#include "CGRenderable.h"
class TessellationHints;
class CGCube : public CGRenderable
{
	DECLARE_SERIAL(CGCube)
public:
	CGCube() :
		mHalfLengths(0.5f, 0.5f, 0.5f) {
	}
	CGCube(float width) :
		mHalfLengths(width * 0.5f, width * 0.5f, width * 0.5f) {
	}
	CGCube(float lengthX, float lengthY, float lengthZ) :
		mHalfLengths(lengthX * 0.5f, lengthY * 0.5f, lengthZ * 0.5f) {
	}
	CGCube(const CGCube& box) :
		mHalfLengths(box.mHalfLengths)
	{
	}
	virtual ~CGCube() {}
	void setHalfLengths(const glm::vec3& halfLengths) { mHalfLengths = halfLengths; }
	const glm::vec3& halfLengths() const { return mHalfLengths; }
	void setTessellationHints(std::shared_ptr<TessellationHints> hints);
	TessellationHints* tessellationHints() { return mTessellationHints.get(); }
	const TessellationHints* tessellationHints() const { return mTessellationHints.get(); }
protected:
	virtual void buildDisplayList(); //重写基类虚函数
protected:
	glm::vec3 mHalfLengths; //三方向边的半长
	std::shared_ptr<TessellationHints> mTessellationHints = nullptr;
};