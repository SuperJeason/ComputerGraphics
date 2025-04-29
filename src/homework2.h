#include "CG2022111073·ë½ÜView.h"

void DDALine(int startx,int starty,int endx,int endy, glm::vec3 color);

void MidLine(int startx, int starty, int endx, int endy, glm::vec3 color);

void BresenhamLine(int startx, int starty, int endx, int endy, glm::vec3 color);

void CenterCircle(int x,int y,int r, glm::vec3 color);

void BresenhamCircle(int x, int y, int r, glm::vec3 color);

void drawArc(int x, int y, int r,double theta1,double theta2, glm::vec3 color);

void ScanPolygon(std::vector<glm::ivec2> vtxs,glm::vec3 color);

void floodFill(int x, int y, glm::vec3 color, const std::vector<glm::ivec2>& vtxs, int n);
