#ifndef __FONT_H__
#define __FONT_H__

#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>
#include <string>
#include "types.h"
#include "color.h"


class CFont
{
     private :
	float m_Height;
	uint * m_Textures;
	uint m_ListBase;
	bool m_IsLoaded;

	void _build_display_list( FT_Face face, char ch );
	void _push_matrix() const;
	void _pop_matrix() const;

     public :
	CFont( const std::string & filename, const uint height, const color4f & color );
	virtual ~CFont();

	bool load( const std::string & filename, const uint height, const color4f & color );
	bool is_loaded() const;
	void put_text( const std::string & str, const float x, const float y, const color4f & color = color4f(color3f::white, 1.0f) ) const;
};

#endif //__FONT_H__
