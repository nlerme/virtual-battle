#ifndef __APPLICATION_BASE_H__
#define __APPLICATION_BASE_H__

#include "local_timer.h"
#include "window.h"


enum EMouseButton
{
	MOUSE_BUTTON_NULL = 0,
	MOUSE_BUTTON_LEFT,
	MOUSE_BUTTON_RIGHT,
	MOUSE_BUTTON_MIDDLE
};

class IApplicationBase
{
     private :
	IWindow *m_Window;
	bool m_Quit, m_Pause;
	CLocalTimer m_TimerFPS, m_TimerVSync;
	int m_FPS;

	void _events();

     protected :
	IApplicationBase();
	virtual ~IApplicationBase();

	virtual void begin() = 0;
	virtual void mouse_motion( const int x, const int y ) = 0;
	virtual void mouse_button_up( const int x, const int y, const EMouseButton & button ) = 0;
	virtual void mouse_button_down( const int x, const int y, const EMouseButton & button ) = 0;
	virtual void key_down( const int key ) = 0;
	virtual void key_up( const int key ) = 0;
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual void end() = 0;

	IWindow* window() const;

	const bool is_paused() const;
	void pause();
	void quit();

     public :
	void run( int argc, char **argv );
};

#endif //__APPLICATION_BASE_H__
