#ifndef __GROUND_H__
#define __GROUND_H__

#include <cmath>
#include <vector>
#include "color.h"
#include "window.h"
#include "utils.h"
#include "geometry.h"
#include "singleton.h"
#include "logger.h"


class CGround : public CSingleton<CGround>, CScopeLogger
{
     friend class CSingleton<CGround>;

     private :
	int m_Width, m_Height;
	std::vector<double> m_Data;

	CGround();
	virtual ~CGround();

     public :
	void generate( const int width, const int height );
	double & operator () ( const int x, const int y );
	void render( IWindow *window ) const;
};

#endif //__GROUND_H__
