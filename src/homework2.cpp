#include "pch.h"
#include "homework2.h"
#include <cmath>
#include <algorithm>
#include <queue>
#include <set>

#define DEG2RAD(angle) ((angle) * M_PI / 180.0)
const double M_PI = 3.1415926;
using namespace std;
void DDALine(int startx, int starty, int endx, int endy, glm::vec3 color) {
	int steps;
	int dx = endx - startx;
	int dy = endy - starty;
	if (abs(dx) >= abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	if (steps == 0)
		return;
	float x = (float)startx, y = (float)starty, xincre = (float)dx / steps, yincre = (float)dy /
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

void MidLine(int startx, int starty, int endx, int endy, glm::vec3 color) {
    int dx = endx - startx;
    int dy = endy - starty;
    int stepx = (dx > 0) ? 1 : -1;  
    int stepy = (dy > 0) ? 1 : -1;
    dx = abs(dx);
    dy = abs(dy);

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(startx, starty); 

    if (dx >= dy) {
        int d = 2 * dy - dx;
        int delta1 = 2 * dy;
        int delta2 = 2 * (dy - dx);
        int x = startx, y = starty;
        for (int i = 0; i < dx; ++i) {
            x += stepx;
            if (d < 0) {
                d += delta1;
            }
            else {
                y += stepy;
                d += delta2;
            }
            glVertex2i(x, y);
        }
    }
    else {
        int d = 2 * dx - dy;
        int delta1 = 2 * dx;
        int delta2 = 2 * (dx - dy);
        int x = startx, y = starty;
        for (int i = 0; i < dy; ++i) {
            y += stepy;
            if (d < 0) {
                d += delta1;
            }
            else {
                x += stepx;
                d += delta2;
            }
            glVertex2i(x, y);
        }
    }
    glEnd();
}

void BresenhamLine(int startx, int starty, int endx, int endy, glm::vec3 color) {
    int dx = abs(endx - startx);
    int dy = abs(endy - starty);
    int stepx = (startx < endx) ? 1 : -1;  
    int stepy = (starty < endy) ? 1 : -1;  
    int err = dx - dy;                    

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(startx, starty);         

    int x = startx, y = starty;
    while (x != endx || y != endy) {   
        glVertex2i(x, y);                
        int e2 = 2 * err;               

        if (e2 > -dy) {    
            err -= dy;
            x += stepx;
        }
        if (e2 < dx) {             
            err += dx;
            y += stepy;
        }
    }
    glVertex2i(endx, endy);             
    glEnd();
}


void CenterCircle(int xc, int yc, int r, glm::vec3 color) {
    int x = 0;
    int y = r;
    int d = 1 - r;  

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);

    while (x <= y) {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);

        if (d < 0) {
            d += 2 * x + 3;
        }
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
    glEnd();
}


void BresenhamCircle(int xc, int yc, int r, glm::vec3 color) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);

    while (x <= y) {
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);
        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);

        if (d < 0) {
            d += 4 * x + 6;
        }
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glEnd();
}

std::vector<glm::ivec2> BresenhamCircleWithPoints(int xc, int yc, int r, glm::vec3 color) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    std::vector<glm::ivec2> points;
    std::vector<std::vector<glm::ivec2>> octants(8);

    while (x <= y) {  // 包含x=y的情况
        // 生成八个象限的点，每个象限按逆时针方向存储
        octants[0].push_back(glm::ivec2(xc + x, yc + y));  // 第一象限
        octants[1].push_back(glm::ivec2(xc + y, yc + x));  // 第二象限
        octants[2].push_back(glm::ivec2(xc + y, yc - x));  // 第三象限
        octants[3].push_back(glm::ivec2(xc + x, yc - y));  // 第四象限
        octants[4].push_back(glm::ivec2(xc - x, yc - y));  // 第五象限
        octants[5].push_back(glm::ivec2(xc - y, yc - x));  // 第六象限
        octants[6].push_back(glm::ivec2(xc - y, yc + x));  // 第七象限
        octants[7].push_back(glm::ivec2(xc - x, yc + y));  // 第八象限

        // 更新决策参数
        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }

    // 按顺时针顺序拼接各象限的点，并移除重复的端点
    auto addOctant = [&](int idx, bool reverse) {
        if (octants[idx].size() <= 2) return;  // 没有中间点可添加
        auto begin = octants[idx].begin() + 1;
        auto end = octants[idx].end() - 1;
        if (reverse) {
            points.insert(points.end(), std::make_reverse_iterator(end), std::make_reverse_iterator(begin));
        } else {
            points.insert(points.end(), begin, end);
        }
    };

    addOctant(0, true);  // 第一象限
    addOctant(7, false);   // 第八象限反转
    addOctant(6, true);  // 第七象限
    addOctant(5, false);   // 第六象限反转
    addOctant(4, true);  // 第五象限
    addOctant(3, false);   // 第四象限反转
    addOctant(2, true);  // 第三象限
    addOctant(1, false);   // 第二象限反转

    // 闭合圆，添加起点到末尾
    if (!points.empty()) {
        points.push_back(points.front());
    }

    // 使用OpenGL绘制
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_LINE_LOOP);
    for (const auto& point : points) {
        glVertex2i(point.x, point.y);
    }
    glEnd();

    return points;
}




struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
};

double normalizeAngle(double angle) {
    if (angle == 2 * M_PI) {
        return angle;
    }
    angle = fmod(angle, 2 * M_PI);
    return angle < 0 ? angle + 2 * M_PI : angle;
}

struct ArcSegment {
    double startAngle;
    double endAngle;
    int xSign;
    int ySign;
    bool swapXY;

    ArcSegment(double start, double end, int xs, int ys, bool swap) :
        startAngle(start), endAngle(end), xSign(xs), ySign(ys), swapXY(swap) {
    }
};

vector<Point> midPointArc(int cx, int cy, int r, double startAngle, double endAngle) {
    vector<Point> points;

    startAngle = normalizeAngle(startAngle);
    endAngle = normalizeAngle(endAngle);
    if (startAngle > endAngle) endAngle += 2 * M_PI;

    vector<ArcSegment> segments;
    double currentAngle = startAngle;

    const double OCTANT_ENDS[] = {
        M_PI / 4, M_PI / 2, 3 * M_PI / 4, M_PI,
        5 * M_PI / 4, 3 * M_PI / 2, 7 * M_PI / 4, 2 * M_PI
    };

    while (currentAngle < endAngle) {
        int xSign = 1, ySign = 1;
        bool swapXY = false;
        double segmentEnd;

        if (currentAngle < OCTANT_ENDS[0]) {
            xSign = 1; ySign = 1; swapXY = true;
            segmentEnd = min(endAngle, OCTANT_ENDS[0]);
        }
        else if (currentAngle < OCTANT_ENDS[1]) {
            xSign = 1; ySign = 1; swapXY = false;
            segmentEnd = min(endAngle, OCTANT_ENDS[1]);
        }
        else if (currentAngle < OCTANT_ENDS[2]) {
            xSign = -1; ySign = 1; swapXY = false;
            segmentEnd = min(endAngle, OCTANT_ENDS[2]);
        }
        else if (currentAngle < OCTANT_ENDS[3]) {
            xSign = -1; ySign = 1; swapXY = true;
            segmentEnd = min(endAngle, OCTANT_ENDS[3]);
        }
        else if (currentAngle < OCTANT_ENDS[4]) {
            xSign = -1; ySign = -1; swapXY = true;
            segmentEnd = min(endAngle, OCTANT_ENDS[4]);
        }
        else if (currentAngle < OCTANT_ENDS[5]) {
            xSign = -1; ySign = -1; swapXY = false;
            segmentEnd = min(endAngle, OCTANT_ENDS[5]);
        }
        else if (currentAngle < OCTANT_ENDS[6]) {
            xSign = 1; ySign = -1; swapXY = false;
            segmentEnd = min(endAngle, OCTANT_ENDS[6]);
        }
        else {
            xSign = 1; ySign = -1; swapXY = true;
            segmentEnd = min(endAngle, OCTANT_ENDS[7]);
        }

        double mappedStart, mappedEnd;
        double delta = currentAngle;
        double segLen = segmentEnd - currentAngle;

        if (currentAngle < OCTANT_ENDS[0]) {
            mappedStart = OCTANT_ENDS[1] - delta;
            mappedEnd = OCTANT_ENDS[1] - segmentEnd;
        }
        else if (currentAngle < OCTANT_ENDS[1]) {
            mappedStart = delta;
            mappedEnd = segmentEnd;
        }
        else if (currentAngle < OCTANT_ENDS[2]) {
            mappedStart = OCTANT_ENDS[1] - (delta - OCTANT_ENDS[1]);
            mappedEnd = OCTANT_ENDS[1] - (segmentEnd - OCTANT_ENDS[1]);
        }
        else if (currentAngle < OCTANT_ENDS[3]) {
            mappedStart = delta - OCTANT_ENDS[1];
            mappedEnd = segmentEnd - OCTANT_ENDS[1];
        }
        else if (currentAngle < OCTANT_ENDS[4]) {
            mappedStart = OCTANT_ENDS[1] - (delta - OCTANT_ENDS[3]);
            mappedEnd = OCTANT_ENDS[1] - (segmentEnd - OCTANT_ENDS[3]);
        }
        else if (currentAngle < OCTANT_ENDS[5]) {
            mappedStart = delta - OCTANT_ENDS[3];
            mappedEnd = segmentEnd - OCTANT_ENDS[3];
        }
        else if (currentAngle < OCTANT_ENDS[6]) {
            mappedStart = OCTANT_ENDS[1] - (delta - OCTANT_ENDS[5]);
            mappedEnd = OCTANT_ENDS[1] - (segmentEnd - OCTANT_ENDS[5]);
        }
        else {
            mappedStart = delta - OCTANT_ENDS[5];
            mappedEnd = segmentEnd - OCTANT_ENDS[5];
        }

        mappedStart = max(OCTANT_ENDS[0], min(OCTANT_ENDS[1], mappedStart));
        mappedEnd = max(OCTANT_ENDS[0], min(OCTANT_ENDS[1], mappedEnd));

        if (mappedEnd < mappedStart) swap(mappedStart, mappedEnd);

        segments.emplace_back(mappedStart, mappedEnd, xSign, ySign, swapXY);
        currentAngle = segmentEnd;
    }

    double minAngle = OCTANT_ENDS[1];
    double maxAngle = OCTANT_ENDS[0];

    for (const auto& s : segments) {
        minAngle = min(minAngle, s.startAngle);
        maxAngle = max(maxAngle, s.endAngle);
    }

    int x = round(r * cos(maxAngle));
    int y = round(r * sin(maxAngle));
    int endX = round(r * cos(minAngle));
    double d = pow(x - 1, 2) + pow(y + 0.5, 2) - r * r;
    vector<pair<int, int>> octantPoints;

    while (x <= endX) {
        octantPoints.emplace_back(x, y);
        if (d < 0) {
            d += 2 * x + 3;
        }
        else {
            y--;
            d += 2 * (x - y) + 5;  // 重新计算 d
        }
        x++;
    }

    for (const auto& p : octantPoints) {
        int px = p.first;
        int py = p.second;
        double angle = atan2(py, px);

        for (const auto& s : segments) {
            if (angle >= s.startAngle && angle <= s.endAngle) {
                int tx, ty;
                if (s.swapXY) {
                    tx = s.xSign * py;
                    ty = s.ySign * px;
                }
                else {
                    tx = s.xSign * px;
                    ty = s.ySign * py;
                }
                points.emplace_back(cx + tx, cy + ty);
            }
        }
    }

    return points;
}

vector<Point> BresenhamPointArc(int cx, int cy, int r, double startAngle, double endAngle) {
    vector<Point> points;

    // 规范化角度
    startAngle = normalizeAngle(startAngle);
    endAngle = normalizeAngle(endAngle);
    if (startAngle > endAngle) endAngle += 2 * M_PI;

    vector<ArcSegment> segments;
    double currentAngle = startAngle;

    const double OCTANT_ENDS[] = {
        M_PI / 4, M_PI / 2, 3 * M_PI / 4, M_PI,
        5 * M_PI / 4, 3 * M_PI / 2, 7 * M_PI / 4, 2 * M_PI
    };

    while (currentAngle < endAngle) {
        int xSign = 1, ySign = 1;
        bool swapXY = false;
        double segmentEnd;

        if (currentAngle < OCTANT_ENDS[0]) {
            xSign = 1; ySign = 1; swapXY = true;
            segmentEnd = min(endAngle, OCTANT_ENDS[0]);
        }
        else if (currentAngle < OCTANT_ENDS[1]) {
            xSign = 1; ySign = 1; swapXY = false;
            segmentEnd = min(endAngle, OCTANT_ENDS[1]);
        }
        else if (currentAngle < OCTANT_ENDS[2]) {
            xSign = -1; ySign = 1; swapXY = false;
            segmentEnd = min(endAngle, OCTANT_ENDS[2]);
        }
        else if (currentAngle < OCTANT_ENDS[3]) {
            xSign = -1; ySign = 1; swapXY = true;
            segmentEnd = min(endAngle, OCTANT_ENDS[3]);
        }
        else if (currentAngle < OCTANT_ENDS[4]) {
            xSign = -1; ySign = -1; swapXY = true;
            segmentEnd = min(endAngle, OCTANT_ENDS[4]);
        }
        else if (currentAngle < OCTANT_ENDS[5]) {
            xSign = -1; ySign = -1; swapXY = false;
            segmentEnd = min(endAngle, OCTANT_ENDS[5]);
        }
        else if (currentAngle < OCTANT_ENDS[6]) {
            xSign = 1; ySign = -1; swapXY = false;
            segmentEnd = min(endAngle, OCTANT_ENDS[6]);
        }
        else {
            xSign = 1; ySign = -1; swapXY = true;
            segmentEnd = min(endAngle, OCTANT_ENDS[7]);
        }

        double mappedStart, mappedEnd;
        double delta = currentAngle;
        double segLen = segmentEnd - currentAngle;

        if (currentAngle < OCTANT_ENDS[0]) {
            mappedStart = OCTANT_ENDS[1] - delta;
            mappedEnd = OCTANT_ENDS[1] - segmentEnd;
        }
        else if (currentAngle < OCTANT_ENDS[1]) {
            mappedStart = delta;
            mappedEnd = segmentEnd;
        }
        else if (currentAngle < OCTANT_ENDS[2]) {
            mappedStart = OCTANT_ENDS[1] - (delta - OCTANT_ENDS[1]);
            mappedEnd = OCTANT_ENDS[1] - (segmentEnd - OCTANT_ENDS[1]);
        }
        else if (currentAngle < OCTANT_ENDS[3]) {
            mappedStart = delta - OCTANT_ENDS[1];
            mappedEnd = segmentEnd - OCTANT_ENDS[1];
        }
        else if (currentAngle < OCTANT_ENDS[4]) {
            mappedStart = OCTANT_ENDS[1] - (delta - OCTANT_ENDS[3]);
            mappedEnd = OCTANT_ENDS[1] - (segmentEnd - OCTANT_ENDS[3]);
        }
        else if (currentAngle < OCTANT_ENDS[5]) {
            mappedStart = delta - OCTANT_ENDS[3];
            mappedEnd = segmentEnd - OCTANT_ENDS[3];
        }
        else if (currentAngle < OCTANT_ENDS[6]) {
            mappedStart = OCTANT_ENDS[1] - (delta - OCTANT_ENDS[5]);
            mappedEnd = OCTANT_ENDS[1] - (segmentEnd - OCTANT_ENDS[5]);
        }
        else {
            mappedStart = delta - OCTANT_ENDS[5];
            mappedEnd = segmentEnd - OCTANT_ENDS[5];
        }

        mappedStart = max(OCTANT_ENDS[0], min(OCTANT_ENDS[1], mappedStart));
        mappedEnd = max(OCTANT_ENDS[0], min(OCTANT_ENDS[1], mappedEnd));

        if (mappedEnd < mappedStart) swap(mappedStart, mappedEnd);

        segments.emplace_back(mappedStart, mappedEnd, xSign, ySign, swapXY);
        currentAngle = segmentEnd;
    }

    // 计算映射角度范围
    double minAngle = OCTANT_ENDS[1];
    double maxAngle = OCTANT_ENDS[0];
    for (const auto& s : segments) {
        minAngle = min(minAngle, s.startAngle);
        maxAngle = max(maxAngle, s.endAngle);
    }

    int x = round(r * cos(maxAngle));
    int y = round(r * sin(maxAngle));
    int endX = round(r * cos(minAngle));
    int d = round(pow(x + 1, 2) + pow(y - 1, 2) - r * r);
    vector<pair<int, int>> octantPoints;

    while (x <= endX) {
        octantPoints.emplace_back(x, y);
        if (d < 0) {
            if ((2 * d + y) - 1 <= 0) {
                d += 2 * x + 3;
                x++;
            }
            else {
                d += 2 * (x - y + 3);
                x++;
                y--;
            }
        }
        else if (d == 0) {
            d += 2 * (x - y + 3);
            x++;
            y--;
        }else {
            if ((2 * (d - x) - 1) <= 0) {
                d += 2 * (x - y + 3);
                x++;
                y--;
            }
            else {
                d += -2 * y + 3;
                y--;
            }
        }
    }

    // 变换到原始坐标
    for (const auto& p : octantPoints) {
        int px = p.first;
        int py = p.second;
        double angle = atan2(py, px);

        for (const auto& s : segments) {
            if (angle >= s.startAngle && angle <= s.endAngle) {
                int tx, ty;
                if (s.swapXY) {
                    tx = s.xSign * py;
                    ty = s.ySign * px;
                }
                else {
                    tx = s.xSign * px;
                    ty = s.ySign * py;
                }
                points.emplace_back(cx + tx, cy + ty);
            }
        }
    }

    return points;
}


void drawArc(int x, int y, int r, double theta1, double theta2, glm::vec3 color) {
    double startRad = DEG2RAD(theta1);
    double endRad = DEG2RAD(theta2);

    // vector<Point> arcPoints = midPointArc(x, y, r, startRad, endRad);
    vector<Point> arcPoints = BresenhamPointArc(x, y, r, startRad, endRad);
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_POINTS); 
    for (const auto& p : arcPoints) {
        glVertex2i(p.x, p.y);
    }
    glEnd();
}




struct Edge {
    double x;  // x
    int y;     // y_max
    double m;  // 斜率倒数
    struct Edge* next;
};



void ScanPolygon(std::vector<glm::ivec2> vtxs, glm::vec3 color) {
    if (vtxs.size() < 3)
        return;
    int y_max = vtxs[0].y;
    int y_min = vtxs[0].y;
    for (auto vtx : vtxs) {
        if (vtx.y >= y_max)
            y_max = vtx.y;
        if (vtx.y <= y_min)
            y_min = vtx.y;
    }

    std::vector<Edge*> edgeTable(y_max - y_min + 1, nullptr);
    for (int i = 0;i < vtxs.size();i++) {
        const glm::ivec2 v1 = vtxs[i];
        const glm::ivec2 v2 = vtxs[(i + 1) % (vtxs.size())];
        if (v1.y == v2.y)
            continue;
        Edge* edge = new Edge();
        if (v1.y < v2.y) {
            edge->x = v1.x;
            edge->y = v2.y;
            edge->m = double(v1.x - v2.x) / (v1.y - v2.y);
            edge->next = nullptr;
            // 判断链表长度
            if (edgeTable[v1.y - y_min] == nullptr)
                edgeTable[v1.y - y_min] = edge;
            else {
                // 找到链表末尾位置
                Edge* current = edgeTable[v1.y - y_min];
                while (current->next != nullptr)
                    current = current->next;
                current->next = edge;
            }
        }
        else {
            edge->x = v2.x;
            edge->y = v1.y;
            edge->m = double(v1.x - v2.x) / (v1.y - v2.y);
            edge->next = nullptr;
            // 判断链表长度
            if (edgeTable[v2.y - y_min] == nullptr)
                edgeTable[v2.y - y_min] = edge;
            else {
                // 找到链表末尾位置
                Edge* current = edgeTable[v2.y - y_min];
                while (current->next != nullptr)
                    current = current->next;
                current->next = edge;
            }
        }
    }
    // 有效边表构建完成后，扫描线处理

    std::vector<Edge*> activateEdge;
    
    for (int y = y_min;y <= y_max;y++) {
         if (edgeTable[y - y_min] != nullptr && y - y_min <= edgeTable.size()) {
            Edge* current = edgeTable[y - y_min];
            while (current != nullptr) {
                activateEdge.push_back(current);
                current = current->next;
            }
         }
         // 移除多余边表
         for (auto it = activateEdge.begin(); it != activateEdge.end(); ) {
             if ((*it)->y <= y) {
                 it = activateEdge.erase(it);
             }
             else {
                 ++it;
             }
         }
        std::sort(activateEdge.begin(), activateEdge.end(), [](Edge* a, Edge* b) {return a->x < b->x;});
        std::vector<double> x_intersections;

        for (int i = 0; i < activateEdge.size();i += 2) {
            double x_start = activateEdge[i]->x;
            double x_end = (i + 1 < activateEdge.size()) ? activateEdge[i + 1]->x : activateEdge[i]->x;
            while (x_start <= x_end) {
                glColor3f(color.r, color.g, color.b);
                glBegin(GL_POINTS);
                glVertex2i(x_start,y);
                glEnd();
                x_start++;
            }
        }
        // 更新边表位置信息
        
        for (auto e : activateEdge) {
            e->x += e->m;
        }
    }
    // 在函数末尾统一释放所有边对象
    for (auto e : edgeTable) {
        Edge* current = e;
        while (current != nullptr) {
            Edge* next = current->next;
            delete current;
            current = next;
        }
    }
}


bool isInsidePolygon(int x, int y, const std::vector<glm::ivec2>& vtxs, int n) {
    // 第一步：检查点是否在任意边上（包括斜边）
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        int xi = vtxs[i].x, yi = vtxs[i].y;
        int xj = vtxs[j].x, yj = vtxs[j].y;

        if (xi-1 == x && yi-1 == y)
            return false;

        // 计算向量
        int dx = xj - xi;
        int dy = yj - yi;
        int dxp = x - xi;
        int dyp = y - yi;

        // 检查共线条件
        if (dxp * dy == dyp * dx) {
            // 检查点是否在边的包围盒内
            if (std::min(xi, xj)-1 < x && x < std::max(xi, xj)-1 &&
                std::min(yi, yj)-1 < y && y < std::max(yi, yj)-1) {
                return false; // 点在边上，不填充
            }
        }
    }

    // 第二步：射线交叉算法判断点是否在内部
    bool inside = false;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        int xi = vtxs[i].x, yi = vtxs[i].y;
        int xj = vtxs[j].x, yj = vtxs[j].y;

        // 检查射线与边的交叉
        if ((yi > y) != (yj > y)) {
            double x_intersect = static_cast<double>(xj - xi) * (y - yi) / (yj - yi) + xi;
            if (x < x_intersect) {
                inside = !inside;
            }
        }
    }

    return inside;
}




// 自定义比较器
struct CompareIVec2 {
    bool operator()(const glm::ivec2& a, const glm::ivec2& b) const {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }
};

void floodFill(int x, int y, glm::vec3 color, const std::vector<glm::ivec2>& vtxs, int n) {
    if (!isInsidePolygon(x, y, vtxs, n)) {
        return;
    }

    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);

    std::queue<glm::ivec2> toFill;
    toFill.push(glm::ivec2(x, y));
    std::set<glm::ivec2, CompareIVec2> filled; 
    filled.insert(glm::ivec2(x, y));

    while (!toFill.empty()) {
        glm::ivec2 point = toFill.front();
        toFill.pop();
        glVertex2i(point.x, point.y);

        // 检查四个相邻点
        glm::ivec2 neighbors[] = {
            {point.x - 1, point.y},
            {point.x + 1, point.y},
            {point.x, point.y - 1},
            {point.x, point.y + 1}
        };

        for (const auto& neighbor : neighbors) {
            if (isInsidePolygon(neighbor.x, neighbor.y, vtxs, n)) {
                auto it = filled.find(neighbor);
                if (it == filled.end()) {
                    toFill.push(neighbor);
                    filled.insert(neighbor);
                }
            }
        }

    }
    glEnd();
}