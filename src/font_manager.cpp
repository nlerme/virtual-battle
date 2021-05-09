#include <GL/glew.h>
#include <string>
#include "file.h"
#include "logger.h"
#include "font_manager.h"


CFontManager::CFontManager() : CScopeLogger(__FUNCTION__)
{
	_init();
}

CFontManager::~CFontManager()
{
	for( TFontsIt it(m_Fonts.begin()); it!=m_Fonts.end(); it++ )
		delete it->second;
}

void CFontManager::_init()
{
	add_font(new CFont("./fonts/arialbd.ttf", 10, color4f(color3f::black, 1.0f)), "default");
	add_font(new CFont("./fonts/star_wars.ttf", 10, color4f(color3f::black, 1.0f)), "star_wars");
}

CFont* CFontManager::font( const std::string & key )
{
	TFontsCIt it;


	if( (it = m_Fonts.find(key)) != m_Fonts.end() )
		return it->second;
	else
		return m_Fonts["default"];
}

bool CFontManager::add_font( CFont *font, const std::string & key )
{
	if( !font || !font->is_loaded() )
		return false;

	TFontsIt it;

	if( (it = m_Fonts.find(key)) == m_Fonts.end() )
	{
		m_Fonts.insert(std::make_pair(key, font));
		CLogger::instance()->write(std::string("- font `" + key + "' successfully loaded\n"));
		return true;
	}

	return false;
}
