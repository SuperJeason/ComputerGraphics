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