#pragma once
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>

class Planet
{
private:
	//std::vector<Planet*> m_childPlanet;
	Planet* m_ParentPlanet;
		
	D3DXVECTOR3 m_vecTranslation;  // 행성의 위치벡터
	D3DXMATRIXA16 m_matTranslation; // 행성의 위치행렬
	D3DXVECTOR3 m_vecRotateAxis; // 자전축
	D3DXMATRIXA16 m_matRotate; // 자전축을 기준으로하는 회전행렬	
	D3DXVECTOR3 m_vecRevolveAxis; // 공전축
	D3DXMATRIXA16 m_matRevolve; // 공전축을 기준으로하는 회전행렬

	//void setRevolveAxis(float a_x, float a_y, float a_z); // 공전축 설정	

public:

	void setPosition(float a_x, float a_y, float a_z); // 위치 설정
	void setRotateAxis(float a_x, float a_y, float a_z); // 자전축 설정	
	void rotate(float angle); // 자전축기준으로 angle 만큼 회전
	void revolve(float angle); // 공전축기준으로 angle 만큼 회전

	D3DXMATRIXA16* getWorldMatrix(D3DXMATRIXA16* matrix); // 최종 계산된 행렬을 반환
	void addChildPlanet(Planet* child);

	Planet();
	virtual ~Planet();
};