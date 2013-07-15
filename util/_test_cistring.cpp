

#include <iostream>

#include "cistring.h"


int main( int argc, char const* argv[] ) {
	cistring s( "Hello" );

	std::cout << ( s == "heLLo" ) << std::endl;
	std::cout << ( s == "Hello" ) << std::endl;
	std::cout << ( s == "Hello2" ) << std::endl;
	std::cout << ( s == "Foo" ) << std::endl;

	return 0;
}
