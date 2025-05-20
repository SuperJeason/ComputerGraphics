#include "CGObject.h"
#include "CGTransform.h"
//�ڵ�任�Զ�����������Ը��ݸ�����Ҫ�������
class RobotBodyTransformParam : public CGObject
{
public:
	void setRotateDegree(float degree) { mRotateDegree = degree; }
	float rotateDegree() const { return mRotateDegree; }
protected:
	float mRotateDegree = 1.0f;
};
//��ת���»ص�ʾ��
class RobotBodyRotate : public CGCallback
{
public:
	virtual bool run(CGObject* object, void* data) override
	{
		if (!mEnabled || !object)
			return false;
		CGTransform* body = dynamic_cast<CGTransform*>(object); //Ҫ��任�ڵ�
		if (body) {
			RobotBodyTransformParam* d = nullptr;
			if (data) { //�Ƿ����Զ������
				d = dynamic_cast<RobotBodyTransformParam*>((CGObject*)data);
			}
			if (d) {
				body->rotate(d->rotateDegree(), 0.0f, 1.0f, 0.0f);
			}
			else { //���û�����Զ���������Ĭ�ϲ�������
				body->rotate(1.0f, 0.0f, 1.0f, 0.0f);
			}
			return true;
		}
		return false;
	}
};