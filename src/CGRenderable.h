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
protected:
    bool mDisplayListEnabled = false;
    bool mDisplayListDirty = true;
    GLuint mDisplayList = 0;
protected:
    CGRenderable(const CGRenderable& other) : CGNode(other)
    {
    }
    CGRenderable& operator=(const CGRenderable&) = default;
    virtual void buildDisplayList() {} //派生类中重写
public:
    bool isDisplayListEnabled() const { return mDisplayListEnabled; }
    void setDisplayListEnabled(bool enabled) { mDisplayListEnabled = enabled; }
    bool displayListDirty() const { return mDisplayListDirty; }
    void setDisplayListDirty(bool dirty) { mDisplayListDirty = dirty; }
    GLuint displayList() const { return mDisplayList; }
    void setDisplayList(unsigned int disp_list) { mDisplayList = disp_list; }
    void deleteDisplayList()
    {
        if (displayList())
            glDeleteLists(displayList(), 1);
        mDisplayList = 0;
    }
};
