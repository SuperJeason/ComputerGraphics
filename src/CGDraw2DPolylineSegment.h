#pragma once
#include "UIEventHandler.h" // 假设 UIEventHandler 是基类
#include "CGPolylineSegment.h" // 使用之前定义的折线类 CGPolylineSegment
#include <vector> // 需要包含 vector 头文件

// 将类名修改为 CGDraw2DPolylineSegment
class CGDraw2DPolylineSegment : public UIEventHandler
{
public:
	// 构造函数
	CGDraw2DPolylineSegment(GLFWwindow* window);

	// 析构函数
	virtual ~CGDraw2DPolylineSegment();


	// 处理鼠标按键事件
	virtual int OnMouseButton(GLFWwindow* window, int button, int action, int mods) override;

	// 处理鼠标光标位置事件
	virtual int OnCursorPos(GLFWwindow* window, double xpos, double ypos) override;

	// 取消正在执行的命令（如按ESC键）
	virtual int Cancel(GLFWwindow* window) override;

protected:
	// 绘制二维线（辅助函数）
	static void draw2dline(glm::dvec3& s, glm::dvec3& e);

protected:
	std::vector<glm::dvec3> mPoints; // 存储折线的所有顶点 (屏幕坐标系)
	glm::dvec3 mCurrentPos; // 存储当前鼠标位置 (屏幕坐标系)，用于绘制橡皮筋线
	bool mDrawing; // 标记是否正在绘制折线

	// 用于橡皮筋线 (从最后一个已确定点到当前鼠标位置)
	glm::dvec3 mRubberBandStart; // 橡皮筋线的起点 (最后一个确定点，屏幕坐标系)
	glm::dvec3 mRubberBandEnd;   // 橡皮筋线的终点 (当前鼠标位置，屏幕坐标系)

	int mRubberBandMoveCount; // 橡皮筋线移动次数计数
	bool mRubberBandActive;      // 标记当前是否有橡皮筋线正在绘制
	glm::dvec3 mPrePos1; // 存储上一次绘制橡皮筋线时的终点位置 (用于擦除旧线)
	glm::dvec3 mPrePos2;
};
