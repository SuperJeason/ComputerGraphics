#include "pch.h"
#include "CGMaterial.h"
IMPLEMENT_SERIAL(CGMaterial, CGRenderState, 1)
CGMaterial::CGMaterial() :
    mFrontAmbient(0.2f, 0.2f, 0.2f, 1.0f),
    mFrontDiffuse(0.8f, 0.8f, 0.8f, 1.0f),
    mFrontSpecular(0.0f, 0.0f, 0.0f, 1.0f),
    mFrontEmission(0.0f, 0.0f, 0.0f, 1.0f),
    mFrontShininess(0.0f),
    mBackAmbient(0.2f, 0.2f, 0.2f, 1.0f),
    mBackDiffuse(0.8f, 0.8f, 0.8f, 1.0f),
    mBackSpecular(0.0f, 0.0f, 0.0f, 1.0f),
    mBackEmission(0.0f, 0.0f, 0.0f, 1.0f),
    mBackShininess(0.0f),
    mColorMaterialFace(EPolygonFace::PF_FRONT_AND_BACK),
    mColorMaterial(EColorMaterial::CM_AMBIENT_AND_DIFFUSE),
    mColorMaterialEnabled(false)
{
}
void CGMaterial::apply(const CGCamera* camera, CGRenderContext* ctx, int index) const
{
    // 设置正面材质属性
    glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(mFrontAmbient));
    glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(mFrontDiffuse));
    glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(mFrontSpecular));
    glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(mFrontEmission));
    glMaterialf(GL_FRONT, GL_SHININESS, mFrontShininess);
    // 设置背面材质属性
    glMaterialfv(GL_BACK, GL_AMBIENT, glm::value_ptr(mBackAmbient));
    glMaterialfv(GL_BACK, GL_DIFFUSE, glm::value_ptr(mBackDiffuse));
    glMaterialfv(GL_BACK, GL_SPECULAR, glm::value_ptr(mBackSpecular));
    glMaterialfv(GL_BACK, GL_EMISSION, glm::value_ptr(mBackEmission));
    glMaterialf(GL_BACK, GL_SHININESS, mBackShininess);
    // 设置颜色材质
    if (mColorMaterialEnabled) {
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial((GLenum)mColorMaterialFace, (GLenum)mColorMaterial);
    }
    else {
        glDisable(GL_COLOR_MATERIAL);
    }
}
void CGMaterialShow::SetMaterialProperties(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, float shininess) {
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, glm::value_ptr(ambient));
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, glm::value_ptr(diffuse));
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, glm::value_ptr(specular));
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}
void CGMaterialShow::SetMetallic() {
    SetMaterialProperties(
        glm::vec4(0.9f, 0.9f, 0.9f, 1.0f),
        glm::vec4(0.9f, 0.9f, 0.9f, 1.0f),
        glm::vec4(0.9f, 0.9f, 0.9f, 1.0f),
        10.0f);
}
void CGMaterialShow::CloseMaterial() {
    glDisable(GL_COLOR_MATERIAL);
    SetMaterialProperties(
        glm::vec4(0.2f, 0.2f, 0.2f, 1.0f),
        glm::vec4(0.8f, 0.8f, 0.8f, 1.0f),
        glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
        0.0f);
}