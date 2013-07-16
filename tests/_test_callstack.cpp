
#include <iostream>
#include <string>

#include "../variant/variant.h"
#include "../callstack.h"

using namespace gold;

int main() {
	CallStack tbl;

	try {

		tbl.Define( "Foo", Variant( "FooGlobal" ) );

		// FooGlobal
		std::cout << tbl.Eval( "Foo" ) << std::endl;


		std::cout << "Entering scope" << std::endl;
		tbl.Enter( );


		tbl.Define( "Test", Variant( "TestValue" ) );


		std::cout << "Entering scope" << std::endl;
		tbl.Enter( new FunctionFrame( "FooBar" ) );

		tbl.Define( "Bar", Variant( "BarValue" ) );
		tbl.Define( "Foo", Variant( "FooLocal" ) );

		// FooLocal
		std::cout << tbl.Eval( "Foo" ) << std::endl;

		// BarValue
		std::cout << tbl.Eval( "Bar" ) << std::endl;

		// BarValue
		std::cout << tbl.Eval( "Test" ) << std::endl;

		std::cout << "Leaving scope" << std::endl;
		tbl.Leave();

		std::cout << "Leaving scope" << std::endl;
		tbl.Leave();

		// FooGlobal
		std::cout << tbl.Eval( "Foo" ) << std::endl;

		// Error
		std::cout << tbl.Eval( "Bar" ) << std::endl;
	}
	catch ( const char* s ) {
		std::cerr << s << std::endl << "Back trace: " << std::endl;
		tbl.BackTrace(std::cerr);
	}

	return 0;
}
