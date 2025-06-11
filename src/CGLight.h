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
	//���л�
	virtual void Serialize(CArchive& ar);
	//���������������в���
	void setEnabled(bool enabled) { mEnabled = enabled; }
	bool enabled() const { return mEnabled; }
	//Ӧ�ã���дʵ�ֶ�̬
	virtual void apply(int index, const CGCamera* camera, CGRenderContext* ctx) const;
public:
	glm::vec4 mAmbient; //��������ɣ�����ȡֵ0~1��
	glm::vec4 mDiffuse; //��������ɣ�����ȡֵ0~1��
	glm::vec4 mSpecular; //���������ɣ�����ȡֵ0~1��
	glm::vec4 mPosition; //λ�ã���ʵ��λ�ù�Դ�������Դ��
	glm::vec4 mSpotDirection; //�۹ⷽ��
	float mSpotExponent; //�۹�̶ȣ�0~128��
	float mSpotCutoff; //��ɢ�Ƕȣ�0~180��
	float mConstantAttenuation; //˥����ϵ�������ڵ���0��
	float mLinearAttenuation; //˥��һ��ϵ�������ڵ���0��
	float mQuadraticAttenuation; //˥������ϵ�������ڵ���0��
	bool mEnabled; //������Դ��Ҫ�򿪹��գ�
};
