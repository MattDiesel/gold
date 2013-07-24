
#include <vector>

#include "../variant/variant.h"
#include "../variant/vararray.h"
#include "production.h"

#include "arglistproduction.h"


namespace gold {


// class ArgListProduction

ArgListProduction::ArgListProduction() {
}

ArgListProduction::~ArgListProduction() {
	for (Production* pr : this->elements) {
		delete pr;
	}
}

Variant ArgListProduction::Evaluate() {
	VarArray* ret = new VarArray( this->elements.size( ) );

	for (Production* pr : this->elements) {
		ret->Add( pr->Evaluate( ) );
	}

	return( ret );
}

void ArgListProduction::Add(Production* pr) {
	this->elements.push_back(pr);
}


} // namespace gold
