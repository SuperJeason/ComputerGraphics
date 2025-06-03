#include "pch.h"
#include "CameraControl.h"
#include "CG2022111073冯杰Doc.h"
//包含View之前要包含Doc
#include "CG2022111073冯杰View.h" //用户交互绘制，并将图形对象通过Doc添加到场景
#include "CameraControl.h"
#include <string>
// 绘制二维线

CameraControl::CameraControl(GLFWwindow* window, CGCamera* camera)
	:UIEventHandler(window), mCamera(camera)
{
}
CameraControl::~CameraControl()
{
}
EventType CameraControl::GetType() //命令类型
{
	return EventType::CameraControl;
}

int CameraControl::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (window == nullptr)
		return -1;
	CCG2022111073冯杰View* view = (CCG2022111073冯杰View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {

		}
	}
	return 0;
}

int CameraControl::OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
	if (window == nullptr)
		return -1;
	CCG2022111073冯杰View* view = (CCG2022111073冯杰View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (yoffset > 0) {
		mCamera->mLeft *= 0.9;
		mCamera->mRight *= 0.9;
		mCamera->mTop *= 0.9;
		mCamera->mBottom *= 0.9;
	}
	else if (yoffset < -0.1) {
		mCamera->mLeft *= 1.11;
		mCamera->mRight *= 1.11;
		mCamera->mTop *= 1.11;
		mCamera->mBottom *= 1.11;
	}
	view->Invalidate();
	view->UpdateWindow();
	view->ShowPrompt("当前 mNearPlane：" + std::to_string(mCamera->mNearPlane));
	return 0;
}


int CameraControl::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
	if (window == nullptr)
		return -1;
	CCG2022111073冯杰View* view = (CCG2022111073冯杰View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

	if (state == GLFW_PRESS) {
		if (xpos > mPrev.x) {
			mCamera->mEye.x -= 10;
		}
		else if (xpos < mPrev.x) {
			mCamera->mEye.x += 10;
		}
		if (ypos > mPrev.y) {
			mCamera->mEye.y += 10;
		}
		else if (ypos < mPrev.y) {
			mCamera->mEye.y -= 10;
		}
		view->Invalidate();
		view->UpdateWindow();
		view->ShowPrompt("当前 mTop：" + std::to_string(mCamera->mTop));
		view->ShowPrompt("当前 mLeft：" + std::to_string(mCamera->mLeft));
		mPrev = glm::dvec3(xpos, ypos, 0);
	}
	return 0;
}

int CameraControl::Cancel(GLFWwindow* window)
{
	if (window == nullptr)
		return -1;
	CCG2022111073冯杰View* view = (CCG2022111073冯杰View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	return 0;
}

int CameraControl::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (window == nullptr)
		return -1;
	CCG2022111073冯杰View* view = (CCG2022111073冯杰View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_EQUAL) {  // + 放大
			mCamera->mLeft *= 0.8;
			mCamera->mRight *= 0.8;
			mCamera->mTop *= 0.8;
			mCamera->mBottom *= 0.8;
		}
		else if (key == GLFW_KEY_MINUS) {  // - 缩小
			mCamera->mLeft *= 1.25;
			mCamera->mRight *= 1.25;
			mCamera->mTop *= 1.25;
			mCamera->mBottom *= 1.25;
		}
		else if (mCamera->mProjectionMode == 0 && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_L) { // 切换左视图
			mCamera->mEye = glm::vec3(-200, 0, 0);  // 从左侧观察
			mCamera->mTarget = glm::vec3(0, 0, 0);  // 看向原点
			mCamera->mUp = glm::vec3(0, 1, 0);      // 保持Y轴向上
		}
		else if (mCamera->mProjectionMode == 0 && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_R) { // 切换右视图
			mCamera->mEye = glm::vec3(200, 0, 0);   // 从右侧观察
			mCamera->mTarget = glm::vec3(0, 0, 0);  // 看向原点
			mCamera->mUp = glm::vec3(0, 1, 0);      // 保持Y轴向上

		}
		else if (mCamera->mProjectionMode == 0 && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_F) { // 切换前视图
			mCamera->mEye = glm::vec3(0, 0, 200);   // 从前方观察
			mCamera->mTarget = glm::vec3(0, 0, 0);  // 看向原点
			mCamera->mUp = glm::vec3(0, 1, 0);      // 保持Y轴向上

		}
		else if (mCamera->mProjectionMode == 0 && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_B) { // 切换后视图
			mCamera->mEye = glm::vec3(0, 0, -200);  // 从后方观察
			mCamera->mTarget = glm::vec3(0, 0, 0);  // 看向原点
			mCamera->mUp = glm::vec3(0, 1, 0);      // 保持Y轴向上

		}
		else if (mCamera->mProjectionMode == 0 && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_T) { // 切换俯视图
			mCamera->mEye = glm::vec3(0, 200, 0);   // 从上方观察
			mCamera->mTarget = glm::vec3(0, 0, 0);  // 看向原点
			mCamera->mUp = glm::vec3(0, 0, -1);     // 上向量调整为-Z方向
		}
		else if (mCamera->mProjectionMode == 0 && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_D) { // 切换顶视图
			mCamera->mEye = glm::vec3(0, -200, 0);  // 从下方观察
			mCamera->mTarget = glm::vec3(0, 0, 0);   // 看向原点
			mCamera->mUp = glm::vec3(0, 0, 1);       // 上向量调整为+Z方向
		}
		else if (mods == GLFW_MOD_SHIFT && key == GLFW_KEY_L) {  // L 左边界左移
			mCamera->mLeft -= 10.0f;
		}
		else if (key == GLFW_KEY_L) {  // l 左边界右移
			mCamera->mLeft += 10.0f;
		}
		else if (mods == GLFW_MOD_SHIFT && key == GLFW_KEY_R) {  // R 右边界左移
			mCamera->mRight -= 10.0f;
		}
		else if (key == GLFW_KEY_R) {  // r 右边界右移
			mCamera->mRight += 10.0f;
		}
		else if (mods == GLFW_MOD_SHIFT && key == GLFW_KEY_B) {  // B 下边界下移
			mCamera->mBottom -= 10.0f;
		}
		else if (key == GLFW_KEY_B) {  // b 下边界上移
			mCamera->mBottom += 10.0f;
		}
		else if (mods == GLFW_MOD_SHIFT && key == GLFW_KEY_T) {  // T 上边界下移
			mCamera->mTop -= 10.0f;
		}
		else if (key == GLFW_KEY_T) {  // t 上边界上移
			mCamera->mTop += 10.0f;
		}
		else if (key == GLFW_KEY_P) {  // P 切换透视投影
			mCamera->mProjectionMode = 1;
		}
		else if (key == GLFW_KEY_O) {  // O 切换正交投影
			mCamera->mProjectionMode = 0;
		}
		view->Invalidate();
		view->UpdateWindow();
	}

	return 0;
}