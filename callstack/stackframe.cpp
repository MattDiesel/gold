
#include <string>
#include <ostream>

#include "../variant/variant.h"
#include "symbol.h"
#include "scopeframe.h"

#include "stackframe.h"

namespace gold {

StackFrame::StackFrame()
		: tail( nullptr ) {
}

StackFrame::~StackFrame() {
}


/// Assigns a value to a symbol on this stack frame
void StackFrame::BlockAssign( const std::string& name, Variant v ) {
	if ( !this->tail ) {
		// Error: Symbol not found
		throw "Symbol not found";
	}

	return( this->tail->BlockAssign( name, v ) );
}

/// Gets the value of a symbol on this stack frame
Variant& StackFrame::BlockEval( const std::string& name ) {
	if ( !this->tail ) {
		// Error: Symbol not found
		throw "Symbol not found";
	}

	return( this->tail->BlockEval( name ) );
}

/// Checks if a symbol is declrared
bool StackFrame::BlockIsDeclared( const std::string& name ) const {
	if ( !this->tail ) {
		// Error: Symbol not found
		throw "Symbol not found";
	}

	return( this->tail->BlockIsDeclared( name ) );
}


/// Enters a new, empty, frame onto the stack
StackFrame* StackFrame::Enter( ) {
	return( this->Enter( nullptr ) );
}

/// Enters a new frame onto the stack
StackFrame* StackFrame::Enter( StackFrame* fr ) {
	if ( !fr ) {
		fr = new ScopeFrame( );
	}

	fr->tail = this;
	return( fr );
}

/// Leaves the stack frame.
StackFrame* StackFrame::Leave( ) {
	StackFrame* top = this->tail;
	delete this;
	return( top );
}

/// Leaves the entire stack.
void StackFrame::LeaveStack( ) {
	StackFrame* t = this->Leave( );

	if ( t ) {
		t->LeaveStack();
	}
}


/// Exits N levels of loop
StackFrame* StackFrame::ExitLoop(int level) {
	if ( !this->tail ) {
		// Error: ExitLoop statement has no matching loop
		throw "ExitLoop statement has no matching loop";
	}

	if (level <= 0) {
		return( this );
	}

	StackFrame* t = this->tail;
	this->Leave();

	return( t->ExitLoop( level ) );
}

/// Continues N levels of loop
StackFrame* StackFrame::ContinueLoop(int level) {
	if ( !this->tail ) {
		// Error: ExitLoop statement has no matching loop
		throw "ExitLoop statement has no matching loop";
	}

	if (level <= 0) {
		return( this );
	}

	StackFrame* t = this->tail;
	this->Leave( );

	return( t->ContinueLoop( level ) );
}

/// Returns from a function
StackFrame* StackFrame::Return() {
	if ( !this->tail ) {
		// Error: Return statement not in function
		throw "Return statement not in function";
	}

	return( this->Leave( ) );
}

/// Calls the next frames BackTrace
void StackFrame::BackTrace(std::ostream& os, int count, int limit) const {
	if ( this->tail ) {
		this->tail->BackTrace(os, count, limit);
	}
}

/// Prints this stack frames line in a back trace.
void StackFrame::ScopeTrace(std::ostream& os, int count, int limit) const {
	os << count << ". Stack frame" << std::endl;

	if ( count < limit && this->tail ) {
		this->tail->ScopeTrace(os, count + 1, limit);
	}
}


} // namespace gold
