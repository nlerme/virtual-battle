#include <SDL/SDL.h>
#include "config.h"
#include "window.h"
#include "utils.h"
#include "window_factory.h"
#include "application_base.h"


IApplicationBase::IApplicationBase() : m_Window(NULL), 
				       m_Quit(false), 
				       m_Pause(false), 
				       m_FPS(0){}

IApplicationBase::~IApplicationBase()
{
	delete m_Window, m_Window=NULL;
	SDL_Quit();
}

void IApplicationBase::_events()
{
	SDL_Event event;

	while( SDL_PollEvent(&event) )
	{
		if( event.type == SDL_QUIT )
			quit();
		else if( event.type == SDL_KEYDOWN )
			key_down(event.key.keysym.sym);
		else if( event.type == SDL_KEYUP )
			key_up(event.key.keysym.sym);
		else if( event.type == SDL_MOUSEMOTION )
		{
			SDL_MouseMotionEvent * mouse_motion_event = (SDL_MouseMotionEvent*)&event;

			if( m_Window->get_window_type() == WT_OPENGL )
				mouse_motion(mouse_motion_event->x, CConfig::WindowHeight-mouse_motion_event->y);
			else
				mouse_motion(mouse_motion_event->x, mouse_motion_event->y);
		}
		else if( event.type == SDL_MOUSEBUTTONDOWN )
		{
			SDL_MouseButtonEvent * mouse_button_event = (SDL_MouseButtonEvent*)&event;
			EMouseButton button;

			switch( mouse_button_event->button )
			{
				case SDL_BUTTON_LEFT :
					button = MOUSE_BUTTON_LEFT;
					break;

				case SDL_BUTTON_RIGHT :
					button = MOUSE_BUTTON_RIGHT;
					break;

				case SDL_BUTTON_MIDDLE :
					button = MOUSE_BUTTON_MIDDLE;
					break;

				default :
					button = MOUSE_BUTTON_NULL;
					break;
			}

			if( button != MOUSE_BUTTON_NULL )
			{
				if( m_Window->get_window_type() == WT_OPENGL )
					mouse_button_down(mouse_button_event->x, CConfig::WindowHeight-mouse_button_event->y, button);
				else
					mouse_button_down(mouse_button_event->x, mouse_button_event->y, button);
			}
		}
		else if( event.type == SDL_MOUSEBUTTONUP )
		{
			SDL_MouseButtonEvent * mouse_button_event = (SDL_MouseButtonEvent*)&event;
			EMouseButton button;

			switch( mouse_button_event->button )
			{
				case SDL_BUTTON_LEFT :
					button = MOUSE_BUTTON_LEFT;
					break;

				case SDL_BUTTON_RIGHT :
					button = MOUSE_BUTTON_RIGHT;
					break;

				case SDL_BUTTON_MIDDLE :
					button = MOUSE_BUTTON_MIDDLE;
					break;

				default :
					button = MOUSE_BUTTON_NULL;
					break;
			}

			if( button != MOUSE_BUTTON_NULL )
			{
				if( m_Window->get_window_type() == WT_OPENGL )
					mouse_button_up(mouse_button_event->x, CConfig::WindowHeight-mouse_button_event->y, button);
				else
					mouse_button_up(mouse_button_event->x, mouse_button_event->y, button);
			}
		}
	}
}

void IApplicationBase::pause()
{
	m_Pause = !m_Pause;
}

const bool IApplicationBase::is_paused() const
{
	return m_Pause;
}

IWindow* IApplicationBase::window() const
{
	return m_Window;
}

void IApplicationBase::quit()
{
	m_Quit = true;
}

void IApplicationBase::run( int argc, char **argv )
{
	// We create the window
	m_Window = CWindowFactory::create(CConfig::WindowType, CConfig::WindowTitle, CConfig::WindowWidth, CConfig::WindowHeight);

	// We allocate some objects
	begin();

	// We init timers
	m_TimerFPS.init();
	m_TimerVSync.init();

	while( !m_Quit )
	{
		// We manage events
		_events();

		if( m_TimerVSync.time() >= CConfig::VSync )
		{
			++m_FPS;
			m_TimerVSync.init();

			// We do rendering
			render();
			m_Window->swap_buffers();

			// We update window title
			if( m_TimerFPS.time() >= 1.0f )
			{
				m_Window->set_title(CConfig::WindowTitle + " - " + to_string(m_FPS) + " fps");
				m_TimerFPS.init();
				m_FPS = 0;
			}

			if( !m_Pause )
			{
				// We do updating
				update();
			}
		}
	}

	// We deallocate some objects
	end();
}
