#ifndef __SINGLETON_MANAGER_H__
#define __SINGLETON_MANAGER_H__

#include <stack>
#include "types.h"


class CSingletonBase;

class CSingletonManager
{
     private :
	std::stack<CSingletonBase*> m_InstancesList;

	CSingletonManager(){}

	~CSingletonManager()
	{
		while( !m_InstancesList.empty() )
		{
			m_InstancesList.top()->_kill();
			m_InstancesList.pop();
		}
	}

     public :
	static void add( CSingletonBase *singleton )
	{
		static CSingletonManager instance;
		instance.m_InstancesList.push(singleton);
	}

	static const uint number_instances()
	{
		static CSingletonManager instance;
		return instance.m_InstancesList.size();
	}
};

#endif //__SINGLETON_MANAGER_H__
