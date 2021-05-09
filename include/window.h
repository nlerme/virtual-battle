#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <string>
#include <SDL/SDL.h>
#include "color.h"
#include "logger.h"


enum EWindowType
{
	WT_SOFTWARE = 0,
	WT_OPENGL   = 1
};

class IWindow : public CScopeLogger
{
     protected :
	SDL_Surface *m_Screen;
	int m_Height, m_Width;
	int m_Flags;

     public :
	IWindow( const std::string & title, const int width, const int height, const int flags, const bool centered );
	virtual ~IWindow();

	void set_cursor_position( const int x, const int y );
	void toggle_fullscreen() const;
	const int & height() const;
	const int & width() const;
	const std::string get_title() const;
	const bool is_inside( const int x, const int y ) const;
	void set_title( const std::string & title );
	void center() const;

	virtual void swap_buffers() const = 0;
	virtual void resize( const int width, const int height ) = 0;
	virtual void clear( const color4f & c ) = 0;
	virtual void set_pixel( const int x, const int y, const color4f & c ) = 0;
	virtual color4f get_pixel( const int x, const int y ) const = 0;
	virtual void draw_rectangle( const int x, const int y, const int width, const int height, const color4f & c ) = 0;
	virtual void fill_rectangle( const int x, const int y, const int width, const int height, const color4f & c ) = 0;
	virtual void draw_circle( const int xc, const int yc, const int radius, const color4f & c ) = 0;
	virtual void fill_circle( const int xc, const int yc, const int radius, const color4f & c ) = 0;
	virtual void draw_line( const int x1, const int y1, const int x2, const int y2, const color4f & c ) = 0;
	virtual EWindowType get_window_type() const = 0;
};

#endif //__WINDOW_H__
