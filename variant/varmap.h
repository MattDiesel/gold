

#include <string>
#include <ostream>

#include "variant.h"


#ifndef GOLD_VARIANT_VARMAP_H
#define GOLD_VARIANT_VARMAP_H

namespace gold {

/// Variant class for a map (dictionary/associative array etc.)
class VarMap : public VariantBase {
public:
	/// Creates a new, empty, map variant.
	VarMap();

	virtual Variant Copy() const;

	/// Returns the type as a string.
	virtual const std::string& GetType() const;

	/// Returns true.
	virtual bool IsMap() const;

	/// Retrieves the item at the given key
	virtual Variant Get( const Variant );

	/// Sets the item at the given key
	virtual Variant Set( const Variant, Variant );

	/// Adds a variant to the map.
	virtual bool Add( const Variant, Variant );

	/// Removes a variant from the map
	virtual bool Remove( const Variant );

	/// Returns the number of key-value pairs in the map
	virtual Variant Count();

	/// Writes the string version of the variant to the output stream
	virtual std::ostream& Write( std::ostream& ) const;

	std::map<Variant, Variant, VariantBase::Less> Value;
private:
	/// The type name as returned by GetType()
	static const std::string typeName;
};


} // namespace gold

#endif
