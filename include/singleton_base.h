#ifndef __SINGLETON_BASE_H__
#define __SINGLETON_BASE_H__


class CSingletonManager;


class CSingletonBase
{
     private :
	friend class CSingletonManager;
	virtual void _kill() = 0;

     protected :
	virtual ~CSingletonBase(){}
};

#endif //__SINGLETON_BASE_H__
