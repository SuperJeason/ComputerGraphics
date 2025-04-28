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

void CGLineSegment::Translate(float tx, float ty)
{
	mStart.x += tx;
	mStart.y += ty;

	mEnd.x += tx;
	mEnd.y += ty;
}

void CGLineSegment::Rotate(double angle, double cx, double cy)
{
	// ���Ƕ�ת��Ϊ���ȣ���Ϊ���Ǻ���ʹ�û��ȣ�
	double radians = angle * (M_PI / 180.0);

	// ������ת�����Ԫ��
	double cosTheta = cos(radians);
	double sinTheta = sin(radians);

	// ������ת����
	glm::mat2 rotationMatrix(cosTheta, sinTheta, -sinTheta, cosTheta);

	// ����������ת
	glm::dvec2 startRel = glm::dvec2(mStart.x - cx, mStart.y - cy);
	glm::dvec2 rotatedStart = rotationMatrix * startRel;
	mStart.x = rotatedStart.x + cx;
	mStart.y = rotatedStart.y + cy;

	// ���յ������ת
	glm::dvec2 endRel = glm::dvec2(mEnd.x - cx, mEnd.y - cy);
	glm::dvec2 rotatedEnd = rotationMatrix * endRel;
	mEnd.x = rotatedEnd.x + cx;
	mEnd.y = rotatedEnd.y + cy;
}

