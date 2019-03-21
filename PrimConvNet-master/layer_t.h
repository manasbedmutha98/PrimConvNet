//#pragma once
//#include "types.h"
#ifndef PRIM_CNN_LAYER
#define PRIM_CNN_LAYER
#include "tensor_t.h"

// #pragma pack(push, 1)

struct layer_t
{
	int layer_type;
	tensor_t* grads_in;
	tensor_t* in;
	tensor_t* out;
};
// #pragma pack(pop)

#endif /* PRIM_CNN_LAYER */
