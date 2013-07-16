
#include <string>
#include <ostream>

#include "../variant/variant.h"

#include "symbol.h"


#ifndef GOLD_CALLSTACK_STACKFRAME_H
#define GOLD_CALLSTACK_STACKFRAME_H


namespace gold {


/// A scope on the stack.
class StackFrame {
public:
	typedef std::map<std::string, Symbol> SetType;

	/// Initializes a new, empty, stack frame structure.
	StackFrame();

	/// Destructor for a stack frame
	~StackFrame();


	// Symbol functions -----------------------------------

	/// Defines a variable on this stack frame
	void Define( const std::string&, Variant );

	/// Defines a variable on this stack frame
	virtual void Define( const std::string&, Variant, Symbol::Flags );

	/// Assigns a value to a symbol on this stack frame
	virtual void Assign( const std::string&, Variant );

	/// Gets the value of a symbol on this stack frame
	virtual Variant& Eval( const std::string& );

	/// Gets a reference to a symbol on this stack frame.
	virtual Symbol& Get( const std::string& );

	/// Checks if a symbol is declrared
	virtual bool IsDeclared( const std::string& ) const;


	// Stack functions ------------------------------------

	/// Enters a new, empty, frame onto the stack
	StackFrame* Enter();

	/// Enters a new frame onto the stack
	virtual StackFrame* Enter( StackFrame* );

	/// Leaves the stack frame.
	virtual StackFrame* Leave();


	// Jump functions -------------------------------------
	// These only do the stack management part of these operations.

	/// Exits N levels of loop
	virtual StackFrame* ExitLoop(int);

	/// Continues N levels of loop
	virtual StackFrame* ContinueLoop(int);

	/// Returns from a function
	virtual StackFrame* Return();


	// Debug functions ------------------------------------

	/// Calls the next frames BackTrace
	virtual void BackTrace(std::ostream&, int, int) const;

	/// Prints this stack frames line in a back trace.
	virtual void ScopeTrace(std::ostream&, int, int) const;

	SetType symbols;
	StackFrame* tail;
};


} // namespace gold

#endif
