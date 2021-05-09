#include "exceptions.h"
#include "utils.h"
#include "software_window.h"


CSoftwareWindow::CSoftwareWindow( const std::string & title, const int width, const int height, const int flags, const bool centered ) : IWindow(title, width, height, flags, centered)
{
	Assert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) >= 0);

	if( centered )
		putenv((char*)"SDL_VIDEO_CENTERED=1");

	Assert((m_Screen = SDL_SetVideoMode(width, height, SDL_GetVideoInfo()->vfmt->BitsPerPixel, flags)) != 0);

	set_title(title);
	resize(width, height);
}

CSoftwareWindow::~CSoftwareWindow(){}

void CSoftwareWindow::swap_buffers() const
{
	SDL_Flip(m_Screen);
}

void CSoftwareWindow::resize( const int width, const int height ){}

void CSoftwareWindow::clear( const color4f & c )
{
	SDL_FillRect(m_Screen, NULL, SDL_MapRGB(m_Screen->format, Uint8(c.r*255.0f), Uint8(c.g*255.0f), Uint8(c.b*255.0f)));
}

void CSoftwareWindow::set_pixel( const int x, const int y, const color4f & c )
{
	Uint32 p(SDL_MapRGB(m_Screen->format, Uint8(c.r*255.0f), Uint8(c.g*255.0f), Uint8(c.b*255.0f)));
	*((Uint32*)(m_Screen->pixels) + y * m_Screen->w + x) = p;
}

color4f CSoftwareWindow::get_pixel( const int x, const int y ) const
{
	Uint8 red, green, blue;
	Uint32 p = *((Uint32*)(m_Screen->pixels) + y * m_Screen->w + x);
	SDL_GetRGB(p, m_Screen->format, &red, &green, &blue);
	return color4f(red/255.0f, green/255.0f, blue/255.0f, 1.0f);
}

void CSoftwareWindow::draw_rectangle( const int x, const int y, const int width, const int height, const color4f & c )
{
	draw_line(x, y, x+width, y, c);
	draw_line(x+width, y, x+width, y+height, c);
	draw_line(x+width, y+height, x, y+height, c);
	draw_line(x, y+height, x, y, c);
}

void CSoftwareWindow::fill_rectangle( const int x, const int y, const int width, const int height, const color4f & c )
{
	for( int y=0; y<height; y++ )
		draw_line(x, y, x+width, y, c);
}

void CSoftwareWindow::draw_circle( const int xc, const int yc, const int radius, const color4f & c )
{
	int xf(sqrtf(2.0f)/2.0f*radius);
	register int x, y;


	for( x=0; x<=xf; x++ )
	{
		y = int(sqrtf(sq(radius) - sq(x)));
		set_pixel(xc+x, yc-y, c);
		set_pixel(xc+x, yc+y, c);
		set_pixel(xc-x, yc+y, c);
		set_pixel(xc-x, yc-y, c);
		set_pixel(xc+y, yc-x, c);
		set_pixel(xc+y, yc+x, c);
		set_pixel(xc-y, yc+x, c);
		set_pixel(xc-y, yc-x, c);
	}
}

void CSoftwareWindow::fill_circle( const int xc, const int yc, const int radius, const color4f & c ){}

void CSoftwareWindow::draw_line( const int _x1, const int _y1, const int _x2, const int _y2, const color4f & c )
{
	register int x1(_x1), x2(_x2), y1(_y1), y2(_y2), x, y;
	float pente, yflt, xflt;


	if( x1 == x2 )
	{
		if( y1>y2 )
		{
			for( y=y1; y>y2; y-- )
				set_pixel(x1, y, c);
		}
		else
		{
			for( y=y1; y<y2; y++ )
				set_pixel(x1, y, c);
		}
	}
	else
	{
		pente = float(y2-y1) / (x2-x1);

		if( fabsf(pente) <= 1.0f )
		{
			if( x1>x2 )
			{
				yflt = y2 + 0.5f;
				swap(x1, x2);
				swap(y1, y2);
			}
			else
				yflt = y1 + 0.5f;

			for( x=x1; x<=x2; x++ )
			{
				y = int(yflt);
				set_pixel(x, y, c);
				yflt += pente;
			}
		}
		else
		{
			pente = 1.0f / pente;

			if( y1>y2 )
			{
				xflt = x2 + 0.5f;
				swap(x1, x2);
				swap(y1, y2);
			}
			else
				xflt = x1 + 0.5f;

			for( y=y1; y<=y2; y++ )
			{
				x = int(xflt);
				set_pixel(x, y, c);
				xflt += pente;
			}
		}
	}
}

EWindowType CSoftwareWindow::get_window_type() const
{
	return WT_SOFTWARE;
}
