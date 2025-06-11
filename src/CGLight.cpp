#include "pch.h"
#include "CGLight.h"
#include <glm/gtc/type_ptr.hpp> // ����glm::value_ptr

IMPLEMENT_SERIAL(CGLight, CGRenderState, 1) // ����ʵ�ʻ������

// ���캯��
CGLight::CGLight() :
    mAmbient(0.0f, 0.0f, 0.0f, 1.0f),
    mDiffuse(1.0f, 1.0f, 1.0f, 1.0f),
    mSpecular(1.0f, 1.0f, 1.0f, 1.0f),
    mPosition(0.0f, 0.0f, 0.0f, 1.0f),
    mSpotDirection(0.0f, 0.0f, -1.0f, 0.0f),
    mSpotExponent(0.0f),
    mSpotCutoff(180.0f),
    mConstantAttenuation(1.0f),
    mLinearAttenuation(0.0f),
    mQuadraticAttenuation(0.0f),
    mEnabled(true) {
}

// �������캯��
CGLight::CGLight(const CGLight& other) :
    CGRenderState(other),
    mAmbient(other.mAmbient),
    mDiffuse(other.mDiffuse),
    mSpecular(other.mSpecular),
    mPosition(other.mPosition),
    mSpotDirection(other.mSpotDirection),
    mSpotExponent(other.mSpotExponent),
    mSpotCutoff(other.mSpotCutoff),
    mConstantAttenuation(other.mConstantAttenuation),
    mLinearAttenuation(other.mLinearAttenuation),
    mQuadraticAttenuation(other.mQuadraticAttenuation),
    mEnabled(other.mEnabled) {
}

// ���л�ʵ��
void CGLight::Serialize(CArchive& ar) {
    CGRenderState::Serialize(ar); // ��������

    if (ar.IsStoring()) {
        // д��GLM�������ݣ�ֱ�Ӳ����ײ�float���飩
        ar.Write(glm::value_ptr(mAmbient), 4);
        ar.Write(glm::value_ptr(mDiffuse), 4);
        ar.Write(glm::value_ptr(mSpecular), 4);
        ar.Write(glm::value_ptr(mPosition), 4);
        ar.Write(glm::value_ptr(mSpotDirection), 3); // ֻ�洢xyz
        ar << mSpotExponent << mSpotCutoff
            << mConstantAttenuation << mLinearAttenuation << mQuadraticAttenuation
            << mEnabled;
    }
    else {
        // ��ȡGLM��������
        ar.Read(glm::value_ptr(mAmbient), 4);
        ar.Read(glm::value_ptr(mDiffuse), 4);
        ar.Read(glm::value_ptr(mSpecular), 4);
        ar.Read(glm::value_ptr(mPosition), 4);
        ar.Read(glm::value_ptr(mSpotDirection), 3);
        ar >> mSpotExponent >> mSpotCutoff
            >> mConstantAttenuation >> mLinearAttenuation >> mQuadraticAttenuation
            >> mEnabled;
        mSpotDirection.w = 0.0f; // ȷ��w����Ϊ0
    }
}

// Ӧ�ù�������
void CGLight::apply(int index, const CGCamera* camera, CGRenderContext* ctx) const {
    if (index < 0 || index >= GL_MAX_LIGHTS) {
        return; // ȷ����Դ������Ч
    }

    GLenum light = GL_LIGHT0 + index;
    if (!mEnabled) {
        glDisable(light);
        return;
    }

    glEnable(light);

    // 1. ���ù�����ɫ���ԣ�������/������/���淴�䣩
    glLightfv(light, GL_AMBIENT, glm::value_ptr(mAmbient));
    glLightfv(light, GL_DIFFUSE, glm::value_ptr(mDiffuse));
    glLightfv(light, GL_SPECULAR, glm::value_ptr(mSpecular));

    // 2. �����Դλ��/������ת������ͼ�ռ䣩
    glm::vec4 viewSpacePos = mPosition;
    if (camera) {
        viewSpacePos = camera->viewMatrix() * viewSpacePos;
    }
    glLightfv(light, GL_POSITION, glm::value_ptr(viewSpacePos));

    // 3. �۹�����ԣ����ھ۹��ģʽ�����ã�
    if (mSpotCutoff <= 90.0f) {
        glm::vec3 viewSpaceDir = glm::vec3(mSpotDirection);
        if (camera) {
            viewSpaceDir = glm::mat3(camera->viewMatrix()) * viewSpaceDir;
        }
        glLightfv(light, GL_SPOT_DIRECTION, glm::value_ptr(glm::vec4(viewSpaceDir, 0.0f)));
        glLightf(light, GL_SPOT_EXPONENT, mSpotExponent);
        glLightf(light, GL_SPOT_CUTOFF, mSpotCutoff);
    }
    else {
        // �Ǿ۹��ʱ��ʽ���þ۹�����
        glLightf(light, GL_SPOT_CUTOFF, 180.0f);
    }

    // 4. ˥��ϵ��������λ�ù�Դ��Ч��
    if (mPosition.w != 0.0f) { // ����w=1�����Դ/�۹�ƣ�ʱ����˥��
        glLightf(light, GL_CONSTANT_ATTENUATION, mConstantAttenuation);
        glLightf(light, GL_LINEAR_ATTENUATION, mLinearAttenuation);
        glLightf(light, GL_QUADRATIC_ATTENUATION, mQuadraticAttenuation);
    }
    else {
        // �����Դʱ����˥��ϵ��
        glLightf(light, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(light, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(light, GL_QUADRATIC_ATTENUATION, 0.0f);
    }
}
