#include "pch.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CCGRenderContext.h"
#include "CGNode.h"
IMPLEMENT_SERIAL(CGScene, CGObject, 1)
CGScene::CGScene()
{
}
CGScene::~CGScene()
{
}
void CGScene::Serialize(CArchive& ar)
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
void CGScene::SetSceneData(std::shared_ptr<CGNode> root)
{
	if (!root->asGroup()) //�˴�Ҫ��Group���������������Ϊͼ�γ���ʵ�������ڵ�
		return;
	mRoot = root;
}
//��Ⱦ����
bool CGScene::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	//�����ڵ����
	//���ͶӰ
	//pCamera->Projection(pCamera->ProjectionMode());
	//����
	mRoot->Render(pRC, pCamera);
}