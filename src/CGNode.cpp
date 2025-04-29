#include "pch.h"
#include "CGNode.h"
#include "CGGroup.h"
IMPLEMENT_SERIAL(CGNode, CGObject, 1)
CGNode::CGNode()
{
}
CGNode::~CGNode()
{

}
void CGNode::Serialize(CArchive& ar)
{
	CGObject::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要）
	if (ar.IsStoring()) //保存
	{
		//ar << ; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明
	}
	else //读取
	{
		//ar >> ;
	}
}
bool CGNode::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	return true;
}

//+2支持共享子节点
CGGroup* CGNode::GetParent(unsigned int i)
{
	if (i < mParents.size())
		return mParents[i];
	return nullptr;
}
const CGGroup* CGNode::GetParent(unsigned int i) const
{
	if (i < mParents.size())
		return mParents[i];
		return nullptr;
}
void CGNode::AddParent(CGGroup* parent)
{
	mParents.push_back(parent);
}
void CGNode::RemoveParent(CGGroup* parent)
{
	auto pitr = std::find(mParents.begin(), mParents.end(), parent);
	if (pitr != mParents.end()) mParents.erase(pitr);
}