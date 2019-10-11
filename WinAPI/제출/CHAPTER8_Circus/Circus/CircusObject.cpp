#include "CircusObject.h"

int CircusObject::getX()
{
	return m_ix;
}

int CircusObject::getY()
{
	return m_iy;
}

bool CircusObject::isCollision(CircusObject* object)
{
	RECT rect;
	for (auto iter = m_RectList.begin(); iter != m_RectList.end(); ++iter)
	{
		for (auto iter2 = object->m_RectList.begin(); iter2 != object->m_RectList.end(); ++iter2)
		{
			if (IntersectRect(&rect, &(*iter), &(*iter2)))
			{
				return true;
			}
		}
	}
	return false;
}

CircusObject::CircusObject()
{
	m_ix = m_iy = m_iCameraX = 0;
	m_iWidth = m_iHeight = 0;

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
}

CircusObject::~CircusObject()
{
}
