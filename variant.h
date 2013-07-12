
#include <string>
#include <ostream>
#include <sstream>
#include <vector>
#include <map>
#include <memory>

#include <iostream>

#ifndef GOLD_VARIANT_H
#define GOLD_VARIANT_H

namespace gold {

class VariantBase;

/// The variant class.
/// A reference counting pointer wrapper around VariantBase derived objects.
class Variant {
public:

	// Constructors required for ref counting -------------

	/// Creates a new null variant.
	Variant();

	/// Creates a new variant wrapper for the VariantBase derived pointer
	Variant( VariantBase* );

	/// Copies a variant.
	Variant( const Variant& );

	/// Variant destructor. Decrements the reference count.
	~Variant();


	// Convenience constructors ---------------------------

	/// Creates a boolean variant
	Variant( bool );

	/// Creates a numeric variant from an integer
	Variant( int );

	/// Creates a numeric variant
	Variant( double );

	/// Creates a string variant from a literal string
	Variant( const char* );

	/// Creates a string variant.
	Variant( std::string );


	// Assignment (for ref counting) ----------------------

	/// Assigns a variant to another variant.
	Variant& operator=( const Variant& );

	/// Assigns a pointer to a variant.
	/// Allows Variant v = new VarType(args)
	Variant& operator=( VariantBase* );

	// Methods for ref counting ---------------------------

	/// Redirects access from variant to pointer
	VariantBase* operator->();

	/// Const variant.
	const VariantBase* operator->() const;

	/// Allows checking for NULL in the same way as a pointer
	/// if (MyVariant) { ... }
	operator bool() const;

	// Methods working on variant types -------------------
	// TODO

private:
	VariantBase* variant;

};


// Commonly used variants.
extern Variant VarTrue;
extern Variant VarFalse;
extern Variant VarZero;
extern Variant VarEmptyStr;


/// Base variant class.
/// All variant types overload inherit from this class.
class VariantBase {
	friend class Variant;

private:
	// For ref counting -----------------------------------

	mutable int refCount;
protected:
	VariantBase();
	virtual ~VariantBase();

	void refInc() const;
	void refDec() const;

public:
	// Type checking --------------------------------------

	/// Returns the type as a string.
	/// Must be implemented by all derived classes.
	virtual const std::string& GetType() const = 0;

	/// Checks if the Variant is a number
	virtual bool IsNumber() const;

	/// Checks if the Variant is an integer
	virtual bool IsInt() const;

	/// Checks if the Variant is a real number
	virtual bool IsFloat() const;

	/// Checks if the Variant is an Array
	virtual bool IsArray() const;

	/// Checks if the Variant is a map
	virtual bool IsMap() const;

	/// Checks if the Variant is a tuple
	virtual bool IsTuple() const;

	/// Checks if the Variant is a boolean
	virtual bool IsBool() const;

	/// Checks if the Variant is a string
	virtual bool IsString() const;

	// Collection methods ---------------------------------

	/// Retrieves the item at the given index or key
	virtual Variant& Get( const Variant );

	/// Sets the item at the given index or key
	virtual Variant Set( const Variant, Variant );

	// Function methods -----------------------------------

	/// Invokes a function
	virtual Variant Call( Variant );


	// To native types ------------------------------------

	/// Returns the native boolean representation of the variant
	virtual bool AsBool() const;

	/// Returns the native string representation of the variant
	virtual std::string AsString() const;

	/// Returns the native integer representation of the variant
	virtual int AsInt() const;

	/// Returns the native real representation of the variant
	virtual double AsFloat() const;


	// Conversion methods ---------------------------------

	/// Returns the boolean version of the variant
	virtual Variant ToBool() const;

	/// Returns the string version of the variant
	virtual Variant ToString() const;

	/// Returns the number version of the variant
	virtual Variant ToNumber() const;

	/// Returns the integral version of the variant
	virtual Variant ToInt() const;

	/// Returns the real version of the variant.
	virtual Variant ToFloat() const;


	// Comparison functions -------------------------------

	/// Compares two variants
	static int Compare( const Variant&, const Variant& );

	/// Less than operator for STL containers to use.
	struct Less {
		/// Less-Than operator
		bool operator()( const Variant&, const Variant& ) const;
	};

	// Utility methods ------------------------------------

	/// Writes the string version of the variant to the output stream
	virtual std::ostream& Write( std::ostream& ) const;

	// Debugging and diagnostic methods -------------------
	// Todo: Repr?
};


/// Wrapper around VariantBase::Write for use with C++ streams.
std::ostream& operator<<( std::ostream&, Variant& );


/// Variant class for all number types.
class VarNumeric : public VariantBase {
public:

	/// Creates a new Numeric variant.
	/// Same constructor used for all native numeric types
	VarNumeric( double );

	/// Parses a number from a string.
	VarNumeric( const std::string& );


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

/// Variant class for boolean types
class VarBool : public VariantBase {
public:
	/// Creates a new boolean Variant.
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
	static const std::string typeName;
};

/// Variant class for strings types
class VarString : public VariantBase {
public:
	/// Creates a new string variant.
	VarString( std::string );

	/// Returns the type as a string.
	virtual const std::string& GetType() const;

	/// Returns true.
	virtual bool IsString() const;

	virtual bool AsBool() const;
	virtual std::string AsString() const;
	virtual int AsInt() const;
	virtual double AsFloat() const;

	virtual Variant ToNumber() const;

	static int Compare( const Variant&, const Variant& );

	std::string Value;
private:
	static const std::string typeName;
};

/// Variant class for array types
class VarArray : public VariantBase {
public:
	/// Returns the type as a string.
	virtual const std::string& GetType() const;

	/// Returns true.
	virtual bool IsArray() const;

	virtual Variant& Get( const Variant );
	virtual Variant Set( const Variant, Variant );

	virtual Variant& Get( int );
	virtual Variant Set( int, Variant );

	bool Add( Variant );
	bool Insert( const Variant, int );
	bool Insert( const Variant, Variant );
	bool Remove( int );
	bool Remove( const Variant );
	Variant Count();

	virtual std::ostream& Write( std::ostream& ) const;

	std::vector<Variant> Value;
private:
	static const std::string typeName;
};

class VarMap : public VariantBase {
public:
	VarMap();

	/// Returns the type as a string.
	virtual const std::string& GetType() const;

	/// Returns true.
	virtual bool IsMap() const;

	/// Retrieves the item at the given index or key
	virtual Variant& Get( const Variant );

	/// Sets0 the item at the given key
	virtual Variant Set( const Variant, Variant );

	bool Add( const Variant, Variant );
	bool Remove( const Variant );
	Variant Count();

	virtual std::ostream& Write( std::ostream& ) const;

	std::map<Variant, Variant, VariantBase::Less> Value;
private:
	static const std::string typeName;
};

class VarTuple : public VarArray {
public:
	/// Returns the type as a string.
	virtual const std::string& GetType() const;

	/// Returns false.
	virtual bool IsArray() const;

	/// Returns true.
	virtual bool IsTuple() const;

	virtual std::ostream& Write( std::ostream& ) const;

private:
	static const std::string typeName;
};


} // namespace gold

#endif
