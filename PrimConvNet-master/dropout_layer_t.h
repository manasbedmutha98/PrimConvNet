//#pragma once
#ifndef PRIM_CNN_DROP
#define PRIM_CNN_DROP

#include "layer_t.h"
#include <stdio.h>

struct dropout_layer_t
{
	int type;
	tensor_t * grads_in;
	tensor_t * in;
	tensor_t * out;
	tensor_t * hitmap;
	float p_activation;
};

struct dropout_layer_t * init_dropout(int in_x, int in_y, int in_z, float p_act){		
	struct dropout_layer_t * layer  = malloc(sizeof(struct dropout_layer_t));
	layer->in = malloc(sizeof(tensor_t));

	//malloc(in_x*in_y*in_z*dizeof(float));
	layer->out = malloc(sizeof(tensor_t));
	layer->hitmap = malloc(sizeof(tensor_t));
	layer->grads_in = malloc(sizeof(tensor_t));
	layer->p_activation = p_act;

	layer->in->size->x = in_x;
	layer->in->size->y = in_y;
	layer->in->size->z = in_z;

	layer->out->size->x = in_x;
	layer->out->size->y = in_y;
	layer->out->size->z = in_z;

	layer->grads_in->size->x = in_x;
	layer->grads_in->size->y = in_y;
	layer->grads_in->size->z = in_z;

	layer->hitmap->size->x = in_x;
	layer->hitmap->size->y = in_y;
	layer->hitmap->size->z = in_z;


	/* Original code
	in( in_size.x, in_size.y, in_size.z ),
	out( in_size.x, in_size.y, in_size.z ),
	hitmap( in_size.x, in_size.y, in_size.z ),
	grads_in( in_size.x, in_size.y, in_size.z ),
	p_activation( p_activation ) */

	return layer;
}	

// int in_x = layer->in->size->x;
// int in_x = layer->in->size->x;

// void activate( tensor_t<float>& in )
// {
// 	this->in = in;
// 	activate();
// }

// If the probability of activation is greater than random number then, activate

void activate(struct dropout_layer_t * layer)
{
	for ( int i = 0; i < layer->in->size->x*layer->in->size->y*layer->in->size->z; i++ )
	{
		int active;
		if (rand()<= layer->p_activation)
			active = 1;
		else
			active = 0;
		layer->hitmap->data[i] = active;
		layer->out->data[i] = active ? layer->in->data[i] : 0.0f;
	}
}


void fix_weights()
{
	
}

// void calc_grads( tensor_t<float>& grad_next_layer )
// {
// 	for ( int i = 0; i < in.size.x*in.size.y*in.size.z; i++ )
// 		grads_in.data[i] = hitmap.data[i] ? grad_next_layer.data[i] : 0.0f;
// }
// #pragma pack(pop)

#endif /*PRIM_CNN_DROP*/