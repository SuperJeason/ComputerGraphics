#pragma once
#include "CGNode.h"
#include <glm/glm.hpp> // ���GLM֧��

class CGRenderContext; // Ԥ����
class CGCamera;        // Ԥ����

class CGRenderable : public CGNode
{
    DECLARE_SERIAL(CGRenderable)
public:
    CGRenderable();
    virtual ~CGRenderable();

    // ���л�
    virtual void Serialize(CArchive& ar) override;

    // ���ƶ���������������д��
    virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);

    // ��ȡ/���ñ任����
    virtual glm::mat4 GetTransform() const { return mTransform; }
    virtual void SetTransform(const glm::mat4& transform) { mTransform = transform; }

    // ����ת��
    virtual CGRenderable* asRenderable() { return this; }
    virtual const CGRenderable* asRenderable() const { return this; }

protected:
    glm::mat4 mTransform = glm::mat4(1.0f); // ��ʼ��Ϊ��λ����
};
