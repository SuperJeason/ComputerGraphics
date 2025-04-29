#include "pch.h"
#include "CGObject.h"
IMPLEMENT_SERIAL(CGObject, CObject, 1) //1可以看作是数据版本号，用于兼容升级（增加数据成员）
unsigned long CGObject::sID = 0L;
CGObject::CGObject()
	: CGObject(CString("CGObject"))
{
	mName.Format(_T("CGObject%ld"), sID);
}
CGObject::CGObject(const CString& name)
	: mName(name)
{
	sID++;
}
CGObject::CGObject(const CGObject& other)
	: mName(other.mName)
{
	//拷贝构造不改变sID
}
void CGObject::Serialize(CArchive& ar)
{
	CObject::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要）
	if (ar.IsStoring()) //保存
	{
		ar << mName; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明
	}
	else //读取
	{
		ar >> mName;
	}
}