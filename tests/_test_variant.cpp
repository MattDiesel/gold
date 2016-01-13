
#include "../variant/variant.h"
#include "../variant/vararray.h"
#include <iostream>




int main() {
	gold::Variant v = new gold::VarArray( 10 );


	v->Append(42);
	v->Append("Hello");

	{
		gold::Variant v2 = new gold::VarArray( 10 );
		v2->Append(12);
		v2->Append("World");

		v->Concat(v2);
	}

	std::cout << v << std::endl;

	return 0;
}
