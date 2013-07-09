
#include "../variant.h"
#include <iostream>
#include <string>
#include <typeinfo>

using namespace gold;

int main() {

	Variant v(123);
	Variant v2("Hello");

	{
		Variant v3 = v;

		v2 = v3;
	}

	std::cout << v2 << std::endl;

	return 0;
}
