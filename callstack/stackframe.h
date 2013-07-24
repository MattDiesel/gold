
#include <string>
#include <ostream>
#include <map>

#include "../variant/variant.h"


#ifndef GOLD_CALLSTACK_STACKFRAME_H
#define GOLD_CALLSTACK_STACKFRAME_H


namespace gold {


/// Abstract base class for a stack frame.
class StackFrame {
public:
	StackFrame();

	virtual ~StackFrame();

	// Symbol functions -----------------------------------

	/// Defines a variable on this stack frame
	virtual void Define( const std::string&, Variant ) = 0;

	/// Assigns a value to a symbol on this stack frame
	virtual void Assign( const std::string&, Variant ) = 0;

	/// Gets the value of a symbol on this stack frame
	virtual Variant& Eval( const std::string& ) = 0;

	/// Checks if a symbol is declrared
	virtual bool IsDeclared( const std::string& ) const = 0;

	/// Assigns a value to a symbol on this stack frame
	virtual void BlockAssign( const std::string&, Variant );

	/// Gets the value of a symbol on this stack frame
	virtual Variant& BlockEval( const std::string& );

	/// Checks if a symbol is declrared
	virtual bool BlockIsDeclared( const std::string& ) const;


	// Stack functions ------------------------------------

	/// Enters a new, empty, frame onto the stack
	StackFrame* Enter();

	/// Enters a new frame onto the stack
	virtual StackFrame* Enter( StackFrame* );

	/// Leaves the stack frame.
	virtual StackFrame* Leave();

	/// Leaves the stack frame.
	void LeaveStack();


	// Jump functions -------------------------------------
	// These only do the stack management part of these operations.

	/// Exits N levels of loop
	virtual StackFrame* ExitLoop( int );

	/// Continues N levels of loop
	virtual StackFrame* ContinueLoop( int );

	/// Returns from a function
	virtual StackFrame* Return();


	// Debug functions ------------------------------------

	/// Calls the next frames BackTrace
	virtual void BackTrace( std::ostream&, int, int ) const;

	/// Prints this stack frames line in a back trace.
	virtual void ScopeTrace( std::ostream&, int, int ) const;

	StackFrame* tail;
};


} // namespace gold

#endif
