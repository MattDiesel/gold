
#include <string>
#include <map>
#include <vector>

#include "util/cistring.h"
#include "variant.h"


#ifndef GOLD_SYMBOLTABLE_H
#define GOLD_SYMBOLTABLE_H


namespace gold {


class Symbol {
public:
	enum Flags {
		NoFlags = 0,
		Static = 1,
		Const = 2
	};

	Symbol( Variant );
	Symbol( Variant, Flags );
	~Symbol();

	bool IsConst();
	bool IsStatic();

	Flags flags;
	Variant value;
};

class StackFrame {
public:
	StackFrame();
	~StackFrame();

	void Define( const std::string&, Variant, Symbol::Flags );
	void Assign( const std::string&, Variant );
	Variant& Eval( const std::string& );
	Symbol& Get( const std::string& );
	bool IsDeclared( const std::string& );

	std::map<std::string, Symbol> symbols;
};


class SymbolTable {
public:

	SymbolTable();
	~SymbolTable();

	void Define( const std::string&, Variant );
	void Define( const std::string&, Variant, Symbol::Flags );
	void Assign( const std::string&, Variant );
	Variant& Eval( const std::string& );
	Symbol& Get( const std::string& );
	bool IsDeclared( const std::string& );

	void Enter();
	void Enter( StackFrame* );
	void Leave();
	StackFrame* LeaveFrame();

	StackFrame* globalScope;
	std::vector<StackFrame*> scopes;
};


} // namespace gold


#endif
