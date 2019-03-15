//#pragma once
//#include "types.h"
#include "tensor_t.h"

// #pragma pack(push, 1)

struct layer_t
{
	int layer_type;
	tensor_t grads_in;
	tensor_t in;
	tensor_t out;
};
// #pragma pack(pop)