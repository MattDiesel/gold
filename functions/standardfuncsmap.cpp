
#include <map>
#include <string>

#include "../variant/variant.h"
#include "../variant/varfunc.h"

#include "standardsymbols.h"

#include "math.h"

namespace gold {


std::map<std::string, Variant> Functions = {
	{ "Cos", new VarFunc( &Cos ) },
	{ "Sin", new VarFunc( &Sin ) },
	{ "Tan", new VarFunc( &Tan ) }
};


} // namespace gold
