#include "pch.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CCGRenderContext.h"
#include "CGNode.h"

IMPLEMENT_SERIAL(CGScene, CGObject, 1)
CGScene::CGScene()
{
    mlightmodel = std::make_shared<CGLightModel>();
    mlightmodel->setAmbientColor(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));   // ����ȫ�ֻ�����
    mlightmodel->setLocalViewer(true);
    mlightmodel->setTwoSide(true);

    // ���Դ���ڻ�������ǰ��
    auto pointLight = std::make_shared<CGLight>();
    pointLight->mPosition = glm::vec4(0.0f, 600.0f, 0.0f, 1.0f); // ���Դλ��
    pointLight->mSpotDirection = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
    pointLight->mDiffuse = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);    // ���ȼӱ�
    pointLight->mSpecular = glm::vec4(2.0f, 2.0f, 2.0f, 1.0f);   // �߹�ӱ�
    pointLight->mAmbient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f); // 
    pointLight->mConstantAttenuation = 1.0f;
    pointLight->mLinearAttenuation = 0.0005f;       // ��0.001��СΪ0.0005 (��С50%)
    pointLight->mQuadraticAttenuation = 0.001f;
    pointLight->setEnabled(false);  // ���õ��Դ
    mLights.push_back(pointLight);

    // ƽ�й⣺�����Ϸ�������
    auto directionalLight = std::make_shared<CGLight>();
    directionalLight->mPosition = glm::vec4(-1.0f, 1.0f, -1.0f, 0.0f); // ƽ�йⷽ��w=0��ʾƽ�й⣩
    directionalLight->mDiffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // ��ǿ��������
    directionalLight->mSpecular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // �еȾ��淴��
    directionalLight->mAmbient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f); // �еȻ�����
    directionalLight->setEnabled(true);  // ����ƽ��
    mLights.push_back(directionalLight);

    // �۹�ƣ����Ϸ�����
    auto spotLight = std::make_shared<CGLight>();
    spotLight->mPosition = glm::vec4(0.0f, 800.0f, 0.0f, 1.0f); // ���;۹��λ�ã�ʹ����ӽ���������
    spotLight->mSpotDirection = glm::vec4(0.0f, -1.0f, 0.0f, 0.0f); // �۹�Ʒ������£�
    spotLight->mSpotCutoff = 60.0f; // �����۹���Ž�
    spotLight->mSpotExponent = 1.0f; // ����˥��ָ��
    spotLight->mDiffuse = glm::vec4(10.0f, 10.0f, 10.0f, 1.0f);
    spotLight->mSpecular = glm::vec4(10.0f, 10.0f, 10.0f, 1.0f);
    spotLight->mAmbient = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // ������ǿ��
    spotLight->mConstantAttenuation = 1.0f;
    spotLight->mLinearAttenuation = 0.001f; // ��������˥��
    spotLight->mQuadraticAttenuation = 0.0001f; // ��������˥��
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
    CGObject::Serialize(ar); //�ȵ��û�������л������������л��Լ��ĳ�Ա��������Ҫ��
    if (ar.IsStoring()) //����
    {
        //ar << ; //����������Ҫ��������ݳ�Ա��<<�����֧�ֵ����Ͳ���CArchiveʹ��˵��
    }
    else //��ȡ
    {
        //ar >> ;
    }
}
void CGScene::SetSceneData(std::shared_ptr<CGNode> root)
{
    if (!root->asGroup()) //�˴�Ҫ��Group���������������Ϊͼ�γ���ʵ�������ڵ�
        return;
    mRoot = root;
}
//��Ⱦ����
bool CGScene::Render(CGRenderContext* pRC, CGCamera* pCamera)
{
    if (mRoot == nullptr || pRC == nullptr || pCamera == nullptr)
        return false;
    //�����ڵ����
    //���ͶӰ
    //pCamera->Projection(pCamera->ProjectionMode());
    //����
    // ������Ȳ���
    glEnable(GL_DEPTH_TEST);

    // ���ù�����ع���
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    // glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // ���÷��߹�һ��
    glEnable(GL_NORMALIZE);
    mRoot->update();
    //���ͶӰ
    pCamera->Projection(pCamera->ProjectionMode());

    // �������ù���ʱӦ�ù�Դ�͹���ģ��
    if (mlightmodel) {
        mlightmodel->apply(pCamera, pRC, 0);
    }

    // Ӧ�����й�Դ
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
//	//�����Զ��壬��ʹ�ù淶������ʱ���轫���������(-1��1)
//	//glm::vec3 xs(-100, 0, 0), xe(100, 0, 0);
//	//glm::vec3 ys(0, -100, 0), ye(0, 100, 0);
//	//glm::vec3 zs(0, 0, -100), ze(0, 0, 100);
//	////X���ɫ��Y����ɫ��Z����ɫ
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
    // ���浱ǰ����״̬
    glPushMatrix();

    const float PI = 3.14159265358979323846f;
    float theta, phi;

    // ����γ��
    for (int i = 0; i < stacks; i++) {
        phi = PI * (float(i) / float(stacks) - 0.5f); // -��/2 �� ��/2
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

    // ���ƾ���
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

    // �ָ�����״̬
    glPopMatrix();
}

void CGScene::DrawWCS(CGCamera* pCamera)
{
    // ���浱ǰOpenGL״̬
    glPushAttrib(GL_ENABLE_BIT | GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);  // ���ù����Ա㿴����ɫ���
    glDisable(GL_TEXTURE_2D);

    // ����������
    glm::vec3 xs(-100, 0, 0), xe(100, 0, 0);
    glm::vec3 ys(0, -100, 0), ye(0, 100, 0);
    glm::vec3 zs(0, 0, -100), ze(0, 0, 100);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // X���ɫ
    glVertex3fv(glm::value_ptr(xs));
    glVertex3fv(glm::value_ptr(xe));
    glColor3f(0.0f, 1.0f, 0.0f); // Y����ɫ
    glVertex3fv(glm::value_ptr(ys));
    glVertex3fv(glm::value_ptr(ye));
    glColor3f(0.0f, 0.0f, 1.0f); // Z����ɫ
    glVertex3fv(glm::value_ptr(zs));
    glVertex3fv(glm::value_ptr(ze));
    glEnd();

    // �����������ù�Դ��λ�ñ��
    for (const auto& light : mLights)
    {
        if (light && light->enabled())
        {
            // ֻ�����о���λ�õĹ�Դ�����Դ�;۹�ƣ�
            if (light->mPosition.w == 1.0f)
            {
                bool isSpotlight = glm::length(glm::vec3(light->mSpotDirection)) > 0.001f;

                glm::vec3 color = isSpotlight ?
                    glm::vec3(0.0f, 0.5f, 1.0f) :  // ��ɫ�۹��
                    glm::vec3(1.0f, 1.0f, 0.0f);   // ��ɫ���Դ

                // ���ñ��λ��
                glm::vec3 position(light->mPosition);

                // ���ƹ�Դ�������
                glPushMatrix();
                glTranslatef(position.x, position.y, position.z);
                glColor3fv(glm::value_ptr(color));

                // ʹ���Զ����������ƺ�������ʹ��GLUT��
                DrawWireSphere(15.0f, 16, 12); // �������뾶����������γ����

                glPopMatrix();

                // ����Ǿ۹�ƣ�������Ʒ����ͷ
                if (glm::length(glm::vec3(light->mSpotDirection)) > 0.001f)
                {
                    glm::vec3 dir(light->mSpotDirection);

                    // ���Ʒ�����
                    glBegin(GL_LINES);
                    glColor3fv(glm::value_ptr(color));
                    glm::vec3 end = position + dir * 50.0f;
                    glVertex3fv(glm::value_ptr(position));
                    glVertex3fv(glm::value_ptr(end));
                    glEnd();

                    // ���Ʒ����ͷ
                    glPushMatrix();
                    glTranslatef(end.x, end.y, end.z);

                    // ���������Դ����
                    glm::vec3 up = glm::abs(glm::dot(dir, glm::vec3(0, 1, 0)) > 0.9f ?
                        glm::vec3(1, 0, 0) : glm::vec3(0, 1, 0));
                    glm::mat4 lookAt = glm::inverse(glm::lookAt(glm::vec3(0), -dir, up));
                    glMultMatrixf(glm::value_ptr(lookAt));

                    // ���Ƽ�ͷ��С��������
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

    // �ָ�OpenGL״̬
    glEnable(GL_LIGHTING);
    glPopAttrib();
}