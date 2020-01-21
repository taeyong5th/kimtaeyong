#pragma once
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>

class Planet
{
private:
	//std::vector<Planet*> m_childPlanet;
	Planet* m_ParentPlanet;
		
	D3DXVECTOR3 m_vecTranslation;  // �༺�� ��ġ����
	D3DXMATRIXA16 m_matTranslation; // �༺�� ��ġ���
	D3DXVECTOR3 m_vecRotateAxis; // ������
	D3DXMATRIXA16 m_matRotate; // �������� ���������ϴ� ȸ�����	
	D3DXVECTOR3 m_vecRevolveAxis; // ������
	D3DXMATRIXA16 m_matRevolve; // �������� ���������ϴ� ȸ�����

	//void setRevolveAxis(float a_x, float a_y, float a_z); // ������ ����	

public:

	void setPosition(float a_x, float a_y, float a_z); // ��ġ ����
	void setRotateAxis(float a_x, float a_y, float a_z); // ������ ����	
	void rotate(float angle); // ������������� angle ��ŭ ȸ��
	void revolve(float angle); // ������������� angle ��ŭ ȸ��

	D3DXMATRIXA16* getWorldMatrix(D3DXMATRIXA16* matrix); // ���� ���� ����� ��ȯ
	void addChildPlanet(Planet* child);

	Planet();
	virtual ~Planet();
};