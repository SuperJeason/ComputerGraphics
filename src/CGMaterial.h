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

    // ��������
    glm::vec4 mFrontAmbient;    // ���滷���ⷴ��
    glm::vec4 mFrontDiffuse;    // ����������
    glm::vec4 mFrontSpecular;   // ���澵�淴��
    glm::vec4 mFrontEmission;   // �����Է���
    float mFrontShininess;      // ��������

    glm::vec4 mBackAmbient;     // ���滷���ⷴ��
    glm::vec4 mBackDiffuse;     // ����������
    glm::vec4 mBackSpecular;    // ���澵�淴��
    glm::vec4 mBackEmission;    // �����Է���
    float mBackShininess;       // ��������

    EPolygonFace mColorMaterialFace;    // ��ɫ������
    EColorMaterial mColorMaterial;      // ��ɫ��������
    bool mColorMaterialEnabled;         // �Ƿ�������ɫ����
};

// ����ԭ�е�CGMaterialShow������������;
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