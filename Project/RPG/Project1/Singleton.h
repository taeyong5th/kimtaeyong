#pragma once
#include "Mecro.h"

template <typename T>
class Singleton
{
private:
	static T* m_this;
public:
	static T* getInstance()
	{
		if (m_this == NULL)
		{
			m_this = new T;
		}
		return m_this;
	}

protected:
	Singleton() {};
	virtual ~Singleton() {};
};

template <typename T> T* Singleton<T>::m_this = 0;