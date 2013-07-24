

#include "../callstack/stackframe.h"
#include "../variant/variant.h"

#include "symbolterminal.h"


namespace gold {


// class SymbolTerminal

SymbolTerminal::SymbolTerminal( std::string n )
		: name( n ) {
}

Variant SymbolTerminal::Evaluate( StackFrame* fr ) {
	return( fr->Eval( this->name ) );
}


} // namespace gold
