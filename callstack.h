
#include <string>
#include <map>
#include <vector>

#include "util/cistring.h"
#include "variant/variant.h"


#ifndef GOLD_CALLSTACK_H
#define GOLD_CALLSTACK_H


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


	// Symbol functions -----------------------------------

	/// Defines a variable on this stack frame
	void Define( const std::string&, Variant );

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


	// Stack functions ------------------------------------

	/// Enters a new, empty, frame onto the stack
	StackFrame* Enter();

	/// Enters a new frame onto the stack
	virtual StackFrame* Enter( StackFrame* );

	/// Leaves the stack frame.
	virtual StackFrame* Leave();


	// Jump functions -------------------------------------
	// These only do the stack management part of these operations.

	/// Exits N levels of loop
	virtual StackFrame* ExitLoop(int);

	/// Continues N levels of loop
	virtual StackFrame* ContinueLoop(int);

	/// Returns from a function
	virtual StackFrame* Return();


	// Debug functions ------------------------------------

	/// Calls the next frames BackTrace
	virtual void BackTrace(std::ostream&, int, int) const;

	/// Prints this stack frames line in a back trace.
	virtual void ScopeTrace(std::ostream&, int, int) const;

	SetType symbols;
	StackFrame* tail;
};


/// A scope on the stack for a function
class FunctionFrame : public StackFrame {
public:
	/// Creates a new stack frame for a function
	FunctionFrame(std::string);

	/// Function stack frame destructor
	~FunctionFrame();

	// Symbol functions -----------------------------------

	/// Gets a reference to a symbol on this stack frame.
	virtual Symbol& Get( const std::string& );

	/// Checks if a symbol is declrared
	virtual bool IsDeclared( const std::string& ) const;

	// Stack functions ------------------------------------

	/// Leaves the stack frame.
	virtual StackFrame* Leave();

	// Jump functions -------------------------------------
	// These only do the stack management part of these operations.

	/// Throws an error, as there is no loop remaining.
	virtual StackFrame* ExitLoop(int);

	/// Throws an error, as there is no loop remaining.
	virtual StackFrame* ContinueLoop(int);

	/// Returns from the function
	virtual StackFrame* Return();

	// Debug functions ------------------------------------

	/// Prints this stack frames line in a back trace.
	virtual void BackTrace(std::ostream&, int, int) const;

	/// Prints this stack frames line in a back trace.
	virtual void ScopeTrace(std::ostream&, int, int) const;

private:
	std::string funcName;
};


/// Generic class for loop scopes on the stack
class LoopFrame : public StackFrame {
public:
	/// Creates a new stack frame for a loop
	LoopFrame();

	/// Loop stack frame destructor
	~LoopFrame();

	// Jump functions -------------------------------------
	// These only do the stack management part of these operations.

	/// Exits the loop
	virtual StackFrame* ExitLoop(int);

	/// Continues the loop
	virtual StackFrame* ContinueLoop(int);

	// Debug functions ------------------------------------

	/// Prints this stack frames line in a back trace.
	virtual void ScopeTrace(std::ostream&, int, int) const;
};


} // namespace gold


#endif
