
#include <vector>
#include <cmath>

#include "../variant/variant.h"


namespace gold {


Variant Sin( std::vector<Variant> args ) {
	if ( args.size() != 1 ) {
		// Error: Incorrect number of arguments to function.
		throw "Incorrect number of arguments to function.";
	}

	return( std::sin( args.front()->AsFloat() ) );
}

Variant Cos( std::vector<Variant> ) {
	throw "Not Implemented.";
}

Variant Tan( std::vector<Variant> ) {
	throw "Not Implemented.";
}


} // namespace gold
