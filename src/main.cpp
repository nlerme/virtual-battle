#include <cstdlib>
#include <iostream>
#include "application.h"


int main( int argc, char ** argv )
{
	try
	{
		CApplication::instance()->run(argc, argv);
	}
	catch( const std::exception & e )
	{
		std::cerr << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}
