#include "pch.h" // ��������Ŀʹ����Ԥ����ͷ�ļ�
#include "CGDraw2DPolylineSegment.h"
#include "CG2022111073���Doc.h" // ����View֮ǰҪ����Doc
#include "CG2022111073���View.h" // �û��������ƣ�����ͼ�ζ���ͨ��Doc��ӵ�����
#include <gl/GL.h> // ���� OpenGL ͷ�ļ�
// ���ƶ�ά�ߣ������������� CGDraw2DLineSeg ��ͬ��
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
    CCG2022111073���View* view = (CCG2022111073���View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    glm::dvec3 currentMousePos(xpos, ypos, 0.0);
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        if (!mDrawing) // ��ʼ����
        {
            mDrawing = true;
            mPoints.clear();
            mPoints.push_back(currentMousePos);
            mRubberBandStart = currentMousePos;
            mPrePos1 = currentMousePos;
            mPrePos2 = currentMousePos;
            mRubberBandMoveCount = 0;
            view->ShowPrompt("������������������һ���㣬�Ҽ���������");
        }
        else // ����µ�
        {
            // ����Ƿ�����һ�����غ�
            if (!mPoints.empty() && glm::distance(currentMousePos, mPoints.back()) < 1.0)
            {
                view->ShowPrompt("����һ�����غϣ�����������");
                return -1;
            }
            // ������ǰ����Ƥ����
            if (mRubberBandMoveCount > 0)
            {
                glEnable(GL_COLOR_LOGIC_OP);
                glLogicOp(GL_XOR);
                glColor3f(1.0f, 1.0f, 1.0f);
                glm::dvec3 startWCS = view->DCS2WCS(mRubberBandStart);
                glm::dvec3 prePos1WCS = view->DCS2WCS(mPrePos1);
                glm::dvec3 currentWCS = view->DCS2WCS(currentMousePos);
                draw2dline(startWCS, prePos1WCS); // ��������
                draw2dline(startWCS, currentWCS);
                glDisable(GL_COLOR_LOGIC_OP);
                glfwSwapBuffers(window);
            }
            glColor3f(1.0f, 1.0f, 1.0f);
            glm::dvec3 startWCS = view->DCS2WCS(mRubberBandStart);
            glm::dvec3 currentWCS = view->DCS2WCS(currentMousePos);
            draw2dline(startWCS, currentWCS);
            // ����µ㣬��������Ƥ�������
            mPoints.push_back(currentMousePos);
            mRubberBandStart = currentMousePos; // ����Ƥ���ߴӵ�ǰ�㿪ʼ
            mPrePos1 = currentMousePos;
            mPrePos2 = currentMousePos;
            mRubberBandMoveCount = 0; // ���ü���
            view->ShowPrompt("������������������һ���㣬�Ҽ���������");
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        if (mDrawing)
        {
            mPoints.push_back(currentMousePos);
            // ������Ƥ����
            if (mRubberBandMoveCount > 0)
            {
                glEnable(GL_COLOR_LOGIC_OP);
                glLogicOp(GL_XOR);
                glColor3f(1.0f, 1.0f, 1.0f);
                glm::dvec3 startWCS = view->DCS2WCS(mRubberBandStart);
                glm::dvec3 prePos1WCS = view->DCS2WCS(mPrePos1);
                draw2dline(startWCS, prePos1WCS);
                glDisable(GL_COLOR_LOGIC_OP);
                glfwSwapBuffers(window);
            }
            if (mPoints.size() >= 2) // �����㹻����������
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
                view->ShowPrompt("�������㣬ȡ������");
            }
            // ����״̬
            mDrawing = false;
            mPoints.clear();
            mRubberBandMoveCount = 0;
            view->ShowPrompt("����");
        }
        else
        {
            view->ShowPrompt("������������ʼ��������");
        }
    }
    return 0;
}


int CGDraw2DPolylineSegment::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
    if (window == nullptr)
        return -1;
    CCG2022111073���View* view = (CCG2022111073���View*)glfwGetWindowUserPointer(window);
    if (view == nullptr)
        return -1;
    mCurrentPos.x = xpos;
    mCurrentPos.y = ypos;
    if (mDrawing)
    {
        // ����ǰ���λ��ת��Ϊ�������꣨���ڻ��ƣ�
        glm::dvec3 startWCS = view->DCS2WCS(mRubberBandStart);
        glm::dvec3 currentWCS = view->DCS2WCS(mCurrentPos);
        glEnable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_XOR);
        glColor3f(1.0f, 1.0f, 1.0f); // ��ɫ��Ƥ����
        if (mRubberBandMoveCount == 0)
        {
            // ��һ���ƶ���ֱ�ӻ�������
            draw2dline(startWCS, currentWCS);
            mPrePos1 = mCurrentPos; // ��¼��һ�ε��յ�
            mPrePos2 = mCurrentPos; // ��ʼ�� mPrePos2
        }
        else if (mRubberBandMoveCount == 1)
        {
            // �ڶ����ƶ���������һ�ε��ߣ��ٻ�������
            glm::dvec3 prePos1WCS = view->DCS2WCS(mPrePos1);
            draw2dline(startWCS, prePos1WCS); // ��������
            draw2dline(startWCS, currentWCS); // ��������
            mPrePos2 = mPrePos1; // ���� mPrePos2
            mPrePos1 = mCurrentPos; // ���� mPrePos1
        }
        else
        {
            // �����ƶ����������ϴε��ߣ��ٻ�������
            glm::dvec3 prePos2WCS = view->DCS2WCS(mPrePos2);
            draw2dline(startWCS, prePos2WCS); // ��������
            draw2dline(startWCS, currentWCS); // ��������
            mPrePos2 = mPrePos1; // ���� mPrePos2
            mPrePos1 = mCurrentPos; // ���� mPrePos1
        }
        glDisable(GL_COLOR_LOGIC_OP);
        glfwSwapBuffers(window);
        mRubberBandMoveCount++; // �����ƶ�����
        view->ShowPrompt("������������������һ���㣬�Ҽ���������");
    }
    else
    {
        view->ShowPrompt("�������������ʼ��������");
    }
    return 0;
}




int CGDraw2DPolylineSegment::Cancel(GLFWwindow* window)
{
	if (window == nullptr)
		return -1;
	CCG2022111073���View* view = (CCG2022111073���View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;

	if (mDrawing) // ������ڻ�����
	{
		// ������ǰ����Ƥ����
		if (mRubberBandMoveCount > 0)
		{
			glEnable(GL_COLOR_LOGIC_OP);
			glLogicOp(GL_XOR);
			glColor3f(1.0f, 0.0f, 1.0f);
			glm::dvec3 rbStartWCS = view->DCS2WCS(mRubberBandStart);
			glm::dvec3 preRbEnd2WCS = view->DCS2WCS(mPrePos1);
			draw2dline(rbStartWCS, preRbEnd2WCS); // ��������Ƥ����
			glDisable(GL_COLOR_LOGIC_OP);
			glfwSwapBuffers(window);
		}

		// ����״̬
		mDrawing = false;
		mPoints.clear();
		mRubberBandMoveCount = 0;

		view->ShowPrompt("����"); // ״̬����ʾ
	}
	else // û�����ڻ���
	{
		view->ShowPrompt("����");
	}

	return 0;
}