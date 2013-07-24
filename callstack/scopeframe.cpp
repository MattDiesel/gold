
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
void ScopeFrame::Define( const std::string& name, Variant var ) {
	this->Define( name, var, Symbol::NoFlags );
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

/// Assigns a value to a symbol on this stack frame
void ScopeFrame::Assign( const std::string& name, Variant var ) {
	ScopeFrame::SetType::iterator sym = this->symbols.find( name );

	if ( sym == this->symbols.end() ) {
		if ( !this->tail ) {
			// Error: Symbol not found
			throw "Symbol not found in scope";
		}

		this->tail->Assign( name, var );
		return;
	}

	if ( ( *sym ).second.IsConst() ) {
		// Error: Attempt to assign to a constant
		throw "Assigning to a constant";
	}

	( *sym ).second.value = var;
}

/// Gets the value of a symbol on this stack frame
Variant& ScopeFrame::Eval( const std::string& name ) {
	if ( this->Exists( name ) ) {
		return( this->Get( name ).value );
	}

	if ( !this->tail ) {
		// Error: Symbol not found
		throw "Symbol not found";
	}

	return ( this->tail->Eval( name ) );
}

Symbol& ScopeFrame::Get( const std::string& name ) {
	ScopeFrame::SetType::iterator sym = this->symbols.find( name );

	if ( sym == this->symbols.end() ) {
		// Error: Symbol not found
		throw "Symbol not found in scope";
	}

	return( ( *sym ).second );
}

/// Checks if a symbol is declrared
bool ScopeFrame::IsDeclared( const std::string& name ) const {
	if ( !this->Exists( name ) ) {
		if ( !this->tail ) {
			return( false );
		}

		return( this->tail->IsDeclared( name ) );
	}

	return( true );
}

bool ScopeFrame::Exists( const std::string& name ) const {
	return ( this->symbols.find( name ) != this->symbols.end() );
}

} // namespace gold
