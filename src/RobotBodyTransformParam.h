#include "CGObject.h"
#include "CGTransform.h"
#include "iostream"
//节点变换自定义参数，可以根据更新需要定义参数
class RobotBodyTransformParam : public CGObject
{
public:
	void setRotateDegree(float degree) { mRotateDegree = degree; }
	float rotateDegree() const { return mRotateDegree; }
protected:
	float mRotateDegree = 1.0f;
};
//旋转更新回调示例
class RobotBodyRotate : public CGCallback
{
public:
	virtual bool run(CGObject* object, void* data) override
	{
		if (!mEnabled || !object)
			return false;
		CGTransform* body = dynamic_cast<CGTransform*>(object); //要求变换节点
		if (body) {
			RobotBodyTransformParam* d = nullptr;
			if (data) { //是否传入自定义参数
				d = dynamic_cast<RobotBodyTransformParam*>((CGObject*)data);
			}
			if (d) {
				body->rotate(d->rotateDegree(), 0.0f, 1.0f, 0.0f);
			}
			else { //如果没传入自定参数，按默认参数进行
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
            std::cerr << "回调未启用或对象无效" << std::endl;
            return false;
        }
        CGTransform* robot = dynamic_cast<CGTransform*>(object);
        if (!robot)
        {
            std::cerr << "对象不是 CGTransform 类型" << std::endl;
            return false;
        }

        // 获取手臂和腿部子节点（索引 5-8）
        CGTransform* leftArmAnchor = dynamic_cast<CGTransform*>(robot->GetChild(5));
        CGTransform* rightArmAnchor = dynamic_cast<CGTransform*>(robot->GetChild(6));
        CGTransform* leftLegAnchor = dynamic_cast<CGTransform*>(robot->GetChild(7));
        CGTransform* rightLegAnchor = dynamic_cast<CGTransform*>(robot->GetChild(8));
        if (!leftArmAnchor || !rightArmAnchor || !leftLegAnchor || !rightLegAnchor)
        {
            std::cerr << "未找到手臂或腿部子节点（手臂索引 5-6，腿部索引 7-8）" << std::endl;
            return false;
        }

        RobotBodyTransformParam* param = dynamic_cast<RobotBodyTransformParam*>((CGObject*)data);
        float armAmplitude = param ? param->rotateDegree() : 30.0f; // 默认手臂摆动幅度：30度
        float legAmplitude = armAmplitude * 0.66f; // 腿部幅度：手臂的2/3
        float legLift = 5.0f; // 腿部微小抬高：5单位
        static float time = 0.0f;
        time += 0.1f; // 统一频率，手臂和腿部一致

        // 缓存腿部初始平移（仅首次运行）
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
            std::cout << "左腿初始平移：" << glm::to_string(leftLegInitial) << std::endl;
            std::cout << "右腿初始平移：" << glm::to_string(rightLegInitial) << std::endl;
        }

        // 处理右臂
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

            std::cout << "右臂旋转角度：" << waveAngle << " degree, matrix：" << glm::to_string(rightArmAnchor->localMatrix()) << std::endl;
        }

        // 处理左臂（反向摆动）
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

            std::cout << "左臂旋转角度：" << waveAngle << " degree, matrix：" << glm::to_string(leftArmAnchor->localMatrix()) << std::endl;
        }

        // 处理右腿
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
            float lift = legLift * std::max(0.0f, sin(time)); // 仅向前迈步时抬高
            rightLegAnchor->rotate(waveAngle, 1.0f, 0.0f, 0.0f);
            rightLegAnchor->translate(0.0f, lift, 0.0f);

            // 处理右腿子节点（索引 0，膝盖或下腿）
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
                std::cout << "右腿子节点平移：" << glm::to_string(childTranslation) << ", matrix：" << glm::to_string(rightLegChild->localMatrix()) << std::endl;
            }
            else
            {
                std::cerr << "未找到右腿子节点（索引 0）" << std::endl;
            }

            std::cout << "右腿旋转角度：" << waveAngle << " degree, lift：" << lift << " units, translation：" << glm::to_string(rightLegInitial + glm::vec3(0.0f, lift, 0.0f)) << std::endl;
        }

        // 处理左腿（相位差 π/2，交替迈步）
        {
            glm::mat4 originalMatrix = leftLegAnchor->localMatrix();
            glm::vec3 translation, scale, skew;
            glm::quat rotation;
            glm::vec4 original;
            glm::decompose(originalMatrix, scale, rotation, translation, skew, original);

            leftLegAnchor->setLocalMatrix(glm::mat4(1.0f));
            leftLegAnchor->translate(leftLegInitial.x, leftLegInitial.y, leftLegInitial.z);
            leftLegAnchor->scale(scale.x, scale.y, scale.z);

            float waveAngle = legAmplitude * sin(time + 1.5708f); // 相位差 π/2 (cos(time))
            float lift = legLift * std::max(0.0f, sin(time + 1.5708f));
            leftLegAnchor->rotate(waveAngle, 1.0f, 0.0f, 0.0f);
            leftLegAnchor->translate(0.0f, lift, 0.0f);

            // 处理左腿子节点（索引 0，膝盖或下腿）
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
                std::cout << "左腿子节点平移：" << glm::to_string(childTranslation) << ", matrix：" << glm::to_string(leftLegChild->localMatrix()) << std::endl;
            }
            else
            {
                std::cerr << "未找到左腿子节点（索引 0）" << std::endl;
            }

            std::cout << "左腿旋转角度：" << waveAngle << " degree, lift：" << lift << " units, translation：" << glm::to_string(leftLegInitial + glm::vec3(0.0f, lift, 0.0f)) << std::endl;
        }

        // 调试：检查机器人位置
        std::cout << "机器人矩阵：" << glm::to_string(robot->localMatrix()) << std::endl;

        return true;
    }
};