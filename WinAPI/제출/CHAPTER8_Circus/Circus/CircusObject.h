#pragma once
#include "GameDefine.h"

class CircusObject
{

protected:
	int m_ix, m_iy, m_iCameraX; // �׷��� ��ġ(�»���� �ƴ� �߽���ġ)
	int m_iWidth, m_iHeight;
	const float m_iMultiple = 2.0f; // ���� �̹����� �� �� ũ��� �׸���

	std::vector<RECT> m_RectList; // �浹�� üũ�� RECT ����

	//Ÿ��üũ��
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
public:
	// object�� �浹�ϴ��� �˻�, �浹�ϸ� true �ƴϸ� false
	bool isCollision(CircusObject* object);
	// ������Ʈ�� x, y �ʱ� ��ġ�� ���Ѵ�.
	virtual void init(int x, int y) = 0;
	// camera�� X��ġ�� ���� ȭ����� ��ġ�� �ٽ� ���Ѵ�.
	virtual void update(int cameraX = 0) = 0;
	// ��Ʈ�� �Ŵ����� Memory DC�� �׸���.
	virtual void draw() = 0;

	CircusObject();
	virtual ~CircusObject();
};
