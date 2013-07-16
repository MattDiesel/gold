
#include <string>
#include <ostream>

#include "../variant/variant.h"
#include "symbol.h"

#include "stackframe.h"


namespace gold {

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

/// Leaves the entire stack.
void StackFrame::LeaveStack( ) {
	StackFrame* t = this->Leave( );

	t->LeaveStack();
}

/// Exits N levels of loop
StackFrame* StackFrame::ExitLoop(int level) {
	if ( !this->tail ) {
		// Error: ExitLoop statement has no matching loop
		throw "ExitLoop statement has no matching loop";
	}

	if (level <= 0) {
		return( this );
	}

	StackFrame* t = this->tail;
	this->Leave();

	return( t->ExitLoop( level ) );
}

/// Continues N levels of loop
StackFrame* StackFrame::ContinueLoop(int level) {
	if ( !this->tail ) {
		// Error: ExitLoop statement has no matching loop
		throw "ExitLoop statement has no matching loop";
	}

	if (level <= 0) {
		return( this );
	}

	StackFrame* t = this->tail;
	this->Leave( );

	return( t->ContinueLoop( level ) );
}

/// Returns from a function
StackFrame* StackFrame::Return() {
	if ( !this->tail ) {
		// Error: Return statement not in function
		throw "Return statement not in function";
	}

	return( this->Leave( ) );
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


} // namespace
