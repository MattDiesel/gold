
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
	return( this->Leave() );
}

/// Continues the loop
StackFrame* LoopFrame::ContinueLoop( int level ) {
	return( this->Leave() );
}

/// Prints this stack frames line in a back trace.
void LoopFrame::ScopeTrace( std::ostream& os, int count, int limit ) const {
	os << count << ". Loop Frame" << std::endl;

	if ( count < limit && this->tail ) {
		this->tail->ScopeTrace( os, count + 1, limit );
	}
}


} // namespace gold
