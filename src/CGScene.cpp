#include "pch.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CCGRenderContext.h"
#include "CGNode.h"

IMPLEMENT_SERIAL(CGScene, CGObject, 1)
CGScene::CGScene()
{
    mlightmodel = std::make_shared<CGLightModel>();
    mlightmodel->setAmbientColor(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));   // 设置全局环境光
    mlightmodel->setLocalViewer(true);
    mlightmodel->setTwoSide(true);

    // 点光源：在机器人右前方
    auto pointLight = std::make_shared<CGLight>();
    pointLight->mPosition = glm::vec4(0.0f, 600.0f, 0.0f, 1.0f); // 点光源位置
    pointLight->mSpotDirection = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    pointLight->mDiffuse = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);    // 亮度加倍
    pointLight->mSpecular = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);   // 高光加倍
    pointLight->mAmbient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f); // 
    pointLight->mConstantAttenuation = 1.0f;
    pointLight->mLinearAttenuation = 0.0005f;       // 从0.001减小为0.0005 (减小50%)
    pointLight->mQuadraticAttenuation = 0.001f;
    pointLight->setEnabled(false);  // 启用点光源
    mLights.push_back(pointLight);

    // 平行光：从左上方向照射
    auto directionalLight = std::make_shared<CGLight>();
    directionalLight->mPosition = glm::vec4(-1.0f, 1.0f, -1.0f, 0.0f); // 平行光方向（w=0表示平行光）
    directionalLight->mDiffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // 较强的漫反射
    directionalLight->mSpecular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // 中等镜面反射
    directionalLight->mAmbient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f); // 中等环境光
    directionalLight->setEnabled(true);  // 启用平行
    mLights.push_back(directionalLight);

    // 聚光灯：从上方照射
    auto spotLight = std::make_shared<CGLight>();
    spotLight->mPosition = glm::vec4(0.0f, 800.0f, 0.0f, 1.0f); // 降低聚光灯位置，使其更接近场景中心
    spotLight->mSpotDirection = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f); // 聚光灯方向（向下）
    spotLight->mSpotCutoff = 60.0f; // 调整聚光灯张角
    spotLight->mSpotExponent = 1.0f; // 调整衰减指数
    spotLight->mDiffuse = glm::vec4(10.0f, 10.0f, 10.0f, 1.0f);
    spotLight->mSpecular = glm::vec4(10.0f, 10.0f, 10.0f, 1.0f);
    spotLight->mAmbient = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // 环境光强度
    spotLight->mConstantAttenuation = 1.0f;
    spotLight->mLinearAttenuation = 0.001f; // 调整线性衰减
    spotLight->mQuadraticAttenuation = 0.0001f; // 调整二次衰减
    spotLight->setEnabled(false);
    mLights.push_back(spotLight);

    SetMainCamera(std::make_shared<CGCamera>());
    SetSceneData(std::make_shared<CGTransform>());

}
CGScene::~CGScene()
{
}


void CGScene::Serialize(CArchive& ar)
{
    CGObject::Serialize(ar); //先调用基类的序列化函数，再序列化自己的成员（根据需要）
    if (ar.IsStoring()) //保存
    {
        //ar << ; //保存自身需要保存的数据成员。<<运算符支持的类型查阅CArchive使用说明
    }
    else //读取
    {
        //ar >> ;
    }
}
void CGScene::SetSceneData(std::shared_ptr<CGNode> root)
{
    if (!root->asGroup()) //此处要求Group或其派生类才能作为图形场景实例树根节点
        return;
    mRoot = root;
}
//渲染场景
bool CGScene::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
    if (mRoot == nullptr || pRC == nullptr || pCamera == nullptr)
        return false;
    //场景节点更新
    //相机投影
    //pCamera->Projection(pCamera->ProjectionMode());
    //绘制
    // 启用深度测试
    glEnable(GL_DEPTH_TEST);

    // 启用光照相关功能
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    // glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // 启用法线归一化
    glEnable(GL_NORMALIZE);
    mRoot->update();
    //相机投影
    pCamera->Projection(pCamera->ProjectionMode());

    // 仅在启用光照时应用光源和光照模型
    if (mlightmodel) {
        mlightmodel->apply(pCamera, pRC, 0);
    }

    // 应用所有光源
    int lightIndex = 0;
    for (const auto& light : mLights) {
        if (light && light->enabled()) {
            light->apply(lightIndex++, pCamera, pRC);
        }
    }

    mlightmodel->apply(pCamera, pRC, 0);
    mRoot->Render(pRC, pCamera);
    DrawWCS(pCamera);
    return true;
}

//void CGScene::DrawWCS(CGCamera* pCamera)
//{
//	//坐标自定义，在使用规范化坐标时，需将坐标调整到(-1，1)
//	//glm::vec3 xs(-100, 0, 0), xe(100, 0, 0);
//	//glm::vec3 ys(0, -100, 0), ye(0, 100, 0);
//	//glm::vec3 zs(0, 0, -100), ze(0, 0, 100);
//	////X轴红色、Y轴绿色、Z轴蓝色
//	//glBegin(GL_LINES);
//	//glColor3f(1.0f, 0.0f, 0.0f);
//	//glVertex3fv(glm::value_ptr(xs));
//	//glVertex3fv(glm::value_ptr(xe));
//	//glColor3f(0.0f, 1.0f, 0.0f);
//	//glVertex3fv(glm::value_ptr(ys));
//	//glVertex3fv(glm::value_ptr(ye));
//	//glColor3f(0.0f, 0.0f, 1.0f);
//	//glVertex3fv(glm::value_ptr(zs));
//	//glVertex3fv(glm::value_ptr(ze));
//	//glEnd();
//
//	glm::vec3 xs(-100, 0, 0), xe(100, 0, 0);
//	glm::vec3 ys(0, -100, 0), ye(0, 100, 0);
//	glm::vec3 zs(0, 0, -100), ze(0, 0, 100);
//	glBegin(GL_LINES);
//	glColor3f(1.0f, 0.0f, 0.0f); // Red for X-axis
//	glVertex3fv(glm::value_ptr(xs));
//	glVertex3fv(glm::value_ptr(xe));
//	glColor3f(0.0f, 1.0f, 0.0f); // Green for Y-axis
//	glVertex3fv(glm::value_ptr(ys));
//	glVertex3fv(glm::value_ptr(ye));
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue for Z-axis
//	glVertex3fv(glm::value_ptr(zs));
//	glVertex3fv(glm::value_ptr(ze));
//	glEnd();
//	// Re-enable lighting for subsequent rendering
//	glEnable(GL_LIGHTING);
//	// Reset color to avoid affecting other objects
//	glColor3f(1.0f, 1.0f, 1.0f);
//}

void DrawWireSphere(float radius, int slices, int stacks)
{
    // 保存当前矩阵状态
    glPushMatrix();

    const float PI = 3.14159265358979323846f;
    float theta, phi;

    // 绘制纬线
    for (int i = 0; i < stacks; i++) {
        phi = PI * (float(i) / float(stacks) - 0.5f); // -π/2 到 π/2
        float next_phi = PI * (float(i + 1) / float(stacks) - 0.5f);

        glBegin(GL_LINE_LOOP);
        for (int j = 0; j <= slices; j++) {
            theta = 2.0f * PI * float(j) / float(slices);
            float x = radius * cosf(theta) * cosf(phi);
            float y = radius * sinf(phi);
            float z = radius * sinf(theta) * cosf(phi);
            glVertex3f(x, y, z);
        }
        glEnd();
    }

    // 绘制经线
    for (int i = 0; i < slices; i++) {
        theta = 2.0f * PI * float(i) / float(slices);
        glBegin(GL_LINE_STRIP);
        for (int j = 0; j <= stacks; j++) {
            phi = PI * (float(j) / float(stacks) - 0.5f);
            float x = radius * cosf(theta) * cosf(phi);
            float y = radius * sinf(phi);
            float z = radius * sinf(theta) * cosf(phi);
            glVertex3f(x, y, z);
        }
        glEnd();
    }

    // 恢复矩阵状态
    glPopMatrix();
}

void CGScene::DrawWCS(CGCamera* pCamera)
{
    // 保存当前OpenGL状态
    glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);  // 禁用光照以便看到纯色标记
    glDisable(GL_TEXTURE_2D);

    // 绘制坐标轴
    glm::vec3 xs(-100, 0, 0), xe(100, 0, 0);
    glm::vec3 ys(0, -100, 0), ye(0, 100, 0);
    glm::vec3 zs(0, 0, -100), ze(0, 0, 100);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // X轴红色
    glVertex3fv(glm::value_ptr(xs));
    glVertex3fv(glm::value_ptr(xe));
    glColor3f(0.0f, 1.0f, 0.0f); // Y轴绿色
    glVertex3fv(glm::value_ptr(ys));
    glVertex3fv(glm::value_ptr(ye));
    glColor3f(0.0f, 0.0f, 1.0f); // Z轴蓝色
    glVertex3fv(glm::value_ptr(zs));
    glVertex3fv(glm::value_ptr(ze));
    glEnd();

    // 绘制所有启用光源的位置标记
    for (const auto& light : mLights)
    {
        if (light && light->enabled())
        {
            // 只绘制有具体位置的光源（点光源和聚光灯）
            if (light->mPosition.w == 1.0f)
            {
                bool isSpotlight = glm::length(glm::vec3(light->mSpotDirection)) > 0.001f;

                glm::vec3 color = isSpotlight ?
                    glm::vec3(0.0f, 0.5f, 1.0f) :  // 蓝色聚光灯
                    glm::vec3(1.0f, 1.0f, 0.0f);   // 黄色点光源

                // 设置标记位置
                glm::vec3 position(light->mPosition);

                // 绘制光源标记球体
                glPushMatrix();
                glTranslatef(position.x, position.y, position.z);
                glColor3fv(glm::value_ptr(color));

                // 使用自定义的球体绘制函数（不使用GLUT）
                DrawWireSphere(15.0f, 16, 12); // 参数：半径、经线数、纬线数

                glPopMatrix();

                // 如果是聚光灯，额外绘制方向箭头
                if (glm::length(glm::vec3(light->mSpotDirection)) > 0.001f)
                {
                    glm::vec3 dir(light->mSpotDirection);

                    // 绘制方向线
                    glBegin(GL_LINES);
                    glColor3fv(glm::value_ptr(color));
                    glm::vec3 end = position + dir * 50.0f;
                    glVertex3fv(glm::value_ptr(position));
                    glVertex3fv(glm::value_ptr(end));
                    glEnd();

                    // 绘制方向箭头
                    glPushMatrix();
                    glTranslatef(end.x, end.y, end.z);

                    // 将方向朝向光源方向
                    glm::vec3 up = glm::abs(glm::dot(dir, glm::vec3(0, 1, 0)) > 0.9f ?
                        glm::vec3(1, 0, 0) : glm::vec3(0, 1, 0));
                    glm::mat4 lookAt = glm::inverse(glm::lookAt(glm::vec3(0), -dir, up));
                    glMultMatrixf(glm::value_ptr(lookAt));

                    // 绘制箭头（小金字塔）
                    float arrowSize = 10.0f;
                    glBegin(GL_LINES);
                    glVertex3f(0, 0, 0); glVertex3f(arrowSize, arrowSize, arrowSize);
                    glVertex3f(0, 0, 0); glVertex3f(-arrowSize, arrowSize, arrowSize);
                    glVertex3f(0, 0, 0); glVertex3f(arrowSize, -arrowSize, arrowSize);
                    glVertex3f(0, 0, 0); glVertex3f(-arrowSize, -arrowSize, arrowSize);
                    glEnd();

                    glPopMatrix();
                }
            }
        }
    }

    // 恢复OpenGL状态
    glEnable(GL_LIGHTING);
    glPopAttrib();
}