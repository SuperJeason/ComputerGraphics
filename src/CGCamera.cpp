#include "pch.h"
#include "CGCamera.h"
IMPLEMENT_SERIAL(CGCamera, CGTransform, 1)
CGCamera::CGCamera()
{
}
CGCamera::~CGCamera()
{
}
void CGCamera::Serialize(CArchive& ar)
{
	CGTransform::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要）
	if (ar.IsStoring()) //保存
	{
		//ar << ; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明
	}
	else //读取
	{
		//ar >> ;
	}
}
void CGCamera::Projection(int mode)
{
	//待补充实现投影操作
}