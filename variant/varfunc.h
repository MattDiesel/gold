
#include <string>
#include <ostream>

#include "../functions/standardsymbols.h"
#include "../callstack/functionframe.h"
#include "variant.h"


#ifndef GOLD_VARIANT_VARFUNC_H
#define GOLD_VARIANT_VARFUNC_H


namespace gold {


class VarFunc : public VariantBase {
public:
	/// Creates a new function variant based on the function pointer.
	VarFunc( StandardFunction );

	/// Returns the type as a string.
	virtual const std::string& GetType() const;

	/// Returns true
	virtual bool IsFunc() const;

	/// Invokes the function
	virtual Variant Call( Variant );

private:
	/// The type name as returned by GetType()
	static const std::string typeName;

	StandardFunction func;
	// FunctionFrame* scope;

};


} // namespace gold


#endif
