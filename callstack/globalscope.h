
#include <string>
#include <ostream>
#include <map>

#include "../variant/variant.h"
#include "stackframe.h"

#include "symbol.h"


#ifndef GOLD_CALLSTACK_GLOBALSCOPE_H
#define GOLD_CALLSTACK_GLOBALSCOPE_H


namespace gold {


/// A scope on the stack.
class GlobalScope : public ScopeFrame {
public:

	/// Initializes a new, empty, stack frame structure.
	GlobalScope();

	/// Destructor for a stack frame
	~GlobalScope();

	// Symbol functions -----------------------------------

	/// Assigns a value to a symbol on this stack frame
	virtual void BlockAssign( const std::string&, Variant );

	/// Gets the value of a symbol on this stack frame
	virtual Variant& BlockEval( const std::string& );

	/// Checks if a symbol is declrared
	virtual bool BlockIsDeclared( const std::string& ) const;
};


} // namespace gold


#endif
