
#include <string>
#include <ostream>
#include <map>

#include "../variant/variant.h"
#include "symbol.h"

#include "scopeframe.h"


namespace gold {

// class ScopeFrame


/// Initializes a new, empty, stack frame structure.
ScopeFrame::ScopeFrame( ) {
}

/// Destructor for a stack frame
ScopeFrame::~ScopeFrame( ) {
}


/// Defines a variable on this stack frame
void ScopeFrame::Define( const std::string& name, Variant var, Symbol::Flags flags ) {
	ScopeFrame::SetType::const_iterator it = this->symbols.find( name );

	if ( it != this->symbols.end() ) {
		// Error: Already defined in scope
		throw "Already defined in scope";
	}

	this->symbols.insert( std::pair<std::string, Symbol>( name, Symbol( var, flags ) ) );
}

/// Gets a reference to a symbol on this stack frame.
Symbol& ScopeFrame::Get( const std::string& name ) {
	ScopeFrame::SetType::iterator it = this->symbols.find( name );

	if ( it == this->symbols.end() ) {
		if ( !this->tail ) {
			// Error: Symbol not found
			throw "Symbol not found!";
		}

		return( this->tail->Get( name ) );
	}

	return( ( *it ).second );
}

/// Checks if a symbol is declrared
bool ScopeFrame::IsDeclared( const std::string& name ) const {
	ScopeFrame::SetType::const_iterator it = this->symbols.find( name );

	if ( it != this->symbols.end() ) {
		if ( !this->tail ) {
			return( false );
		}

		return( this->tail->IsDeclared( name ) );
	}

	return( true );
}


} // namespace gold
