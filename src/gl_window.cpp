#include <GL/glew.h>
#include <stdexcept>
#include "exceptions.h"
#include "gl_window.h"


CGLWindow::CGLWindow( const std::string & title, const int width, const int height, const int flags, const bool centered ) : IWindow(title, width, height, flags, centered)
{
	Assert(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) >= 0);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,      1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,       16);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE,      0);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,    0);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,  0);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,   0);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,  0);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,          5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,        5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,         5);

	if( centered )
		putenv((char*)"SDL_VIDEO_CENTERED=1");

	Assert((m_Screen = SDL_SetVideoMode(width, height, SDL_GetVideoInfo()->vfmt->BitsPerPixel, flags)) != 0);

	glewInit();
	set_title(title);
	resize(width, height);
}

CGLWindow::~CGLWindow(){}

void CGLWindow::swap_buffers() const
{
	SDL_GL_SwapBuffers();
}

void CGLWindow::resize( const int width, const int height )
{
	Assert(height != 0);

	m_Width  = width;
	m_Height = height;

	glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, static_cast<GLdouble>(width), 0.0, static_cast<GLdouble>(height), -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

void CGLWindow::clear( const color4f & c )
{
	glClearColor(c.r, c.g, c.b, c.a);
}

void CGLWindow::set_pixel( const int x, const int y, const color4f & c )
{
	glBegin(GL_POINTS);
		glColor4f(c.r, c.g, c.b, c.a);
		glVertex2f(x, y);
	glEnd();
}

color4f CGLWindow::get_pixel( const int x, const int y ) const
{
	throw std::logic_error("not implemented yet");
}

void CGLWindow::draw_rectangle( const int x, const int y, const int width, const int height, const color4f & c )
{
	glBegin(GL_LINE_LOOP);
	  glColor4f(c.r, c.g, c.b, c.a);
	  glVertex2f(x, y);
	  glVertex2f(x+width, y);
	  glVertex2f(x+width, y+height);
	  glVertex2f(x, y+height);
	glEnd();
}

void CGLWindow::fill_rectangle( const int x, const int y, const int width, const int height, const color4f & c )
{
	glBegin(GL_QUADS);
	  glColor4f(c.r, c.g, c.b, c.a);
	  glVertex2f(x, y);
	  glVertex2f(x+width, y);
	  glVertex2f(x+width, y+height);
	  glVertex2f(x, y+height);
	glEnd();
}

void CGLWindow::draw_circle( const int xc, const int yc, const int radius, const color4f & c )
{
	glBegin(GL_LINE_LOOP);
	  glColor4f(c.r, c.g, c.b, c.a);
	  for( int k=0; k<360; k+=10 )
		glVertex2f(xc+cosf(degrees2radians<float>(k))*radius, yc+sinf(degrees2radians<float>(k))*radius);
	glEnd();
}

void CGLWindow::fill_circle( const int xc, const int yc, const int radius, const color4f & c )
{
	glBegin(GL_TRIANGLE_FAN);
	  glColor4f(c.r, c.g, c.b, c.a);
	  glVertex2f(xc, yc);
	  for( int k=0; k<=360; k++ )
		glVertex2f(xc+cosf(degrees2radians<float>(k))*radius, yc+sinf(degrees2radians<float>(k))*radius);
	glEnd();
}

void CGLWindow::draw_line( const int x1, const int y1, const int x2, const int y2, const color4f & c )
{
	glBegin(GL_LINES);
	  glColor4f(c.r, c.g, c.b, c.a);
	  glVertex2f(x1, y1);
	  glVertex2f(x2, y2);
	glEnd();
}

EWindowType CGLWindow::get_window_type() const
{
	return WT_OPENGL;
}
