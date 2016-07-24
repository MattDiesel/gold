
#include <string>
#include <ostream>
#include <map>
#include <utility>

#include "variant.h"

#include "varmap.h"


namespace gold {


// class VarMap
const std::string VarMap::typeName( "Map" );

/// Creates a new, empty, map variant.
VarMap::VarMap() {
}

Variant VarMap::Copy() const {
	VarMap* ret = new VarMap();

	for ( auto iter : this->Value) {
		ret->Value.insert( std::pair<Variant, Variant>( std::get<0>( iter ).Copy(), std::get<1>( iter ).Copy() ) );
	}

	return ret;
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
Variant VarMap::Get( const Variant key ) {
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
	return( true ); // TODO: Error check then return
}

/// Removes a variant from the map
bool VarMap::Remove( const Variant key ) {
	throw "Not Implemented"; // TODO: VarMap::Remove
}

/// Returns the number of key-value pairs in the map
Variant VarMap::Count() {
	return( Variant( int( this->Value.size() ) ) );
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


} // namespace gold
