
#include <string>
#include <ostream>


#ifndef GOLD_VARIANT_VARIANT_H
#define GOLD_VARIANT_VARIANT_H

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

	/// Const version of the above.
	/// Allows const methods to be used on variants.
	const VariantBase* operator->() const;

	/// Allows checking for NULL in the same way as a pointer
	/// if (MyVariant) { ... }
	operator bool() const;

	// Methods working on variant types -------------------
	// TODO

private:
	VariantBase* variant;

};


/// Base variant class.
/// All variant types overload inherit from this class.
class VariantBase {
	friend class Variant;

private:
	// For ref counting -----------------------------------

	mutable int refCount;
protected:
	/// Initializes the ref count for a new variant
	VariantBase();

	/// Increments the ref counter.
	void refInc() const;

	/// Decrements the ref counter.
	/// If this moves the ref count to zero then the variant is deleted.
	void refDec() const;

public:
	// Type checking --------------------------------------

	/// Returns the type as a string.
	/// Must be implemented by all derived classes.
	virtual const std::string& GetType() const = 0;

	/// Checks if the Variant is a boolean
	virtual bool IsBool() const;

	/// Checks if the Variant is a number
	virtual bool IsNumber() const;

	/// Checks if the Variant is an integer
	virtual bool IsInt() const;

	/// Checks if the Variant is a real number
	virtual bool IsFloat() const;

	/// Checks if the Variant is a string
	virtual bool IsString() const;

	/// Checks if the Variant is an Array
	virtual bool IsArray() const;

	/// Checks if the Variant is a map
	virtual bool IsMap() const;

	/// Checks if the Variant is a tuple
	virtual bool IsTuple() const;

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
	/// Returns:
	///    -1 if a < b
	///    1 if a > b
	///    0 if a == b
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
std::ostream& operator<<( std::ostream&, const Variant& );


// Commonly used variants.
extern Variant VarTrue;
extern Variant VarFalse;
extern Variant VarZero;
extern Variant VarEmptyStr;


// TODO: Put this somewhere better:

/// Compares two values of the same type using the comparison operators.
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


} // namespace gold

#endif
