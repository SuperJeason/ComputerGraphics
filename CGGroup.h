#pragma once
#include "CGNode.h"
#include <vector>

class CGGroup : public CGNode
{
	DECLARE_SERIAL(CGGroup)
public:
	CGGroup();
	//���л�
	virtual void Serialize(CArchive& ar) override;
	//���ƶ���������������д��
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);
	virtual CGGroup* asGroup() { return this; }
	virtual const CGGroup* asGroup() const { return this; }
	typedef std::vector< std::shared_ptr<CGNode>> NodeList;
	virtual bool AddChild(std::shared_ptr<CGNode> child);
	virtual bool InsertChild(unsigned int index, std::shared_ptr<CGNode>& child);

protected:
	virtual ~CGGroup();
	NodeList mChildren;
};