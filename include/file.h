#ifndef __FILE_H__
#define __FILE_H__

#include <string>
#include <iostream>
#include <fstream>
#include "types.h"


class CFile : public std::fstream
{
     private :
	std::string m_Name;

     public :
	CFile( const std::string & name, std::ios_base::openmode mode = ios_base::in | ios_base::out );
	const std::string & fullname() const;
	const std::string filename() const;
	const std::string short_filename() const;
	const std::string extension() const;
};

#endif //__FILE_H__
