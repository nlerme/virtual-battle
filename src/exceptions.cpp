#include "exceptions.h"
#include <sstream>

using std::endl;


//------------------------------------- General exception -------------------------------------
CException::CException( const std::string & message ) : m_Message(message){}

CException::~CException() throw() {}

const char * CException::what() const throw()
{
	return m_Message.c_str();
}


//------------------------------------ Assertion exception ------------------------------------
CAssertException::CAssertException( const std::string & file, const uint line, const std::string & message )
{
	std::ostringstream oss;
	oss << "[ Assertion ] File `" << file << "` (" << line << ") - " << message << endl;
	m_Message = oss.str();
}


//------------------------------------- Loading exception -------------------------------------
CLoadingFailed::CLoadingFailed( const std::string & filename, const std::string & message )
{
	std::ostringstream oss;
	oss << "[ File Loading ] File `" << filename << "` - " << message;
	m_Message = oss.str();
}


COutOfMemory::COutOfMemory( const std::string & message )
{
	std::ostringstream oss;
	oss << "[ Out Of Memory ] " << message << endl;
	m_Message = oss.str();
}
