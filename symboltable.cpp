
#include <string>
#include <map>
#include <vector>

#include "util/cistring.h"
#include "variant/variant.h"

#include "symboltable.h"

namespace gold {


// class Symbol

Symbol::Symbol( Variant v, Flags fl = NoFlags )
	: value( v ), flags( fl ) {
}

Symbol::~Symbol() {
}

inline bool Symbol::IsConst() {
	return( this->flags & Const );
}

inline bool Symbol::IsStatic() {
	return( this->flags & Static );
}




// class StackFrame
StackFrame::StackFrame() {
}

StackFrame::~StackFrame() {
}


void StackFrame::Define( const std::string& name, Variant var, Symbol::Flags flags ) {
	if ( this->IsDeclared( name ) ) {
		// Error: Already defined in scope
		throw "Already defined in scope";
	}

	this->symbols.insert( std::pair<std::string, Symbol>( name, Symbol( var, flags ) ) );
}

void StackFrame::Assign( const std::string& name, Variant var ) {
	Symbol& v = this->Get( name );

	if ( v.IsConst() ) {
		// Error: Attempt to assign to a constant
		throw "Assigning to a constant";
	}

	v.value = var;
}

Variant& StackFrame::Eval( const std::string& name ) {
	return( this->Get( name ).value );
}

Symbol& StackFrame::Get( const std::string& name ) {
	return( this->symbols.at( name ) );
}

bool StackFrame::IsDeclared( const std::string& name ) {
	return( this->symbols.find( name ) != this->symbols.end() );
}




// class SymbolTable

SymbolTable::SymbolTable() {
	this->globalScope = new StackFrame();
}

SymbolTable::~SymbolTable() {
	for ( auto i = this->scopes.rbegin(); i != this->scopes.rend(); ++i ) {
		delete *i;
	}

	delete this->globalScope;
}

void SymbolTable::Define( const std::string& name, Variant var ) {
	this->Define( name, var, Symbol::NoFlags );
}

void SymbolTable::Define( const std::string& name, Variant var, Symbol::Flags flags ) {
	if (this->scopes.empty()) {
		this->globalScope->Define( name, var, flags );
	}
	else {
		this->scopes.back()->Define( name, var, flags );
	}
}

void SymbolTable::Assign( const std::string& name, Variant var ) {
	Symbol& s = this->Get( name );
	s.value = var;
}

Symbol& SymbolTable::Get( const std::string& name ) {
	for ( auto i = this->scopes.rbegin(); i != this->scopes.rend(); ++i ) {
		if ( (*i)->IsDeclared( name ) ) {
			return( (*i)->Get( name ) );
		}
	}

	if ( this->globalScope->IsDeclared( name ) ) {
		return( this->globalScope->Get( name ) );
	}

	// Error: Variable not declared.
	throw "Variable not declared";
}

Variant& SymbolTable::Eval( const std::string& name ) {
	return( this->Get( name ).value );
}

bool SymbolTable::IsDeclared( const std::string& name ) {
	for ( auto i = this->scopes.rbegin(); i != this->scopes.rend(); ++i ) {
		if ( (*i)->IsDeclared( name ) ) {
			return( true );
		}
	}

	return( false );
}

void SymbolTable::Enter() {
	this->Enter( nullptr );
}

void SymbolTable::Enter( StackFrame* frame ) {
	// if ( SymbolTable::MaxStack &&
	// 	 this->scopes.size() >= SymbolTable::MaxStack ) {
	// 	// Error: Stack overflow
	// 	throw "Stack Overflow";
	// }

	if (!frame) {
		frame = new StackFrame();
	}

	this->scopes.push_back( frame );
}

void SymbolTable::Leave() {
	if ( this->scopes.empty() ) {
		// Error: At global scope
		throw "Stack empty";
	}

	delete this->scopes.back();
	this->scopes.pop_back();
}

StackFrame* SymbolTable::LeaveFrame() {
	if ( this->scopes.empty() ) {
		// Error: At global scope
		throw "Stack empty";
	}

	StackFrame* ret = this->scopes.back();
	this->scopes.pop_back();

	return( ret );
}


} // namespace gold
