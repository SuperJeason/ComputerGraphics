#include "CGObject.h"
#include "CGTransform.h"
#include "iostream"
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

class RobotRun : public CGCallback
{
public:
    virtual bool run(CGObject* object, void* data) override
    {
        if (!mEnabled || !object)
        {
            std::cerr << "�ص�δ���û������Ч" << std::endl;
            return false;
        }
        CGTransform* robot = dynamic_cast<CGTransform*>(object);
        if (!robot)
        {
            std::cerr << "������ CGTransform ����" << std::endl;
            return false;
        }

        // ��ȡ�ֱۺ��Ȳ��ӽڵ㣨���� 5-8��
        CGTransform* leftArmAnchor = dynamic_cast<CGTransform*>(robot->GetChild(5));
        CGTransform* rightArmAnchor = dynamic_cast<CGTransform*>(robot->GetChild(6));
        CGTransform* leftLegAnchor = dynamic_cast<CGTransform*>(robot->GetChild(7));
        CGTransform* rightLegAnchor = dynamic_cast<CGTransform*>(robot->GetChild(8));
        if (!leftArmAnchor || !rightArmAnchor || !leftLegAnchor || !rightLegAnchor)
        {
            std::cerr << "δ�ҵ��ֱۻ��Ȳ��ӽڵ㣨�ֱ����� 5-6���Ȳ����� 7-8��" << std::endl;
            return false;
        }

        RobotBodyTransformParam* param = dynamic_cast<RobotBodyTransformParam*>((CGObject*)data);
        float armAmplitude = param ? param->rotateDegree() : 30.0f; // Ĭ���ֱ۰ڶ����ȣ�30��
        float legAmplitude = armAmplitude * 0.66f; // �Ȳ����ȣ��ֱ۵�2/3
        float legLift = 5.0f; // �Ȳ�΢С̧�ߣ�5��λ
        static float time = 0.0f;
        time += 0.1f; // ͳһƵ�ʣ��ֱۺ��Ȳ�һ��

        // �����Ȳ���ʼƽ�ƣ����״����У�
        static bool firstRun = true;
        static glm::vec3 leftLegInitial, rightLegInitial;
        if (firstRun)
        {
            glm::mat4 leftLegMatrix = leftLegAnchor->localMatrix();
            glm::mat4 rightLegMatrix = rightLegAnchor->localMatrix();
            glm::vec3 scale, skew;
            glm::quat rotation;
            glm::vec4 origin;
            glm::decompose(leftLegMatrix, scale, rotation, leftLegInitial, skew, origin);
            glm::decompose(rightLegMatrix, scale, rotation, rightLegInitial, skew, origin);
            firstRun = false;
            std::cout << "���ȳ�ʼƽ�ƣ�" << glm::to_string(leftLegInitial) << std::endl;
            std::cout << "���ȳ�ʼƽ�ƣ�" << glm::to_string(rightLegInitial) << std::endl;
        }

        // �����ұ�
        {
            glm::mat4 originalMatrix = rightArmAnchor->localMatrix();
            glm::vec3 translation, scale, skew;
            glm::quat rotation;
            glm::vec4 original;
            glm::decompose(originalMatrix, scale, rotation, translation, skew, original);

            rightArmAnchor->setLocalMatrix(glm::mat4(1.0f));
            rightArmAnchor->translate(translation.x, translation.y, translation.z);
            rightArmAnchor->scale(scale.x, scale.y, scale.z);

            float waveAngle = armAmplitude * sin(time);
            rightArmAnchor->rotate(waveAngle, 1.0f, 0.0f, 0.0f);

            std::cout << "�ұ���ת�Ƕȣ�" << waveAngle << " degree, matrix��" << glm::to_string(rightArmAnchor->localMatrix()) << std::endl;
        }

        // ������ۣ�����ڶ���
        {
            glm::mat4 originalMatrix = leftArmAnchor->localMatrix();
            glm::vec3 translation, scale, skew;
            glm::quat rotation;
            glm::vec4 original;
            glm::decompose(originalMatrix, scale, rotation, translation, skew, original);

            leftArmAnchor->setLocalMatrix(glm::mat4(1.0f));
            leftArmAnchor->translate(translation.x, translation.y, translation.z);
            leftArmAnchor->scale(scale.x, scale.y, scale.z);

            float waveAngle = -armAmplitude * sin(time);
            leftArmAnchor->rotate(waveAngle, 1.0f, 0.0f, 0.0f);

            std::cout << "�����ת�Ƕȣ�" << waveAngle << " degree, matrix��" << glm::to_string(leftArmAnchor->localMatrix()) << std::endl;
        }

        // ��������
        {
            glm::mat4 originalMatrix = rightLegAnchor->localMatrix();
            glm::vec3 translation, scale, skew;
            glm::quat rotation;
            glm::vec4 original;
            glm::decompose(originalMatrix, scale, rotation, translation, skew, original);

            rightLegAnchor->setLocalMatrix(glm::mat4(1.0f));
            rightLegAnchor->translate(rightLegInitial.x, rightLegInitial.y, rightLegInitial.z);
            rightLegAnchor->scale(scale.x, scale.y, scale.z);

            float waveAngle = legAmplitude * sin(time);
            float lift = legLift * std::max(0.0f, sin(time)); // ����ǰ����ʱ̧��
            rightLegAnchor->rotate(waveAngle, 1.0f, 0.0f, 0.0f);
            rightLegAnchor->translate(0.0f, lift, 0.0f);

            // ���������ӽڵ㣨���� 0��ϥ�ǻ����ȣ�
            CGTransform* rightLegChild = dynamic_cast<CGTransform*>(rightLegAnchor->GetChild(0));
            if (rightLegChild)
            {
                glm::mat4 childMatrix = rightLegChild->localMatrix();
                glm::vec3 childTranslation, childScale, childSkew;
                glm::quat childRotation;
                glm::vec4 childOriginal;
                glm::decompose(childMatrix, childScale, childRotation, childTranslation, childSkew, childOriginal);
                rightLegChild->setLocalMatrix(glm::mat4(1.0f));
                rightLegChild->translate(childTranslation.x, childTranslation.y, childTranslation.z);
                rightLegChild->scale(childScale.x, childScale.y, childScale.z);
                rightLegChild->rotate(waveAngle * 0.5f, 1.0f, 0.0f, 0.0f);
                std::cout << "�����ӽڵ�ƽ�ƣ�" << glm::to_string(childTranslation) << ", matrix��" << glm::to_string(rightLegChild->localMatrix()) << std::endl;
            }
            else
            {
                std::cerr << "δ�ҵ������ӽڵ㣨���� 0��" << std::endl;
            }

            std::cout << "������ת�Ƕȣ�" << waveAngle << " degree, lift��" << lift << " units, translation��" << glm::to_string(rightLegInitial + glm::vec3(0.0f, lift, 0.0f)) << std::endl;
        }

        // �������ȣ���λ�� ��/2������������
        {
            glm::mat4 originalMatrix = leftLegAnchor->localMatrix();
            glm::vec3 translation, scale, skew;
            glm::quat rotation;
            glm::vec4 original;
            glm::decompose(originalMatrix, scale, rotation, translation, skew, original);

            leftLegAnchor->setLocalMatrix(glm::mat4(1.0f));
            leftLegAnchor->translate(leftLegInitial.x, leftLegInitial.y, leftLegInitial.z);
            leftLegAnchor->scale(scale.x, scale.y, scale.z);

            float waveAngle = legAmplitude * sin(time + 1.5708f); // ��λ�� ��/2 (cos(time))
            float lift = legLift * std::max(0.0f, sin(time + 1.5708f));
            leftLegAnchor->rotate(waveAngle, 1.0f, 0.0f, 0.0f);
            leftLegAnchor->translate(0.0f, lift, 0.0f);

            // ���������ӽڵ㣨���� 0��ϥ�ǻ����ȣ�
            CGTransform* leftLegChild = dynamic_cast<CGTransform*>(leftLegAnchor->GetChild(0));
            if (leftLegChild)
            {
                glm::mat4 childMatrix = leftLegChild->localMatrix();
                glm::vec3 childTranslation, childScale, childSkew;
                glm::quat childRotation;
                glm::vec4 childOriginal;
                glm::decompose(childMatrix, childScale, childRotation, childTranslation, childSkew, childOriginal);
                leftLegChild->setLocalMatrix(glm::mat4(1.0f));
                leftLegChild->translate(childTranslation.x, childTranslation.y, childTranslation.z);
                leftLegChild->scale(childScale.x, childScale.y, childScale.z);
                leftLegChild->rotate(waveAngle * 0.5f, 1.0f, 0.0f, 0.0f);
                std::cout << "�����ӽڵ�ƽ�ƣ�" << glm::to_string(childTranslation) << ", matrix��" << glm::to_string(leftLegChild->localMatrix()) << std::endl;
            }
            else
            {
                std::cerr << "δ�ҵ������ӽڵ㣨���� 0��" << std::endl;
            }

            std::cout << "������ת�Ƕȣ�" << waveAngle << " degree, lift��" << lift << " units, translation��" << glm::to_string(leftLegInitial + glm::vec3(0.0f, lift, 0.0f)) << std::endl;
        }

        // ���ԣ���������λ��
        std::cout << "�����˾���" << glm::to_string(robot->localMatrix()) << std::endl;

        return true;
    }
};