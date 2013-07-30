


#include <string>
#include <ostream>
#include <vector>
#include <map>

#include "../variant/variant.h"
#include "../callstack/stackframe.h"
#include "standardfuncsmap.h"

#ifndef GOLD_FUNCTIONS_STANDARDSYMBOLS_H
#define GOLD_FUNCTIONS_STANDARDSYMBOLS_H


namespace gold {


/// A scope for the built in language symbols.
class StandardSymbols : public StackFrame {
public:

	/// Initializes a new, empty, stack frame structure.
	StandardSymbols();

	/// Destructor for a stack frame
	~StandardSymbols();


	// Symbol functions -----------------------------------

	/// Defines a variable on this stack frame
	virtual void Define( const std::string&, Variant );

	/// Assigns a value to a symbol on this stack frame
	virtual void Assign( const std::string&, Variant );

	/// Gets the value of a symbol on this stack frame
	virtual Variant& Eval( const std::string& );

	/// Checks if a symbol is declrared
	virtual bool IsDeclared( const std::string& ) const;


	// Debug functions ------------------------------------

	/// Calls the next frames BackTrace
	virtual void BackTrace( std::ostream&, int, int ) const;

	/// Prints this stack frames line in a back trace.
	virtual void ScopeTrace( std::ostream&, int, int ) const;
};


} // namespace gold

#endif
