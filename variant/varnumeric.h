

#include <string>
#include <ostream>

#include "variant.h"


#ifndef GOLD_VARIANT_VARNUMERIC_H
#define GOLD_VARIANT_VARNUMERIC_H

namespace gold {

/// Variant class for all number types.
class VarNumeric : public VariantBase {
public:

	/// Creates a new Numeric variant.
	/// Same constructor used for all native numeric types
	VarNumeric( double );

	/// Parses a number from a string.
	VarNumeric( const std::string& );

	virtual Variant Copy() const;


	/// Returns the type as a string.
	virtual const std::string& GetType() const;


	/// Returns true.
	virtual bool IsNumber() const;

	/// Returns true if the value is integral
	virtual bool IsInt() const;

	/// Returns true if the value is not integral
	virtual bool IsFloat() const;


	/// Returns the native boolean representation of the variant
	/// If Value is 0.0 then this returns FALSE. Otherwise it returns TRUE
	virtual bool AsBool() const;

	/// Returns the native string representation of the variant
	virtual std::string AsString() const;

	/// Returns the native integer representation of the variant
	/// Values are truncated
	virtual int AsInt() const;

	/// Returns the native real representation of the variant
	virtual double AsFloat() const;


	/// Returns the number version of the variant
	/// This overload returns a copy of itself.
	virtual Variant ToNumber() const;


	/// Writes the string version of the variant to the output stream
	virtual std::ostream& Write( std::ostream& ) const;


	/// Compares two Variants using a numeric comparison
	static int Compare( const Variant&, const Variant& );

	/// The stored value.
	double Value;
private:
	/// The type name as returned by GetType()
	static const std::string typeName;
};


} // namespace gold

#endif
