#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <exception>
#include <string>
#include "types.h"


//------------------------------------- General exception -------------------------------------
class CException : public std::exception
{
     protected :
        std::string m_Message;

     public :
        CException( const std::string & message = "" );
        virtual ~CException() throw();
        virtual const char * what() const throw();
};


//------------------------------------ Assertion exception ------------------------------------
struct CAssertException : public CException
{
	CAssertException( const std::string & file, const uint line, const std::string & message );
};

#define Assert(condition) if (!(condition)) throw CAssertException(__FILE__, __LINE__, "Condition non satisfied\n\n" #condition)


//------------------------------------- Loading exception -------------------------------------
struct CLoadingFailed : public CException
{
	CLoadingFailed( const std::string & filename, const std::string & message );
};


//---------------------------------- Out of memory exception ----------------------------------
struct COutOfMemory : public CException
{
	COutOfMemory( const std::string & message );
};

#endif //__EXCEPTIONS_H__
