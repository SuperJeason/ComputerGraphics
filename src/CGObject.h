#ifndef _CGObject_H_INCLUDED
#define _CGObject_H_INCLUDED
#include <afx.h>
#include <memory>
#include <string>
#include "glIncludes.h"
/// CGObject：作为可序列化相关类的基类
/// 使用MFC 的CObject作为基类，用于支持运行时类信息、动态创建、串行化、对象诊断输出
/// 基本功能：不支持运行时类信息或序列化，但包括诊断内存管理。
/// 基本功能加上对运行时类信息的支持。（DECLARE_DYNAMIC）（IMPLEMENT_DYNAMIC放在类的实现文件 (.CPP) 中）
/// 基本功能加上对运行时类信息和动态创建的支持。（DECLARE_DYNCREATE）（IMPLEMENT_DYNCREATE 放在类的实现文件(.CPP) 中）
/// 基本功能加上对运行时类信息、动态创建和序列化的支持。（DECLARE_SERIAL）（IMPLEMENT_SERIAL放在类的实现文件(.CPP) 中）
class CGObject : public CObject
{
	DECLARE_SERIAL(CGObject) //对运行时类信息、动态创建和序列化的支持（IMPLEMENT_SERIAL放在类的实现文件(.CPP) 中）
public:
	CGObject();
	CGObject(const CString& name);
	CGObject(const CGObject& other);
	virtual ~CGObject() = default; //虚析构函数
	//序列化（如果需要序列化/反序列化支持派生类应使用DECLARE_SERIAL/IMPLEMENT_SERIA并重写该虚函数）
	virtual void Serialize(CArchive& ar) override;
	const CString& Name() const { return mName; }
	CString& Name() { return mName; }
protected:
	CString mName; //对象名称，默认由“类名+序号”构成，用于显示
	static unsigned long sID; //对象ID，仅用于辅助对象命名，不能唯一标识

public:
	const CGObject* userData() const { return mUserData.get(); }
	CGObject* userData() { return mUserData.get(); }
	void setUserData(std::shared_ptr<CGObject> user_data) { mUserData = user_data; }
private:
	std::shared_ptr<CGObject> mUserData = nullptr;
};
//回调，根据需要派生类定义回调行为（通过run运行）
class CGCallback : public CGObject
{
public:
	CGCallback() : mEnabled(true) {}
	//派生类中重写实现需要的回调功能
	virtual bool run(CGObject* object, void* data)
	{
		if (!mEnabled)
			return false;
		return true;
	}
	void setEnabled(bool enabled) { mEnabled = enabled; }
	bool isEnabled() const { return mEnabled; }
protected:
	virtual ~CGCallback() = default;
	bool mEnabled;
};
#endif //_CGObject_H_INCLUDED