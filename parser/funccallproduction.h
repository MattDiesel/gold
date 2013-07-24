
#include "../callstack/stackframe.h"
#include "../variant/variant.h"
#include "production.h"

#ifndef GOLD_PARSER_FUNCCALLPRODUCTION_H
#define GOLD_PARSER_FUNCCALLPRODUCTION_H


namespace gold {


/// Production class for function call
class FuncCallProduction : public Production
{
public:
	FuncCallProduction(Production*, Production*);
	~FuncCallProduction();

	virtual Variant Evaluate( StackFrame* );
private:
	Production* func;
	Production* args;
};


} // namespace gold


#endif
