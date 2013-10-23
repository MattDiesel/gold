
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

Variant Cos( std::vector<Variant> args ) {
	throw "Not Implemented.";
}

Variant Tan( std::vector<Variant> args ) {
	throw "Not Implemented.";
}

Variant Round( std::vector<Variant> args ) {
	if ( args.size() == 1 ) {
		// If second argument is not given then set it to default.
		args.push_back( 0 );
	}
	else if ( args.size() != 2 ) {
		// Error: Incorrect number of arguments to function.
		throw "Incorrect number of arguments to function.";
	}

	double p = std::pow(10.0, args[1]->AsFloat());

	return(std::round(args[0]->AsFloat() * p) / p);
}


} // namespace gold
