#pragma once
#include "CGGroup.h"
class CGTransform : public CGGroup
{
	DECLARE_SERIAL(CGTransform)
public:
	CGTransform();
	virtual ~CGTransform();
	virtual void Serialize(CArchive& ar) override;
	//渲染场景
	bool Render(CGRenderContext * pRC, CGCamera * pCamera);
	virtual CGTransform* asTransform() { return this; }
	virtual const CGTransform* asTransform() const { return this; }
protected:
	bool mWorldMatrixDirty = true; //
	glm::mat4 mLocalMatrix = glm::mat4(1.0f); //局部（到上级的矩阵）
	glm::mat4 mWorldMatrix = glm::mat4(1.0f); //全局（到场景坐标系）
protected:
	void dirtyWorldMatrix();
public:
	//模型坐标系在父节点中的定位
	const glm::mat4& localMatrix() const { return mLocalMatrix; }
	glm::mat4& localMatrix() { return mLocalMatrix; }
	void setLocalMatrix(const glm::mat4& m);
	//相对父节点的变换
	void translate(float tx, float ty, float tz); //平移
	void translate(const glm::vec3& t); //平移
	void scale(float sx, float sy, float sz); //缩放
	void rotate(float degrees, float x, float y, float z); //旋转
	void preMultiply(const glm::mat4& m); //左乘矩阵m
	void postMultiply(const glm::mat4& m); //右乘矩阵 m
};