
#include <string>
#include <ostream>
#include <map>

#include "../variant/variant.h"
#include "symbol.h"
#include "scopeframe.h"

#include "globalscope.h"


namespace gold {


/// Initializes a new, empty, stack frame structure.
GlobalScope::GlobalScope() {
}

/// Destructor for a stack frame
GlobalScope::~GlobalScope() {
}

// Symbol functions -----------------------------------

/// Assigns a value to a symbol on this stack frame
void GlobalScope::BlockAssign( const std::string& name, Variant var ) {
	ScopeFrame::SetType::iterator sym = this->symbols.find( name );

	if ( sym == this->symbols.end() ) {
		if ( !this->tail ) {
			// Error: Symbol not found
			throw "Symbol not found in scope";
		}

		this->tail->BlockAssign( name, var );
		return;
	}

	if ( ( *sym ).second.IsConst() ) {
		// Error: Attempt to assign to a constant
		throw "Assigning to a constant";
	}

	( *sym ).second.value = var;
}

/// Gets the value of a symbol on this stack frame
Variant& GlobalScope::BlockEval( const std::string& name ) {
	if ( this->Exists( name ) ) {
		return( this->Get( name ).value );
	}

	if ( !this->tail ) {
		// Error: Symbol not found
		throw "Symbol not found";
	}

	return ( this->tail->BlockEval( name ) );
}

/// Checks if a symbol is declrared
bool GlobalScope::BlockIsDeclared( const std::string& name ) const {
	if ( !this->Exists( name ) ) {
		if ( !this->tail ) {
			return( false );
		}

		return( this->tail->BlockIsDeclared( name ) );
	}

	return( true );
}


} // namespace gold
