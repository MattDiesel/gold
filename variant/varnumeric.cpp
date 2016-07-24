
#include <string>
#include <ostream>
#include <cmath>

#include "variant.h"

#include "varnumeric.h"


namespace gold {


// class VarNumeric
const std::string VarNumeric::typeName( "Number" );

/// Creates a new Numeric variant.
/// Same constructor used for all native numeric types
VarNumeric::VarNumeric( double d ) {
	this->Value = d;
}

/// Parses a number from a string.
VarNumeric::VarNumeric( const std::string& s ) {
	this->Value = std::stod( s );

	// Todo: Error checking.
}

Variant VarNumeric::Copy() const {
	return new VarNumeric(this->Value);
}

/// Returns the type as a string.
const std::string& VarNumeric::GetType() const {
	return( VarNumeric::typeName );
}


/// Returns true.
bool VarNumeric::IsNumber() const {
	return( true );
}

/// Returns true if the value is integral
bool VarNumeric::IsInt() const {
	return( std::fmod( this->Value, 1.0 ) == 0.0 );
}

/// Returns true if the value is not integral
bool VarNumeric::IsFloat() const {
	return( !this->IsInt() );
}

/// Returns the native boolean representation of the variant
/// If Value is 0.0 then this returns FALSE. Otherwise it returns TRUE
bool VarNumeric::AsBool() const {
	return( this->Value != 0.0 );
}

/// Returns the native string representation of the variant
std::string VarNumeric::AsString() const {
	return std::to_string( this->Value );
}

/// Returns the native integer representation of the variant
/// Values are truncated
int VarNumeric::AsInt() const {
	return static_cast<int>( this->Value );
}

/// Returns the native real representation of the variant
double VarNumeric::AsFloat() const {
	return this->Value;
}

/// Returns the number version of the variant
/// This overload returns a copy of itself.
Variant VarNumeric::ToNumber() const {
	return( this->Value );
}

/// Writes the string version of the variant to the output stream
std::ostream& VarNumeric::Write( std::ostream& os ) const {
	return os << this->Value;
}

/// Compares two Variants using a numeric comparison
int VarNumeric::Compare( const Variant& a, const Variant& b ) {
	return( basicComparison<double>( a->AsFloat(), b->AsFloat() ) );
}


} // namespace gold
