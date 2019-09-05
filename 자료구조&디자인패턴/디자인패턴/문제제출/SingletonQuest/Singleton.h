#pragma once

template <typename T>
class Singleton
{
private:
	static T* m_ptr;

public:
	static T* GetInstance()
	{
		if (m_ptr == NULL)
		{
			m_ptr = new T;
		}
		return m_ptr;
	}

protected:
	Singleton() 
	{
		//cout << "SINGLETON Constructor" << endl;
		//m_ptr = NULL;
	}

	virtual ~Singleton() 
	{
		if (m_ptr != NULL)
		{
			delete m_ptr;
		}		
		m_ptr = NULL;
	}
};

template <typename T> T* Singleton<T>::m_ptr = NULL;