
#include <string>
#include <ostream>

#include "stackframe.h"
#include "symbol.h"

#include "functionframe.h"


namespace gold {


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


} // namespace gold
