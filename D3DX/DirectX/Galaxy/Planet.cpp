#include "Planet.h"

void Planet::setPosition(float a_x, float a_y, float a_z)
{
	m_vecTranslation.x = a_x;
	m_vecTranslation.y = a_y;
	m_vecTranslation.z = a_z;
	D3DXMatrixTranslation(&m_matTranslation, a_x, a_y, a_z);
}

void Planet::setRotateAxis(float a_x, float a_y, float a_z)
{
	m_vecRotateAxis.x = a_x;
	m_vecRotateAxis.y = a_y;
	m_vecRotateAxis.z = a_z;	
}

/*
void Planet::setRevolveAxis(float a_x, float a_y, float a_z)
{
	m_vecRevolveAxis.x = a_x;
	m_vecRevolveAxis.y = a_y;
	m_vecRevolveAxis.z = a_z;
}*/

void Planet::rotate(float angle)
{
	D3DXMatrixRotationAxis(&m_matRotate, &m_vecRotateAxis, angle);
}

void Planet::revolve(float angle)
{
	if (m_ParentPlanet != nullptr)
	{
		D3DXVec3Cross(&m_vecRevolveAxis, &m_ParentPlanet->m_vecTranslation, &m_vecTranslation);
	}
	D3DXMatrixRotationAxis(&m_matRevolve, &m_vecRevolveAxis, angle);
}

D3DXMATRIXA16* Planet::getWorldMatrix(D3DXMATRIXA16* matrix)
{
	*matrix = m_matRotate * m_matTranslation * m_matRevolve;

	Planet* parent = m_ParentPlanet;
	while (parent != nullptr)
	{
		*matrix *= parent->m_matTranslation * parent->m_matRevolve;
		parent = parent->m_ParentPlanet;
	}

	return matrix;
}

void Planet::addChildPlanet(Planet* child)
{
	//m_childPlanet.push_back(child);
	child->m_ParentPlanet = this;
}

Planet::Planet()
{
	m_vecTranslation = {0.0f, 0.0f, 0.0f};
	D3DXMatrixIdentity(&m_matTranslation); 
	
	m_vecRotateAxis = { 0.0f, 1.0f, 0.0f };
	D3DXMatrixIdentity(&m_matRotate);
	
	m_vecRevolveAxis = { 0.0f, 1.0f, 0.0f };
	D3DXMatrixIdentity(&m_matRevolve);
	
	m_ParentPlanet = nullptr;
}

Planet::~Planet()
{

}
