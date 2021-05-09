#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <limits>
#include <cmath>
#include <cassert>
#include "exceptions.h"
#include "utils.h"


//-----------------------------------------------------------------------------------------------------------
//-------------------------------------------------- Points -------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
template<typename Type> struct point2
{
	union
	{
		Type data[2];
		struct{ Type x, y; };
	};

	point2( const Type _x = Type(), const Type _y = Type() ) : x(_x), y(_y){}
	point2( const Type _data[2] ){ x = _data[0]; y = _data[1]; }
	template<typename Type2> point2( const point2<Type2> & p ){ x = Type(p.x); y = Type(p.y); }
	point2<Type> operator + ( const Type k ) const{ return point2<Type>(x+k, y+k); }
	point2<Type> operator += ( const Type k ){ x += k; y += k; return *this; }
	point2<Type> operator - ( const Type k ) const{ return point2<Type>(x-k, y-k); }
	point2<Type> operator -= ( const Type k ){ x -= k; y -= k; return *this; }
	point2<Type> operator - () const{ return point2<Type>(-x, -y); }
	point2<Type> operator * ( const Type k ) const{ return point2<Type>(x*k, y*k); }
	point2<Type> operator *= ( const Type k ) const{ x *= k; y *= k; return *this; }
	template<typename Type2> point2<Type2> operator = ( const point2<Type2> & p ){ x = Type(p.x); y = Type(p.y); return *this; }
	friend std::ostream & operator << ( std::ostream & out, const point2<Type> & p ){ return (out << "point2[" << p.x << ", " << p.y << "]"); }
	static point2<Type> zero(){ return point2<Type>(0, 0); }
	static point2<Type> one(){ return point2<Type>(1, 1); }
	static point2<Type> grandom( const point2<Type> & mu, const point2<Type> & sigma ){ return point2<Type>(gaussian(mu.x, sigma.x), gaussian(mu.y, sigma.y)); }
	static point2<Type> urandom( const Type min, const Type max ){ return point2<Type>(uniform(min, max), uniform(min, max)); }
	void clamp( const point2<Type> & min, const point2<Type> & max ){ x = ::clamp<Type>(x, min.x, max.x); y = ::clamp<Type>(y, min.y, max.y); }
};

template<typename Type> point2<Type> operator * ( const Type k, const point2<Type> & p )
{
	return p*k;
}

// aliases
typedef point2<unsigned int> point2ui;
typedef point2<int>          point2i;
typedef point2<float>        point2f;
typedef point2<double>       point2d;


//-----------------------------------------------------------------------------------------------------------
//------------------------------------------------- Vectors -------------------------------------------------
//-----------------------------------------------------------------------------------------------------------
template<typename Type> struct vec2
{
	union
	{
		Type data[2];
		struct{ Type x, y; };
	};

	vec2( const Type _x = Type(), const Type _y = Type() ) : x(_x), y(_y){}
	vec2( const Type _data[2] ){ x = _data[0]; y = _data[1]; }
	vec2( const point2<Type> & p1, const point2<Type> & p2 ){ x = (p2.x-p1.x); y = (p2.y-p1.y); }
	template<typename Type2> vec2( const vec2<Type2> & v ){ x = Type(v.x); y = Type(v.y); }
	vec2<Type> operator + ( const vec2<Type> & v ) const{ return vec2<Type>(x+v.x, y+v.y); }
	vec2<Type> operator += ( const vec2<Type> & v ){ x += v.x; y += v.y; return *this; }
	vec2<Type> operator - ( const vec2<Type> & v ) const{ return vec2<Type>(x-v.x, y-v.y); }
	vec2<Type> operator -= ( const vec2<Type> & v ){ x -= v.x; y -= v.y; return *this; }
	vec2<Type> operator - () const{ return vec2<Type>(-x, -y); }
	vec2<Type> operator * ( const Type k ) const{ return vec2<Type>(x*k, y*k); }
	vec2<Type> operator *= ( const Type k ) const{ x *= k; y *= k; return *this; }
	template<typename Type2> vec2<Type2> operator = ( const vec2<Type2> & v ){ x = Type(v.x); y = Type(v.y); return *this; }
	friend std::ostream & operator << ( std::ostream & out, const vec2<Type> & v ){ return (out << "vec2[" << v.x << ", " << v.y << "]"); }
	Type norm_squared(){ return sq(x)+sq(y); }
	Type norm(){ return sqrt(norm_squared()); }
	void normalize()
	{
		Type n(norm());
		x /= (n + std::numeric_limits<Type>::epsilon());
		y /= (n + std::numeric_limits<Type>::epsilon());
	}
	static vec2<Type> zero(){ return vec2<Type>(0, 0); }
	static vec2<Type> one(){ return vec2<Type>(1, 1); }
	static vec2<Type> urandom( const Type min, const Type max ){ return vec2<Type>(uniform<Type>(min, max), uniform<Type>(min, max)); }
	void rotate( const Type angle )
	{
		Type radians(degrees2radians(angle)), xx(x), yy(y);
		x = xx*cosf(radians) - yy*sinf(radians);
		y = xx*sinf(radians) + yy*cosf(radians);
	}
};

template<typename Type> vec2<Type> operator * ( const Type k, const vec2<Type> & v )
{
	return v*k;
}

template<typename Type> Type distance( const point2<Type> & p1, const point2<Type> & p2 )
{
	return vec2<Type>(p1, p2).norm();
}

// aliases
typedef vec2<unsigned int> vec2ui;
typedef vec2<int>          vec2i;
typedef vec2<float>        vec2f;
typedef vec2<double>       vec2d;

#endif //__GEOMETRY_H__
