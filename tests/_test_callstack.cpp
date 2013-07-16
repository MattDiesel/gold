
#include <iostream>
#include <string>

#include "../variant/variant.h"
#include "../callstack.h"

using namespace gold;

int main() {
	// Global Scope
	StackFrame* tbl = new StackFrame( );

	try {

		tbl->Define( "Foo", Variant( "FooGlobal" ) );

		// FooGlobal
		std::cout << tbl->Eval( "Foo" ) << std::endl;


		std::cout << "Entering scope" << std::endl;
		tbl = tbl->Enter( );


		tbl->Define( "Test", Variant( "TestValue" ) );


		std::cout << "Entering scope" << std::endl;
		tbl = tbl->Enter( new FunctionFrame( "FooBar" ) );

		tbl->Define( "Bar", Variant( "BarValue" ) );
		tbl->Define( "Foo", Variant( "FooLocal" ) );

		// FooLocal
		std::cout << tbl->Eval( "Foo" ) << std::endl;

		// BarValue
		std::cout << tbl->Eval( "Bar" ) << std::endl;

		// Error!
		// std::cout << tbl->Eval( "Test" ) << std::endl;

		std::cout << "Leaving scope" << std::endl;
		tbl = tbl->Leave();

		std::cout << "Leaving scope" << std::endl;
		tbl = tbl->Leave();

		// FooGlobal
		std::cout << tbl->Eval( "Foo" ) << std::endl;

		// Error
		std::cout << tbl->Eval( "Bar" ) << std::endl;
	}
	catch ( const char* s ) {
		std::cerr << s << std::endl << "Back trace: " << std::endl;
		tbl->BackTrace(std::cerr, 1, 10);
	}

	tbl = tbl->Leave( );

	return 0;
}
