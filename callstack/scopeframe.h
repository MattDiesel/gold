
#include <string>
#include <ostream>
#include <map>

#include "../variant/variant.h"
#include "stackframe.h"

#include "symbol.h"


#ifndef GOLD_CALLSTACK_SCOPEFRAME_H
#define GOLD_CALLSTACK_SCOPEFRAME_H


namespace gold {


/// A scope on the stack.
class ScopeFrame : public StackFrame {
public:

	/// Initializes a new, empty, stack frame structure.
	ScopeFrame();

	/// Destructor for a stack frame
	~ScopeFrame();

	// Symbol functions -----------------------------------

	/// Defines a variable on this stack frame
	virtual void Define( const std::string&, Variant, Symbol::Flags );

	/// Gets a reference to a symbol on this stack frame.
	virtual Symbol& Get( const std::string& );

	/// Checks if a symbol is declrared
	virtual bool IsDeclared( const std::string& ) const;

protected:
	typedef std::map<std::string, Symbol> SetType;
	SetType symbols;
};


} // namespace gold

#endif
