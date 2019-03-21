#ifndef  PRIM_CNN_FCLAYER
#define PRIM_CNN_FCLAYER


#include <math.h>
#include <float.h>
#include <string.h>
#include "layer_t.h"
//#include "tensor.h"
#include "gradient_t.h"
#include <stdio.h>

#pragma push(push,1) //Not sure about its purpose. Check ????

struct fc_layer
{
	//layer_type type = layer_typefc; // check how to write this with manas
	struct tensor_t* grads_in;
	struct tensor_t* in;
	struct tensor_t* out;
	struct tensor_t* weights; // 
	struct gradient_t** gradients ;  // initializing a pointer to an array of pointers to the gradient 
	float*    input;
};


//function to initialize the fc_layer
struct fc_layer* init_fclayer(tdsize* in_size, int out_size )
{		
	struct fc_layer* layer = malloc(sizeof(struct fc_layer));
    layer->in 			= init_tensor( in_size->x, in_size->y, in_size->z ); // initializing the input tensor 
	layer->out 			= init_tensor( out_size, 1, 1 );
	layer->grads_in 	= init_tensor( in_size->x, in_size->y, in_size->z );
	layer->weights    	= init_tensor( in_size->x*in_size->y*in_size->z, out_size, 1 );

	layer->gradients = malloc(out_size*sizeof(struct gradient*)); // allocating  memory to the array of pointer (check if the statement is fine)


	int maxval = in_size->x * in_size->y * in_size->z;

	for ( int i = 0; i < out_size; i++ )
	{	

		//((layer->input)+i) = malloc(sizeof(float)); // allocating memory for each element in the array of floats(giving error,check)
		*((layer->gradients)+i) = malloc(2*sizeof(float)); // allocating memory  for each element in the array of gradients
		for ( int h = 0; h < in_size->x*in_size->y*in_size->z; h++ ){
			//*(get (h, i, 0 ,layer->weights) = 2.19722f / maxval * rand() / ((float) RAND_MAX ));
			float * init_ptr = get(h, i, 0 ,layer->weights);
			*init_ptr = 2.19722f/maxval*rand()/((float) RAND_MAX ); ;
		}
	}// 2.19722f = f^-1(0.9) => x where [1 / (1 + exp(-x) ) = 0.9]

	return layer;
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


// void activate( struct tensor* in, struct fc_layer* fclayer )
// 	{   
// 		fclayer->in =  load_tensor( in);
// 		activate(); //how to use activate function
// 	}

int map( tdsize* d ,struct fc_layer* fclayer) //point also must be converted to a pointer??
	{	

		int x0 = fclayer->in->size->x;
		int y0 = fclayer->in->size->y;

		return d->z * ( x0*y0 ) +
		d->y * (x0) +
			d->x;
	}

void activate(struct tensor_t* in, struct fc_layer* fclayer) //why are there 2 activate functions??
	{
		fclayer->in =  load_tensor(in);
		for ( int n = 0; n < (fclayer->out)->size->x; n++ )
		{
			float inputv = 0;
			for ( int i = 0; i < (fclayer->in)->size->x; i++ ) // attribute of fc layer,in is a pointer pointing to the pointer to a tensor with attribute size
				for ( int j = 0; j < fclayer->in->size->y; j++ )
					for ( int z = 0; z < fclayer->in->size->z; z++ )
					{	tdsize* point;
						point->x = i;
						point->y =j;
						point->z = z;
						int m = map( point, fclayer );
						float* input_p= (get( i, j, z,(fclayer->in)));
						float* weight_p = (get( m, n, 0,fclayer->weights));
						inputv += *input_p * *weight_p;
					}

		*((fclayer->input)+n) = inputv; //input seems to be an array of structures
		float* p = get( n, 0, 0,fclayer->out ) ;

			* p= activator_function( inputv ); //what is the type pf input v??
		}
	}


//below this needs to be changed
	/*void fix_weights(struct fc_layer* fclayer)
	{
		for ( int n = 0; n < fclayer->out->size->x; n++ )
		{
			struct gradient_t* grad = *((fclayer->gradients)+n); 
			for ( int i = 0; i < fclayer->in->size->x; i++)
				for ( int j = 0; j < fclayer->in->size->y; j++ )
					for ( int z = 0; z < fclayer->in->size->z; z++ )
					{	tdsize point;
						point.x = i;
						point.y =j;
						point.z = z;
						int m = map( point,fclayer );
						float* w = get( m, n, 0,fclayer->weights );
						*w = update_weight( *w, grad, i, get(i,j, z ,fclayer->in));// update_weight function of different file
					}
			update_gradient( grad ); //function of different file 
		}
	}
	void calc_grads( struct tensor* grad_next_layer ,struct fc_layer* fclayer)
	{
		memset( fclayer->grads_in->data, 0, fclayer->grads_in->size->x *fclayer->grads_in->size->y*fclayer->grads_in->size->z * sizeof( float ) );
		for ( int n = 0; n < fclayer->out->size->x; n++ )
		{
			struct gradient_t*  slope = *((fclayer->gradients)+n); // gradient structure
			slope->grad = *(get(n, 0, 0, grad_next_layer))  * activator_derivative( ((fclayer->input)+n) ); // acitvating using the pointer to the nth input//what deos grad.grad mean
			for ( int i = 0; i < fclayer->in->size->x; i++ )
				for ( int j = 0; j < fclayer->in->size->y; j++ )
					for ( int z = 0; z < fclayer->in->size->z; z++ )
					{	tdsize point;
						point.x = i;
						point.y =j;
						point.z = z;
						int m = map( point , grad_next_layer);
						*get( i, j, z,fclayer->grads_in ) += slope->grad * (*get( m, n, 0,fclayer->weights));//gradient structure
					}
		}
	}
*/
	#endif /* PRIM_CNN_FCLAYER*/

#pragma pack(pop)