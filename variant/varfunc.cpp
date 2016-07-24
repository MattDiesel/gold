
#include <string>
#include <vector>

#include "variant.h"
#include "vararray.h"

#include "varfunc.h"

namespace gold {


// class VarFunc
const std::string VarFunc::typeName( "Function" );


VarFunc::VarFunc( StandardFunction fn )
	: func( fn ) {
}

Variant VarFunc::Copy() const {
	return new VarFunc(this->func);
}

/// Returns the type as a string.
const std::string& VarFunc::GetType() const {
	return( VarFunc::typeName );
}

/// Returns true.
bool VarFunc::IsFunc( ) const {
	return( true );
}


/// Calls the function
Variant VarFunc::Call( Variant args ) {
	if ( !args->IsArray( ) ) {
		throw "Not Implemented: Non array argument lists";
	}

	return( this->func( ( args.Raw<VarArray>( ) )->Value ) );
}


} // namespace gold
