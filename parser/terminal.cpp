

#include "../variant/variant.h"

#include "terminal.h"


namespace gold {


// class Terminal

Terminal::Terminal( Variant v )
		: value( v ) {
}

Variant Terminal::Evaluate( ) {
	return( this->value );
}


} // namespace gold
