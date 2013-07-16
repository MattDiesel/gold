

#include <string>
#include <ostream>

#include "variant.h"


#ifndef GOLD_VARIANT_VARSTRING_H
#define GOLD_VARIANT_VARSTRING_H

namespace gold {

/// Variant class for strings types
class VarString : public VariantBase {
public:
	/// Creates a new string variant.
	VarString( std::string );

	/// Returns the type as a string.
	virtual const std::string& GetType() const;

	/// Returns true.
	virtual bool IsString() const;

	/// Returns the string as a boolean value.
	/// "" is FALSE, all other values are TRUE.
	virtual bool AsBool() const;

	/// Returns the native string value
	virtual std::string AsString() const;

	/// Returns the string value as an integer.
	/// Non-integer strings return zero
	virtual int AsInt() const;

	/// Returns the string value as a real
	/// Non-numeric string values return zero
	virtual double AsFloat() const;

	/// Returns the string value as a numeric variant.
	/// Non-numeric string values return zero.
	virtual Variant ToNumber() const;

	/// Compares two variants for equality as strings (native version).
	/// Comparison is case insensitive.
	static int Compare( const std::string&, const std::string& );

	/// Compares two variants for equality as strings.
	/// Comparison is case insensitive.
	static int Compare( const Variant&, const Variant& );

	std::string Value;
private:
	/// The type name as returned by GetType()
	static const std::string typeName;
};


} // namespace gold

#endif
