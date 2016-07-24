
#include <string>
#include <ostream>
#include <vector>

#include "variant.h"
#include "varnumeric.h"

#include "vararray.h"


namespace gold {


// class VarArray
const std::string VarArray::typeName( "Array" );


VarArray::VarArray( int cap )
	: Value( ) {
	this->Value.reserve( cap );
}

// Creates a deep copy of an array.
Variant VarArray::Copy() const {
	Variant ret = new VarArray(this->Value.size());

	for (auto v : this->Value) {
		ret->Append(v.Copy());
	}

	return ret;
}


/// Returns the type as a string.
const std::string& VarArray::GetType() const {
	return( VarArray::typeName );
}


/// Returns true.
bool VarArray::IsArray() const {
	return( true );
}

/// Retrieves the item at the given index
Variant VarArray::Get( int i ) {
	return( this->Value.at( i ) );
}

/// Sets the item at the given index
Variant VarArray::Get( const Variant v ) {
	return( this->Get( v->AsInt() ) );
}

/// Sets the item at the given index
Variant VarArray::Set( const Variant key, Variant val ) {
	this->Set( key->AsInt(), val);
	return( val );
}

/// Sets the item at the given index
Variant VarArray::Set( int key, Variant val ) {
	this->Value.at( key ) = val;
	return( val );
}

/// Appends an item to a collection
bool VarArray::Append( Variant value ) {
	return this->Add(value);
}

/// Concatenates collections
bool VarArray::Concat( Variant value ) {
	if (!value->IsArray()) {
		throw "TODO";
	}

	VarArray* arr = value.Raw<VarArray>();

	this->Value.reserve(this->Value.size() + arr->Value.size());
	this->Value.insert(this->Value.end(), arr->Value.begin(), arr->Value.end());

	return true;
}


/// Adds an item to the array
bool VarArray::Add( Variant v ) {
	this->Value.push_back( v );
	return( true ); // TODO: Error check then return
}

/// Inserts an item into the array.
bool VarArray::Insert( const Variant v, int i ) {
	this->Value.insert( this->Value.begin() + i, v );
	return( true ); // TODO: Error check then return
}

/// Inserts an item into the array.
bool VarArray::Insert( const Variant v, Variant i ) {
	return( this->Insert( v, i->AsInt() ) );
}

/// Removes an item from the array
bool VarArray::Remove( int i ) {
	this->Value.erase( this->Value.begin() + i );
	return( true ); // TODO: Error check the return
}

/// Removes an item from the array
bool VarArray::Remove( const Variant i ) {
	return( this->Remove( i->AsInt() ) );
}

/// Returns the number of items in the array.
Variant VarArray::Count() {
	return( Variant( new VarNumeric( int( this->Value.size() ) ) ) );
}

/// Writes the string version of the variant to the output stream
std::ostream& VarArray::Write( std::ostream& os ) const {
	os << '[';

	for ( auto i = this->Value.begin(); i != this->Value.end(); ++i ) {
		( *i )->Write( os );

		os << ( ( i + 1 == this->Value.end() ) ? "]" : ", " );
	}

	return( os );
}


} // namespace gold
