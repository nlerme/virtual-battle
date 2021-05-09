#include "file.h"


CFile::CFile( const std::string & name, std::ios_base::openmode mode ) : std::fstream(name.c_str(), mode), m_Name(name) {}

const std::string & CFile::fullname() const
{
	return m_Name;
}

const std::string CFile::filename() const
{
	std::string::size_type pos(m_Name.find_last_of("\\/"));
	return (pos != std::string::npos) ? m_Name.substr(pos + 1) : m_Name;
}

const std::string CFile::short_filename() const
{
	std::string fn(filename());
	return fn.substr(0, fn.find_last_of("."));
}

const std::string CFile::extension() const
{
	std::string::size_type pos(m_Name.find_last_of("."));
	return (pos != std::string::npos) ? m_Name.substr(pos + 1) : "";
}
