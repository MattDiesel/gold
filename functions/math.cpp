
#include <vector>
#include <cmath>

#include "../variant/variant.h"


namespace gold {


Variant Sin(std::vector<Variant> args) {
	return( std::sin( args[0]->AsFloat() ) );
}

Variant Cos(std::vector<Variant>) {
	return( 0 );
}

Variant Tan(std::vector<Variant>) {
	return( 0 );
}


} // namespace gold
