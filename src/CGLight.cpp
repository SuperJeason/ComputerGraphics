#include "pch.h"
#include "CGLight.h"
#include <glm/gtc/type_ptr.hpp> // 用于glm::value_ptr

IMPLEMENT_SERIAL(CGLight, CGRenderState, 1) // 根据实际基类调整

// 构造函数
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

// 拷贝构造函数
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

// 序列化实现
void CGLight::Serialize(CArchive& ar) {
    CGRenderState::Serialize(ar); // 基类数据

    if (ar.IsStoring()) {
        // 写入GLM向量数据（直接操作底层float数组）
        ar.Write(glm::value_ptr(mAmbient), 4);
        ar.Write(glm::value_ptr(mDiffuse), 4);
        ar.Write(glm::value_ptr(mSpecular), 4);
        ar.Write(glm::value_ptr(mPosition), 4);
        ar.Write(glm::value_ptr(mSpotDirection), 3); // 只存储xyz
        ar << mSpotExponent << mSpotCutoff
            << mConstantAttenuation << mLinearAttenuation << mQuadraticAttenuation
            << mEnabled;
    }
    else {
        // 读取GLM向量数据
        ar.Read(glm::value_ptr(mAmbient), 4);
        ar.Read(glm::value_ptr(mDiffuse), 4);
        ar.Read(glm::value_ptr(mSpecular), 4);
        ar.Read(glm::value_ptr(mPosition), 4);
        ar.Read(glm::value_ptr(mSpotDirection), 3);
        ar >> mSpotExponent >> mSpotCutoff
            >> mConstantAttenuation >> mLinearAttenuation >> mQuadraticAttenuation
            >> mEnabled;
        mSpotDirection.w = 0.0f; // 确保w分量为0
    }
}

// 应用光照设置
void CGLight::apply(int index, const CGCamera* camera, CGRenderContext* ctx) const {
    if (index < 0 || index >= GL_MAX_LIGHTS) {
        return; // 确保光源索引有效
    }

    GLenum light = GL_LIGHT0 + index;
    if (!mEnabled) {
        glDisable(light);
        return;
    }

    glEnable(light);

    // 1. 设置光照颜色属性（环境光/漫反射/镜面反射）
    glLightfv(light, GL_AMBIENT, glm::value_ptr(mAmbient));
    glLightfv(light, GL_DIFFUSE, glm::value_ptr(mDiffuse));
    glLightfv(light, GL_SPECULAR, glm::value_ptr(mSpecular));

    // 2. 处理光源位置/方向（需转换到视图空间）
    glm::vec4 viewSpacePos = mPosition;
    if (camera) {
        viewSpacePos = camera->viewMatrix() * viewSpacePos;
    }
    glLightfv(light, GL_POSITION, glm::value_ptr(viewSpacePos));

    // 3. 聚光灯特性（仅在聚光灯模式下设置）
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
        // 非聚光灯时显式禁用聚光特性
        glLightf(light, GL_SPOT_CUTOFF, 180.0f);
    }

    // 4. 衰减系数（仅对位置光源有效）
    if (mPosition.w != 0.0f) { // 仅当w=1（点光源/聚光灯）时设置衰减
        glLightf(light, GL_CONSTANT_ATTENUATION, mConstantAttenuation);
        glLightf(light, GL_LINEAR_ATTENUATION, mLinearAttenuation);
        glLightf(light, GL_QUADRATIC_ATTENUATION, mQuadraticAttenuation);
    }
    else {
        // 方向光源时重置衰减系数
        glLightf(light, GL_CONSTANT_ATTENUATION, 1.0f);
        glLightf(light, GL_LINEAR_ATTENUATION, 0.0f);
        glLightf(light, GL_QUADRATIC_ATTENUATION, 0.0f);
    }
}
