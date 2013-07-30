
#include <vector>
#include <string>

#include "../variant/variant.h"

#ifndef GOLD_FUNCTIONS_STANDARDFUNCSMAP_H
#define GOLD_FUNCTIONS_STANDARDFUNCSMAP_H


namespace gold {


typedef Variant ( *StandardFunction )( std::vector<Variant> );

extern std::map<std::string, Variant> Functions;


} // namespace gold


#endif
