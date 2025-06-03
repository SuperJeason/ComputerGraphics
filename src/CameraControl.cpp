#include "pch.h"
#include "CameraControl.h"
#include "CG2022111073���Doc.h"
//����View֮ǰҪ����Doc
#include "CG2022111073���View.h" //�û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ�����
#include "CameraControl.h"
#include <string>
// ���ƶ�ά��

CameraControl::CameraControl(GLFWwindow* window, CGCamera* camera)
	:UIEventHandler(window), mCamera(camera)
{
}
CameraControl::~CameraControl()
{
}
EventType CameraControl::GetType() //��������
{
	return EventType::CameraControl;
}

int CameraControl::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (window == nullptr)
		return -1;
	CCG2022111073���View* view = (CCG2022111073���View*)glfwGetWindowUserPointer(window);
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
	CCG2022111073���View* view = (CCG2022111073���View*)glfwGetWindowUserPointer(window);
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
	view->ShowPrompt("��ǰ mNearPlane��" + std::to_string(mCamera->mNearPlane));
	return 0;
}


int CameraControl::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
	if (window == nullptr)
		return -1;
	CCG2022111073���View* view = (CCG2022111073���View*)glfwGetWindowUserPointer(window);
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
		view->ShowPrompt("��ǰ mTop��" + std::to_string(mCamera->mTop));
		view->ShowPrompt("��ǰ mLeft��" + std::to_string(mCamera->mLeft));
		mPrev = glm::dvec3(xpos, ypos, 0);
	}
	return 0;
}

int CameraControl::Cancel(GLFWwindow* window)
{
	if (window == nullptr)
		return -1;
	CCG2022111073���View* view = (CCG2022111073���View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	return 0;
}

int CameraControl::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (window == nullptr)
		return -1;
	CCG2022111073���View* view = (CCG2022111073���View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_EQUAL) {  // + �Ŵ�
			mCamera->mLeft *= 0.8;
			mCamera->mRight *= 0.8;
			mCamera->mTop *= 0.8;
			mCamera->mBottom *= 0.8;
		}
		else if (key == GLFW_KEY_MINUS) {  // - ��С
			mCamera->mLeft *= 1.25;
			mCamera->mRight *= 1.25;
			mCamera->mTop *= 1.25;
			mCamera->mBottom *= 1.25;
		}
		else if (mCamera->mProjectionMode == 0 && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_L) { // �л�����ͼ
			mCamera->mEye = glm::vec3(-200, 0, 0);  // �����۲�
			mCamera->mTarget = glm::vec3(0, 0, 0);  // ����ԭ��
			mCamera->mUp = glm::vec3(0, 1, 0);      // ����Y������
		}
		else if (mCamera->mProjectionMode == 0 && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_R) { // �л�����ͼ
			mCamera->mEye = glm::vec3(200, 0, 0);   // ���Ҳ�۲�
			mCamera->mTarget = glm::vec3(0, 0, 0);  // ����ԭ��
			mCamera->mUp = glm::vec3(0, 1, 0);      // ����Y������

		}
		else if (mCamera->mProjectionMode == 0 && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_F) { // �л�ǰ��ͼ
			mCamera->mEye = glm::vec3(0, 0, 200);   // ��ǰ���۲�
			mCamera->mTarget = glm::vec3(0, 0, 0);  // ����ԭ��
			mCamera->mUp = glm::vec3(0, 1, 0);      // ����Y������

		}
		else if (mCamera->mProjectionMode == 0 && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_B) { // �л�����ͼ
			mCamera->mEye = glm::vec3(0, 0, -200);  // �Ӻ󷽹۲�
			mCamera->mTarget = glm::vec3(0, 0, 0);  // ����ԭ��
			mCamera->mUp = glm::vec3(0, 1, 0);      // ����Y������

		}
		else if (mCamera->mProjectionMode == 0 && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_T) { // �л�����ͼ
			mCamera->mEye = glm::vec3(0, 200, 0);   // ���Ϸ��۲�
			mCamera->mTarget = glm::vec3(0, 0, 0);  // ����ԭ��
			mCamera->mUp = glm::vec3(0, 0, -1);     // ����������Ϊ-Z����
		}
		else if (mCamera->mProjectionMode == 0 && mods == GLFW_MOD_CONTROL && key == GLFW_KEY_D) { // �л�����ͼ
			mCamera->mEye = glm::vec3(0, -200, 0);  // ���·��۲�
			mCamera->mTarget = glm::vec3(0, 0, 0);   // ����ԭ��
			mCamera->mUp = glm::vec3(0, 0, 1);       // ����������Ϊ+Z����
		}
		else if (mods == GLFW_MOD_SHIFT && key == GLFW_KEY_L) {  // L ��߽�����
			mCamera->mLeft -= 10.0f;
		}
		else if (key == GLFW_KEY_L) {  // l ��߽�����
			mCamera->mLeft += 10.0f;
		}
		else if (mods == GLFW_MOD_SHIFT && key == GLFW_KEY_R) {  // R �ұ߽�����
			mCamera->mRight -= 10.0f;
		}
		else if (key == GLFW_KEY_R) {  // r �ұ߽�����
			mCamera->mRight += 10.0f;
		}
		else if (mods == GLFW_MOD_SHIFT && key == GLFW_KEY_B) {  // B �±߽�����
			mCamera->mBottom -= 10.0f;
		}
		else if (key == GLFW_KEY_B) {  // b �±߽�����
			mCamera->mBottom += 10.0f;
		}
		else if (mods == GLFW_MOD_SHIFT && key == GLFW_KEY_T) {  // T �ϱ߽�����
			mCamera->mTop -= 10.0f;
		}
		else if (key == GLFW_KEY_T) {  // t �ϱ߽�����
			mCamera->mTop += 10.0f;
		}
		else if (key == GLFW_KEY_P) {  // P �л�͸��ͶӰ
			mCamera->mProjectionMode = 1;
		}
		else if (key == GLFW_KEY_O) {  // O �л�����ͶӰ
			mCamera->mProjectionMode = 0;
		}
		view->Invalidate();
		view->UpdateWindow();
	}

	return 0;
}