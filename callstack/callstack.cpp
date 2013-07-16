
#include <string>
#include <map>
#include <vector>

#include "../util/cistring.h"
#include "../variant/variant.h"

#include "callstack.h"

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



// class StackFrame


/// Initializes a new, empty, stack frame structure.
StackFrame::StackFrame( )
		: tail( nullptr ) {
}

/// Destructor for a stack frame
StackFrame::~StackFrame( ) {
}


/// Defines a variable on this stack frame
void StackFrame::Define( const std::string& name, Variant var ) {
	this->Define( name, var, Symbol::NoFlags );
}

/// Defines a variable on this stack frame
void StackFrame::Define( const std::string& name, Variant var, Symbol::Flags flags ) {
	StackFrame::SetType::const_iterator it = this->symbols.find( name );

	if ( it != this->symbols.end() ) {
		// Error: Already defined in scope
		throw "Already defined in scope";
	}

	this->symbols.insert( std::pair<std::string, Symbol>( name, Symbol( var, flags ) ) );
}

/// Assigns a value to a symbol on this stack frame
void StackFrame::Assign( const std::string& name, Variant var ) {
	Symbol& v = this->Get( name );

	if ( v.IsConst() ) {
		// Error: Attempt to assign to a constant
		throw "Assigning to a constant";
	}

	v.value = var;
}

/// Gets the value of a symbol on this stack frame
Variant& StackFrame::Eval( const std::string& name ) {
	return( this->Get( name ).value );
}

/// Gets a reference to a symbol on this stack frame.
Symbol& StackFrame::Get( const std::string& name ) {
	StackFrame::SetType::iterator it = this->symbols.find( name );

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
bool StackFrame::IsDeclared( const std::string& name ) const {
	StackFrame::SetType::const_iterator it = this->symbols.find( name );

	if ( it != this->symbols.end() ) {
		if ( !this->tail ) {
			return( false );
		}

		return( this->tail->IsDeclared( name ) );
	}

	return( true );
}


StackFrame* StackFrame::Enter( ) {
	return( this->Enter( nullptr ) );
}

StackFrame* StackFrame::Enter( StackFrame* fr ) {
	if ( !fr ) {
		fr = new StackFrame( );
	}

	fr->tail = this;
	return( fr );
}


/// Leaves the stack frame.
StackFrame* StackFrame::Leave( ) {
	StackFrame* top = this->tail;
	delete this;
	return( top );
}


/// Exits N levels of loop
StackFrame* StackFrame::ExitLoop(int level) {
	if ( !this->tail ) {
		// Error: ExitLoop statement has no matching loop
		throw "ExitLoop statement has no matching loop";
	}

	return( this->Leave() );
}

/// Continues N levels of loop
StackFrame* StackFrame::ContinueLoop(int level) {
	if ( !this->tail ) {
		// Error: ExitLoop statement has no matching loop
		throw "ExitLoop statement has no matching loop";
	}

	return( this->Leave() );
}

/// Returns from a function
StackFrame* StackFrame::Return() {
	if ( !this->tail ) {
		// Error: Return statement not in function
		throw "Return statement not in function";
	}

	return( this->Leave() );
}

/// Calls the next frames BackTrace
void StackFrame::BackTrace(std::ostream& os, int count, int limit) const {
	if ( this->tail ) {
		this->tail->BackTrace(os, count, limit);
	}
}

/// Prints this stack frames line in a back trace.
void StackFrame::ScopeTrace(std::ostream& os, int count, int limit) const {
	os << count << ". Stack frame" << std::endl;

	if ( count < limit && this->tail ) {
		this->tail->ScopeTrace(os, count + 1, limit);
	}
}


// class FunctionFrame

/// Creates a new stack frame for a function
FunctionFrame::FunctionFrame( std::string s )
		: funcName( s ) {
}

/// Function stack frame destructor
FunctionFrame::~FunctionFrame() {
}

/// Gets a reference to a symbol on this stack frame.
Symbol& FunctionFrame::Get( const std::string& name ) {
	StackFrame::SetType::iterator it = this->symbols.find( name );

	if ( it == this->symbols.end() ) {
		if ( !this->tail ) {
			// Error: Symbol not found
			throw "Symbol not found!";
		}

		// Skip to bottom frame.

		StackFrame* bottom = this->tail;

		while (bottom->tail) {
			bottom = bottom->tail;
		}

		return( bottom->Get( name ) );
	}

	return( ( *it ).second );
}

/// Checks if a symbol is declrared
bool FunctionFrame::IsDeclared( const std::string& name ) const {
	StackFrame::SetType::const_iterator it = this->symbols.find( name );

	if ( it != this->symbols.end() ) {
		if ( !this->tail ) {
			return( false );
		}

		// Skip to bottom frame.

		StackFrame* bottom = this->tail;

		while ( bottom->tail ) {
			bottom = bottom->tail;
		}

		return( bottom->IsDeclared( name ) );
	}

	return( true );
}

/// Leaves the stack frame.
StackFrame* FunctionFrame::Leave( ) {
	for ( auto i = this->symbols.begin(); i != this->symbols.end(); ++i ) {
		if ( !( ( *i ).second.flags & ( Symbol::Static | Symbol::Argument ) ) ) {
			this->symbols.erase( i );
		}
	}

	StackFrame* ret = this->tail;
	this->tail = nullptr;
	return( ret );
}


/// Throws an error, as there is no loop remaining.
StackFrame* FunctionFrame::ExitLoop( int level ) {
	// Error: ExitLoop statement has no matching loop
	throw "ExitLoop statement has no matching loop";
}

/// Throws an error, as there is no loop remaining.
StackFrame* FunctionFrame::ContinueLoop( int level ) {
	// Error: ContinueLoop statement has no matching loop
	throw "ContinueLoop statement has no matching loop";
}

/// Returns from the function
StackFrame* FunctionFrame::Return() {
	return( this->Leave() );
}


/// Prints this stack frames line in a back trace.
void FunctionFrame::BackTrace( std::ostream& os, int count, int limit ) const {
	os << count << ". Function '" << this->funcName << "'" << std::endl;

	if ( count < limit && this->tail ) {
		this->tail->BackTrace(os, count + 1, limit);
	}
}


/// Prints this stack frames line in a back trace.
void FunctionFrame::ScopeTrace( std::ostream& os, int count, int limit ) const {
	os << count << ". Function '" << this->funcName << "'" << std::endl;

	if ( count < limit && this->tail ) {
		this->tail->ScopeTrace( os, count + 1, limit );
	}
}


// class LoopFrame

/// Creates a new stack frame for a loop
LoopFrame::LoopFrame() {
}

/// Loop stack frame destructor
LoopFrame::~LoopFrame() {
}

/// Exits the loop
StackFrame* LoopFrame::ExitLoop( int level ) {
	return( this->Leave() );
}

/// Continues the loop
StackFrame* LoopFrame::ContinueLoop( int level ) {
	return( this->Leave() );
}

/// Prints this stack frames line in a back trace.
void LoopFrame::ScopeTrace( std::ostream& os, int count, int limit ) const {
	os << count << ". Loop Frame" << std::endl;

	if ( count < limit && this->tail ) {
		this->tail->ScopeTrace( os, count + 1, limit );
	}
}


} // namespace gold
