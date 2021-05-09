#include <cstdarg>
#include "exceptions.h"
#include "logger.h"
#include "utils.h"
#include "config.h"

using std::endl;
using std::flush;


static uint g_NbIndents = 0;

//----------------------------------------------------------------------------------
//----------------------------- General logging system -----------------------------
//----------------------------------------------------------------------------------
CLogger::CLogger() : m_Filename(CConfig::LogFilename), m_File(m_Filename.c_str())
{
	if( !m_File )
		throw CLoadingFailed(m_Filename, "I/O error (probably bad rights)");

	m_File << "------------------------------------------------------------------------------------" << endl;
	m_File << "# Start - " << _current_date() << " @ " << _current_time() << "                                                    #" << endl;
	m_File << "------------------------------------------------------------------------------------" << endl << endl;
}

CLogger::~CLogger()
{
	m_File << endl;
	m_File << "------------------------------------------------------------------------------------" << endl;
	m_File << "# End - " << _current_date() << " @ " << _current_time() << "                                                      #" << endl;
	m_File << "------------------------------------------------------------------------------------" << endl;

	m_File.close();
}

std::string CLogger::_current_date() const
{
	char ctime[24];

	time_t currentTime = time(NULL);
	strftime(ctime, sizeof(ctime), "%d/%m/%Y", localtime(&currentTime));

	return ctime;
}

std::string CLogger::_current_time() const
{
	char ctime[24];

	time_t currentTime = time(NULL);
	strftime(ctime, sizeof(ctime), "%H:%M:%S", localtime(&currentTime));

	return ctime;
}

void CLogger::log( const char *format, ... )
{
	char buffer[512]={0};

	va_list params;
	va_start(params, format);
	vsprintf(buffer, format, params);
	va_end(params);

	write(buffer);
}

void CLogger::write( const std::string & message )
{
	Assert(m_File.is_open());
	m_File << indent(g_NbIndents) << message << flush;
}

void CLogger::set_filename( const std::string & filename )
{
	m_Filename = filename;
}


//----------------------------------------------------------------------------------
//------------------------------ Scope logging system ------------------------------
//----------------------------------------------------------------------------------
CScopeLogger::CScopeLogger( const std::string & function_name )
{
	m_FunctionNames.push(function_name);
	CLogger::instance()->log("[+] %s\n", function_name.c_str());
	g_NbIndents++;
}

CScopeLogger::~CScopeLogger()
{
	std::string function_name(m_FunctionNames.top());
	m_FunctionNames.pop();
	g_NbIndents--;
	CLogger::instance()->log("[-] %s\n", function_name.c_str());
}

std::stack<std::string> CScopeLogger::m_FunctionNames = std::stack<std::string>();
