#include "pch.h"
#include "CGGroup.h"
#include <algorithm>
IMPLEMENT_SERIAL(CGGroup, CGNode, 1)

CGGroup::CGGroup()
{
}
CGGroup::~CGGroup()
{
}
void CGGroup::Serialize(CArchive& ar)
{
	CGNode::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要）
	if (ar.IsStoring()) //保存
	{
		//ar << ; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明
	}
	else //读取
	{
		//ar >> ;
	}
}
bool CGGroup::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr)
	{
		(*itr)->Render(pRC, pCamera);
	}
}
bool CGGroup::AddChild(std::shared_ptr<CGNode> child)
{
	return CGGroup::InsertChild(mChildren.size(), child);
}

bool CGGroup::InsertChild(unsigned int index, std::shared_ptr<CGNode>&child)
{
	if (!child) return false;
	if (index >= mChildren.size())
	{
		index = mChildren.size();
		mChildren.push_back(child);
	}
	else
	{
		mChildren.insert(mChildren.begin() + index, child);
	}
	return true;
}