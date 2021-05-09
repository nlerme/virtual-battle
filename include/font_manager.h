#ifndef __FONT_MANAGER_H__
#define __FONT_MANAGER_H__

#include <string>
#include <map>
#include <iterator>
#include "font.h"
#include "types.h"
#include "logger.h"
#include "singleton.h"


class CFontManager : public CSingleton<CFontManager>, public CScopeLogger
{
     friend class CSingleton<CFontManager>;

     private :
	// aliases
	typedef std::map<const std::string, CFont*> TFonts;
	typedef std::map<const std::string, CFont*>::iterator TFontsIt;
	typedef std::map<const std::string, CFont*>::const_iterator TFontsCIt;

	TFonts m_Fonts;

	CFontManager();
	~CFontManager();
	void _init();

     public :
	CFont* font( const std::string & key );
	bool add_font( CFont *font, const std::string & key );
};

#endif //__FONT_MANAGER_H__
