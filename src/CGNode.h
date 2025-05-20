#pragma once
#include "CGObject.h"
#include "CGRenderState.h"
#include <vector>
//预声明（本文件中只用到相关类指针，为避免交叉包含）
class CGNode;
class CGCamera;
class CGRenderContext;
class CGGroup;
class CGTransform;
class CGGeode;
class CGRenderable;
class CGGeometry;
class CGNode : public CGObject
{
	DECLARE_SERIAL(CGNode)
public:
	CGNode();
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//绘制对象（在派生类中重写）
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual CGNode* asNode() { return this; }
	virtual const CGNode* asNode() const { return this; }
	virtual CGGroup* asGroup() { return 0; }
	virtual const CGGroup* asGroup() const { return 0; }
	virtual CGTransform* asTransform() { return 0; }
	virtual const CGTransform * asTransform() const { return 0; }
	virtual CGRenderable* asRenderable() { return 0; }
	virtual const CGRenderable* asRenderable() const { return 0; }
	virtual CGGeode* asGeode() { return 0; }
	virtual const CGGeode* asGeode() const { return 0; }
	virtual CGGeometry* asGeometry() { return 0; }
	virtual const CGGeometry* asGeometry() const { return 0; }
	void SetUpdateCallback(std::shared_ptr<CGCallback> uc) { mUpdateCallback = uc; }
	inline CGCallback* GetUpdateCallback() { return mUpdateCallback.get(); }
	//支持共享子节点（如，实例节点共享几何模型）
	typedef std::vector<CGGroup*> ParentList;
	CGGroup* GetParent(unsigned int i);
	const CGGroup* GetParent(unsigned int i) const;
	inline const ParentList& GetParents() const { return mParents; }
	inline ParentList GetParents() { return mParents; }
	inline unsigned int GetNumParents() const { return static_cast<unsigned int>(mParents.size()); }
	virtual void Translate(float dx, float dy) {}
	virtual void Rotate(double angle, double cx, double cy) {}
	virtual void Scale(double sx, double sy,double cx,double cy) {}
protected:
	virtual ~CGNode();
	std::shared_ptr<CGCallback> mUpdateCallback = nullptr;
	friend class CGGroup;
	friend class CGRenderable;
	ParentList mParents; //一个模型关联到多个图形节点（产生多个实例节点）
	void AddParent(CGGroup* parent);
	void RemoveParent(CGGroup* parent);
protected:
	bool mBoundsDirty = true; //对象包围盒是否需要重新计算
	std::shared_ptr<CGRenderStateSet> mRenderStateSet; // 渲染状态集合的智能指针
public:
	bool boundDirty() const { return mBoundsDirty; } //对象包围盒是否需要重新计算
	void dirtyBound(); //设置包围盒变化需要重新计算
	//计算到世界坐标系矩阵（到场景根节点）

	virtual glm::mat4 worldMatrix();
	CGRenderStateSet* gocRenderStateSet() {
		if (!mRenderStateSet)
			mRenderStateSet = std::make_shared<CGRenderStateSet>();
		return mRenderStateSet.get();
	}
	CGRenderStateSet* getRenderStateSet() { return mRenderStateSet.get(); }
	const CGRenderStateSet* getRenderStateSet() const {
		return mRenderStateSet.get();
	}

public:
	virtual void update() { if (mUpdateCallback) mUpdateCallback->run(this, userData()); }

};