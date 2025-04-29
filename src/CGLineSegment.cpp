#include "pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

void CGLineSegment::Translate(float tx, float ty)
{
	mStart.x += tx;
	mStart.y += ty;

	mEnd.x += tx;
	mEnd.y += ty;
}

void CGLineSegment::Rotate(double angle, double cx, double cy)
{
	// 将角度转换为弧度（因为三角函数使用弧度）
	double radians = angle * (M_PI / 180.0);

	// 计算旋转矩阵的元素
	double cosTheta = cos(radians);
	double sinTheta = sin(radians);

	// 创建旋转矩阵
	glm::mat2 rotationMatrix(cosTheta, sinTheta, -sinTheta, cosTheta);

	// 对起点进行旋转
	glm::dvec2 startRel = glm::dvec2(mStart.x - cx, mStart.y - cy);
	glm::dvec2 rotatedStart = rotationMatrix * startRel;
	mStart.x = rotatedStart.x + cx;
	mStart.y = rotatedStart.y + cy;

	// 对终点进行旋转
	glm::dvec2 endRel = glm::dvec2(mEnd.x - cx, mEnd.y - cy);
	glm::dvec2 rotatedEnd = rotationMatrix * endRel;
	mEnd.x = rotatedEnd.x + cx;
	mEnd.y = rotatedEnd.y + cy;
}

void CGLineSegment::Scale(double sx, double sy, double cx, double cy)
{
	// 1. 创建平移矩阵（将缩放中心点移动到原点）
	glm::dmat4 translateToOrigin = glm::translate(glm::dmat4(1.0), glm::dvec3(-cx, -cy, 0.0));

	// 2. 创建缩放矩阵
	glm::dmat4 scaleMatrix = glm::scale(glm::dmat4(1.0), glm::dvec3(sx, sy, 1.0));

	// 3. 创建反向平移矩阵（将中心点移回原位置）
	glm::dmat4 translateBack = glm::translate(glm::dmat4(1.0), glm::dvec3(cx, cy, 0.0));

	// 4. 组合变换矩阵：T⁻¹ * S * T
	glm::dmat4 transformMatrix = translateBack * scaleMatrix * translateToOrigin;

	// 5. 对起点和终点应用变换
	glm::dvec4 transformedStart = transformMatrix * glm::dvec4(mStart, 1.0);
	glm::dvec4 transformedEnd = transformMatrix * glm::dvec4(mEnd, 1.0);

	// 6. 更新线段端点
	mStart = glm::dvec3(transformedStart);
	mEnd = glm::dvec3(transformedEnd);
}



