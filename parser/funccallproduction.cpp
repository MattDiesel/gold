
#include "../callstack/stackframe.h"
#include "../variant/variant.h"
#include "production.h"

#include "funccallproduction.h"


namespace gold {


// class FuncCallProduction

FuncCallProduction::FuncCallProduction( Production* fn, Production* arg )
	: func( fn ), args( arg ) {
}

FuncCallProduction::~FuncCallProduction() {
	delete this->func;
	delete this->args;
}

Variant FuncCallProduction::Evaluate( StackFrame* fr ) {
	return( this->func->Evaluate( fr )->Call( this->args->Evaluate( fr ) ) );
}


} // namespace gold
