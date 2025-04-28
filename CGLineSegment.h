#pragma once
#include "CGGeometry.h"
class CGLineSegment : public CGGeometry
{
	DECLARE_SERIAL(CGLineSegment)
public:
	CGLineSegment();
	CGLineSegment(const glm::dvec3& start, const glm::dvec3& end);
	virtual ~CGLineSegment();
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//绘制对象（在派生类中重写）
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	void Translate(float tx, float ty); //平移
	virtual void Rotate(double angle, double cx, double cy);
	virtual void Scale(double sx, double sy, double cx, double cy);
protected:
	glm::dvec3 mStart;
	glm::dvec3 mEnd;
	const double M_PI = 3.1415926;
};