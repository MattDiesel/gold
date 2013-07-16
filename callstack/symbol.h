
#include "../variant/variant.h"

#ifndef GOLD_CALLSTACK_SYMBOL_H
#define GOLD_CALLSTACK_SYMBOL_H

namespace gold {

/// Represents an entry in the symbol table.
class Symbol {
public:
	/// Symbol flags
	/// Static and Argument symbols are not deleted when leaving scope.
	enum Flags {
		NoFlags = 0, ///< No extra flags
		Static = 1,  ///< Variable is static to a scope
		Const = 2,   ///< Variable cannot be assigned to.
		Argument = 4 ///< Variable is part of a function parameter list.
	};

	/// Creates a new null symbol.
	Symbol( );

	/// Creates a new symbol for the given variant
	Symbol( Variant );

	/// Creates a new symbol for the given variant with the set flags
	Symbol( Variant, Flags );

	/// Symbol destructor.
	~Symbol();

	/// Returns TRUE if the symbol is static, FALSE otherwise.
	bool IsStatic() const;

	/// Returns TRUE if the symbol is a constant, FALSE otherwise.
	bool IsConst() const;

	/// Returns TRUE if the symbol is an argument, FALSE otherwise.
	bool IsArgument() const;

	Flags flags;
	Variant value;
};


} // namespace gold


#endif
