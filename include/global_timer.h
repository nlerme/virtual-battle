#ifndef __GLOBAL_TIMER_H__
#define __GLOBAL_TIMER_H__

#include "singleton.h"


class CGlobalTimer : public CSingleton<CGlobalTimer>
{
     friend class CSingleton<CGlobalTimer>;

     private :
	float m_StartTime, m_Decal, m_StartDecal, m_LastTime;
	CGlobalTimer();
	~CGlobalTimer();

     public :
	void init();
	void pause();
	float time();
};

#endif //__GLOBAL_TIMER_H__
