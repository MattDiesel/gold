
#include "../variant/variant.h"
#include "production.h"

#include "funccallproduction.h"


namespace gold {


// class FuncCallProduction

FuncCallProduction::FuncCallProduction(Production* fn, Production* arg)
		: func(fn), args(arg) {
}

FuncCallProduction::~FuncCallProduction() {
	delete this->func;
	delete this->args;
}

Variant FuncCallProduction::Evaluate() {
	return( this->func->Evaluate( )->Call( this->args->Evaluate( ) ) );
}


} // namespace gold
