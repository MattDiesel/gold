



#include <iostream>

#include "../variant/variant.h"
#include "../variant/vararray.h"
#include "../functions/standardsymbols.h"
#include "../callstack/stackframe.h"


int main() {
	gold::StackFrame* st = new gold::StandardSymbols( );



	gold::Variant v = new gold::VarArray( );

	{
		gold::VarArray* a = v.Raw<gold::VarArray>();
		a->Add( 3.14159625 );
	}

	std::cout << v << std::endl;


	gold::Variant fn = st->Eval( "Sin" );

	std::cout << "Sin(pi) ~= " << fn->Call( v ) << std::endl;

	return 0;
}
