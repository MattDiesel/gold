
#include "../callstack/stackframe.h"
#include "../variant/variant.h"


#ifndef GOLD_PARSER_PRODUCTION_H
#define GOLD_PARSER_PRODUCTION_H


namespace gold {

/// Production abstract base class
class Production {
public:
	virtual ~Production();

	virtual Variant Evaluate( StackFrame* ) = 0;
};


} // namespace gold


#endif
