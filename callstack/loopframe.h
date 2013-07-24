
#include <ostream>

#include "scopeframe.h"


#ifndef GOLD_CALLSTACK_LOOPFRAME_H
#define GOLD_CALLSTACK_LOOPFRAME_H


namespace gold {

/// Generic class for loop scopes on the stack
class LoopFrame : public ScopeFrame {
public:
	/// Creates a new stack frame for a loop
	LoopFrame();

	/// Loop stack frame destructor
	~LoopFrame();

	// Jump functions -------------------------------------
	// These only do the stack management part of these operations.

	/// Exits the loop
	virtual StackFrame* ExitLoop( int );

	/// Continues the loop
	virtual StackFrame* ContinueLoop( int );

	// Debug functions ------------------------------------

	/// Prints this stack frames line in a back trace.
	virtual void ScopeTrace( std::ostream&, int, int ) const;
};


} // namespace gold


#endif
