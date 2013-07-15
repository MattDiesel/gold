
#include <iostream>
#include <sstream>
#include "iposstream.h"


void Assert_AtPos( iposstream& st, char c, int line, int col ) {
	if ( st.get() != c ) {
		throw "Assertion failed, characters do not match.";
	}

	if ( st.Pos.Line != line
		 || st.Pos.Column != col ) {
		throw "Assertion failed, positions do not match.";
	}

	std::cout << "Assertion Passed." << std::endl;

	return;
}



int main( int argc, char* argv[] ) {

	std::istringstream st( "#\r\n#\t#" );

	iposstream posStr( st );
	posStr.TabWidth = 4;

	try {
		Assert_AtPos( posStr, '#', 1, 1 );
		Assert_AtPos( posStr, '\n', 1, 2 );
		Assert_AtPos( posStr, '#', 2, 1 );
		Assert_AtPos( posStr, '\t', 2, 2 );
		Assert_AtPos( posStr, '#', 2, 6 );
	}
	catch ( const char* s ) {
		std::cout << s << " " << posStr.Pos << std::endl;
	}


	return( 0 );
}
