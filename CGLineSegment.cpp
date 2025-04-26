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
	CGRenderable::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
	}
	else //��ȡ
	{
		//ar >> ;
	}
}
//��Ⱦ
bool CGLineSegment::Render(CGRenderContext* pRC, CGCamera* pCamera)
{

	if (pRC == nullptr || pCamera == nullptr)
		return false;
	glColor3f(1.0f, 1.0f, 1.0f); // ��ɫ
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
