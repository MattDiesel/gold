
#include <string>
#include <ostream>

#include "variant.h"

#include "varbool.h"


namespace gold {


// class VarBool
const std::string VarBool::typeName( "Boolean" );
const std::string VarBool::strTrue( "true" );
const std::string VarBool::strFalse( "false" );

/// Creates a new boolean Variant.
VarBool::VarBool( bool d )
	: Value( d ) {
}

/// Creates a new boolean variant from a string value.
/// Empty strings are FALSE, non empty strings are TRUE.
VarBool::VarBool( const std::string& s ) {
	this->Value = !s.empty();
}

/// Returns the type as a string.
const std::string& VarBool::GetType() const {
	return( VarBool::typeName );
}

/// Returns true.
bool VarBool::IsBool() const {
	return( true );
}

/// Returns the native boolean representation of the variant
bool VarBool::AsBool() const {
	return( this->Value );
}

/// Returns the native string representation of the variant
std::string VarBool::AsString() const {
	return( this->Value ? VarBool::strTrue : VarBool::strFalse );
}

/// Returns the native integer representation of the variant
int VarBool::AsInt() const {
	return( this->Value ? 1 : 0 );
}

/// Returns the native real representation of the variant
double VarBool::AsFloat() const {
	return( this->Value ? 1.0 : 0.0 );
}


} // namespace gold
