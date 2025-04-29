#pragma once

#include "CG2022111073冯杰View.h"


// 绘制点集
void drawPoint();

// 绘制线段集合，两两一组，绘制线段
void drawLine();

// 绘制首尾不相连线段
void drawLineStrip();

// 绘制首尾相连线段
void drawLineLoop();

// 通过点集合，每三个点组成一组绘制一个三角形, 带上颜色填充 
void drawTriangles();

// 遍历点集合，依次将三个点组成一组，绘制三角形
void drawTriangStrip();

// 给定点集合，其中第一个点为圆心，剩余点依次与其组成三角形，绘制, 风扇形状
void drawTriangFan();

// 给定点集合，绘制四边形，每四个点一组绘制
void drawQuads();

// 给定点集合，遍历点集合，依次将四个点组成四边形绘制
void drawQuadsStrip();

// 给定点集合，将所有的点构成的多边形连接起来绘制
void drawPolygon();

void drawStar(float cx, float cy, float outerRadius, float innerRadius, glm::vec3 color1, glm::vec3 color2);

std::vector<glm::ivec2> BresenhamCircleWithPoints(int xc, int yc, int r, glm::vec3 color);