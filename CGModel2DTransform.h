#pragma once

#include "UIEventHandler.h"
#include "CGRenderable.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class CGModel2DTransform : public UIEventHandler
{
public:
    // Constructor with the object to be transformed (e.g., line segments, polylines)
    CGModel2DTransform(CGRenderable* node, GLFWwindow* window = nullptr);
    ~CGModel2DTransform();

    virtual EventType GetType() override; // Command type

    // Mouse wheel for scaling, left button drag for translation, right button drag for rotation
    virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;
    virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;
    virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) override;

    // Cancel current command (e.g., when ESC is pressed)
    virtual int Cancel(GLFWwindow* window) override;

protected:
    CGRenderable* mNode; // The model being manipulated
    glm::vec3 mPivotPoint; // Transformation reference point (set with Shift+Left Click)

    // Additional member variables needed for implementation
    bool mIsDragging;
    bool mIsRotating;
    glm::dvec2 mLastCursorPos;
};
