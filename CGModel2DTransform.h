#pragma once

#include "UIEventHandler.h"
#include "CGRenderable.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class CGModel2DTransform : public UIEventHandler
{
public:
    CGModel2DTransform(
        CGNode* node,
        GLFWwindow* window,
        bool isScaleX = false,    
        bool isScaleY = false,    
        glm::vec3 pivotPoint = glm::vec3(0.0f), 
        bool showPivot = false    
    );
    ~CGModel2DTransform();

    virtual EventType GetType() override; 
    virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;

    virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
    virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) override;

    virtual int Cancel(GLFWwindow* window) override;

protected:
    CGNode* mNode; 
    glm::vec3 mPivotPoint;

    bool mIsDragging;
    bool mIsRotating;
    bool mShowPivot;
    bool mIsScaleX;
    bool mIsScaleY;
    glm::dvec2 mLastCursorPos;

    const double M_PI = 3.1415926;
};
