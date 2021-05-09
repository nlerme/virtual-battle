#ifndef __COLOR_H__
#define __COLOR_H__

#include <algorithm>
#include <iostream>
#include "utils.h"


class color3f
{
     private :
	typedef float Type;

     public :
	union
	{
		// Color in [0,1]^3
		Type data[3];
		struct{ Type r, g, b; };
	};

	color3f( const Type value=Type() ){ std::fill(data, data+4, value); }
	color3f( const Type _r, const Type _g, const Type _b ) : r(_r), g(_g), b(_b){}
	color3f( const Type _data[3] ){ data[0] = _data[0]; data[1] = _data[1]; data[2] = _data[2]; }
	Type to_gray() const{ return 0.3f*r+0.59f*g+0.11f*b; }
	friend std::ostream & operator << ( std::ostream & out, const color3f & c ){ return (out << "color3f[" << c.r << ", " << c.g << ", " << c.b << "]"); }

	static color3f random(){ return color3f(uniform<Type>(), uniform<Type>(), uniform<Type>()); }

	// Some predefined colors
	static color3f red;
	static color3f green;
	static color3f blue;
	static color3f yellow;
	static color3f orange;
	static color3f purple;
	static color3f cyan;
	static color3f black;
	static color3f gray;
	static color3f light_gray;
	static color3f dark_gray;
	static color3f white;
};

class color4f
{
     private :
	typedef float Type;

     public :
	union
	{
		// Color in [0,1]^3 + alpha channel
		Type data[4];
		struct{ Type r, g, b, a; };
	};

	color4f( const color3f & c, const Type _a ) : r(c.r), g(c.g), b(c.b), a(_a){}
	color4f( const Type value=Type() ){ std::fill(data, data+4, value); }
	color4f( const Type _r, const Type _g, const Type _b, const Type _a ) : r(_r), g(_g), b(_b), a(_a){}
	color4f( const Type _data[4] ){ data[0] = _data[0]; data[1] = _data[1]; data[2] = _data[2]; data[3] = _data[3]; }
	Type to_gray() const{ return 0.3f*r+0.59f*g+0.11f*b; }
	friend std::ostream & operator << ( std::ostream & out, const color4f & c ){ return (out << "color4f[" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << "]"); }

	static color4f random(){ return color4f(uniform<Type>(), uniform<Type>(), uniform<Type>(), uniform<Type>()); }
};

#endif //__COLOR_H__
