#ifndef __LOCAL_TIMER_H__
#define __LOCAL_TIMER_H__


class CLocalTimer
{
     private :
	float m_StartTime;

     public :
	CLocalTimer();
	~CLocalTimer();

	void init();
	float time() const;
};

#endif //__LOCAL_TIMER_H__
