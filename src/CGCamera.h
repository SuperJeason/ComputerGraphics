#pragma once
#include "CGTransform.h"
typedef enum
{
	CF_DO_NOT_CLEAR = 0,
	CF_CLEAR_COLOR = GL_COLOR_BUFFER_BIT,
	CF_CLEAR_DEPTH = GL_DEPTH_BUFFER_BIT,
	CF_CLEAR_STENCIL = GL_STENCIL_BUFFER_BIT,
	CF_CLEAR_COLOR_DEPTH = CF_CLEAR_COLOR + CF_CLEAR_DEPTH,
	CF_CLEAR_COLOR_STENCIL = CF_CLEAR_COLOR + CF_CLEAR_STENCIL,
	CF_CLEAR_DEPTH_STENCIL = CF_CLEAR_DEPTH + CF_CLEAR_STENCIL,
	CF_CLEAR_COLOR_DEPTH_STENCIL = CF_CLEAR_COLOR + CF_CLEAR_DEPTH + CF_CLEAR_STENCIL,
} EClearFlags;
class Viewport : public CGObject
{
	DECLARE_SERIAL(Viewport)
public:
	Viewport();
	Viewport(int x, int y, int w, int h);
	void activate() const;
	void set(int x, int y, int w, int h) { mX = x; mY = y; mWidth = w; mHeight = h; }
	void setX(int x) { mX = x; }
	int x() const { return mX; }
	void setY(int y) { mY = y; }
	int y() const { return mY; }
	void setWidth(int width) { mWidth = width; }
	int width() const { return mWidth; }
	void setHeight(int height) { mHeight = height; }
	int height() const { return mHeight; }
	glm::vec2 center() const { return glm::vec2(mX + mWidth / 2.0f, mY + mHeight / 2.0f); }
	void setClearColor(float r, float g, float b, float a) { mClearColor = glm::vec4(r, g, b, a); }
	void setClearColor(const glm::vec4& color) { mClearColor = color; }
	const glm::vec4& clearColor() const { return mClearColor; }
	void setClearStencil(int stencil) { mClearStencil = stencil; }
	int clearStencil() const { return mClearStencil; }
	void setClearDepth(GLfloat depth) { mClearDepth = depth; }
	GLfloat clearDepth() const { return mClearDepth; }
	void setClearFlags(EClearFlags clear_flags) { mClearFlags = clear_flags; }
	EClearFlags clearFlags() const { return mClearFlags; }
	void setScissorEnabled(bool enable) { mScissorEnabled = enable; }
	bool isScissorEnabled() const { return mScissorEnabled; }
protected:
	int mX = 0;
	int mY = 0;
	int mWidth = 0;
	int mHeight = 0;
	glm::vec4 mClearColor = glm::vec4(0, 0, 0, 1);
	GLfloat mClearDepth = 1.0f;
	int mClearStencil = 0;
	EClearFlags mClearFlags = CF_CLEAR_COLOR_DEPTH;
	bool mScissorEnabled = true;
};


class CGCamera : public CGTransform
{
	DECLARE_SERIAL(CGCamera)
public:
	CGCamera();
	virtual ~CGCamera();
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//mode=0为正交投影（三维），mode=1为透视投影，mode=2或其他为正交投影（二维）
	virtual void Projection(int mode);
	int ProjectionMode() { return mProjectionMode; }
	void SetProjectionMode(int mode) { if (mode >= 0 && mode <= 2) mProjectionMode = mode; }

public:
	int mProjectionMode = 0;
	std::shared_ptr<Viewport> mViewport;
	//观察体定义（在观察坐标系中定义）：近截面上的矩形的左、右、下、上（观察窗口），近截面、远截面
	GLfloat mLeft = -200.0f;
	GLfloat mBottom = -200.0f;
	GLfloat mRight = 200.0f;
	GLfloat mTop = 200.0f;
	GLfloat mNearPlane = 100.0f; //近截面（可视为Eye到近截面的距离）
	GLfloat mFarPlane = 10000.0f; //远截面（最远能看多远）
	glm::vec3 mEye = glm::vec3(0, 0, 200); //相机位置（影响透视投影）
	glm::vec3 mTarget = glm::vec3(0, 0, 0); //被观察点
	glm::vec3 mUp = glm::vec3(0, 1, 0); //向上方向（相机坐标系Y轴对应向量）
public:
	void setViewport(Viewport* viewport) { mViewport = std::shared_ptr<Viewport>(viewport); }
	Viewport* viewport() { return mViewport.get(); }
	const Viewport * viewport() const { return mViewport.get(); }
};