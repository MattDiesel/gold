
#include <iostream>
#include <string>

#include "../variant/variant.h"
#include "../callstack/stackframe.h"
#include "../callstack/functionframe.h"
#include "../callstack/loopframe.h"

using namespace gold;


int main() {
	// Global Scope
	StackFrame* tbl = new StackFrame( );

	try {

		tbl = tbl->Enter( new LoopFrame( ) );
		tbl = tbl->Enter( new StackFrame( ) );

		tbl->ScopeTrace(std::cout, 1, 10);

		std::cout << "ContinueLoop" << std::endl;
		tbl = tbl->ContinueLoop( 1 );

		tbl->ScopeTrace(std::cout, 1, 10);
	}
	catch ( const char* s ) {
		std::cerr << s << std::endl << "Back trace: " << std::endl;
		tbl->BackTrace(std::cerr, 1, 10);
	}

	tbl->LeaveStack( );

	return 0;
}
