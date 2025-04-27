#pragma once
#include "CGGeometry.h"
#include <vector> // ��Ҫ���� vector ͷ�ļ����洢�����

// �������޸�Ϊ CGPolylineSegment
class CGPolylineSegment : public CGGeometry
{
	DECLARE_SERIAL(CGPolylineSegment) // ���� MFC ���л�

public:
	// ���캯��
	CGPolylineSegment();
	// ���캯��������һ�����б�
	CGPolylineSegment(const std::vector<glm::dvec3>& points);
	// ���캯��������ָ���Ƿ�պ�
	CGPolylineSegment(const std::vector<glm::dvec3>& points, bool closed);

	// ��������
	virtual ~CGPolylineSegment();

	// ���л�
	virtual void Serialize(CArchive& ar) override;

	// ���ƶ���������������д��
	virtual bool Render(CGRenderContext* pRC, CGCamera* pCamera);

	// ���һ���㵽����
	void AddPoint(const glm::dvec3& point);
	
	// ��ȡ�����ϵ����е�
	const std::vector<glm::dvec3>& GetPoints() const { return mPoints; }

	// ���������Ƿ�պ�
	void SetClosed(bool closed) { mClosed = closed; }

	// ��ȡ�����Ƿ�պ�
	bool IsClosed() const { return mClosed; }

	void Translate(float tx, float ty); //ƽ��

protected:
	std::vector<glm::dvec3> mPoints; // �洢�����ϵĵ�
	bool mClosed; // ��������Ƿ�պϣ���β������
};
