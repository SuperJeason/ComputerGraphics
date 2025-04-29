#include "pch.h" // 如果你的项目使用了预编译头文件
#include "CGDraw2DPolylineSegment.h"
#include "CG2022111073冯杰Doc.h" // 包含View之前要包含Doc
#include "CG2022111073冯杰View.h" // 用户交互绘制，并将图形对象通过Doc添加到场景
#include <gl/GL.h> // 包含 OpenGL 头文件
#include "homework2.h"
// 绘制二维线（辅助函数，与 CGDraw2DLineSeg 相同）
void CGDraw2DPolylineSegment::draw2dline(glm::dvec3& s, glm::dvec3& e)
{
	glBegin(GL_LINES);
	glVertex2d(s.x, s.y);
	glVertex2d(e.x, e.y);
	glEnd();
}

CGDraw2DPolylineSegment::CGDraw2DPolylineSegment(GLFWwindow* window)
	: UIEventHandler(window), mDrawing(false)
{
}

CGDraw2DPolylineSegment::~CGDraw2DPolylineSegment()
{
}
int CGDraw2DPolylineSegment::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (window == nullptr)
        return -1;
    CCG2022111073冯杰View* view = (CCG2022111073冯杰View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glm::dvec3 currentMousePos(xpos, ypos, 0.0);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if (!mDrawing) // 开始绘制
        {
            mDrawing = true;
            mPoints.clear();
            mPoints.push_back(currentMousePos);
            mRubberBandStart = currentMousePos;
            mPrePos1 = currentMousePos;
            mPrePos2 = currentMousePos;
            mRubberBandMoveCount = 0;
            view->ShowPrompt("请鼠标左键单击输入下一个点，右键结束绘制");
        }
        else // 添加新点
        {
            // 检查是否与上一个点重合
            if (!mPoints.empty() && glm::distance(currentMousePos, mPoints.back()) < 1.0)
            {
                view->ShowPrompt("与上一个点重合，请重新输入");
                return -1;
            }
            // 擦除当前的橡皮筋线
            if (mRubberBandMoveCount > 0)
            {
                glEnable(GL_COLOR_LOGIC_OP);
                glLogicOp(GL_XOR);
                glColor3f(1.0f, 1.0f, 1.0f);
                glm::dvec3 startWCS = view->DCS2WCS(mRubberBandStart);
                glm::dvec3 prePos1WCS = view->DCS2WCS(mPrePos1);
                glm::dvec3 currentWCS = view->DCS2WCS(currentMousePos);
                //draw2dline(startWCS, prePos1WCS); // 擦除旧线
                MidLine(startWCS.x, startWCS.y, prePos1WCS.x, prePos1WCS.y, glm::vec3(1.0f, 1.0f, 1.0f));
                /*draw2dline(startWCS, currentWCS);*/
                MidLine(startWCS.x, startWCS.y, currentWCS.x, currentWCS.y, glm::vec3(1.0f, 1.0f, 1.0f));
                glDisable(GL_COLOR_LOGIC_OP);
                // glfwSwapBuffers(window);
            }
            glColor3f(1.0f, 1.0f, 1.0f);
            glm::dvec3 startWCS = view->DCS2WCS(mRubberBandStart);
            glm::dvec3 currentWCS = view->DCS2WCS(currentMousePos);
            /*draw2dline(startWCS, currentWCS);*/
            MidLine(startWCS.x, startWCS.y, currentWCS.x, currentWCS.y, glm::vec3(1.0f, 1.0f, 1.0f));
            // 添加新点，并更新橡皮筋线起点
            mPoints.push_back(currentMousePos);
            mRubberBandStart = currentMousePos; // 新橡皮筋线从当前点开始
            mPrePos1 = currentMousePos;
            mPrePos2 = currentMousePos;
            mRubberBandMoveCount = 0; // 重置计数
            view->ShowPrompt("请鼠标左键单击输入下一个点，右键结束绘制");
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        if (mDrawing)
        {
            mPoints.push_back(currentMousePos);
            // 擦除橡皮筋线
            if (mRubberBandMoveCount > 0)
            {
                glEnable(GL_COLOR_LOGIC_OP);
                glLogicOp(GL_XOR);
                glColor3f(1.0f, 1.0f, 1.0f);
                glm::dvec3 startWCS = view->DCS2WCS(mRubberBandStart);
                glm::dvec3 prePos1WCS = view->DCS2WCS(mPrePos1);
                /*draw2dline(startWCS, prePos1WCS);*/
                MidLine(startWCS.x, startWCS.y, prePos1WCS.x, prePos1WCS.y, glm::vec3(1.0f, 1.0f, 1.0f));
                glDisable(GL_COLOR_LOGIC_OP);
                glfwSwapBuffers(window);
            }
            if (mPoints.size() >= 2) // 点数足够，创建折线
            {
                std::vector<glm::dvec3> wcsPoints;
                for (const auto& pt : mPoints)
                {
                    wcsPoints.push_back(view->DCS2WCS(pt));
                }
                view->AddRenderable(std::make_shared<CGPolylineSegment>(wcsPoints, false));
                view->Invalidate();
                view->UpdateWindow();
            }
            else
            {
                view->ShowPrompt("点数不足，取消绘制");
            }
            // 重置状态
            mDrawing = false;
            mPoints.clear();
            mRubberBandMoveCount = 0;
            view->ShowPrompt("就绪");
        }
        else
        {
            view->ShowPrompt("请先左键点击开始绘制折线");
        }
    }
    return 0;
}


int CGDraw2DPolylineSegment::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    if (window == nullptr)
        return -1;
    CCG2022111073冯杰View* view = (CCG2022111073冯杰View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;
    mCurrentPos.x = xpos;
    mCurrentPos.y = ypos;
    if (mDrawing)
    {
        // 将当前鼠标位置转换为世界坐标（用于绘制）
        glm::dvec3 startWCS = view->DCS2WCS(mRubberBandStart);
        glm::dvec3 currentWCS = view->DCS2WCS(mCurrentPos);
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_XOR);
        glColor3f(1.0f, 1.0f, 1.0f); // 蓝色橡皮筋线
        if (mRubberBandMoveCount == 0)
        {
            // 第一次移动：直接绘制新线
            /*draw2dline(startWCS, currentWCS);*/
            MidLine(startWCS.x, startWCS.y, currentWCS.x, currentWCS.y, glm::vec3(1.0f, 1.0f, 1.0f));
            mPrePos1 = mCurrentPos; // 记录第一次的终点
            mPrePos2 = mCurrentPos; // 初始化 mPrePos2
        }
        else if (mRubberBandMoveCount == 1)
        {
            // 第二次移动：擦除第一次的线，再绘制新线
            glm::dvec3 prePos1WCS = view->DCS2WCS(mPrePos1);
            //draw2dline(startWCS, prePos1WCS); // 擦除旧线
            MidLine(startWCS.x, startWCS.y, prePos1WCS.x, prePos1WCS.y, glm::vec3(1.0f, 1.0f, 1.0f));
            //draw2dline(startWCS, currentWCS); // 绘制新线
            MidLine(startWCS.x, startWCS.y, currentWCS.x, currentWCS.y, glm::vec3(1.0f, 1.0f, 1.0f));
            mPrePos2 = mPrePos1; // 更新 mPrePos2
            mPrePos1 = mCurrentPos; // 更新 mPrePos1
        }
        else
        {
            // 后续移动：擦除上上次的线，再绘制新线
            glm::dvec3 prePos2WCS = view->DCS2WCS(mPrePos2);
            //draw2dline(startWCS, prePos2WCS); // 擦除旧线
            MidLine(startWCS.x, startWCS.y, prePos2WCS.x, prePos2WCS.y, glm::vec3(1.0f, 1.0f, 1.0f));
            //draw2dline(startWCS, currentWCS); // 绘制新线
            MidLine(startWCS.x, startWCS.y, currentWCS.x, currentWCS.y, glm::vec3(1.0f, 1.0f, 1.0f));
            mPrePos2 = mPrePos1; // 更新 mPrePos2
            mPrePos1 = mCurrentPos; // 更新 mPrePos1
        }
        glDisable(GL_COLOR_LOGIC_OP);
        glfwSwapBuffers(window);
        mRubberBandMoveCount++; // 增加移动计数
        view->ShowPrompt("请鼠标左键单击输入下一个点，右键结束绘制");
    }
    else
    {
        view->ShowPrompt("请鼠标左键点击开始绘制折线");
    }
    return 0;
}




int CGDraw2DPolylineSegment::Cancel(GLFWwindow* window)
{
	if (window == nullptr)
		return -1;
	CCG2022111073冯杰View* view = (CCG2022111073冯杰View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;

	if (mDrawing) // 如果正在绘制中
	{
		// 擦除当前的橡皮筋线
		if (mRubberBandMoveCount > 0)
		{
			glEnable(GL_COLOR_LOGIC_OP);
			glLogicOp(GL_XOR);
			glColor3f(1.0f, 0.0f, 1.0f);
			glm::dvec3 rbStartWCS = view->DCS2WCS(mRubberBandStart);
			glm::dvec3 preRbEnd2WCS = view->DCS2WCS(mPrePos1);
			//draw2dline(rbStartWCS, preRbEnd2WCS); // 擦除旧橡皮筋线
            MidLine(rbStartWCS.x, rbStartWCS.y, preRbEnd2WCS.x, preRbEnd2WCS.y, glm::vec3(1.0f, 1.0f, 1.0f));
			glDisable(GL_COLOR_LOGIC_OP);
			glfwSwapBuffers(window);
		}

		// 重置状态
		mDrawing = false;
		mPoints.clear();
		mRubberBandMoveCount = 0;

		view->ShowPrompt("就绪"); // 状态栏显示
	}
	else // 没有正在绘制
	{
		view->ShowPrompt("就绪");
	}

	return 0;
}