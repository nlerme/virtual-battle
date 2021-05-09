#include <SDL/SDL.h>
#include "local_timer.h"


CLocalTimer::CLocalTimer() : m_StartTime(0.0f){}

CLocalTimer::~CLocalTimer(){}

void CLocalTimer::init()
{
	m_StartTime = SDL_GetTicks();
}

float CLocalTimer::time() const
{
	return static_cast<float>(SDL_GetTicks() - m_StartTime) / 1000.0f;
}
