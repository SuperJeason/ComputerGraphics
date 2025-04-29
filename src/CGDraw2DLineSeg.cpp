#include "pch.h"
#include "CGDraw2DLineSeg.h"
#include "CG2022111073冯杰Doc.h" //包含View之前要包含Doc
#include "CG2022111073冯杰View.h" //用户交互绘制，并将图形对象通过Doc添加到场景
#include "CGLineSegment.h"
// 绘制二维线
static void draw2dline(glm::dvec3& s, glm::dvec3& e)
{
	glBegin(GL_LINES);
	glVertex2d(s.x, s.y);
	glVertex2d(e.x, e.y);
	glEnd();
}
CGDraw2DLineSeg::CGDraw2DLineSeg(GLFWwindow* window)
	:UIEventHandler(window), mStart(0.0, 0.0, 0.0), mEnd(0.0, 0.0, 0.0)
{
}
CGDraw2DLineSeg::~CGDraw2DLineSeg()
{
}
EventType CGDraw2DLineSeg::GetType() //命令类型
{
	//UIEventHandler.h中定义，要根据不同的命令对象进行修改，此处是绘制直线段
	return EventType::Draw2DLineSeg;
}
//假定鼠标左键单击拾取线段起点、终点，移动鼠标时画橡皮筋线
int CGDraw2DLineSeg::OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
	if (window == nullptr)
		return -1;
	CCG2022111073冯杰View* view = (CCG2022111073冯杰View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			mStep++; //每次单击鼠标左键时操作步骤计数加一
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			if (mStep == 1) { //第一次单击鼠标左键，记录鼠标点击位置作为将创建线段的起点
				mStart.x = xpos;
				mStart.y = ypos;
				mEnd = mStart;
				mPrePos1 = mEnd;
				mPrePos2 = mEnd;
				view->ShowPrompt("请鼠标左键单击输入直线段的终点"); //通过处理事件的View显示到状态栏
			}
			else if (mStep == 2) {//第二次单击鼠标左键，记录鼠标点击位置作为将创建线段的终点
				if (xpos == mStart.x && ypos == mStart.y) {
					mStep = 1;
					view->ShowPrompt("与起点重合，请鼠标左键单击重新输入直线段的终点");
					return -1;
				}
				//判断是否按下SHIFT键，如果是，则根据X、Y方向的增量大小决定绘制水平线或垂直线
				int state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
				if (state == GLFW_PRESS) {
					if (abs(xpos - mStart.x) <= abs(ypos - mStart.y)) { //x方向变化小，垂直线
						mEnd.x = mStart.x; //X保持不变
						mEnd.y = ypos;
					}
					else { //x方向变化大，水平线
						mEnd.x = xpos;
						mEnd.y = mStart.y; //Y保持不变
					}
				}
				else { //一般直线段（非水平、垂直），记录终点。
					mEnd.x = xpos;
					mEnd.y = ypos;
				}
				glm::dvec3 start = view->DCS2WCS(mStart);
				glm::dvec3 pre2 = view->DCS2WCS(mPrePos2);
				glm::dvec3 end = view->DCS2WCS(mEnd);
				//擦除最后橡皮线
				glEnable(GL_COLOR_LOGIC_OP);
				glLogicOp(GL_XOR); // 使用异或模式实现橡皮线效果GL_XOR
				glColor3f(0.0f, 0.0f, 1.0f);
				if (mMoveCount == 0) {//第一次移动
					draw2dline(start, end); // 绘制新线
					mPrePos1 = mEnd;
					mPrePos2 = mEnd;
				}
				else if (mMoveCount == 1) { //第二次移动
					draw2dline(start, end); // 绘制新线
					mPrePos2 = mPrePos1;
					mPrePos1 = mEnd;
				}
				else {
					draw2dline(start, pre2);// 擦除旧线
					draw2dline(start, end); // 绘制新线
					mPrePos2 = mPrePos1;
					mPrePos1 = mEnd;
				}
				glDisable(GL_COLOR_LOGIC_OP);
				glfwSwapBuffers(window);
				//鼠标左键第二次单击，直线段创建的起点、终点已获取。
					//创建对象要注意坐标转换到场景，并设置相应的属性。
					//获取起点、终点对应的场景坐标用于创建直线段对象
				view->AddRenderable(std::make_shared<CGLineSegment>(start, end)); //创建添加到场景
				view->Invalidate(); //客户区需要重绘
				view->UpdateWindow(); //客户区执行重绘
				mStep = 0; //设为0可重写开始绘制线段而不用点击命令面板上的线段按钮
				mStart.x = mStart.y = mEnd.x = mEnd.y = 0;
				view->ShowPrompt("请输入直线段的起点"); //状态栏显示
			}
			else {
			}
		}
	}
	return 0;
}
int CGDraw2DLineSeg::OnCursorPos(GLFWwindow* window, double xpos, double ypos)
{
	if (window == nullptr)
		return -1;
	CCG2022111073冯杰View* view = (CCG2022111073冯杰View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mStep == 0) { //还没点击第一个点（获取线段起点）
		view->ShowPrompt("请鼠标左键单击输入直线段的起点"); //状态栏显示
	}
	else if (mStep == 1) {//已经输入了起点后，当前鼠标移动的位置与起点形成橡皮线
		if (xpos == mStart.x && ypos == mStart.y) {
			return -1; //两点重合，不做处理
		}
		//判断是否按下SHIFT键，如果是，则根据X、Y方向的增量大小决定绘制水平线或垂直线
		int state = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
		if (state == GLFW_PRESS) {
			if (abs(xpos - mStart.x) <= abs(ypos - mStart.y)) { //x方向变化小，垂直线
				mEnd.x = mStart.x;
				mEnd.y = ypos;
			}
			else {
				mEnd.x = xpos;
				mEnd.y = mStart.y;
			}
		}
		else {
			mEnd.x = xpos;
			mEnd.y = ypos;
		}
		glm::dvec3 start = view->DCS2WCS(mStart);
		glm::dvec3 pre2 = view->DCS2WCS(mPrePos2);
		glm::dvec3 end = view->DCS2WCS(mEnd);
		glEnable(GL_COLOR_LOGIC_OP);
		glLogicOp(GL_XOR); // 使用异或模式实现橡皮线效果GL_XOR
		glColor3f(0.0f, 0.0f, 1.0f);
		if (mMoveCount == 0) {//第一次移动
			draw2dline(start, end); // 绘制新线
			mPrePos1 = mEnd;
			mPrePos2 = mEnd;
			mMoveCount++;
		}
		else if (mMoveCount == 1) { //第二次移动
			draw2dline(start, end); // 绘制新线
			mPrePos2 = mPrePos1;
			mPrePos1 = mEnd;
			mMoveCount++;
		}
		else {
			draw2dline(start, pre2);// 擦除旧线
			draw2dline(start, end); // 绘制新线
			mPrePos2 = mPrePos1;
			mPrePos1 = mEnd;
			mMoveCount++;
		}
		glDisable(GL_COLOR_LOGIC_OP);
		glfwSwapBuffers(window);
	}
	else {
	}
	return 0;
}
//取消正在执行的命令（如按ESC键）
int CGDraw2DLineSeg::Cancel(GLFWwindow* window)
{
	if (window == nullptr)
		return -1;
	CCG2022111073冯杰View* view = (CCG2022111073冯杰View*)glfwGetWindowUserPointer(window);
	if (view == nullptr)
		return -1;
	if (mStep == 1) { //如果已经单击左键一次，则结束操作前删除橡皮线
		glm::dvec3 start = view->DCS2WCS(mStart);
		glm::dvec3 pre2 = view->DCS2WCS(mPrePos2);
		//擦除最后橡皮线
		glEnable(GL_COLOR_LOGIC_OP);
		glLogicOp(GL_XOR); // 使用异或模式实现橡皮线效果GL_XOR
		glColor3f(0.0f, 0.0f, 1.0f);
		draw2dline(start, pre2);// 擦除旧线
		glDisable(GL_COLOR_LOGIC_OP);
		glfwSwapBuffers(window);
	}
	mStep = 0;
	mStart.x = mStart.y = mEnd.x = mEnd.y = 0.0f;
	view->ShowPrompt("就绪"); //状态栏显示
	return 0;
}