#include "pch.h"
#include "CGCamera.h"
#include <GL/glu.h>
IMPLEMENT_SERIAL(Viewport, CGObject, 1)
Viewport::Viewport()
{
	mX = 0;
	mY = 0;
	mWidth = 0;
	mHeight = 0;
	mClearColor = glm::vec4(0, 0, 0, 1);
	mClearDepth = 1.0f;
	mClearStencil = 0;
	mClearFlags = CF_CLEAR_COLOR_DEPTH;
	mScissorEnabled = true;
}
Viewport::Viewport(int x, int y, int w, int h)
{
	mX = x;
	mY = y;
	mWidth = w;
	mHeight = h;
	mClearColor = glm::vec4(0, 0, 0, 1);
	mClearDepth = 1.0f;
	mClearStencil = 0;
	mClearFlags = CF_CLEAR_COLOR_DEPTH;
	mScissorEnabled = true;
}
void Viewport::activate() const
{
	int x = mX;
	int y = mY;
	int w = mWidth;
	int h = mHeight;
	if (w < 1) w = 1;
	if (h < 1) h = 1;
		glViewport(x, y, w, h);
	if (mClearFlags) {
		GLboolean color_write_mask[4] = { 0,0,0,0 };
		glGetBooleanv(GL_COLOR_WRITEMASK, color_write_mask);
		GLboolean depth_write_mask = 0;
		glGetBooleanv(GL_DEPTH_WRITEMASK, &depth_write_mask);
		GLboolean stencil_write_mask = 0;
		glGetBooleanv(GL_STENCIL_WRITEMASK, &stencil_write_mask);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		glStencilMask(GL_TRUE);
		if (mScissorEnabled) {
			glEnable(GL_SCISSOR_TEST);
			glScissor(x, y, w, h);
		}
		else {
			glDisable(GL_SCISSOR_TEST);
		}
		glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
		glClearDepth(mClearDepth);
		glClearStencil(mClearStencil);
		glClear(mClearFlags);
		glColorMask(color_write_mask[0], color_write_mask[1], color_write_mask[2],
			color_write_mask[3]);
		glDepthMask(depth_write_mask);
		glStencilMask(stencil_write_mask);
	}
}
IMPLEMENT_SERIAL(CGCamera, CGTransform, 1)
CGCamera::CGCamera()
{
	mViewport = std::make_shared<Viewport>();
}
CGCamera::~CGCamera()
{
}
void CGCamera::Serialize(CArchive& ar)
{
	CGTransform::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要）
	if (ar.IsStoring()) //保存
	{
		//ar << ; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明
	}
	else //读取
	{
		//ar >> ;
	}
}
void CGCamera::Projection(int mode)
{
	//待补充实现投影操作
	viewport()->activate();
	//设置投影变换
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRenderMode(GL_RENDER); //用于渲染（非选择）
	if (mode == 0) { //正平行投影（正交投影）
		glOrtho(mLeft, mRight, mBottom, mTop, mNearPlane, mFarPlane);
	}
	else if (mode == 1) {//透视投影
		glFrustum(mLeft, mRight, mBottom, mTop, mNearPlane, mFarPlane);
		//gluPerspective(45, (wRight- wLeft)/(wTop- wBottom), wNearPlane, wFarPlane);
	}
	else {//正交投影（二维效果）
		gluOrtho2D(mLeft, mRight, mBottom, mTop);
	}
	//模型视图变换
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); //视点（相机）相对于世界坐标系
	gluLookAt(mEye.x, mEye.y, mEye.z, mTarget.x, mTarget.y, mTarget.z, mUp.x, mUp.y, mUp.z); //设置
}