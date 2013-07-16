
#include "../variant/variant.h"

#include "symbol.h"

namespace gold {

// class Symbol

/// Creates a new null symbol.
Symbol::Symbol( )
	: value( ), flags( NoFlags ) {
}

/// Creates a new symbol for the given variant
Symbol::Symbol( Variant v )
	: value( v ), flags( NoFlags ) {
}

/// Creates a new symbol for the given variant with the set flags
Symbol::Symbol( Variant v, Flags fl )
	: value( v ), flags( fl ) {
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

