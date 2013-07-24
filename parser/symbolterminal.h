
#include "../callstack/stackframe.h"
#include "../variant/variant.h"
#include "production.h"


#ifndef GOLD_PARSER_SYMBOLTERMINAL_H
#define GOLD_PARSER_SYMBOLTERMINAL_H


namespace gold {


/// Production abstract base class
class SymbolTerminal : public Production {
public:
	SymbolTerminal( std::string );

	virtual Variant Evaluate( StackFrame* );
private:
	std::string name;
};


} // namespace gold


#endif
