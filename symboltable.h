
#include <string>
#include <map>
#include <vector>

#include "util/cistring.h"
#include "variant/variant.h"


#ifndef GOLD_SYMBOLTABLE_H
#define GOLD_SYMBOLTABLE_H


namespace gold {

class Symbol {
public:
	enum Flags {
		NoFlags = 0,
		Static = 1,
		Const = 2,
		Argument = 4
	};

	Symbol( );
	Symbol( Variant );
	Symbol( Variant, Flags );
	~Symbol();

	bool IsConst() const;
	bool IsStatic() const;

	Flags flags;
	Variant value;
};

class StackFrame {
public:
	typedef std::map<std::string, Symbol> SetType;

	StackFrame();
	~StackFrame();

	void Define( const std::string&, Variant, Symbol::Flags );
	void Assign( const std::string&, Variant );
	Variant& Eval( const std::string& );
	Symbol& Get( const std::string& );
	bool IsDeclared( const std::string& ) const;

	void Leave();

	SetType symbols;
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
	bool IsDeclared( const std::string& ) const;

	void Enter();
	void Enter( StackFrame* );
	void Leave();
	StackFrame* LeaveFrame();

	StackFrame* globalScope;
	std::vector<StackFrame*> scopes;
};


} // namespace gold


#endif
