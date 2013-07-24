



#include <iostream>

#include "../variant/variant.h"
#include "../functions/standardsymbols.h"
#include "../callstack/stackframe.h"
#include "../parser/arglistproduction.h"
#include "../parser/funccallproduction.h"
#include "../parser/symbolterminal.h"
#include "../parser/terminal.h"


int main() {
	gold::StackFrame* st = new gold::StandardSymbols( );


	gold::Production* fn = new gold::SymbolTerminal( "Sin" );

	gold::Production* args;

	{
		gold::ArgListProduction* arr = new gold::ArgListProduction( );
		arr->Add( new gold::Terminal( 3.14159625 ) );

		args = arr;
	}

	gold::Production* fncall = new gold::FuncCallProduction( fn, args );


	std::cout << "Sin(pi) ~= " << fncall->Evaluate( st ) << std::endl;

	delete fn;
	delete st;

	return 0;
}
