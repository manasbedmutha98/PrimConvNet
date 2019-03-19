#pragma once
#include <math.h>
#include <float.h>
#include <string.h>
#include "layer_t.h"


#pragma push(push,1) //Not sure about its purpose. Check ????

struct fc_layer
{
	layer_type type = layer_typefc; // check how to write this with manas
	struct tensor* grads_in;
	struct tensor* in;
	struct tensor* out;
	struct tensor* weights; // 
	struct gradient** gradients ;  // initializing a pointer to an array of pointers to the gradient tensors
	float*    input;
}


//function to initialize the fc_layer
struct fc_layer* init_fclayer(tdsize in_size, int out_size )
{		
		struct fc_layer* layer = malloc(sizeof(struct fc_layer));
        layer->in 			= init_tensor( in_size.x, in_size.y, in_size.z ); // initializing the input tensor 
		layer->out 			= init_tensor( out_size, 1, 1 );
		layer->grads_in 	= init_tensor( in_size.x, in_size.y, in_size.z );
		layer->weights    	= init_tensor( in_size.x*in_size.y*in_size.z, out_size, 1 );

		layer-> input= malloc(out_size*sizeof(float)); // allocating  memory to the array of pointer (check if the statement is fine)
		layer->gradients = malloc(out_size*sizeof(struct gradient*)); // allocating  memory to the array of pointer (check if the statement is fine)


		int maxval = in_size.x * in_size.y * in_size.z;

		for ( int i = 0; i < out_size; i++ )
			*((layer->input)+i) = malloc( in_size.x, in_size.y, in_size.z); // allocating memory for each element in the array of tensors
			*((layer->gradients)+i) = malloc(2*sizeof(float)) // allocating memory  for each element in the array of gradients
			for ( int h = 0; h < in_size.x*in_size.y*in_size.z; h++ )
				*(get (h, i, 0 ,weights)) = 2.19722f / maxval * rand() / float( RAND_MAX );
		// 2.19722f = f^-1(0.9) => x where [1 / (1 + exp(-x) ) = 0.9]
	}


float activator_function( float x )
	{
		//return tanhf( x );
		float sig = 1.0f / (1.0f+ exp( -x ));
		return sig;
	}

float activator_derivative( float x )
	{
		//float t = tanhf( x );
		//return 1 - t * t;
		float sig = 1.0f / (1.0f + exp( -x ));
		return sig * (1 - sig);
	}


void activate( struct tensor** in, struct fc_layer* fclayer )
	{   
		fclayer->in = in;
		activate();
	}

int map( point_t d ,struct fc_layer* fclayer) //point also must be converted to a pointer??
	{
		return d.z * ((fclayer->in)->size.x * (fclayer->in)->size.y) +
			d.y * ((fclayer->in)->size.x) +
			d.x;
	}

void activate(struct fc_layer* fclayer) //why are there 2 activate functions??
	{
		for ( int n = 0; n < (fclayer->out)->size.x; n++ )
		{
			float inputv = 0;
//below this is to be changed
			for ( int i = 0; i < (fclayer->in)->size.x; i++ ) // attribute of fc layer,in is a pointer pointing to the pointer to a tensor with attribute size
				for ( int j = 0; j < ((fclayer->in))->size.y; j++ )
					for ( int z = 0; z < ((fclayer->in)+n)->size.z; z++ )
					{
						int m = map( { i, j, z } );
						inputv += *(get( i, j, z,(fclayer->in)) * get( m, n, 0,fclayer->weights );
					}

		*((fclayer->input)+n) = inputv;; //input seems to be an array of structures

			*(get( n, 0, 0,fclayer->out )) = activator_function( inputv ); //what is the type pf input v??
		}
	}


//below this needs to be changed
	void fix_weights(struct fc_layer* fclayer)
	{
		for ( int n = 0; n < fclayer->out->size.x; n++ )
		{
			gradient_t& grad = gradients[n];//not sure about this line
			for ( int i = 0; i < fclayer->in->size.x; i++)
				for ( int j = 0; j < fclayer->in->size.y; j++ )
					for ( int z = 0; z < fclayer->in->size.z; z++ )
					{
						int m = map( { i, j, z},fclayer );
						float& w = get( m, n, 0,fclayer->weight );
						w = update_weight( w, grad, i, get(j, z ,in( )) );// update_weight function of different file
					}

			update_gradient( grad ); //function of different file 
		}
	}

	void calc_grads( struct tensor* grad_next_layer ,struct fc_layer* fclayer)
	{
		memset( fclayer->grads_in->data, 0, fclayer->grads_in->size.x *fclayer->grads_in->size.y*fclayer->grads_in->size.z * sizeof( float ) );
		for ( int n = 0; n < fclayer->out->size.x; n++ )
		{
			gradient_t&  grad = gradients[n]; // gradient structure
			grad->grad = get(n, 0, 0, grad_next_layer)  * activator_derivative( input[n] ); //what deos grad.grad mean

			for ( int i = 0; i < fclayer->in->size.x; i++ )
				for ( int j = 0; j < fclayer->in->size.y; j++ )
					for ( int z = 0; z < fclayer->in->size.z; z++ )
					{
						int m = map( { i, j, z } , grad_next_layer);
						get( i, j, z,fclayer->grads_in ) += grad.grad * get( m, n, 0,fclayer->weights);//gradient structure
					}
		}
	}


#pragma pack(pop)