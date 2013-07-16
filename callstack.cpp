
#include <string>
#include <map>
#include <vector>

#include "util/cistring.h"
#include "variant/variant.h"

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
StackFrame::StackFrame()
		: tail( nullptr ) {
}

/// Destructor for a stack frame
StackFrame::~StackFrame() {
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

/// Leaves the stack frame.
void StackFrame::Leave( ) {
	// for ( auto i = this->symbols.begin(); i != this->symbols.end(); ++i ) {
	// 	if ( !( ( *i ).second.flags & ( Symbol::Static | Symbol::Argument ) ) ) {
	// 		this->symbols.erase( i );
	// 	}
	// }
}

void StackFrame::BackTraceLine(std::ostream& os, int count, int limit) const {
	os << count << ". Stack Frame" << std::endl;

	if (count < limit && this->tail) {
		this->tail->BackTraceLine(os, count + 1, limit);
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

		while (bottom->tail) {
			bottom = bottom->tail;
		}

		return( bottom->IsDeclared( name ) );
	}

	return( true );
}

/// Prints this stack frames line in a back trace.
void FunctionFrame::BackTraceLine(std::ostream& os, int count, int limit) const {
	os << count << ". Function '" << this->funcName << "'" << std::endl;

	if (count < limit && this->tail) {
		this->tail->BackTraceLine(os, count + 1, limit);
	}
}




// class CallStack

/// Creates a new, empty, symbol table
CallStack::CallStack() {
	this->globalScope = new StackFrame();
	this->topScope = this->globalScope;
}

/// Symbol table destructor.
CallStack::~CallStack() {
	StackFrame* s;
	for ( StackFrame* f = this->topScope; f; f = s ) {
		s = f->tail;
		delete f;
	}
}

/// Defines a new symbol, on the top stack frame
void CallStack::Define( const std::string& name, Variant var ) {
	this->Define( name, var, Symbol::NoFlags );
}

/// Defines a new symbol, on the top stack frame
void CallStack::Define( const std::string& name, Variant var, Symbol::Flags flags ) {
	if ( !this->topScope ) {
		this->globalScope->Define( name, var, flags );
	}
	else {
		this->topScope->Define( name, var, flags );
	}
}

/// Assigns a value to a symbol in the table.
void CallStack::Assign( const std::string& name, Variant var ) {
	Symbol& s = this->Get( name );
	s.value = var;
}

/// Evaluates a symbol in the table.
Symbol& CallStack::Get( const std::string& name ) {
	return( this->topScope->Get( name ) );
}

/// Gets a symbol in the table.
Variant& CallStack::Eval( const std::string& name ) {
	return( this->Get( name ).value );
}

/// Checks if a symbol is declared
bool CallStack::IsDeclared( const std::string& name ) const {
	return( this->topScope->IsDeclared( name ) );
}

/// Enters into a new empty stack frame
void CallStack::Enter() {
	this->Enter( nullptr );
}

/// Enters into a new stack frame
void CallStack::Enter( StackFrame* frame ) {
	// if ( CallStack::MaxStack &&
	// 	 this->scopes.size() >= CallStack::MaxStack ) {
	// 	// Error: Stack overflow
	// 	throw "Stack Overflow";
	// }

	if ( !frame ) {
		frame = new StackFrame();
	}

	frame->tail = this->topScope;
	this->topScope = frame;
}

/// Leaves a stack frame and deletes it
void CallStack::Leave() {
	StackFrame* f = this->LeaveFrame( );
	delete f;
}

/// Leaves a stack frame and returns it.
StackFrame* CallStack::LeaveFrame() {
	if ( this->topScope == this->globalScope ) {
		// Error: At global scope
		throw "Stack empty";
	}

	StackFrame* top = this->topScope;
	this->topScope = top->tail;

	top->Leave();

	return( top );
}


/// Prints a back trace of the last 5 stack frames.
void CallStack::BackTrace(std::ostream& os) const {
	this->topScope->BackTraceLine( os, 1, 5 );
}

} // namespace gold
