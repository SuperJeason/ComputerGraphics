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
	CGNode::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
	}
	else //��ȡ
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