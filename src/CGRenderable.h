#pragma once
#include "CGNode.h"
#include <glm/glm.hpp> // 添加GLM支持

class CGRenderContext; // 预声明
class CGCamera;        // 预声明

class CGRenderable : public CGNode
{
    DECLARE_SERIAL(CGRenderable)
public:
    CGRenderable();
    virtual ~CGRenderable();

    // 序列化
    virtual void Serialize(CArchive& ar) override;

    // 绘制对象（在派生类中重写）
    virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);

    // 类型转换
    virtual CGRenderable* asRenderable() { return this; }
    virtual const CGRenderable* asRenderable() const { return this; }

};
