#pragma once
#include "CGRenderState.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class CGMaterial : public CGRenderState
{
    DECLARE_SERIAL(CGMaterial)
public:
    CGMaterial();
    virtual ~CGMaterial() = default;
    virtual ERenderState type() const { return ERenderState::RS_Material; }
    virtual void apply(const CGCamera* camera, CGRenderContext* ctx, int index = 0) const override;

    // 材质属性
    glm::vec4 mFrontAmbient;    // 正面环境光反射
    glm::vec4 mFrontDiffuse;    // 正面漫反射
    glm::vec4 mFrontSpecular;   // 正面镜面反射
    glm::vec4 mFrontEmission;   // 正面自发光
    float mFrontShininess;      // 正面光泽度

    glm::vec4 mBackAmbient;     // 背面环境光反射
    glm::vec4 mBackDiffuse;     // 背面漫反射
    glm::vec4 mBackSpecular;    // 背面镜面反射
    glm::vec4 mBackEmission;    // 背面自发光
    float mBackShininess;       // 背面光泽度

    EPolygonFace mColorMaterialFace;    // 颜色材质面
    EColorMaterial mColorMaterial;      // 颜色材质类型
    bool mColorMaterialEnabled;         // 是否启用颜色材质
};

// 保留原有的CGMaterialShow类用于其他用途
class CGMaterialShow
{
public:
    CGMaterialShow() {}
    ~CGMaterialShow() {}
    void SetMetallic();
    void CloseMaterial();
private:
    void SetMaterialProperties(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, float shininess);
};