#include "pch.h"
#include "CGGeode.h"
IMPLEMENT_SERIAL(CGGeode, CGGroup, 1)
CGGeode::CGGeode()
{
}
CGGeode::~CGGeode()
{
}
void CGGeode::Serialize(CArchive& ar)
{
	CGGroup::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要）
	if (ar.IsStoring()) //保存
	{
		//ar << ; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明
	}
	else //读取
	{
		//ar >> ;
	}
}

bool CGGeode::Render(CGRenderContext * pRC, CGCamera * pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->Render(pRC, pCamera);
	}
}