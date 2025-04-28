#include "pch.h" // ��������Ŀʹ����Ԥ����ͷ�ļ�
#include "CGPolylineSegment.h"
#include <gl/GL.h> // ���� OpenGL ͷ�ļ�

// ��ʵ�����л����е������޸�Ϊ CGPolylineSegment
IMPLEMENT_SERIAL(CGPolylineSegment, CGGeometry, 1)

CGPolylineSegment::CGPolylineSegment()
	: mClosed(false)
{
}

CGPolylineSegment::CGPolylineSegment(const std::vector<glm::dvec3>& points)
	: mPoints(points), mClosed(false)
{
}

CGPolylineSegment::CGPolylineSegment(const std::vector<glm::dvec3>& points, bool closed)
	: mPoints(points), mClosed(closed)
{
}

CGPolylineSegment::~CGPolylineSegment()
{
}

void CGPolylineSegment::Serialize(CArchive& ar)
{
	CGGeometry::Serialize(ar); // ���û�������л�����

	if (ar.IsStoring())
	{
		// ��������
		ar << (int)mPoints.size(); // ����������
		for (const auto& point : mPoints)
		{
			// ʹ�� << ��������л�ÿ����ķ���
			ar << point.x << point.y << point.z;
		}
		ar << mClosed; // ����պ�״̬
	}
	else
	{
		// ��������
		int numPoints;
		ar >> numPoints; // ���ص������
		mPoints.resize(numPoints); // �������б��С
		for (int i = 0; i < numPoints; ++i)
		{
			// ʹ�� >> ����������л�ÿ����ķ���
			ar >> mPoints[i].x >> mPoints[i].y >> mPoints[i].z;
		}
		ar >> mClosed; // ���رպ�״̬
	}
}

// ��Ⱦ
bool CGPolylineSegment::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;

	// ����Ƿ����㹻�ĵ��������߶�
	if (mPoints.size() < 2)
	{
		return false; // �����������޷��γ��߶�
	}

	// ���û�����ɫ (���� CGLineSegment ʹ�ð�ɫ)
	glColor3f(1.0f, 1.0f, 1.0f); // ��ɫ

	// ʹ�� GL_LINE_STRIP �����������߶�
	glBegin(GL_LINE_STRIP);
	for (const auto& point : mPoints)
	{
		glVertex3f(point.x, point.y, point.z); // ��ӵ㵽�߶�����
	}
	glEnd();

	// ������߱պϣ���Ҫ�������ƴ����һ���㵽��һ������߶�
	if (mClosed && mPoints.size() >= 2)
	{
		glBegin(GL_LINES);
		glVertex3f(mPoints.back().x, mPoints.back().y, mPoints.back().z); // ���һ����
		glVertex3f(mPoints.front().x, mPoints.front().y, mPoints.front().z); // ��һ����
		glEnd();
	}

	return true;
}

void CGPolylineSegment::AddPoint(const glm::dvec3& point)
{
	mPoints.push_back(point);
}

void CGPolylineSegment::Translate(float tx, float ty) {
	// �������е㲢Ӧ��ƽ��
	for (auto& point : mPoints) {
		point.x += tx; // x ����ƽ��
		point.y += ty; // y ����ƽ��
		// z ���걣�ֲ��䣨����� 2D ���ߣ�
	}
}

void CGPolylineSegment::Rotate(double angle, double cx, double cy)
{
	// ������б�Ϊ�գ�ֱ�ӷ���
	if (mPoints.empty()) {
		return;
	}

	// �����任����
	glm::dmat4 transform(1.0); // ��ʼ��Ϊ��λ����

	// 1. ƽ�Ƶ�ԭ�� (����ת�����Ƶ�ԭ��)
	transform = glm::translate(transform, glm::dvec3(-cx, -cy, 0.0));

	// 2. ��Z����ת (��ʱ��Ϊ��)
	transform = glm::rotate(transform, glm::radians(angle), glm::dvec3(0.0, 0.0, 1.0));

	// 3. ƽ�ƻ�ԭλ��
	transform = glm::translate(transform, glm::dvec3(cx, cy, 0.0));

	// Ӧ�ñ任�����е�
	for (auto& point : mPoints) {
		// ����ת��Ϊ������� (w=1)
		glm::dvec4 transformed = transform * glm::dvec4(point, 1.0);

		// ���µ����� (����w��������Ȼ����w=1����Ҫ��)
		point = glm::dvec3(transformed.x, transformed.y, point.z);
	}
}
