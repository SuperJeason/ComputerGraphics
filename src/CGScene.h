#pragma once
#include "CGObject.h"
#include <vector>
#include <memory>
#include "CGLight.h"
#include "CGLightModel.h"  // 需要包含光照模型头文件

class CGCamera; // 预声明
class CGRenderContext; // 预声明
class CGNode; // 预声明

class CGScene : public CGObject
{
    DECLARE_SERIAL(CGScene)
public:
    CGScene();
    virtual ~CGScene();

    virtual void Serialize(CArchive& ar) override;

    // 渲染场景
    bool Render(CGRenderContext* pRC, CGCamera* pCamera);

    void SetMainCamera(std::shared_ptr<CGCamera> camera) { mCamera = camera; }
    CGCamera* GetMainCamera() { return mCamera.get(); }

    // 场景中的图形对象，一般是Group或Transform
    void SetSceneData(std::shared_ptr<CGNode> root);
    CGNode* GetSceneData() { return mRoot.get(); }

    // 新增方法：获取光源列表（供外部访问）
    std::vector<std::shared_ptr<CGLight>>& GetLights() { return mLights; }

    // 新增方法：获取光照模型
    std::shared_ptr<CGLightModel> GetLightModel() { return mlightmodel; }

protected:
    std::shared_ptr<CGCamera> mCamera = nullptr;  // 场景主相机
    std::shared_ptr<CGNode> mRoot = nullptr;      // 场景树根节点

    // 新增成员变量
    std::shared_ptr<CGLightModel> mlightmodel;    // 光照模型
    std::vector<std::shared_ptr<CGLight>> mLights; // 光源列表

private:
    // 新增私有方法
    void DrawWCS(CGCamera* pCamera);              // 绘制世界坐标系
};
