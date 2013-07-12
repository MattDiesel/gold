
#include "../variant/variant.h"
#include <iostream>
#include <string>

using namespace gold;

int main() {
	Variant v; // New empty variant

	v->Write(std::cout) << std::endl;

	std::cout << v << std::endl;

	return 0;
}
