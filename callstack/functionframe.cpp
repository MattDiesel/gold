
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



/// Assigns a value to a symbol on this stack frame
void FunctionFrame::Assign( const std::string& name, Variant var ) {
	this->BlockAssign( name, var );
}

/// Gets the value of a symbol on this stack frame
Variant& FunctionFrame::Eval( const std::string& name ) {
	return( this->BlockEval( name ) );
}

/// Checks if a symbol is declrared
bool FunctionFrame::IsDeclared( const std::string& name ) const {
	return( this->BlockIsDeclared( name ) );
}

/// Assigns a value to a symbol on this stack frame
void FunctionFrame::BlockAssign( const std::string& name, Variant var ) {
	ScopeFrame::SetType::iterator sym = this->symbols.find( name );

	if ( sym == this->symbols.end() ) {
		if ( !this->tail) {
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
Variant& FunctionFrame::BlockEval( const std::string& name ) {
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
bool FunctionFrame::BlockIsDeclared( const std::string& name ) const {
	if ( !this->Exists( name ) ) {
		if ( !this->tail ) {
			return( false );
		}

		return( this->tail->BlockIsDeclared( name ) );
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
