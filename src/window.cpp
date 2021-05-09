#include "logger.h"
#include "utils.h"
#include "window.h"


IWindow::IWindow( const std::string & title, const int width, const int height, const int flags, const bool centered ) : CScopeLogger(__FUNCTION__)
{
	m_Width  = width;
	m_Height = height;
	m_Flags  = flags;
}

IWindow::~IWindow()
{
	if( m_Screen != NULL )
		SDL_FreeSurface(m_Screen);
}

void IWindow::set_cursor_position( const int x, const int y )
{
	SDL_WarpMouse(x, y);
}

void IWindow::toggle_fullscreen() const
{
	SDL_WM_ToggleFullScreen(m_Screen);
}

const int & IWindow::height() const
{
	return m_Height;
}

const int & IWindow::width() const
{
	return m_Width;
}

const std::string IWindow::get_title() const
{
	char *title;
	SDL_WM_GetCaption(&title, &title);
	return std::string(title);
}

void IWindow::set_title( const std::string & title )
{
	SDL_WM_SetCaption(title.c_str(), title.c_str());
}

const bool IWindow::is_inside( const int x, const int y ) const
{
	return (is_between(x, 0, m_Width-1) && is_between(y, 0, m_Height-1));
}
