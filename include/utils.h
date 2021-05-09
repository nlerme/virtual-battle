#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>
#include <cmath>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "types.h"


template<typename Type> std::string to_string( const Type & value )
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template<typename Type> bool from_string( const std::string & str, Type & dst )
{
	std::istringstream iss(str);
	return iss >> dst != 0;
}

template<typename Type> void swap( Type & a, Type & b )
{
	Type c(a);
	a = b;
	b = c;
}

template<typename Type> Type clamp( const Type value, const Type min, const Type max )
{
	return std::min(max, std::max(value, min));
}

template<typename Type> Type clamp8( const Type value )
{
	return std::min<Type>(255, std::max<Type>(value, 0));
}

template<typename Type> Type sq( const Type value )
{
	return value*value;
}

template<typename Type> Type cubic( const Type value )
{
	return value*value*value;
}

template<typename Type> Type degrees2radians( const Type degrees )
{
	return degrees*(M_PI/180.0);
}

template<typename Type> Type radians2degrees( const Type radians )
{
	return radians*(180.0/M_PI);
}

template<typename Type> bool is_between( const Type value, const Type v1, const Type v2 )
{
	return (value >= v1 && value <= v2);
}

template<typename Type> Type uniform( const Type min, const Type max )
{
	static bool init(false);

	if( !init )
	{
		srand(time(NULL));
		init = true;
	}

	return Type((std::rand() / double(RAND_MAX) * (max - min)) + min);
}

template<typename Type> Type uniform()
{
	static bool init(false);

	if( !init )
	{
		srand(time(NULL));
		init = true;
	}

	return Type(std::rand() / double(RAND_MAX));
}

template<typename Type> Type gaussian( const Type mu, const Type sigma )
{
	static bool init(false);

	if( !init )
	{
		srand(time(NULL));
		init = true;
	}

	double a(uniform<double>()), b(uniform<double>());
	double z(double(sigma)*sqrt(-2.0*log(a))*cos(2.0*M_PI*b));
	return Type(double(mu)+z);
}

std::string indent( const uint k );
int next_power_of_two( const int value );

#endif //__UTILS_H__
