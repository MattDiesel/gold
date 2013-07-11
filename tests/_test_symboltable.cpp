
#include <iostream>
#include <string>

#include "../variant.h"
#include "../symboltable.h"

using namespace gold;

int main() {
	try {
		SymbolTable tbl;

		tbl.Define( "Foo", Variant( "FooGlobal" ) );

		// FooGlobal
		std::cout << tbl.Eval( "Foo" ) << std::endl;

		std::cout << "Entering scope" << std::endl;
		tbl.Enter();

		tbl.Define( "Bar", Variant( "BarValue" ) );
		tbl.Define( "Foo", Variant( "FooLocal" ) );

		// FooLocal
		std::cout << tbl.Eval( "Foo" ) << std::endl;

		// BarValue
		std::cout << tbl.Eval( "Bar" ) << std::endl;

		std::cout << "Leaving scope" << std::endl;
		tbl.Leave();

		// FooGlobal
		std::cout << tbl.Eval( "Foo" ) << std::endl;

		// Error
		std::cout << tbl.Eval( "Bar" ) << std::endl;
	}
	catch ( const char* s ) {
		std::cerr << s << std::endl;
	}

	return 0;
}
