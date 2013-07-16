

#include <string>
#include <ostream>

#include "variant.h"


#ifndef GOLD_VARIANT_VARBOOL_H
#define GOLD_VARIANT_VARBOOL_H

namespace gold {

/// Variant class for boolean types
class VarBool : public VariantBase {
public:
	/// Creates a new boolean Variant.
	/// This should only be called twice for TRUE and FALSE.
	VarBool( bool );

	/// Creates a new boolean variant from a string value.
	/// Empty strings are FALSE, non empty strings are TRUE.
	VarBool( const std::string& );


	/// Returns the type as a string.
	virtual const std::string& GetType() const;


	/// Returns true.
	virtual bool IsBool() const;


	/// Returns the native boolean representation of the variant
	virtual bool AsBool() const;

	/// Returns the native string representation of the variant
	virtual std::string AsString() const;

	/// Returns the native integer representation of the variant
	virtual int AsInt() const;

	/// Returns the native real representation of the variant
	virtual double AsFloat() const;

	bool Value;
private:
	/// The type name as returned by GetType()
	static const std::string typeName;

	/// The string value of TRUE
	static const std::string strTrue;

	/// The string value of FALSE
	static const std::string strFalse;
};


} // namespace gold

#endif
