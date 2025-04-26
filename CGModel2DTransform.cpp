#include "pch.h"
#include "UIEventHandler.h"
#include "CGRenderable.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CGModel2DTransform : public UIEventHandler
{
public:
    CGModel2DTransform(CGRenderable* node, GLFWwindow* window = nullptr)
        : mNode(node), mPivotPoint(0.0f), mIsDragging(false), mIsRotating(false), mLastCursorPos(0.0)
    {
        if (window) {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            mLastCursorPos = glm::dvec2(x, y);
        }
    }

    ~CGModel2DTransform() = default;

    EventType GetType() override {
        return EventType::Model2DTransform;
    }

    int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override {
        if (!mNode || !window) return 0;

        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                double x, y;
                glfwGetCursorPos(window, &x, &y);

                if (mods & GLFW_MOD_SHIFT) {
                    // Shift+左键：设置旋转中心（世界坐标）
                    mPivotPoint = glm::vec3(x, y, 0.0f);
                }
                else {
                    // 普通左键：开始平移
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

    int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override {
        if (!mNode || (!mIsDragging && !mIsRotating)) return 0;

        glm::dvec2 currentPos(xpos, ypos);
        glm::dvec2 delta = currentPos - mLastCursorPos;

        if (mIsDragging) {
            ApplyTranslation(glm::vec2(delta));
        }
        else if (mIsRotating) {
            // 计算基于旋转中心的相对角度（弧度）
            glm::vec2 pivotToLast = glm::vec2(mLastCursorPos) - glm::vec2(mPivotPoint);
            glm::vec2 pivotToCurrent = glm::vec2(currentPos) - glm::vec2(mPivotPoint);

            float angle = atan2(pivotToCurrent.y, pivotToCurrent.x) -
                atan2(pivotToLast.y, pivotToLast.x);

            ApplyRotation(glm::degrees(angle));
        }

        mLastCursorPos = currentPos;
        return 1;
    }

    int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) override {
        if (!mNode) return 0;

        // 滚轮缩放（灵敏度可调）
        float scaleFactor = 1.0f + static_cast<float>(yoffset) * 0.05f;
        ApplyScale(scaleFactor);
        return 1;
    }

    int Cancel(GLFWwindow* window) override {
        mIsDragging = false;
        mIsRotating = false;
        return 1;
    }

protected:
    CGRenderable* mNode;
    glm::vec3 mPivotPoint;
    bool mIsDragging;
    bool mIsRotating;
    glm::dvec2 mLastCursorPos;  // 使用double存储光标位置

    void ApplyTranslation(const glm::vec2& delta) {
        if (!mNode) return;

        glm::mat4 transform = mNode->GetTransform();
        transform = glm::translate(transform, glm::vec3(delta, 0.0f));
        mNode->SetTransform(transform);
    }

    void ApplyRotation(float angleDegrees) {
        if (!mNode) return;

        glm::mat4 transform = mNode->GetTransform();
        transform = glm::translate(transform, mPivotPoint);
        transform = glm::rotate(transform, glm::radians(angleDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::translate(transform, -mPivotPoint);
        mNode->SetTransform(transform);
    }

    void ApplyScale(float scaleFactor) {
        if (!mNode) return;

        glm::mat4 transform = mNode->GetTransform();
        transform = glm::translate(transform, mPivotPoint);
        transform = glm::scale(transform, glm::vec3(scaleFactor));
        transform = glm::translate(transform, -mPivotPoint);
        mNode->SetTransform(transform);
    }
};
