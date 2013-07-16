
#include <ostream>

#include "stackframe.h"

#include "loopframe.h"


namespace gold {


// class LoopFrame

/// Creates a new stack frame for a loop
LoopFrame::LoopFrame() {
}

/// Loop stack frame destructor
LoopFrame::~LoopFrame() {
}

/// Exits the loop
StackFrame* LoopFrame::ExitLoop( int level ) {
	if ( level <= 0 ) {
		return( this );
	}
	else if ( level == 1 ) {
		return( this->Leave() );
	}
	else {
		StackFrame* t = this->tail;

		this->Leave( );

		return( t->ExitLoop( level - 1 ) );
	}
}

/// Continues the loop
StackFrame* LoopFrame::ContinueLoop( int level ) {
	if ( level <= 0 ) {
		return( this );
	}
	else if ( level == 1 ) {
		return( this );
	}
	else {
		StackFrame* t = this->tail;

		this->Leave( );

		return( t->ContinueLoop( level - 1 ) );
	}
}

/// Prints this stack frames line in a back trace.
void LoopFrame::ScopeTrace( std::ostream& os, int count, int limit ) const {
	os << count << ". Loop Frame" << std::endl;

	if ( count < limit && this->tail ) {
		this->tail->ScopeTrace( os, count + 1, limit );
	}
}


} // namespace gold
