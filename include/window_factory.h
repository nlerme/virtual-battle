#ifndef __WINDOW_FACTORY_H__
#define __WINDOW_FACTORY_H__

#include "window.h"
#include "software_window.h"
#include "gl_window.h"


struct CWindowFactory
{
	static IWindow* create( const EWindowType wt, const std::string & title, const int width, const int height )
	{
		if( wt == WT_OPENGL )
			return new CGLWindow(title, width, height);
		else if( wt == WT_SOFTWARE )
			return new CSoftwareWindow(title, width, height);
		else
			return NULL;
	}
};

#endif //__WINDOW_FACTORY_H__
