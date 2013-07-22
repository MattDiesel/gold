
#include "../variant/variant.h"
#include "../variant/vararray.h"
#include <iostream>




int main() {
	gold::Variant v = new gold::VarArray( );

	{
		gold::VarArray* a = v.Raw<gold::VarArray>();
		a->Add( 42 );
		a->Add( "Hello" );
		a->Add( "World" );
		a->Add( true );
	}

	std::cout << v << std::endl;

	return 0;
}
