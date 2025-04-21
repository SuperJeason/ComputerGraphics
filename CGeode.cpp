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
	CGGroup::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
	if (ar.IsStoring()) //����
	{
		//ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
	}
	else //��ȡ
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