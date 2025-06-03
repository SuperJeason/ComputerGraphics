#pragma once
#include "UIEventHandler.h"
#include "glIncludes.h"
#include "CGCamera.h"
class CameraControl : public UIEventHandler
{
public:
    CameraControl(GLFWwindow* window = nullptr, CGCamera* camera = nullptr);
    ~CameraControl();
    virtual EventType GetType() override; //��������
    //�ٶ�����������ʰȡ�߶���㡢�յ㣬�ƶ����ʱ����Ƥ����
    virtual int OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
    virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
    virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
    virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) override;
    //ȡ������ִ�е�����簴ESC����
    virtual int Cancel(GLFWwindow* window) override;
protected:
    CGCamera* mCamera;
    glm::dvec3 mPrev;
};