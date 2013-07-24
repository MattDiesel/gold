

#include <string>
#include <ostream>
#include <vector>

#include "variant.h"


#ifndef GOLD_VARIANT_VARARRAY_H
#define GOLD_VARIANT_VARARRAY_H

namespace gold {

/// Variant class for array types
class VarArray : public VariantBase {
public:
	VarArray( int );

	/// Returns the type as a string.
	virtual const std::string& GetType() const;

	/// Returns true.
	virtual bool IsArray() const;

	/// Retrieves the item at the given index
	virtual Variant& Get( const Variant );

	/// Sets the item at the given index
	virtual Variant Set( const Variant, Variant );

	/// Retrieves the item at the given index
	virtual Variant& Get( int );

	/// Sets the item at the given index
	virtual Variant Set( int, Variant );


	/// Adds an item to the array
	bool Add( Variant );

	/// Inserts an item into the array.
	bool Insert( const Variant, int );

	/// Inserts an item into the array.
	bool Insert( const Variant, Variant );

	/// Removes an item from the array
	bool Remove( int );

	/// Removes an item from the array
	bool Remove( const Variant );

	/// Returns the number of items in the array.
	Variant Count();

	/// Writes the string version of the variant to the output stream
	virtual std::ostream& Write( std::ostream& ) const;

	std::vector<Variant> Value;
private:
	/// The type name as returned by GetType()
	static const std::string typeName;
};


} // namespace gold

#endif
