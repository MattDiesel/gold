
#include <string>
#include <map>
#include <vector>

#include "util/cistring.h"
#include "variant/variant.h"


#ifndef GOLD_SYMBOLTABLE_H
#define GOLD_SYMBOLTABLE_H


namespace gold {

/// Represents an entry in the symbol table.
class Symbol {
public:
	/// Symbol flags
	/// Static and Argument symbols are not deleted when leaving scope.
	enum Flags {
		NoFlags = 0, ///< No extra flags
		Static = 1,  ///< Variable is static to a scope
		Const = 2,   ///< Variable cannot be assigned to.
		Argument = 4 ///< Variable is part of a function parameter list.
	};

	/// Creates a new null symbol.
	Symbol( );

	/// Creates a new symbol for the given variant
	Symbol( Variant );

	/// Creates a new symbol for the given variant with the set flags
	Symbol( Variant, Flags );

	/// Symbol destructor.
	~Symbol();

	/// Returns TRUE if the symbol is static, FALSE otherwise.
	bool IsStatic() const;

	/// Returns TRUE if the symbol is a constant, FALSE otherwise.
	bool IsConst() const;

	/// Returns TRUE if the symbol is an argument, FALSE otherwise.
	bool IsArgument() const;

	Flags flags;
	Variant value;
};

/// A scope on the stack.
class StackFrame {
public:
	typedef std::map<std::string, Symbol> SetType;

	/// Initializes a new, empty, stack frame structure.
	StackFrame();

	/// Destructor for a stack frame
	~StackFrame();

	/// Defines a variable on this stack frame
	virtual void Define( const std::string&, Variant, Symbol::Flags );

	/// Assigns a value to a symbol on this stack frame
	virtual void Assign( const std::string&, Variant );

	/// Gets the value of a symbol on this stack frame
	virtual Variant& Eval( const std::string& );

	/// Gets a reference to a symbol on this stack frame.
	virtual Symbol& Get( const std::string& );

	/// Checks if a symbol is declrared
	virtual bool IsDeclared( const std::string& ) const;

	/// Leaves the stack frame.
	/// This removes any symbols that are not static or arguments.
	virtual void Leave();

	// Debug functions ------------------------------------

	/// Prints this stack frames line in a back trace.
	virtual void BackTraceLine(std::ostream&, int, int) const;

	SetType symbols;
	StackFrame* tail;
};


/// A scope on the stack for a function
class FunctionFrame : public StackFrame
{
public:
	/// Creates a new stack frame for a function
	FunctionFrame(std::string);

	/// Function stack frame destructor
	~FunctionFrame();

	/// Gets a reference to a symbol on this stack frame.
	virtual Symbol& Get( const std::string& );

	/// Checks if a symbol is declrared
	virtual bool IsDeclared( const std::string& ) const;

	// Debug functions ------------------------------------

	/// Prints this stack frames line in a back trace.
	virtual void BackTraceLine(std::ostream&, int, int) const;

	std::string funcName;
};

/// A symbol table.
class SymbolTable {
public:
	/// Creates a new, empty, symbol table
	SymbolTable();

	/// Symbol table destructor.
	~SymbolTable();

	/// Defines a new symbol, on the top stack frame
	void Define( const std::string&, Variant );

	/// Defines a new symbol, on the top stack frame
	void Define( const std::string&, Variant, Symbol::Flags );

	/// Assigns a value to a symbol in the table.
	void Assign( const std::string&, Variant );

	/// Evaluates a symbol in the table.
	Variant& Eval( const std::string& );

	/// Gets a symbol in the table.
	Symbol& Get( const std::string& );

	/// Checks if a symbol is declared
	bool IsDeclared( const std::string& ) const;

	/// Enters into a new empty stack frame
	void Enter();

	/// Enters into a new stack frame
	void Enter( StackFrame* );

	/// Leaves a stack frame and deletes it
	void Leave();

	/// Leaves a stack frame and returns it.
	StackFrame* LeaveFrame();


	StackFrame* globalScope;
	StackFrame* topScope;

	// Debug functions

	/// Prints a back trace of the last 5 stack frames.
	void BackTrace(std::ostream&) const;
};


} // namespace gold


#endif
