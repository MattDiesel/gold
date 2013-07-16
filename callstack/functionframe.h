
#include <string>
#include <ostream>

#include "stackframe.h"
#include "symbol.h"


#ifndef GOLD_CALLSTACK_FUNCTIONFRAME_H
#define GOLD_CALLSTACK_FUNCTIONFRAME_H


namespace gold {


/// A scope on the stack for a function
class FunctionFrame : public StackFrame {
public:
	/// Creates a new stack frame for a function
	FunctionFrame(std::string);

	/// Function stack frame destructor
	~FunctionFrame();

	// Symbol functions -----------------------------------

	/// Gets a reference to a symbol on this stack frame.
	virtual Symbol& Get( const std::string& );

	/// Checks if a symbol is declrared
	virtual bool IsDeclared( const std::string& ) const;

	// Stack functions ------------------------------------

	/// Leaves the stack frame.
	virtual StackFrame* Leave();

	// Jump functions -------------------------------------
	// These only do the stack management part of these operations.

	/// Throws an error, as there is no loop remaining.
	virtual StackFrame* ExitLoop(int);

	/// Throws an error, as there is no loop remaining.
	virtual StackFrame* ContinueLoop(int);

	/// Returns from the function
	virtual StackFrame* Return();

	// Debug functions ------------------------------------

	/// Prints this stack frames line in a back trace.
	virtual void BackTrace(std::ostream&, int, int) const;

	/// Prints this stack frames line in a back trace.
	virtual void ScopeTrace(std::ostream&, int, int) const;

private:
	std::string funcName;
};


} // namespace gold


#endif
