#pragma once
#include "CGNode.h"
#include <vector>

class CGGroup : public CGNode
{
	DECLARE_SERIAL(CGGroup)
public:
	CGGroup();
	//序列化
	virtual void Serialize(CArchive& ar) override;
	//绘制对象（在派生类中重写）
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual CGGroup* asGroup() { return this; }
	virtual const CGGroup* asGroup() const { return this; }
	typedef std::vector< std::shared_ptr<CGNode>> NodeList;
	virtual bool AddChild(std::shared_ptr<CGNode> child);
	virtual bool InsertChild(unsigned int index, std::shared_ptr<CGNode>& child);
	virtual unsigned int GetNumChildren() const;
	CGNode* GetChild(unsigned int i);
	const CGNode* GetChild(unsigned int i) const;
	bool ContainsNode(const CGNode* node) const;
	unsigned int GetChildIndex(const CGNode* node) const;
protected:
	virtual ~CGGroup();
	NodeList mChildren;
};