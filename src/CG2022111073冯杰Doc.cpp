// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// CG2022111073冯杰Doc.cpp: CCG2022111073冯杰Doc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG2022111073冯杰.h"
#endif

#include "CG2022111073冯杰Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CG2022111073冯杰View.h"
#include "CGScene.h"
#include "CGCamera.h"
#include "CGTransform.h"
#include "CGGeode.h"
#include "CGLineSegment.h"
#include "CCGRenderContext.h"
#include "UIEventHandler.h"
#include "CGDraw2DLineSeg.h"
#include "CGPolylineSegment.h"
#include "CGDraw2DPolylineSegment.h"
#include "CCGSceneGraphView.h"
#include "CGModel2DTransform.h"
#include "CGCube.h"
#include "TessellationHints.h"
#include "CGSphere.h"
#include "CGSphereInput.h"
#include "RobotBodyTransformParam.h"
#include "CameraControl.h"
#include "CGMaterial.h"
// CCG2022111073冯杰Doc

IMPLEMENT_DYNCREATE(CCG2022111073冯杰Doc, CDocument)

BEGIN_MESSAGE_MAP(CCG2022111073冯杰Doc, CDocument)
	ON_COMMAND(ID_DRAW2d_LINESEG, &CCG2022111073冯杰Doc::OnDraw2dLineseg)
	ON_UPDATE_COMMAND_UI(ID_DRAW2d_LINESEG, &CCG2022111073冯杰Doc::OnUpdateDraw2dLineseg)
	ON_COMMAND(ID_DRAW2D_POLYGON, &CCG2022111073冯杰Doc::OnDraw2dPolygon)
	ON_UPDATE_COMMAND_UI(ID_DRAW2D_POLYGON, &CCG2022111073冯杰Doc::OnUpdateDraw2dPolygon)
	ON_COMMAND(ID_TRANSLATE_LEFT, &CCG2022111073冯杰Doc::OnTranslateLeft)
	ON_COMMAND(ID_TRANSLATE_RIGHT, &CCG2022111073冯杰Doc::OnTranslateRight)
	ON_COMMAND(ID_TRANSLATE_UP, &CCG2022111073冯杰Doc::OnTranslateUp)
	ON_COMMAND(ID_TRANSLATE_DOWN, &CCG2022111073冯杰Doc::OnTranslateDown)
	ON_COMMAND(ID_ROTATE_R, &CCG2022111073冯杰Doc::OnRotateR)
	ON_COMMAND(ID_ROTATE_L, &CCG2022111073冯杰Doc::OnRotateL)
	ON_COMMAND(ID_SCALE_X, &CCG2022111073冯杰Doc::OnScaleX)
	ON_COMMAND(ID_SCALE_Y, &CCG2022111073冯杰Doc::OnScaleY)
	ON_COMMAND(ID_SCALE_XY, &CCG2022111073冯杰Doc::OnScaleXy)
	ON_COMMAND(ID_BTN_TIMER, &CCG2022111073冯杰Doc::OnBtnTimer)
	ON_UPDATE_COMMAND_UI(ID_BTN_TIMER, &CCG2022111073冯杰Doc::OnUpdateBtnTimer)
	ON_COMMAND(CAMERACONTROL, &CCG2022111073冯杰Doc::OnCameracontrol)
END_MESSAGE_MAP()


// CCG2022111073冯杰(Doc 构造/析构

CCG2022111073冯杰Doc::CCG2022111073冯杰Doc() noexcept {
	// TODO: 在此添加一次性构造代码
	mScene = std::make_shared<CGScene>();
	mScene->SetMainCamera(std::make_shared<CGCamera>());


	// 创建材质
	auto createMaterial = [](const glm::vec4& baseColor) {
		auto material = std::make_shared<CGMaterial>();
		// 使用材质
		material->mFrontAmbient = baseColor * 0.8f;
		material->mFrontDiffuse = baseColor * 0.8f;
		material->mFrontSpecular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		material->mFrontEmission = glm::vec4(0.0f);
		material->mFrontShininess = 50.0f;
		material->mBackAmbient = baseColor * 0.1f;
		material->mBackDiffuse = baseColor * 0.2f;
		material->mBackSpecular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		material->mBackShininess = 50.0f;
		material->mColorMaterialFace = EPolygonFace::PF_FRONT_AND_BACK;
		material->mColorMaterial = EColorMaterial::CM_DIFFUSE;
		material->mColorMaterialEnabled = false;
		return material;
		};
	auto e = std::make_shared<CGGeode>();
	auto line = std::make_shared<CGLineSegment>(glm::dvec3(100, 100, 0), glm::dvec3(400, 300,
		0));
	e->AddChild(line);
	auto g = std::make_shared<CGTransform>();
	g->AddChild(e);
	mScene->SetSceneData(g);
	auto ballmaterial = createMaterial(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	//////长方体（模型）
	//////长方体（模型）
	auto c = std::make_shared<CGCube>();
	auto h = std::make_shared<TessellationHints>();
	c->setTessellationHints(h);
	c->setDisplayListEnabled(true);
	//右长方体实例节点
	auto t1 = std::make_shared<CGTransform>(); //实列组节点
	auto e1 = std::make_shared<CGGeode>(); //实列叶节点
	auto color1 = std::make_shared<CGColor>(); //属性
	color1->setValue(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)); //黄色
	e1->gocRenderStateSet()->setRenderState(ballmaterial, -1); //设置节点属性
	t1->translate(300, -200, 0);
	t1->rotate(45, 1, 1, 1);
	t1->scale(100, 100, 100);
	e1->AddChild(c);
	t1->AddChild(e1);
	mScene->GetSceneData()->asGroup()->AddChild(t1);
	//左长方体节点
	auto t2 = std::make_shared<CGTransform>(); //实列组节点
	auto e2 = std::make_shared<CGGeode>(); //实列叶节点
	auto color2 = std::make_shared<CGColor>(); //属性
	color2->setValue(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); //蓝色
	e2->gocRenderStateSet()->setRenderState(ballmaterial, -1); //设置节点属性
	auto p = std::make_shared<CGPolygonMode>(PM_FILL, PM_FILL); //设置线框模式
	e2->gocRenderStateSet()->setRenderState(p, -1); //设置节点属性
	t2->translate(-300, -200, 0);
	t2->rotate(45, 1, 1, 1);
	t2->scale(100, 100, 100);
	e2->AddChild(c);
	t2->AddChild(e2);
	mScene->GetSceneData()->asGroup()->AddChild(t2);
	//// 创建共享的球体几何体

	//CGSphereInput dlg;
	//dlg.mTitle = _T("请输入Slice和Stack"); //根据需要设置对话框标题
	//if (dlg.DoModal() == IDOK) //对话框中点击了【确定】按钮，取回输入的数据
	//{ //根据实际需要使用输入的数据
	////假如输入的是数值，则将字符串转换为数值
		//double slice = _ttof(dlg.mValueSlice);
		//double stack = _ttof(dlg.mValueStack);
	double slice = 15;
	double stack = 15;
	//	//
	//	//此处只显示输入的数据，实际应根据获取的值作相应的处理
	//AfxMessageBox(dlg.mValueSlice);

	auto sphere = std::make_shared<CGSphere>(100.0f);
	auto hints = std::make_shared<TessellationHints>();
	hints->setTargetSlices(slice); // 提高细分精度
	hints->setTargetStacks(stack);
	sphere->setTessellationHints(hints);
	sphere->setDisplayListEnabled(true);
	t1 = std::make_shared<CGTransform>();
	e1 = std::make_shared<CGGeode>();
	color1 = std::make_shared<CGColor>();
	color1->setValue(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)); //蓝色
	e1->gocRenderStateSet()->setRenderState(ballmaterial, -1);
	t1->translate(300, 100, 0);
	e1->AddChild(sphere);
	t1->AddChild(e1);
	mScene->GetSceneData()->asGroup()->AddChild(t1);

	t2 = std::make_shared<CGTransform>();
	e2 = std::make_shared<CGGeode>();
	color2 = std::make_shared<CGColor>();
	color2->setValue(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	auto polygonMode = std::make_shared<CGPolygonMode>(PM_FILL, PM_FILL);
	e2->gocRenderStateSet()->setRenderState(ballmaterial, -1);
	e2->gocRenderStateSet()->setRenderState(polygonMode, -1);
	t2->translate(-300, 100, 0);
	t2->rotate(45, 1, 1, 1);
	e2->AddChild(sphere);
	t2->AddChild(e2);
	mScene->GetSceneData()->asGroup()->AddChild(t2);

	std::shared_ptr<RobotBodyTransformParam> data = std::make_shared<RobotBodyTransformParam>();
	std::shared_ptr<RobotBodyRotate> rc = std::make_shared<RobotBodyRotate>();
	t2->setUserData(data); //设置节点更新参数
	t2->SetUpdateCallback(rc); //设置节点更新回调

	auto cube = std::make_shared<CGCube>();
	hints = std::make_shared<TessellationHints>();
	cube->setTessellationHints(hints);
	cube->setDisplayListEnabled(true);

	

	auto createBodyPart = [&cube, &createMaterial](const glm::vec4& color, float scaleX,
		float scaleY, float scaleZ, float posX, float posY, float posZ) {
			auto transform = std::make_shared<CGTransform>();
			auto geode = std::make_shared<CGGeode>();
			auto material = createMaterial(color);
			geode->gocRenderStateSet()->setRenderState(material, -1);
			auto polygonMode = std::make_shared<CGPolygonMode>(PM_FILL, PM_FILL);
			geode->gocRenderStateSet()->setRenderState(polygonMode, -1);
			transform->translate(posX, posY, posZ);
			transform->scale(scaleX, scaleY, scaleZ);
			geode->AddChild(cube);
			transform->AddChild(geode);
			return transform;
		};

	auto robot = std::make_shared<CGTransform>();

	// Colors for a cohesive metallic look
	auto head_color = glm::vec4(0.8f, 0.1f, 0.1f, 1.0f);   // 红色
	auto torso_color = glm::vec4(0.2f, 0.8f, 0.2f, 1.0f);  // 绿色
	auto arm_color = glm::vec4(0.1f, 0.1f, 0.8f, 1.0f);    // 蓝色
	auto leg_color = glm::vec4(0.8f, 0.8f, 0.1f, 1.0f);    // 黄色

	// --- Head ---
	auto head = createBodyPart(
		head_color, 50.0f, 50.0f, 50.0f, 0.0f, 380.0f, 0.0f);
	robot->AddChild(head);

	// Torso: Fewer, tighter segments for a compact look
	float torso_base_scale_X = 100.0f;
	float torso_base_scale_Z = 70.0f;
	float segment_height = 45.0f;
	float top_surface_of_torso_Y = 340.0f;

	// Part 4 (Top Segment)
	float torso4_actual_posY = top_surface_of_torso_Y - segment_height / 2.0f;
	auto torso4_actual = createBodyPart(torso_color, torso_base_scale_X, segment_height,
		torso_base_scale_Z, 0.0f, torso4_actual_posY, 0.0f);
	// Part 3
	float torso3_actual_posY = torso4_actual_posY - segment_height * 0.95f;
	auto torso3_actual = createBodyPart(torso_color, torso_base_scale_X * 0.9f, segment_height,
		torso_base_scale_Z * 0.8f, 0.0f, torso3_actual_posY, 0.0f);
	// Part 2
	float torso2_actual_posY = torso3_actual_posY - segment_height * 0.95f;
	auto torso2_actual = createBodyPart(torso_color, torso_base_scale_X * 0.85f, segment_height,
		torso_base_scale_Z * 0.75f, 0.0f, torso2_actual_posY, 0.0f);
	// Part 1
	float torso1_actual_posY = torso2_actual_posY - segment_height * 0.95f;
	auto torso1_actual = createBodyPart(torso_color, torso_base_scale_X * 0.8f, segment_height,
		torso_base_scale_Z * 0.7f, 0.0f, torso1_actual_posY, 0.0f);

	robot->AddChild(torso1_actual);
	robot->AddChild(torso2_actual);
	robot->AddChild(torso3_actual);
	robot->AddChild(torso4_actual);

	float hip_Y = torso1_actual_posY - segment_height / 2.0f;
	float shoulder_Y = torso4_actual_posY + segment_height / 2.0f;

	// --- Limb Dimensions ---
	float armW = 30.0f, armD = 30.0f;
	float upperArmL = 100.0f;
	float lowerArmL = 90.0f;

	float legW = 40.0f, legD = 40.0f;
	float upperLegL = 110.0f;
	float lowerLegL = 100.0f;

	float footH = 12.0f, footL_extension = 15.0f;

	float shoulder_X_offset = torso_base_scale_X / 2.0f + armW / 4.0f;
	float hip_X_offset = torso_base_scale_X / 2.0f * 0.75f;

	// --- Left Arm ---
	auto leftUpperArmAnchor = std::make_shared<CGTransform>();
	leftUpperArmAnchor->translate(shoulder_X_offset, shoulder_Y, 0.0f);
	leftUpperArmAnchor->rotate(15.0f, 0.0f, 0.0f, 1.0f);
	robot->AddChild(leftUpperArmAnchor);

	auto leftUpperArmVisual =
		createBodyPart(arm_color, armW, upperArmL, armD, 0.0f, -upperArmL / 2.0f, 0.0f);
	leftUpperArmAnchor->AddChild(leftUpperArmVisual);

	auto leftLowerArmAnchor = std::make_shared<CGTransform>();
	leftLowerArmAnchor->translate(0.0f, -upperArmL * 0.98f, 0.0f);
	leftLowerArmAnchor->rotate(-90.0f, 1.0f, 0.0f, 0.0f);
	leftUpperArmAnchor->AddChild(leftLowerArmAnchor);

	auto leftLowerArmVisual =
		createBodyPart(arm_color, armW, lowerArmL, armD, 0.0f, -lowerArmL / 2.0f, 0.0f);
	leftLowerArmAnchor->AddChild(leftLowerArmVisual);

	// --- Right Arm ---
	auto rightUpperArmAnchor = std::make_shared<CGTransform>();
	rightUpperArmAnchor->translate(-shoulder_X_offset, shoulder_Y, 0.0f);
	rightUpperArmAnchor->rotate(-25.0f, 15.0f, 1.0f, 0.0f);
	rightUpperArmAnchor->rotate(-15.0f, 1.0f, 0.0f, 0.0f);
	rightUpperArmAnchor->rotate(10.0f, 0.0f, 0.0f, 1.0f);
	robot->AddChild(rightUpperArmAnchor);

	auto rightUpperArmVisual =
		createBodyPart(arm_color, armW, upperArmL, armD, 0.0f, -upperArmL / 2.0f, 0.0f);
	rightUpperArmAnchor->AddChild(rightUpperArmVisual);

	auto rightLowerArmAnchor = std::make_shared<CGTransform>();
	rightLowerArmAnchor->translate(0.0f, -upperArmL * 0.98f, 0.0f);
	rightLowerArmAnchor->rotate(-30.0f, 1.0f, 0.0f, 0.0f);
	rightLowerArmAnchor->rotate(-10.0f, 0.0f, 1.0f, 0.0f);
	rightUpperArmAnchor->AddChild(rightLowerArmAnchor);

	auto rightLowerArmVisual =
		createBodyPart(arm_color, armW, lowerArmL, armD, 0.0f, -lowerArmL / 2.0f, 0.0f);
	rightLowerArmAnchor->AddChild(rightLowerArmVisual);

	// --- Left Leg ---
	auto leftHipAnchor = std::make_shared<CGTransform>();
	leftHipAnchor->translate(hip_X_offset, hip_Y, 0.0f);
	leftHipAnchor->rotate(10.0f, 0.0f, 1.0f, 0.0f);
	leftHipAnchor->rotate(-20.0f, 1.0f, 0.0f, 0.0f);
	robot->AddChild(leftHipAnchor);

	auto leftUpperLegVisual =
		createBodyPart(leg_color, legW, upperLegL, legD, 0.0f, -upperLegL / 2.0f, 0.0f);
	leftHipAnchor->AddChild(leftUpperLegVisual);

	auto leftKneeAnchor = std::make_shared<CGTransform>();
	leftKneeAnchor->translate(0.0f, -upperLegL * 0.98f, 0.0f);
	leftKneeAnchor->rotate(2.0f, 2.0f, 0.0f, 0.0f);
	leftHipAnchor->AddChild(leftKneeAnchor);

	auto leftLowerLegVisual =
		createBodyPart(leg_color, legW, lowerLegL, legD, 0.0f, -lowerLegL / 2.0f, 0.0f);
	leftKneeAnchor->AddChild(leftLowerLegVisual);

	auto leftAnkleAnchor = std::make_shared<CGTransform>();
	leftAnkleAnchor->translate(0.0f, -lowerLegL * 0.98f, 0.0f);
	leftAnkleAnchor->rotate(0.0f, 1.0f, 0.0f, 0.0f);
	leftKneeAnchor->AddChild(leftAnkleAnchor);

	auto leftFootVisual = createBodyPart(leg_color, legW, footH, legD + footL_extension, 0.0f,
		-footH / 2.0f, (legD + footL_extension) / 2.0f - legD / 2.0f);
	leftAnkleAnchor->AddChild(leftFootVisual);

	// --- Right Leg ---
	auto rightHipAnchor = std::make_shared<CGTransform>();
	rightHipAnchor->translate(-hip_X_offset, hip_Y, 0.0f);
	rightHipAnchor->rotate(-10.0f, 0.0f, 1.0f, 0.0f);
	rightHipAnchor->rotate(10.0f, 1.0f, 0.0f, 0.0f);
	robot->AddChild(rightHipAnchor);

	auto rightUpperLegVisual =
		createBodyPart(leg_color, legW, upperLegL, legD, 0.0f, -upperLegL / 2.0f, 0.0f);
	rightHipAnchor->AddChild(rightUpperLegVisual);

	auto rightKneeAnchor = std::make_shared<CGTransform>();
	rightKneeAnchor->translate(0.0f, -upperLegL * 0.98f, 0.0f);
	rightKneeAnchor->rotate(10.0f, 1.0f, 0.0f, 0.0f);
	rightHipAnchor->AddChild(rightKneeAnchor);

	auto rightLowerLegVisual =
		createBodyPart(leg_color, legW, lowerLegL, legD, 0.0f, -lowerLegL / 2.0f, 0.0f);
	rightKneeAnchor->AddChild(rightLowerLegVisual);

	auto rightAnkleAnchor = std::make_shared<CGTransform>();
	rightAnkleAnchor->translate(0.0f, -lowerLegL * 0.98f, 0.0f);
	rightAnkleAnchor->rotate(-10.0f, 1.0f, 0.0f, 0.0f);
	rightKneeAnchor->AddChild(rightAnkleAnchor);

	auto rightFootVisual = createBodyPart(leg_color, legW, footH, legD + footL_extension, 0.0f,
		-footH / 2.0f, (legD + footL_extension) / 2.0f - legD / 2.0f);
	rightAnkleAnchor->AddChild(rightFootVisual);

	float leg_plus_foot_length = upperLegL + lowerLegL + footH;
	float lowest_point_y = hip_Y - leg_plus_foot_length;

	mScene->GetSceneData()->asGroup()->AddChild(robot);

	// 机器人跑步
	std::shared_ptr<RobotBodyTransformParam> data2 = std::make_shared<RobotBodyTransformParam>();
	data->setRotateDegree(40.0f);   // 手臂摆动 ±40 度，腿部 ±26.4 度（40 * 0.66）
	std::shared_ptr<RobotRun> rc2 = std::make_shared<RobotRun>();
	rc2->setEnabled(true);   // 确保回调启用
	robot->setUserData(data2);
	robot->SetUpdateCallback(rc2);
}


CCG2022111073冯杰Doc::~CCG2022111073冯杰Doc()
{
}

BOOL CCG2022111073冯杰Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCG2022111073冯杰Doc 序列化

void CCG2022111073冯杰Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCG2022111073冯杰Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCG2022111073冯杰Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCG2022111073冯杰Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCG2022111073冯杰Doc 诊断

#ifdef _DEBUG
void CCG2022111073冯杰Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCG2022111073冯杰Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCG2022111073冯杰Doc 命令

void CCG2022111073冯杰Doc::OnDraw2dLineseg()
{
	if (!mSelectedGroup) {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
		return;
	}
	// TODO: 在此添加命令处理程序代码
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(new CGDraw2DLineSeg(view->glfwWindow())); //创建绘制直线段的命令对象
	}
}
void CCG2022111073冯杰Doc::OnUpdateDraw2dLineseg(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(UIEventHandler::CurCommand() && UIEventHandler::CurCommand()->GetType() == EventType::Draw2DLineSeg);
}

bool CCG2022111073冯杰Doc::RenderScene(CGRenderContext* pRC)
{
	if (pRC == nullptr)
		return false;
	if (mScene == nullptr)
		return false;
	CGCamera* pCamera = mScene->GetMainCamera();
	if (pCamera == nullptr)
		return false;
	return mScene->Render(pRC, pCamera);
}
bool CCG2022111073冯杰Doc::AddRenderable(std::shared_ptr<CGNode> r)
{
	if (mSelectedGroup) { //需要先选中一各组节点
		//模型加入实例节点后加入场景
		auto ge = std::make_shared<CGGeode>();
		ge->AddChild(r);
		mSelectedGroup->AddChild(ge);
		CTreeCtrl& tree = GetSceneGraphView()->GetTreeCtrl();
		InstToSceneTree(&tree, mSelectedItem, ge.get());
		return true;
	}
	else {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
	}
	return false;
}
void CCG2022111073冯杰Doc::OnDraw2dPolygon()
{
	if (!mSelectedGroup) {
		AfxMessageBox(_T("请先选择添加子节点的组节点！"));
		return;
	}
	// TODO: 在此添加命令处理程序代码
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGDraw2DPolylineSegment(view->glfwWindow())); //创建绘制折线的命令对象
	}
}

void CCG2022111073冯杰Doc::OnUpdateDraw2dPolygon(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

CCGSceneGraphView* CCG2022111073冯杰Doc::GetSceneGraphView()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCGSceneGraphView))) {
			CCGSceneGraphView* view = dynamic_cast<CCGSceneGraphView*>(pView);
			return view;
		}
	}
	return nullptr;
}
void CCG2022111073冯杰Doc::InstToSceneTree(CTreeCtrl* pTree)
{
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hInst;
	tvinsert.hParent = NULL;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 40;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = NULL;//
	CString str(_T("场景"));
	tvinsert.item.pszText = str.GetBuffer();
	str.ReleaseBuffer();
	hInst = pTree->InsertItem(&tvinsert);
	pTree->SetItemData(hInst, DWORD_PTR(mScene.get()));
	InstToSceneTree(pTree, hInst, mScene->GetSceneData());
	pTree->Expand(hInst, TVE_EXPAND);
}
void CCG2022111073冯杰Doc::InstToSceneTree(CTreeCtrl* pTree, HTREEITEM hParent, CGNode* node)
{
	TV_INSERTSTRUCT tvinsert;
	HTREEITEM hTree;
	tvinsert.hParent = hParent;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT | TVIF_PARAM;
	tvinsert.item.hItem = NULL;
	tvinsert.item.state = 0;
	tvinsert.item.stateMask = 0;
	tvinsert.item.cchTextMax = 40;
	tvinsert.item.cChildren = 0;
	tvinsert.item.lParam = LPARAM(&node);//
	if (node->asGeode()) {
		CString str(_T("Geode"));
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		//叶子实例节点不再显示模型节点
	}
	else if (node->asTransform()) {
		CString str(_T("Trans"));
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		unsigned int childs = node->asTransform()->GetNumChildren();
		for (unsigned int i = 0; i < childs; i++) {
			InstToSceneTree(pTree, hTree, node->asTransform()->GetChild(i));
		}
	}
	else if (node->asGroup()) {
		CString str(_T("Group"));
		tvinsert.item.pszText = str.GetBuffer();
		str.ReleaseBuffer();
		hTree = pTree->InsertItem(&tvinsert);
		pTree->SetItemData(hTree, DWORD_PTR(node));
		unsigned int childs = node->asGroup()->GetNumChildren();
		for (unsigned int i = 0; i < childs; i++) {
			InstToSceneTree(pTree, hTree, node->asGroup()->GetChild(i));
		}
	}
}
void CCG2022111073冯杰Doc::OnSelectSceneTreeItem(CTreeCtrl* pTree, HTREEITEM hItem)
{
	mSelectedItem = hItem;
	if (!mSelectedItem) {
		mSelectedGroup = nullptr;
		return;
	}
	HTREEITEM hRoot = pTree->GetRootItem();
	if (mSelectedItem == hRoot) {
		mSelectedGroup = nullptr;
	}
	else {
		CGGroup* node = (CGGroup*)(pTree->GetItemData(mSelectedItem));
		if (node && node->asGroup() && !(node->asGeode())) { //不允许叶子节点上再
			mSelectedGroup = dynamic_cast<CGGroup*>(node);
		}
		else {
			mSelectedGroup = nullptr;
		}
	}
}
void CCG2022111073冯杰Doc::OnTranslateLeft()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		// UIEventHandler::SetCommand(new CGModel2DTransform((CGRenderable*)pTree->GetItemData(mSelectedItem),view->glfwWindow())); 
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		// 直接应用向左平移变换（每次移动10个单位）
		const float translateAmount = -10.0f; // 负值表示向左移动
		child->Translate(translateAmount, 0);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已向左移动");
	}
}



void CCG2022111073冯杰Doc::OnTranslateRight()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		// UIEventHandler::SetCommand(new CGModel2DTransform((CGRenderable*)pTree->GetItemData(mSelectedItem),view->glfwWindow())); 
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		// 直接应用向左平移变换（每次移动10个单位）
		const float translateAmount = 10.0f; // 负值表示向右移动
		child->Translate(translateAmount, 0);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已向左移动");
	}
}

void CCG2022111073冯杰Doc::OnTranslateUp()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		// UIEventHandler::SetCommand(new CGModel2DTransform((CGRenderable*)pTree->GetItemData(mSelectedItem),view->glfwWindow())); 
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		// 直接应用向左平移变换（每次移动10个单位）
		const float translateAmount = 10.0f; // 负值表示向左移动
		child->Translate(0, translateAmount);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已向上移动");
	}
}

void CCG2022111073冯杰Doc::OnTranslateDown()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}

	if (view != nullptr) {
		// UIEventHandler::SetCommand(new CGModel2DTransform((CGRenderable*)pTree->GetItemData(mSelectedItem),view->glfwWindow())); 
		CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
		if (!renderable) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		CGNode* child = renderable->GetChild(0);
		if (!child) {
			AfxMessageBox(_T("请先选择需要移动的子节点！"));
			return;
		}
		// 直接应用向左平移变换（每次移动10个单位）
		const float translateAmount = -10.0f; // 负值表示向左移动
		child->Translate(0, translateAmount);
		// 更新所有视图
		UpdateAllViews(NULL);

		// 设置状态栏提示
		view->ShowPrompt("对象已向下移动");
	}
}

void CCG2022111073冯杰Doc::OnRotateR()
{
	// TODO: 在此添加命令处理程序代码
	// 顺时针旋转操作
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow())); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}

}

void CCG2022111073冯杰Doc::OnRotateL()
{
	// TODO: 在此添加命令处理程序代码
	// 顺时针旋转操作
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow())); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}

void CCG2022111073冯杰Doc::OnScaleX()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow(), true, false)); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}

void CCG2022111073冯杰Doc::OnScaleY()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow(), false, true)); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}

void CCG2022111073冯杰Doc::OnScaleXy()
{
	// TODO: 在此添加命令处理程序代码
	CCGSceneGraphView* pSceneGraphView = GetSceneGraphView();
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	CTreeCtrl* pTree = &pSceneGraphView->GetTreeCtrl();
	CGGeode* renderable = (CGGeode*)pTree->GetItemData(mSelectedItem);
	if (!renderable) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	// 如果当前有正在执行的命令，先删除它
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	CGNode* child = renderable->GetChild(0);
	if (!child) {
		AfxMessageBox(_T("请先选择需要移动的子节点！"));
		return;
	}
	// 如果找到了视图，创建并设置绘制折线段的命令对象
	if (view != nullptr) {
		// 使用新的 CGDraw2DPolylineSegment 类
		UIEventHandler::SetCommand(new CGModel2DTransform(child, view->glfwWindow(), true, true)); //创建绘制折线的命令对象
		UpdateAllViews(NULL);
	}
}

void CCG2022111073冯杰Doc::OnBtnTimer()
{
	// TODO: 在此添加命令处理程序代码
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	if (view != nullptr) {
		mTimer = view->toggleFrameTimer();// 启动定时器
	}
}

void CCG2022111073冯杰Doc::OnUpdateBtnTimer(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(mTimer != 0);
}

void CCG2022111073冯杰Doc::OnViewResize(int cx, int cy) {
	mScene->GetMainCamera()->viewport()->set(0, 0, cx, cy);
}
void CCG2022111073冯杰Doc::OnCameracontrol()
{
	//// TODO: 在此添加命令处理程序代码
	CCG2022111073冯杰View* view = nullptr;
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL) {
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CCG2022111073冯杰View))) {
			view = dynamic_cast<CCG2022111073冯杰View*>(pView);
			break;
		}
	}
	if (UIEventHandler::CurCommand()) {
		UIEventHandler::DelCommand();
	}
	if (view != nullptr) {
		UIEventHandler::SetCommand(
			new CameraControl(view->glfwWindow(), mScene->GetMainCamera()));
	}
}
