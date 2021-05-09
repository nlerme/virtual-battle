#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "application_base.h"
#include "singleton.h"
#include "logger.h"
#include "global_timer.h"
#include "types.h"


class CApplication : public IApplicationBase, public CSingleton<CApplication>, public CScopeLogger
{
     friend class CSingleton<CApplication>;

     protected :
	CApplication();
	virtual ~CApplication();
	virtual void begin();
	virtual void mouse_motion( const int x, const int y );
	virtual void mouse_button_down( const int x, const int y, const EMouseButton & button );
	virtual void mouse_button_up( const int x, const int y, const EMouseButton & button );
	virtual void key_up( const int key );
	virtual void key_down( const int key );
	virtual void render() const;
	virtual void update();
	virtual void end();
};

#endif //__APPLICATION_H__
