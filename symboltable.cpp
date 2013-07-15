
#include <string>
#include <map>
#include <vector>

#include "util/cistring.h"
#include "variant/variant.h"

#include "symboltable.h"

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




// class SymbolTable

/// Creates a new, empty, symbol table
SymbolTable::SymbolTable() {
	this->globalScope = new StackFrame();
	this->topScope = this->globalScope;
}

/// Symbol table destructor.
SymbolTable::~SymbolTable() {
	StackFrame* s;
	for ( StackFrame* f = this->topScope; f; f = s ) {
		s = f->tail;
		delete f;
	}
}

/// Defines a new symbol, on the top stack frame
void SymbolTable::Define( const std::string& name, Variant var ) {
	this->Define( name, var, Symbol::NoFlags );
}

/// Defines a new symbol, on the top stack frame
void SymbolTable::Define( const std::string& name, Variant var, Symbol::Flags flags ) {
	if ( !this->topScope ) {
		this->globalScope->Define( name, var, flags );
	}
	else {
		this->topScope->Define( name, var, flags );
	}
}

/// Assigns a value to a symbol in the table.
void SymbolTable::Assign( const std::string& name, Variant var ) {
	Symbol& s = this->Get( name );
	s.value = var;
}

/// Evaluates a symbol in the table.
Symbol& SymbolTable::Get( const std::string& name ) {
	return( this->topScope->Get( name ) );
}

/// Gets a symbol in the table.
Variant& SymbolTable::Eval( const std::string& name ) {
	return( this->Get( name ).value );
}

/// Checks if a symbol is declared
bool SymbolTable::IsDeclared( const std::string& name ) const {
	return( this->topScope->IsDeclared( name ) );
}

/// Enters into a new empty stack frame
void SymbolTable::Enter() {
	this->Enter( nullptr );
}

/// Enters into a new stack frame
void SymbolTable::Enter( StackFrame* frame ) {
	// if ( SymbolTable::MaxStack &&
	// 	 this->scopes.size() >= SymbolTable::MaxStack ) {
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
void SymbolTable::Leave() {
	StackFrame* f = this->LeaveFrame( );
	delete f;
}

/// Leaves a stack frame and returns it.
StackFrame* SymbolTable::LeaveFrame() {
	if ( this->topScope == this->globalScope ) {
		// Error: At global scope
		throw "Stack empty";
	}

	StackFrame* top = this->topScope;
	this->topScope = top->tail;

	top->Leave();

	return( top );
}


} // namespace gold
