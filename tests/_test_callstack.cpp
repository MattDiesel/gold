
#include <iostream>
#include <string>

#include "../variant/variant.h"
#include "../callstack/stackframe.h"
#include "../callstack/functionframe.h"
#include "../callstack/globalscope.h"

using namespace gold;


int main() {
	// Global Scope
	StackFrame* tbl = new GlobalScope( );

	tbl->Define( "Test", 24 );

	try {
		tbl = tbl->Enter( new ScopeFrame( ) );

		tbl->Define( "Test", 42 );

		tbl = tbl->Enter( new FunctionFrame( "FooBar" ) );

		std::cout << tbl->Eval( "Test" ) << std::endl;

		tbl->Return();
	}
	catch ( const char* s ) {
		std::cerr << s << std::endl << "Back trace: " << std::endl;
		tbl->BackTrace(std::cerr, 1, 10);
	}

	tbl->LeaveStack( );

	return 0;
}
