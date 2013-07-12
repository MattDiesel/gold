
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <ostream>
#include <sstream>

#include "util/cistring.h"

#include "variant.h"

namespace gold {


// Variant constants

// These are the only two boolean variants ever created. Future boolean values
// will reference one of these.
Variant VarTrue( new VarBool( true ) );
Variant VarFalse( new VarBool( false ) );
Variant VarZero( 0.0 );
Variant VarEmptyStr( "" );



// class Variant


/// Creates a new null variant.
Variant::Variant()
	: variant( nullptr ) {
}

/// Creates a new variant wrapper for the VariantBase derived pointer
Variant::Variant( VariantBase* bs )
	: variant( bs ) {
	if ( bs ) {
		bs->refInc();
	}
}

/// Copies a variant.
Variant::Variant( const Variant& v )
	: variant( v.variant ) {
	if ( this->variant ) {
		this->variant->refInc();
	}
}

/// Variant destructor. Decrements the reference count.
Variant::~Variant() {
	if ( this->variant ) {
		this->variant->refDec();
	}
}


/// Creates a boolean variant
Variant::Variant( bool f ) {
	if ( f ) {
		*this = VarTrue;
	}
	else {
		*this = VarFalse;
	}
}

/// Creates a numeric variant from an integer
Variant::Variant( int i ) {
	this->variant = new VarNumeric( i );

	if ( this->variant ) {
		this->variant->refInc();
	}
}

/// Creates a numeric variant
Variant::Variant( double d ) {
	this->variant = new VarNumeric( d );

	if ( this->variant ) {
		this->variant->refInc();
	}
}

/// Creates a string variant from a literal string
Variant::Variant( const char* s ) {
	this->variant = new VarString( s );

	if ( this->variant ) {
		this->variant->refInc();
	}
}

/// Creates a string variant.
Variant::Variant( std::string s ) {
	this->variant = new VarString( s );

	if ( this->variant ) {
		this->variant->refInc();
	}
}


/// Assigns a variant to another variant.
Variant& Variant::operator=( const Variant& v ) {
	return ( *this ) = v.variant;
}

/// Assigns a pointer to a variant.
/// Allows Variant v = new VarType(args)
Variant& Variant::operator=( VariantBase* bs ) {
	// Decrease the ref count on the current variant
	if ( this->variant ) {
		this->variant->refDec();
	}

	// Increase the ref count for the new variant.
	if ( bs ) {
		bs->refInc();
	}

	this->variant = bs;
	return ( *this );
}

/// Redirects access from variant to pointer
VariantBase* Variant::operator->() {
	return( this->variant );
}

/// Const version of the above.
/// Allows const methods to be used on variants.
const VariantBase* Variant::operator->() const {
	return( this->variant );
}

/// Allows checking for NULL in the same way as a pointer
/// if (MyVariant) { ... }
Variant::operator bool() const {
	return( this->variant );
}


// class VariantBase

/// Initializes the ref count for a new variant
VariantBase::VariantBase()
	: refCount( 0 ) {
}

/// Increments the ref counter.
void VariantBase::refInc() const {
	this->refCount++;
}

/// Decrements the ref counter.
/// If this moves the ref count to zero then the variant is deleted.
void VariantBase::refDec() const {
	this->refCount--;

	if ( !this->refCount ) {
		delete ( VariantBase* )this;
	}
}


/// Checks if the Variant is a boolean
bool VariantBase::IsBool() const {
	return( false );
}

/// Checks if the Variant is a number
bool VariantBase::IsNumber() const {
	return( false );
}

/// Checks if the Variant is an integer
bool VariantBase::IsInt() const {
	return( false );
}

/// Checks if the Variant is a real number
bool VariantBase::IsFloat() const {
	return( false );
}

/// Checks if the Variant is a string
bool VariantBase::IsString() const {
	return( false );
}

/// Checks if the Variant is an Array
bool VariantBase::IsArray() const {
	return( false );
}

/// Checks if the Variant is a map
bool VariantBase::IsMap() const {
	return( false );
}

/// Checks if the Variant is a tuple
bool VariantBase::IsTuple() const {
	return( false );
}


/// Retrieves the item at the given index or key
Variant& VariantBase::Get( const Variant v ) {
	// throw EvaluateError("Attempt to access a non-collection!");
	throw "Attempt to access a non-collection!";
}

/// Sets the item at the given index or key
Variant VariantBase::Set( const Variant key, Variant value ) {
	this->Get( key ) = value;
	return( value );
}


/// Invokes a function
Variant VariantBase::Call( Variant v ) {
	// Error: Calling something that isn't a function.
	throw "Calling a non function";
}


/// Returns the native boolean representation of the variant
bool VariantBase::AsBool() const {
	return( false );
}

/// Returns the native string representation of the variant
std::string VariantBase::AsString() const {
	return( "" );
}

/// Returns the native integer representation of the variant
int VariantBase::AsInt() const {
	return( 0 );
}

/// Returns the native real representation of the variant
double VariantBase::AsFloat() const {
	return( 0.0 );
}


/// Returns the boolean version of the variant
Variant VariantBase::ToBool() const {
	return new VarBool( this->AsBool() );
}

/// Returns the string version of the variant
Variant VariantBase::ToString() const {
	return new VarString( this->AsString() );
}

/// Returns the number version of the variant
Variant VariantBase::ToNumber() const {
	return new VarNumeric( this->AsInt() );
}

/// Returns the integral version of the variant
Variant VariantBase::ToInt() const {
	return new VarNumeric( this->AsInt() );
}

/// Returns the real version of the variant.
Variant VariantBase::ToFloat() const {
	return new VarNumeric( this->AsFloat() );
}

/// Compares two values of the same type using the comparison operators.
template<class T>
int basicComparison( T a, T b ) {
	int ret = 0;

	if ( a > b ) {
		ret = 1;
	}
	else if ( a < b ) {
		ret = -1;
	}

	return ret;
}

/// Compares two variants
/// Returns:
///    -1 if a < b
///    1 if a > b
///    0 if a == b
int VariantBase::Compare( const Variant& a, const Variant& b ) {
	int ret;

	if ( a->IsBool() || b->IsBool() ) {
		ret = basicComparison<int>( a->AsBool(), b->AsBool() );
	}
	else if ( a->IsNumber() || b->IsNumber() ) {
		ret = VarNumeric::Compare( a->ToNumber(), b->ToNumber() );
	}
	else {
		ret = VarString::Compare( a->ToString(), b->ToString() );
	}

	return( ret );
}

/// Less-Than operator
bool VariantBase::Less::operator()( const Variant& a, const Variant& b ) const {
	return( VariantBase::Compare( a, b ) < 0 );
}

/// Writes the string version of the variant to the output stream
std::ostream& VariantBase::Write( std::ostream& os ) const {
	return( os << this->AsString() );
}

/// Wrapper around VariantBase::Write for use with C++ streams.
std::ostream& operator<<( std::ostream& os, const Variant& v ) {
	return( v->Write( os ) );
}




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
	return( this );
}

/// Writes the string version of the variant to the output stream
std::ostream& VarNumeric::Write( std::ostream& os ) const {
	return os << this->Value;
}

/// Compares two Variants using a numeric comparison
int VarNumeric::Compare( const Variant& a, const Variant& b ) {
	return( basicComparison<double>( a->AsFloat(), b->AsFloat() ) );
}



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
	double d = std::stod( this->Value );
	return( Variant( new VarNumeric( d ) ) );
}

/// Compares two variants for equality as strings.
/// Comparison is case insensitive.
int VarString::Compare( const Variant& a, const Variant& b ) {
	std::string s1 = a->AsString();
	std::string s2 = b->AsString();
	std::size_t l1 = s1.size();
	std::size_t l2 = s2.size();
	std::size_t rlen = std::min( l1, l2 );
	int ret = ci_char_traits::compare( s1.c_str(), s2.c_str(), rlen );

	if ( ret == 0 ) {
		return( basicComparison<std::size_t>( l1, l2 ) );
	}

	return( ret );
}


// class VarArray
const std::string VarArray::typeName( "Array" );


/// Returns the type as a string.
const std::string& VarArray::GetType() const {
	return( VarArray::typeName );
}


/// Returns true.
bool VarArray::IsArray() const {
	return( true );
}

/// Retrieves the item at the given index
Variant& VarArray::Get( int i ) {
	// return(Variant(new VariantBase(this->Value.at(i))));
	return( this->Value.at( i ) );
}

/// Retrieves the item at the given index
Variant VarArray::Set( int i, Variant v ) {
	this->Get( i ) = v;
	return( v );
}

/// Sets the item at the given index
Variant& VarArray::Get( const Variant v ) {
	int i = v->AsInt();
	return( this->Get( i ) );
}

/// Sets the item at the given index
Variant VarArray::Set( const Variant key, Variant val ) {
	this->Get( key ) = val;
	return( val );
}

/// Adds an item to the array
bool VarArray::Add( Variant v ) {
	this->Value.push_back( v );
}

/// Inserts an item into the array.
bool VarArray::Insert( const Variant v, int i ) {
	this->Value.insert( this->Value.begin() + i, v );
}

/// Inserts an item into the array.
bool VarArray::Insert( const Variant v, Variant i ) {
	this->Insert( v, i->AsInt() );
}

/// Removes an item from the array
bool VarArray::Remove( int i ) {
	this->Value.erase( this->Value.begin() + i );
	return( true );
}

/// Removes an item from the array
bool VarArray::Remove( const Variant i ) {
	int ind = i->AsInt();
	this->Value.erase( this->Value.begin() + ind );
	return( true );
}

/// Returns the number of items in the array.
Variant VarArray::Count() {
	return( Variant( new VarNumeric( int( this->Value.size() ) ) ) );
}

/// Writes the string version of the variant to the output stream
std::ostream& VarArray::Write( std::ostream& os ) const {
	os << '[';

	for ( Variant v : this->Value ) {
		v->Write( os );
		os << ( ( v == this->Value.back() ) ? "]" : ", " );
	}

	return( os );
}


// class VarMap
const std::string VarMap::typeName( "Map" );

/// Creates a new, empty, map variant.
VarMap::VarMap() {
}

/// Returns the type as a string.
const std::string& VarMap::GetType() const {
	return( VarMap::typeName );
}

/// Returns true.
bool VarMap::IsMap() const {
	return( true );
}

/// Retrieves the item at the given key
Variant& VarMap::Get( const Variant key ) {
	return( this->Value.at( key ) );
}

/// Sets the item at the given key
Variant VarMap::Set( const Variant key, Variant val ) {
	if ( this->Value.find( key ) == this->Value.end() ) {
		this->Add( key, val );
	}
	else {
		this->Value.at( key ) = val;
	}

	return( val );
}

/// Adds a variant to the map.
bool VarMap::Add( const Variant key, Variant val ) {
	this->Value.insert( std::pair<Variant, Variant>( key, val ) );
	return( true );
}

/// Removes a variant from the map
bool VarMap::Remove( const Variant key ) {
	throw "Not Implemented";
}

/// Returns the number of key-value pairs in the map
Variant VarMap::Count() {
	return( Variant( new VarNumeric( int( this->Value.size() ) ) ) );
}

/// Writes the string version of the variant to the output stream
std::ostream& VarMap::Write( std::ostream& os ) const {
	os << "{";

	for ( auto iter = this->Value.begin(); iter != this->Value.end(); ++iter ) {
		std::get<0>( *iter )->Write( os );
		os << ": ";
		std::get<1>( *iter )->Write( os );

		if ( &*iter != &*this->Value.rbegin() ) {
			os << ", ";
		}
	}

	os << "}";
	return( os );
}



// class VarTuple
const std::string VarTuple::typeName( "Tuple" );

/// Returns the type as a string.
const std::string& VarTuple::GetType() const {
	return( VarTuple::typeName );
}


/// Returns false.
bool VarTuple::IsArray() const {
	return( false );
}

/// Returns true.
bool VarTuple::IsTuple() const {
	return( true );
}

/// Writes the string version of the variant to the output stream
std::ostream& VarTuple::Write( std::ostream& os ) const {
	os << '(';

	for ( Variant v : this->Value ) {
		v->Write( os );
		os << ( ( v == this->Value.back() ) ? ")" : ", " );
	}

	return( os );
}


} // namespace gold
