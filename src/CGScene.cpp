#include "pch.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CCGRenderContext.h"
#include "CGNode.h"
IMPLEMENT_SERIAL(CGScene, CGObject, 1)
CGScene::CGScene()
{
	SetMainCamera(std::make_shared<CGCamera>());
	SetSceneData(std::make_shared<CGTransform>());
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
	if (mRoot == nullptr || pRC == nullptr || pCamera == nullptr)
		return false;
	//场景节点更新
	//相机投影
	//pCamera->Projection(pCamera->ProjectionMode());
	//绘制
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	mRoot->update();
	mRoot->Render(pRC, pCamera);
	DrawWCS(pCamera);
	return true;
}

void CGScene::DrawWCS(CGCamera* pCamera)
{
	//坐标自定义，在使用规范化坐标时，需将坐标调整到(-1，1)
	glm::vec3 xs(-100, 0, 0), xe(100, 0, 0);
	glm::vec3 ys(0, -100, 0), ye(0, 100, 0);
	glm::vec3 zs(0, 0, -100), ze(0, 0, 100);
	//X轴红色、Y轴绿色、Z轴蓝色
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3fv(glm::value_ptr(xs));
	glVertex3fv(glm::value_ptr(xe));
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3fv(glm::value_ptr(ys));
	glVertex3fv(glm::value_ptr(ye));
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3fv(glm::value_ptr(zs));
	glVertex3fv(glm::value_ptr(ze));
	glEnd();
}