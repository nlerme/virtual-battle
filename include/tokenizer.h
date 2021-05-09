#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include <functional>
#include <string>
#include <algorithm>
#include <vector>


class CSpace : public std::unary_function<char, bool>
{
     public :
	bool operator () ( char C ) const;
};

class CNewLine : public std::unary_function<char, bool>
{
     public :
	bool operator () ( char C ) const;
};

class CSeparator : public std::unary_function<char, bool>
{
     private :
	std::string m_String;

     public :
	CSeparator( const std::string & String );
	bool operator () ( char C ) const;
};

template <typename Predicate> class CTokenizer
{
     public :
	static std::vector<std::string> tokenize( const std::string & String, const Predicate & P = Predicate() )
	{
		std::vector<std::string> Tokens;
		std::string::const_iterator It(String.begin());
		std::string::const_iterator ItTokenEnd(String.begin());


		while( It != String.end() )
		{
			while( P(*It) )
				It++;

			ItTokenEnd = find_if(It, String.end(), P);

			if( It < ItTokenEnd )
				Tokens.push_back(std::string(It, ItTokenEnd));

			It = ItTokenEnd;
		}

		return Tokens;
	}
};

typedef CTokenizer<CSpace> CSpaceTokenizer;
typedef CTokenizer<CNewLine> CNewLineTokenizer;

#endif //__TOKENIZER_H__
