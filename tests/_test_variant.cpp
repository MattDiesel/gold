
#include "../variant.h"
#include <iostream>
#include <string>

using namespace gold;

int main() {
	Variant MyMap = new VarMap();
	MyMap->Set( "Hello", "World" );
	MyMap->Set( "Foo", "Bar" );
	std::cout << MyMap << std::endl;
	return 0;
}
