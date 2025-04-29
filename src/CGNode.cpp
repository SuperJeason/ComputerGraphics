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
	CGObject::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
	}
	else //��ȡ
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

//+2֧�ֹ����ӽڵ�
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