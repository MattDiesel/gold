
#include "../variant/variant.h"
#include "../variant/vararray.h"
#include <iostream>




int main() {
	gold::Variant v = new gold::VarArray( 10 ); 

	v->Append(42);

	std::cout << "v->Append(\"Hello\");" << std::endl;
	v->Append("Hello");

	{
		gold::Variant v2 = new gold::VarArray( 10 );
		v2->Append(12);
		v2->Append("World");

		v->Concat(v2);
	}

	std::cout << v << std::endl;

	gold::Variant vcopy = v.Copy();

	std::cout << v->Get(1) << std::endl;
	std::cout << v->Get(1)->Set(1, "test") << std::endl;

	std::cout << v << std::endl;
	std::cout << vcopy << std::endl;

	return 0;
}
