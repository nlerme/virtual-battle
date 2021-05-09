#include "utils.h"


std::string indent( const uint k )
{
	return std::string(k<<1, ' ');
}

int next_power_of_two( const int value )
{
        int rval(1);

        while( rval < value )
                rval <<= 1;

        return rval;
}
