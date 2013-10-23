

#include <iostream>
#include <cmath>

#include "../variant/variant.h"
#include "../functions/standardsymbols.h"
#include "../callstack/stackframe.h"
#include "../parser/arglistproduction.h"
#include "../parser/funccallproduction.h"
#include "../parser/symbolterminal.h"
#include "../parser/terminal.h"


int main() {
	gold::StackFrame* st = new gold::StandardSymbols( );

	// Create sin arguments
	gold::Production* sinArgs;
	{
		gold::ArgListProduction* arr = new gold::ArgListProduction( );
		arr->Add( new gold::Terminal( M_PI ) );

		sinArgs = arr;
	}

	// Create Sin function call production
	gold::Production* sinFn = new gold::SymbolTerminal( "Sin" );
	gold::Production* sinFnCall
			= new gold::FuncCallProduction( sinFn, sinArgs );

	// Create Round arguments
	gold::Production* rndArgs;
	{
		gold::ArgListProduction* arr = new gold::ArgListProduction( );
		arr->Add( sinFnCall );
		arr->Add( new gold::Terminal( 5 ) );

		rndArgs = arr;
	}

	// Create Round function call production
	gold::Production* rndFn = new gold::SymbolTerminal( "Round" );
	gold::Production* rndFnCall
			= new gold::FuncCallProduction( rndFn, rndArgs );

	// Evaluate the tree.
	std::cout << "Round(Sin(PI), 5) = " << rndFnCall->Evaluate( st ) << std::endl;

	delete rndFnCall; // Recursively frees, so no need to free other bits.
	delete st;

	return 0;
}
