#include "pch.h"
#include "CGGroup.h"
#include <algorithm>
#include "CGGeometry.h"
IMPLEMENT_SERIAL(CGGroup, CGNode, 1)

CGGroup::CGGroup()
{
}
CGGroup::~CGGroup()
{
	//脱离父节点
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr) {
		(*itr)->RemoveParent(this);
	}
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
	child->AddParent(this);
	return true;
}

//子节点操作
unsigned int CGGroup::GetNumChildren() const
{
	return static_cast<unsigned int>(mChildren.size());
}
CGNode* CGGroup::GetChild(unsigned int i)
{
	if (i >= mChildren.size())
		return nullptr;
	return mChildren[i].get();
}
const CGNode* CGGroup::GetChild(unsigned int i) const
{
	if (i >= mChildren.size())
		return nullptr;
	return mChildren[i].get();
}
bool CGGroup::ContainsNode(const CGNode* node) const
{
	for (auto itr = mChildren.begin(); itr != mChildren.end(); ++itr) {
		if (itr->get() == node)
			return true;
	}
	return false;
}
unsigned int CGGroup::GetChildIndex(const CGNode* node) const
{
	for (unsigned int childNum = 0; childNum < mChildren.size(); ++childNum) {
		if (mChildren[childNum].get() == node) return childNum;
	}
	return static_cast<unsigned int>(mChildren.size()); //没找到，返回子节点个数
}