#ifndef _UIEventHandler_H_INCLUDED
#define _UIEventHandler_H_INCLUDED
#include "CGObject.h"
struct GLFWwindow; //预声明（本文件中只用到GLFWwindow*）
enum class EventType : int //操作命令类型，参考如下定义，可根据需要修改
{
	EventNone = 0, //无，显示鼠标指针，不交互画图
	//二维图形绘制（相当于直接在画布上绘制）
	//点
	Draw2DPoint = 1, //绘制单个点
	Draw2DStroke = 2, //笔划（迹线） 
	Draw2DSeedFill = 3, //拾取种子点
	//线：线段、定长线段、直线、射线、折线、封闭线

	Draw2DLineSeg = 10, //利用起点、终点绘制直线段
	Draw2DLineLen = 11, //利用起点、终点（确定方向）、输入长度绘制直线段
	Draw2DLineX = 12, //利用两点绘制无限长直线
	Draw2DLineRay = 13, //利用起点、终点（第二点确定方向）绘制射线
	Draw2DLineStrip = 14, //折线，连续相连的直线段形成
	Draw2DLineLoop = 15, //封闭线，不是区域
	// 多边形：多边形、正多边形
	Draw2DPolygon = 20, //任意多边形（左键点击得到各点，右键点击最后一点结束）
	Draw2DPolygonNC = 21, //正多边形（左键点击前两点确定一边长，输入边数，中心在边向量的左侧得到正多边形）
	Draw2DPolygonNR = 22, //正多边形（左键第一点得到中心、第二点得到半径、输入边数、鼠标上下移动旋转确定正多边形位置）
	Draw2DRectangle = 23, //轴对齐矩形（左键第一点，第二点）
	Draw2DSquare = 24, //轴对齐正方形（左键第一点，第二点，按较长的方向）
	Draw2DDiamond = 25, //菱形（左键第一点，第二点形成中心线，两个方向等）
	Draw2DTriangle = 26, //三角形（不等边scalene, 等边equilateral,等腰isosceles）、直角三角形
	Model2DTransform = 120,
	EventUnknown = 2000,
	CameraControl = 2002
};
//与绘图客户区的交互，使用命令模式，简化CView派生类中键盘、鼠标事件的处理
class UIEventHandler
{
public:
	UIEventHandler(GLFWwindow* window = nullptr);
	virtual ~UIEventHandler();
	//命令类型，必须在派生类中重写
	virtual EventType GetType() { return EventType::EventNone; }
	//取消命令（按ESC键中断当前命令的执行），必须在派生类中重写
	virtual int Cancel(GLFWwindow* window) { return 0; }
	//鼠标事件（都只给出默认实现，派生类根据需要重写相应的函数）
	virtual int OnKey(GLFWwindow * window, int key, int scancode, int action, int mods) { return 0; }
	virtual int OnChar(GLFWwindow* window, unsigned int codepoint) { return 0; }
	virtual int OnCharMods(GLFWwindow* window, unsigned int codepoint, int mods) { return 0; }
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) { return 0; }
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) { return 0; }
	virtual int OnCursorEnter(GLFWwindow* window, int entered) { return 0; }
	virtual int OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) { return 0; }
	//GLFW键盘鼠标交互回调函数
	//按键输入
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	//字符输入
	static void CharCallback(GLFWwindow* window, unsigned int codepoint);
	//组合键输入，字符也可触发，但修饰符不触发。codepoint是按下的键的unicode码，mods是按下的修饰符。
	static void CharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
	//鼠标按键
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	//光标移动
	static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	//光标进入或离开
	static void CursorEnterCallback(GLFWwindow* window, int entered);
	//鼠标滚轮
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	//拖放操作
	static void DropCallback(GLFWwindow* window, int path_count, const char* paths[]);
	//如果需要附加其他数据（不负责销毁）
	void SetOwnerData(std::shared_ptr<CGObject> owner, std::shared_ptr<CGObject> data)
	{
		mOwnder = owner;
		mData = data;
	}
	//只使用一个命令对象
	static UIEventHandler* CurCommand();
	static void DelCommand();
	static void SetCommand(UIEventHandler * cmd);
protected:
	int mStep = 0; // 命令操作计数
	GLFWwindow* mGLFWwindow = nullptr; //GLFW图形绘制窗口
	std::shared_ptr<CGObject> mOwnder = nullptr; //事件拥有者
	std::shared_ptr<CGObject> mData = nullptr; //事件附加数据 
	static UIEventHandler* sCommand; //交互命令
};
#endif //_UIEventHandler_H_INCLUDED