#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <cstdio>
#include "singleton_base.h"
#include "singleton_manager.h"


template <typename T> class CSingleton : public CSingletonBase
{
     private :
	static T * m_Instance;

	void _kill()
	{
		delete m_Instance;
		m_Instance = NULL;
	}

     protected :
	CSingleton(){}
	virtual ~CSingleton(){}

     public :
	static T * instance()
	{
		if( !m_Instance )
		{
			m_Instance = new T;
			CSingletonManager::add(m_Instance);
		}

		return m_Instance;
	}
};

template <typename T> T * CSingleton<T>::m_Instance = NULL;

#endif //__SINGLETON_H__
