
#include <string>
#include <vector>
#include <ostream>

#include "../variant/variant.h"
#include "../callstack/symbol.h"

#include "standardsymbols.h"


namespace gold {


// class StandardSymbols

/// Initializes a new, empty, stack frame structure.
StandardSymbols::StandardSymbols() {
}

/// Destructor for a stack frame
StandardSymbols::~StandardSymbols() {
}


/// Defines a variable on this stack frame
void StandardSymbols::Define( const std::string&, Variant ) {
	// Error: Cannot define something in this scope
	throw "Cannot define something in this scope";
}

/// Assigns a value to a symbol on this stack frame
void StandardSymbols::Assign( const std::string&, Variant ) {
	// Error: Cannot assign to something in this scope
	throw "Attempt to redefine a constant";
}

/// Gets the value of a symbol on this stack frame
Variant& StandardSymbols::Eval( const std::string& s ) {
	return( gold::Functions[s] );
}

/// Checks if a symbol is declrared
bool StandardSymbols::IsDeclared( const std::string& s ) const {
	throw "Not Implemented";
}


/// Calls the next frames BackTrace
void StandardSymbols::BackTrace( std::ostream&, int, int ) const {
	throw "Not Implemented";
}

/// Prints this stack frames line in a back trace.
void StandardSymbols::ScopeTrace( std::ostream&, int, int ) const {
	throw "Not Implemented";
}


} // namespace gold
