
#include <vector>

#include "../variant/variant.h"
#include "production.h"

#ifndef GOLD_PARSER_ARGLISTPRODUCTION_H
#define GOLD_PARSER_ARGLISTPRODUCTION_H


namespace gold {


/// Production class for function call
class ArgListProduction : public Production
{
public:
	ArgListProduction();
	~ArgListProduction();

	virtual Variant Evaluate();

	virtual void Add(Production*);
private:
	std::vector<Production*> elements;
};


} // namespace gold


#endif

