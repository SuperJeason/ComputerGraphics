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

    // ����ת��
    virtual CGRenderable* asRenderable() { return this; }
    virtual const CGRenderable* asRenderable() const { return this; }

};
