#include "pch.h"
#include "CGGeometry.h"
#include "CGCamera.h"
#include "CCGRenderContext.h"
IMPLEMENT_SERIAL(CGGeometry, CGRenderable, 1)
CGGeometry::CGGeometry()
{
}
CGGeometry::~CGGeometry()
{
}
void CGGeometry::Serialize(CArchive& ar)
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
bool CGGeometry::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	return true;
}