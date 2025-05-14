#include "pch.h"
#include "CGCube.h"
#include "TessellationHints.h"
IMPLEMENT_SERIAL(CGCube, CGRenderable, 1)
void CGCube::setTessellationHints(std::shared_ptr<TessellationHints> hints)
{
	if (mTessellationHints.get() != hints.get())
	{
		mTessellationHints = hints;
		mDisplayListDirty = true;
	}
}
void CGCube::buildDisplayList()
{
	TessellationHints* hints = tessellationHints();
	bool createBody = (hints ? hints->createBody() : true);
	bool createTop = (hints ? hints->createTop() : true);
	bool createBottom = (hints ? hints->createBottom() : true);
	float dx = mHalfLengths.x;
	float dy = mHalfLengths.y;
	float dz = mHalfLengths.z;
	glBegin(GL_QUADS); // 开始绘制立方体，共6个面，绘制时注意顶点顺序逆时针方向（从体外向体内看时）
	if (createBody) { //绕Z轴的4个面。
		// - y 面
		glNormal3f(0.0f, -1.0f, 0.0f); //外法向量
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-dx, -dy, dz);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-dx, -dy, -dz);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(dx, -dy, -dz);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(dx, -dy, dz);
		// + y 面
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(dx, dy, dz);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(dx, dy, -dz);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-dx, dy, -dz);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-dx, dy, dz);
		// + x 面
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(dx, -dy, dz);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(dx, -dy, -dz);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(dx, dy, -dz);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(dx, dy, dz);
		// - x 面
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-dx, dy, dz);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-dx, dy, -dz);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-dx, -dy, -dz);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-dx, -dy, dz);
	}
	if (createTop) {
		// + z 面
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-dx, dy, dz);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-dx, -dy, dz);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(dx, -dy, dz);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(dx, dy, dz);
	}
	if (createBottom) {
		// - z 面
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(dx, dy, -dz);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(dx, -dy, -dz);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-dx, -dy, -dz);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-dx, dy, -dz);
	}
	glEnd();
}