#pragma once
#include "CGRenderState.h"
#include <glm/glm.hpp>
#include "CGCamera.h"
class CGLight : public CGRenderState
{
	DECLARE_SERIAL(CGLight)
public:
	CGLight();
	//CGLight(const CString& name);
	CGLight(const CGLight& other);
	virtual ~CGLight() = default;
	//序列化
	virtual void Serialize(CArchive& ar);
	//其他辅助函数自行补充
	void setEnabled(bool enabled) { mEnabled = enabled; }
	bool enabled() const { return mEnabled; }
	//应用，重写实现多态
	virtual void apply(int index, const CGCamera* camera, CGRenderContext* ctx) const;
public:
	glm::vec4 mAmbient; //环境光组成（各项取值0~1）
	glm::vec4 mDiffuse; //漫反射组成（各项取值0~1）
	glm::vec4 mSpecular; //镜面放射组成（各项取值0~1）
	glm::vec4 mPosition; //位置（可实现位置光源、方向光源）
	glm::vec4 mSpotDirection; //聚光方向
	float mSpotExponent; //聚光程度（0~128）
	float mSpotCutoff; //发散角度（0~180）
	float mConstantAttenuation; //衰减常系数（大于等于0）
	float mLinearAttenuation; //衰减一次系数（大于等于0）
	float mQuadraticAttenuation; //衰减二次系数（大于等于0）
	bool mEnabled; //开启光源（要打开光照）
};
