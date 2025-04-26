#include "pch.h"
#include "CGLineSegment.h"
IMPLEMENT_SERIAL(CGLineSegment, CGGeometry, 1)
CGLineSegment::CGLineSegment()
	: mStart(glm::dvec3(0.0, 0.0, 0.0)), mEnd(glm::dvec3(0.0, 0.0, 0.0))
{
}
CGLineSegment::CGLineSegment(const glm::dvec3& start, const glm::dvec3& end)
	: mStart(start), mEnd(end)
{
}
CGLineSegment::~CGLineSegment()
{
}
void CGLineSegment::Serialize(CArchive& ar)
{
	CGRenderable::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要）
	if (ar.IsStoring()) //保存
	{
		//ar << ; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明
	}
	else //读取
	{
		//ar >> ;
	}
}
//渲染
bool CGLineSegment::Render(CGRenderContext* pRC, CGCamera* pCamera)
{

	if (pRC == nullptr || pCamera == nullptr)
		return false;
	glColor3f(1.0f, 1.0f, 1.0f); // 白色
	glBegin(GL_LINES);
	glVertex3f(mStart.x, mStart.y, mStart.z);
	glVertex3f(mEnd.x, mEnd.y, mEnd.z);
	glEnd();
	return true;
}

void CGLineSegment::Translate(double tx, double ty)
{
	mStart.x += tx;
	mStart.y += ty;

	mEnd.x += tx;
	mEnd.y += ty;
}
