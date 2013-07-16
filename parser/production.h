
#include "../variant/variant.h"


#ifndef GOLD_PARSER_PRODUCTION_H
#define GOLD_PARSER_PRODUCTION_H


namespace gold {

/// Production abstract base class
class Production {
public:
	virtual Variant Evaluate() = 0;
};


} // namespace gold


#endif
