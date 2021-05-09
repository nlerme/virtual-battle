#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include "singleton.h"


//----------------------------------------------------------------------------------
//----------------------------- General logging system -----------------------------
//----------------------------------------------------------------------------------
class CLogger : public CSingleton<CLogger>
{
     friend class CSingleton<CLogger>;

     private :
	std::string m_Filename;
	std::ofstream m_File;

	CLogger();
	virtual ~CLogger();
	std::string _current_date() const;
	std::string _current_time() const;

     public :
	void log( const char * format, ... );
	void write( const std::string & message );
	void set_filename( const std::string & fileName );
	template<typename Type> CLogger & operator << ( const Type & object );
};

template<typename Type> CLogger & CLogger::operator << ( const Type & object )
{
	std::ostringstream stream;
	stream << object;
	write(stream.str());
	return (CLogger&)instance();
}


//----------------------------------------------------------------------------------
//------------------------------ Scope logging system ------------------------------
//----------------------------------------------------------------------------------
class CScopeLogger
{
     friend class CLogger;

     private :
	static std::stack<std::string> m_FunctionNames;

     public :
	CScopeLogger( const std::string & function_name );
	virtual ~CScopeLogger();
};

#endif //__LOGGER_H__
