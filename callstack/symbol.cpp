
#include "../variant/variant.h"

#include "symbol.h"

namespace gold {

// class Symbol

/// Creates a new null symbol.
Symbol::Symbol( )
	: flags( NoFlags ), value( ) {
}

/// Creates a new symbol for the given variant
Symbol::Symbol( Variant v )
	: flags( NoFlags ), value( v ) {
}

/// Creates a new symbol for the given variant with the set flags
Symbol::Symbol( Variant v, Flags fl )
	: flags( fl ), value( v ) {
}

/// Symbol destructor.
Symbol::~Symbol() {
}

/// Returns TRUE if the symbol is static, FALSE otherwise.
bool Symbol::IsStatic() const {
	return( this->flags & Static );
}

/// Returns TRUE if the symbol is a constant, FALSE otherwise.
bool Symbol::IsConst() const {
	return( this->flags & Const );
}

/// Returns TRUE if the symbol is an argument, FALSE otherwise.
bool Symbol::IsArgument() const {
	return( this->flags & Argument );
}


} // namespace gold

