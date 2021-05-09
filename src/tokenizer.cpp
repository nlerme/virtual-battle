#include "tokenizer.h"


//---------------------------------------- CNewLine class ----------------------------------------
bool CNewLine::operator () ( char C ) const
{
	return (C == '\n');
}


//----------------------------------------- CSpace class -----------------------------------------
bool CSpace::operator () ( char C ) const
{
	return (C == ' ');
}


//--------------------------------------- CSeparator class ---------------------------------------
CSeparator::CSeparator( const std::string & String ) : m_String(String){}

bool CSeparator::operator () ( char C ) const
{
	return (m_String.find(C) != std::string::npos);
}
