
#include <string>
#include <ostream>

#include "../util/cistring.h"
#include "variant.h"

#include "varstring.h"


namespace gold {


// class VarString
const std::string VarString::typeName( "String" );

/// Creates a new string variant.
VarString::VarString( std::string s )
	: Value( s ) {
}

/// Returns the type as a string.
const std::string& VarString::GetType() const {
	return( VarString::typeName );
}

/// Returns true.
bool VarString::IsString() const {
	return( true );
}

/// Returns the string as a boolean value.
/// "" is FALSE, all other values are TRUE.
bool VarString::AsBool() const {
	return( !this->Value.empty() );
}

/// Returns the native string value
std::string VarString::AsString() const {
	return( this->Value );
}

/// Returns the string value as an integer.
/// Non-integer strings return zero
int VarString::AsInt() const {
	return( std::stoi( this->Value ) );
}

/// Returns the string value as a real
/// Non-numeric string values return zero
double VarString::AsFloat() const {
	return( std::stod( this->Value ) );
}

/// Returns the string value as a numeric variant.
/// Non-numeric string values return zero.
Variant VarString::ToNumber() const {
	double d = std::stod( this->Value ); // TODO: Error checking
	return( Variant( d ) );
}

/// Compares two variants for equality as strings (native version).
/// Comparison is case insensitive.
int VarString::Compare( const std::string& s1, const std::string& s2 ) {
	std::size_t l1 = s1.size();
	std::size_t l2 = s2.size();
	std::size_t rlen = std::min( l1, l2 );
	int ret = ci_char_traits::compare( s1.c_str(), s2.c_str(), rlen );

	if ( ret == 0 ) {
		return( basicComparison<std::size_t>( l1, l2 ) );
	}

	return( ret );
}

/// Compares two variants for equality as strings.
/// Comparison is case insensitive.
int VarString::Compare( const Variant& a, const Variant& b ) {
	std::string s1 = a->AsString();
	std::string s2 = b->AsString();

	return( VarString::Compare( s1, s2 ) );
}


} // namespace gold
