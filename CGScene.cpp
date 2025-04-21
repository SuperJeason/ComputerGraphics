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
void CGScene::SetSceneData(std::shared_ptr<CGNode> root)
{
	if (!root->asGroup()) //此处要求Group或其派生类才能作为图形场景实例树根节点
		return;
	mRoot = root;
}
//渲染场景
bool CGScene::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
	if (pRC == nullptr || pCamera == nullptr)
		return false;
	//场景节点更新
	//相机投影
	//pCamera->Projection(pCamera->ProjectionMode());
	//绘制
	mRoot->Render(pRC, pCamera);
}