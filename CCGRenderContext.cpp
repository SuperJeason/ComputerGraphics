#include "pch.h"
#include "CCGRenderContext.h"

CCGRenderContext::CCGRenderContext()
{
}
CCGRenderContext::~CCGRenderContext()
{
}
void CCGRenderContext::drawTest(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2d(0, 0);
	glVertex2d(100, 100);
	glVertex2d(100, 0);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex2d(100, 100);
	glVertex2d(300, 300);
	glVertex2d(300, 100);
	glEnd();

}
//void CCGRenderContext::DDALine(int xStart, int yStart, int xEnd, int yEnd, glm::vec3 color)
//{
//	//以下是绘制代码示例：用于其他算法参考，可根据自己的涉及进行修改
//	int steps;
//	int dx = xEnd - xStart;
//	int dy = yEnd - yStart;
//	if (abs(dx) >= abs(dy))
//		steps = abs(dx);
//	else
//		steps = abs(dy);
//	if (steps == 0)
//		return;
//	float x = (float)xStart, y = (float)yStart, xincre = (float)dx / steps, yincre = (float)dy /
//		steps;
//	glColor3f(color.r, color.g, color.b);
//	glBegin(GL_POINTS);
//	for (int i = 0; i <= steps; i++)
//	{
//		glVertex2i((int)(x + 0.5), (int)(y + 0.5)); //在(x,y)处，以颜色color绘像素
//		x = x + xincre;
//		y = y + yincre;
//	}
//	glEnd();
//}

void CCGRenderContext::DRAWPoint(int x,int y, glm::vec3 color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i((int)(x+ 0.5), (int)(y + 0.5)); //在(x,y)处，以颜色color绘像素
	glEnd();
}

void CCGRenderContext::DRAWLine(int xStart, int yStart, int xEnd, int yEnd, glm::vec3 color) {
	// 以下是绘制代码示例：用于其他算法参考，可根据自己的涉及进行修改
	int steps;
	int dx = xEnd - xStart;
	int dy = yEnd - yStart;
	if (abs(dx) >= abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	if (steps == 0)
		return;
	float x = (float)xStart, y = (float)yStart, xincre = (float)dx / steps, yincre = (float)dy /
		steps;
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	for (int i = 0; i <= steps; i++)
	{
		glVertex2i((int)(x + 0.5), (int)(y + 0.5)); //在(x,y)处，以颜色color绘像素
		x = x + xincre;
		y = y + yincre;
	}
	glEnd();
}

void CCGRenderContext::DRAWSurface(std::vector<std::pair<int, int>> Points, glm::vec3 color) {
	if (Points.size() < 3) return;
	// 将点转换为glm::vec2格式
	std::vector<glm::vec2> vertices;
	for (const auto& p : Points) {
		vertices.emplace_back(p.first, p.second);
	}
	// 简单的三角剖分（仅适用于凸多边形）
	// 对于凹多边形，需要使用更复杂的算法如耳切法

	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POLYGON);

	// 遍历所有点，添加顶点
	for (const auto& point : Points) {
		glVertex2i(point.first, point.second);
	}

	glEnd();

}