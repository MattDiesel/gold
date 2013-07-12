
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


Variant::Variant()
	: variant( nullptr ) {
}

Variant::Variant( VariantBase* bs )
	: variant( bs ) {
	if ( bs ) {
		bs->refInc();
	}
}

Variant::Variant( const Variant& v )
	: variant( v.variant ) {
	if ( this->variant ) {
		this->variant->refInc();
	}
}


Variant::Variant( bool f ) {
	if ( f ) {
		*this = VarTrue;
	}
	else {
		*this = VarFalse;
	}
}

Variant::Variant( int i ) {
	this->variant = new VarNumeric( i );

	if ( this->variant ) {
		this->variant->refInc();
	}
}

Variant::Variant( double d ) {
	this->variant = new VarNumeric( d );

	if ( this->variant ) {
		this->variant->refInc();
	}
}

Variant::Variant( const char* s ) {
	this->variant = new VarString( s );

	if ( this->variant ) {
		this->variant->refInc();
	}
}

Variant::Variant( std::string s ) {
	this->variant = new VarString( s );

	if ( this->variant ) {
		this->variant->refInc();
	}
}


Variant::~Variant() {
	if ( this->variant ) {
		this->variant->refDec();
	}
}


Variant& Variant::operator=( const Variant& v ) {
	return ( *this ) = v.variant;
}

Variant& Variant::operator=( VariantBase* bs ) {
	if ( bs ) {
		bs->refInc();
	}

	if ( this->variant ) {
		this->variant->refDec();
	}

	this->variant = bs;
	return ( *this );
}

VariantBase* Variant::operator->() {
	return( this->variant );
}

const VariantBase* Variant::operator->() const {
	return( this->variant );
}

Variant::operator bool() const {
	return( this->variant );
}






// class VariantBase

VariantBase::VariantBase()
	: refCount( 0 ) {
}

VariantBase::~VariantBase() {
}


void VariantBase::refInc() const {
	this->refCount++;
}

void VariantBase::refDec() const {
	this->refCount--;

	if ( !this->refCount ) {
		delete ( VariantBase* )this;
	}
}


bool VariantBase::IsNumber() const {
	return( false );
}

bool VariantBase::IsInt() const {
	return( false );
}

bool VariantBase::IsFloat() const {
	return( false );
}

bool VariantBase::IsBool() const {
	return( false );
}

bool VariantBase::IsString() const {
	return( false );
}

bool VariantBase::IsArray() const {
	return( false );
}

bool VariantBase::IsMap() const {
	return( false );
}

bool VariantBase::IsTuple() const {
	return( false );
}


Variant& VariantBase::Get( const Variant v ) {
	// throw EvaluateError("Attempt to access a non-collection!");
	throw "Attempt to access a non-collection!";
}

Variant VariantBase::Set( const Variant key, Variant value ) {
	this->Get( key ) = value;
	return( value );
}


Variant VariantBase::Call( Variant v ) {
	// Error: Calling something that isn't a function.
	throw "Calling a non function";
}


bool VariantBase::AsBool() const {
	return( false );
}

std::string VariantBase::AsString() const {
	return( "" );
}

int VariantBase::AsInt() const {
	return( 0 );
}

double VariantBase::AsFloat() const {
	return( 0.0 );
}


Variant VariantBase::ToBool() const {
	return new VarBool( this->AsBool() );
}

Variant VariantBase::ToString() const {
	return new VarString( this->AsString() );
}

Variant VariantBase::ToNumber() const {
	return new VarNumeric( this->AsInt() );
}

Variant VariantBase::ToInt() const {
	return new VarNumeric( this->AsInt() );
}

Variant VariantBase::ToFloat() const {
	return new VarNumeric( this->AsFloat() );
}

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

bool VariantBase::Less::operator()( const Variant& a, const Variant& b ) const {
	return( VariantBase::Compare( a, b ) < 0 );
}

std::ostream& VariantBase::Write( std::ostream& os ) const {
	return( os << this->AsString() );
}


std::ostream& operator<<( std::ostream& os, Variant& v ) {
	return( v->Write( os ) );
}




// class VarNumeric

VarNumeric::VarNumeric( double d ) {
	this->Value = d;
}

VarNumeric::VarNumeric( const std::string& s ) {
	this->Value = std::stod( s );
}

const std::string VarNumeric::typeName( "Number" );
const std::string& VarNumeric::GetType() const {
	return( VarNumeric::typeName );
}

bool VarNumeric::IsNumber() const {
	return( true );
}

bool VarNumeric::IsInt() const {
	return( std::fmod( this->Value, 1.0 ) == 0.0 );
}

bool VarNumeric::IsFloat() const {
	return( !this->IsInt() );
}

bool VarNumeric::AsBool() const {
	return( this->Value != 0.0 );
}

std::string VarNumeric::AsString() const {
	return std::to_string( this->Value );
}

int VarNumeric::AsInt() const {
	return static_cast<int>( this->Value );
}

double VarNumeric::AsFloat() const {
	return this->Value;
}

Variant VarNumeric::ToNumber() const {
	return( Variant( new VarNumeric( this->Value ) ) );
}

std::ostream& VarNumeric::Write( std::ostream& os ) const {
	return os << this->Value;
}

int VarNumeric::Compare( const Variant& a, const Variant& b ) {
	return( basicComparison<double>( a->AsFloat(), b->AsFloat() ) );
}



// class VarBool

VarBool::VarBool( bool d )
	: Value( d ) {
}

VarBool::VarBool( const std::string& s ) {
	this->Value = !s.empty();
}

const std::string VarBool::typeName( "Boolean" );
const std::string& VarBool::GetType() const {
	return( VarBool::typeName );
}

bool VarBool::IsBool() const {
	return( true );
}

bool VarBool::AsBool() const {
	return( this->Value );
}

std::string VarBool::AsString() const {
	return( this->Value ? "true" : "false" );
}

int VarBool::AsInt() const {
	return( this->Value ? 1 : 0 );
}

double VarBool::AsFloat() const {
	return( this->Value ? 1.0 : 0.0 );
}



// class VarString

VarString::VarString( std::string s )
	: Value( s ) {
}

const std::string VarString::typeName( "String" );
const std::string& VarString::GetType() const {
	return( VarString::typeName );
}

bool VarString::IsString() const {
	return( true );
}

bool VarString::AsBool() const {
	return( !this->Value.empty() );
}

std::string VarString::AsString() const {
	return( this->Value );
}

int VarString::AsInt() const {
	return( std::stoi( this->Value ) );
}

double VarString::AsFloat() const {
	return( std::stod( this->Value ) );
}

Variant VarString::ToNumber() const {
	double d = std::stod( this->Value );
	return( Variant( new VarNumeric( d ) ) );
}

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
const std::string& VarArray::GetType() const {
	return( VarArray::typeName );
}


bool VarArray::IsArray() const {
	return( true );
}

Variant& VarArray::Get( int i ) {
	// return(Variant(new VariantBase(this->Value.at(i))));
	return( this->Value.at( i ) );
}

Variant& VarArray::Get( const Variant v ) {
	int i = v->AsInt();
	return( this->Get( i ) );
}

Variant VarArray::Set( int i, Variant v ) {
	this->Get( i ) = v;
	return( v );
}

Variant VarArray::Set( const Variant key, Variant val ) {
	this->Get( key ) = val;
	return( val );
}

bool VarArray::Add( Variant v ) {
	this->Value.push_back( v );
}

bool VarArray::Insert( const Variant v, int i ) {
	this->Value.insert( this->Value.begin() + i, v );
}

bool VarArray::Insert( const Variant v, Variant i ) {
	this->Insert( v, i->AsInt() );
}

bool VarArray::Remove( int i ) {
	this->Value.erase( this->Value.begin() + i );
	return( true );
}

bool VarArray::Remove( const Variant i ) {
	int ind = i->AsInt();
	this->Value.erase( this->Value.begin() + ind );
	return( true );
}

Variant VarArray::Count() {
	return( Variant( new VarNumeric( int( this->Value.size() ) ) ) );
}

std::ostream& VarArray::Write( std::ostream& os ) const {
	os << '[';

	for ( Variant v : this->Value ) {
		v->Write( os );
		os << ( ( v == this->Value.back() ) ? "]" : ", " );
	}

	return( os );
}


// class VarMap

VarMap::VarMap() {
}

const std::string VarMap::typeName( "Map" );
const std::string& VarMap::GetType() const {
	return( VarMap::typeName );
}

bool VarMap::IsMap() const {
	return( true );
}

Variant& VarMap::Get( const Variant key ) {
	return( this->Value.at( key ) );
}

Variant VarMap::Set( const Variant key, Variant val ) {
	if ( this->Value.find( key ) == this->Value.end() ) {
		this->Add( key, val );
	}
	else {
		this->Value.at( key ) = val;
	}

	return( val );
}

bool VarMap::Add( const Variant key, Variant val ) {
	this->Value.insert( std::pair<Variant, Variant>( key, val ) );
	return( true );
}

bool VarMap::Remove( const Variant key ) {
	throw "Not Implemented";
}

Variant VarMap::Count() {
	return( Variant( new VarNumeric( int( this->Value.size() ) ) ) );
}

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
const std::string& VarTuple::GetType() const {
	return( VarTuple::typeName );
}


bool VarTuple::IsArray() const {
	return( false );
}

bool VarTuple::IsTuple() const {
	return( true );
}

std::ostream& VarTuple::Write( std::ostream& os ) const {
	os << '(';

	for ( Variant v : this->Value ) {
		v->Write( os );
		os << ( ( v == this->Value.back() ) ? ")" : ", " );
	}

	return( os );
}


} // namespace gold
