
#include "../callstack/stackframe.h"
#include "../variant/variant.h"
#include "production.h"


#ifndef GOLD_PARSER_TERMINAL_H
#define GOLD_PARSER_TERMINAL_H


namespace gold {


/// Production abstract base class
class Terminal : public Production {
public:
	Terminal( Variant );

	virtual Variant Evaluate( StackFrame* );
private:
	Variant value;
};


} // namespace gold


#endif
