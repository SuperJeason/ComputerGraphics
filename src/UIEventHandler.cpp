#include "pch.h"
#include "UIEventHandler.h"
#include "CCGRenderContext.h"
#include "CG2022111073冯杰Doc.h"
#include "CG2022111073冯杰View.h" //包含View前必须包含Doc
UIEventHandler* UIEventHandler::sCommand = nullptr; //交互命令
UIEventHandler::UIEventHandler(GLFWwindow* window)
	:mStep(0), mGLFWwindow(window)
{
}
UIEventHandler::~UIEventHandler()
{
	if (mGLFWwindow) {
		Cancel(mGLFWwindow);
	}
}

//按键输入
void UIEventHandler::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	//CCG20XX110001张三View* pCtx = (CCG20XX110001张三View*)glfwGetWindowUserPointer(window);
	//if (pCtx) {
	//}
	//if (mods == GLFW_MOD_CONTROL) {
	// //按下ctrl的同时，按下了key
	//}
	//if (mods == GLFW_MOD_SHIFT) {
	// //按下shift的同时，按下了key
	//}
	if (action == GLFW_PRESS) { //键位按下
		if (key == GLFW_KEY_ESCAPE) { //触发了ESC，取消当前正在执行的命令
			if (sCommand) {
				sCommand->Cancel(window);
				DelCommand();
			}
			else { //如果有选中的图形对象，此处撤销拾取状态。
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		//键位抬起
	}
	else { //action == GLFW_REPEAT
	}
	if (sCommand) {//命令模式，转发到对应命令对象去处理该事件
		sCommand->OnKey(window, key, scancode, action, mods);
	}
}
//字符输入
void UIEventHandler::CharCallback(GLFWwindow* window, unsigned int codepoint)
{
	//未实现
}
//组合键输入，字符也可触发，但修饰符不触发。codepoint是按下的键的unicode码，mods是按下的修饰符。
void UIEventHandler::CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods)
{
	//未实现
}
//鼠标按键
void UIEventHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	//CCG20XX110001张三View* pCtx = (CCG20XX110001张三View*)glfwGetWindowUserPointer(window);
	//if (pCtx) {
	//}
	if (sCommand) {//命令模式，转发到对应命令对象去处理该事件
		sCommand->OnMouseButton(window, button, action, mods);
	}
}
//光标移动
void UIEventHandler::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	CCG2022111073冯杰View* pCtx = (CCG2022111073冯杰View*)glfwGetWindowUserPointer(window);
	if (pCtx) {
		pCtx->ShowCoord(xpos, ypos);
	}
	if (sCommand) {//命令模式，转发到对应命令对象去处理该事件
		sCommand->OnCursorPos(window, xpos, ypos);
	}
}
//光标进入或离开
void UIEventHandler::CursorEnterCallback(GLFWwindow* window, int entered)
{
		//未实现
}
//鼠标滚轮
void UIEventHandler::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	//CCG20XX110001张三View* pCtx = (CCG20XX110001张三View*)glfwGetWindowUserPointer(window);
	//if (pCtx) {
	//}
	if (sCommand) {//命令模式，转发到对应命令对象去处理该事件
		sCommand->OnMouseScroll(window, xoffset, yoffset);
	}
}
//拖放操作
void UIEventHandler::DropCallback(GLFWwindow* window, int path_count, const char* paths[])
{
	//未实现
}
UIEventHandler* UIEventHandler::CurCommand()
{
	return sCommand;
}
void UIEventHandler::DelCommand()
{
	delete sCommand;
	sCommand = nullptr;
}
void UIEventHandler::SetCommand(UIEventHandler* cmd)
{
	sCommand = cmd;
}