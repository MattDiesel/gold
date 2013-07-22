
#include <string>
#include <ostream>

#include "varnumeric.h"
#include "varbool.h"
#include "varstring.h"

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
Variant::Variant( bool f )
	: variant( nullptr ) {
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
/// If used on a NULL variant, then this is
///   redrected to the empty string variant.
VariantBase* Variant::operator->() {
	if ( !this->variant ) {
		return( VarEmptyStr.variant );
	}

	return( this->variant );
}

/// Const version of the above.
/// Allows const methods to be used on variants.
const VariantBase* Variant::operator->() const {
	if ( !this->variant ) {
		return( VarEmptyStr.variant );
	}

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

/// Checks if the Variant is a tuple
bool VariantBase::IsFunc() const {
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


} // namespace gold
