#include <SDL/SDL.h>
#include "global_timer.h"


CGlobalTimer::CGlobalTimer() : m_Decal(0.0f){}

CGlobalTimer::~CGlobalTimer(){}

void CGlobalTimer::init()
{
	m_StartTime  = SDL_GetTicks();
	m_LastTime   = m_StartTime;
	m_StartDecal = 0.0f;
	m_Decal      = 0.0f;
}

void CGlobalTimer::pause()
{
	if( m_StartDecal )
	{
	        m_Decal     += static_cast<float>(SDL_GetTicks()) - m_StartDecal;
        	m_StartDecal = 0.0f;
	}
	else
		m_StartDecal = static_cast<float>(SDL_GetTicks());
}

float CGlobalTimer::time()
{
	float current_time(0.0f);

	if( !m_StartDecal )
	{
		m_LastTime   = static_cast<float>(SDL_GetTicks());
        	current_time = static_cast<float>(m_LastTime - m_StartTime) - m_Decal;
        }
        else
        	current_time = static_cast<float>(m_LastTime - m_StartTime) - m_Decal;

	return (current_time / 1000.0f);
}
