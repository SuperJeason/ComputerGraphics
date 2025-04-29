#pragma once
#include "glIncludes.h"
#include <vector>
#include <utility>

class CCGRenderContext
{
public:
	CCGRenderContext();
	virtual ~CCGRenderContext();

	void drawTest(void);
	//// 绘制线段
	//void DDALine(int xStart, int yStart, int xEnd, int yEnd, glm::vec3 color);

	//// 绘制点集合
	//void drawPoint(std::vector<std::pair<int,int>> Points, glm::vec3 color);

	//// 绘制线段集合，两两一组，绘制线段
	//void drawLine(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// 绘制首尾不相连线段
	//void drawLineStrip(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// 绘制首尾相连线段
	//void drawLineLoop(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// 通过点集合，每三个点组成一组绘制一个三角形, 带上颜色填充 
	//void drawTriangles(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// 遍历点集合，依次将三个点组成一组，绘制三角形
	//void drawTriangStrip(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// 给定点集合，其中第一个点为圆心，剩余点依次与其组成三角形，绘制, 风扇形状
	//void drawTriangFan(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// 给定点集合，绘制四边形，每四个点一组绘制
	//void drawQuads(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// 给定点集合，遍历点集合，依次将四个点组成四边形绘制
	//void drawQuadsStrip(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	//// 给定点集合，将所有的点构成的多边形连接起来绘制
	//void drawPolygon(std::vector<std::pair<int, int>> Points, glm::vec3 color);

	// 点
	void DRAWPoint(int x,int y,glm::vec3 color);
	// 线
	void DRAWLine(int xStart, int yStart, int xEnd, int yEnd, glm::vec3 color);
	// 面
	void DRAWSurface(std::vector<std::pair<int,int>> Points,glm::vec3 color);
};



