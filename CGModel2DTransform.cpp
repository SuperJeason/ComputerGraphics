#include "pch.h"
#include "CGModel2DTransform.h"
#include <glm/gtc/matrix_transform.hpp>

CGModel2DTransform::CGModel2DTransform(CGRenderable* node, GLFWwindow* window)
    : mNode(node), mPivotPoint(0.0f), mIsDragging(false), mIsRotating(false), mLastCursorPos(0.0)
{
    if (window) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        mLastCursorPos = glm::dvec2(x, y);
    }
}

CGModel2DTransform::~CGModel2DTransform() = default;

EventType CGModel2DTransform::GetType()
{
    return EventType::Model2DTransform;
}

int CGModel2DTransform::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (!mNode || !window) return 0;

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            double x, y;
            glfwGetCursorPos(window, &x, &y);

            if (mods & GLFW_MOD_SHIFT) {
                // Shift+Left Click: Set rotation center (world coordinates)
                mPivotPoint = glm::vec3(x, y, 0.0f);
            }
            else {
                // Left Click: Start translation
                mIsDragging = true;
                mLastCursorPos = glm::dvec2(x, y);
            }
        }
        else if (action == GLFW_RELEASE) {
            mIsDragging = false;
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        mIsRotating = (action == GLFW_PRESS);
        if (mIsRotating) {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            mLastCursorPos = glm::dvec2(x, y);
        }
    }

    return 1;
}

int CGModel2DTransform::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    return 0;
}

int CGModel2DTransform::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    if (!mNode) return 0;

   
    return 1;
}

int CGModel2DTransform::Cancel(GLFWwindow* window)
{
    mIsDragging = false;
    mIsRotating = false;
    return 1;
}