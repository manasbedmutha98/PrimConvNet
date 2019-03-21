
#ifndef PRIM_CNN_CNN
#define PRIM_CNN_CNN
#include "tensor_t.h"
#include "optimization_method.h"
#include "fc_layer.h"
#include "pool_layer_t.h"
#include "relu_layer_t.h"
#include "conv_layer_t.h"
#include "dropout_layer_t.h"

extern float RAND_MAX = 100;
static void calc_grads( layer_t* layer, tensor_t<float>& grad_next_layer )
{
	switch ( layer->type )
	{
		case 0:
			((conv_layer_t*)layer)->calc_grads( grad_next_layer );
			return;
		case 1:
			((relu_layer_t*)layer)->calc_grads( grad_next_layer );
			return;
		case 2:
			((fc_layer_t*)layer)->calc_grads( grad_next_layer );
			return;
		case 3:
			((pool_layer_t*)layer)->calc_grads( grad_next_layer );
			return;
		case 4:
			((dropout_layer_t*)layer)->calc_grads( grad_next_layer );
			return;
		default:
			assert( false );
	}
}

static void fix_weights( layer_t* layer )
{
	switch ( layer->type )
	{
		case 0:
			((conv_layer_t*)layer)->fix_weights();
			return;
		case 1:
			((relu_layer_t*)layer)->fix_weights();
			return;
		case 2:
			((fc_layer_t*)layer)->fix_weights();
			return;
		case 3:
			((pool_layer_t*)layer)->fix_weights();
			return;
		case 4:
			((dropout_layer_t*)layer)->fix_weights();
			return;
		default:
			assert( false );
	}
}

static void activate( layer_t* layer, tensor_t<float>& in )
{
	switch (layer->type)
	{
		case 0:
			((conv_layer_t*)layer)->activate(in);
			return;
		case 1:
			((relu_layer_t*)layer)->activate(in);
			return;
		case 2:
			((fc_layer_t*)layer)->activate(in);
			return;
		case 3:
			((pool_layer_t*)layer)->activate(in);
			return;
		case 4:
			((dropout_layer_t*)layer)->activate(in);
			return;
		default:
			assert( false );
	}
}
#endif /* PRIM_CNN_CNN */