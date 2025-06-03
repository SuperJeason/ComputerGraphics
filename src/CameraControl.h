#pragma once
#include "UIEventHandler.h"
#include "glIncludes.h"
#include "CGCamera.h"
class CameraControl : public UIEventHandler
{
public:
    CameraControl(GLFWwindow* window = nullptr, CGCamera* camera = nullptr);
    ~CameraControl();
    virtual EventType GetType() override; //命令类型
    //假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
    virtual int OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
    virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
    virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
    virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) override;
    //取消正在执行的命令（如按ESC键）
    virtual int Cancel(GLFWwindow* window) override;
protected:
    CGCamera* mCamera;
    glm::dvec3 mPrev;
};