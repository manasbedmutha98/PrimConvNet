//#pragma once
#ifndef PRIM_CNN_CONV
#define PRIM_CNN_CONV

#include "layer_t.h"
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
//#pragma pack(push, 1)

struct filts{
	int size;
	tensor_t ** coeffs;
} filts;

// struct filter_grads{
// 	//
// 	gradient_t grads;
// 	tensor ** f;
// };

typedef struct conv_layer_t
{
	int type;
	tensor_t * grads_in;
	tensor_t * in;
	tensor_t * out;
	struct filts * filters;
	//std::vector<tensor_t> filters;
	//std::vector<tensor_t<gradient_t>> filter_grads;
	uint16_t stride;
	uint16_t extend_filter;
} conv_layer_t;

//9K0CRR-7SR9J9-XD7X7G-G02W03

uint16_t stride, extend_filter, number_filters;
tdsize in_size;

conv_layer_t * init(uint16_t stride_l, uint16_t extend_filter_l, uint16_t number_filters_l, tdsize in_size_l ){
	
	// :
	// conv_layer_t 
	// grads_in( in_size.x, in_size.y, in_size.z ),
	// in( in_size.x, in_size.y, in_size.z ),
	// out(
	// (in_size.x - extend_filter) / stride + 1,
	// 	(in_size.y - extend_filter) / stride + 1,
	// 	number_filters
	// )
	stride = stride_l;
	extend_filter = extend_filter_l;
	number_filters = number_filters_l;
	in_size = in_size_l;

	in_size.x = 3;
	in_size.y = 3;
	in_size.z = 3;
	conv_layer_t * convlayer = malloc(sizeof(conv_layer_t));

	convlayer->in = malloc(in_size.x*in_size.y*in_size.z*sizeof(float));
	convlayer->grads_in = malloc(in_size.x*in_size.y*in_size.z*sizeof(float));
	convlayer->out = malloc( ((in_size.x - extend_filter) / stride + 1) * 
		((in_size.y - extend_filter) / stride + 1) * (number_filters) * sizeof(float));
	convlayer->stride = stride;
	convlayer->extend_filter = extend_filter;

	/*
	//?? What is this
	assert( (float( in_size.x - extend_filter)/ stride + 1)
			==
			((in_size.x - extend_filter)/ stride + 1) );

	assert( (float( in_size.y - extend_filter)/ stride + 1)
			==
			((in_size.y - extend_filter)/ stride + 1) );
	*/

	for (int a = 0; a < number_filters; a++ )
	{
		//Should allocate tensor of dims as parameters as
		// tensor_t t(extend_filter, extend_filter, in_size.z);
		//Currently assigning locally as malloc

		tensor_t * t = malloc(sizeof(tensor_t));
		t->data = malloc(sizeof(float)*extend_filter*extend_filter*in_size.z);

		int maxval = extend_filter * extend_filter * in_size.z;
		printf("%d",maxval);
		for (int i = 0; i < extend_filter; i++)
			for (int j = 0; j < extend_filter; j++)
				for (int z = 0; z < in_size.z; z++)
					//t(i, j, z) = 1.0f / maxval * rand() / float( RAND_MAX );
					//Assume rand max is 100
					t->data[(extend_filter*i+j)*extend_filter+in_size.z] = 1.0f/maxval*rand();///float(100)
		//Add this
		//filters.push_back( t );
	}
	//Figure this out
	// for ( int i = 0; i < number_filters; i++ )
	// {
	// 	tensor_t<gradient_t> t( extend_filter, extend_filter, in_size.z );
	// 	filter_grads.push_back( t );
	// }
	return convlayer;

}

struct tdsize map_to_input(tensor_t * out, int z, int stride)
{
	out->size->x *= stride;
	out->size->y *= stride;
	out->size->z = z;
	return out;
}

typedef struct range_t
{
	int min_x, min_y, min_z;
	int max_x, max_y, max_z;
} range_t;

int normalize_range(float f, int max, int lim_min)
{
	if (f <=0)
		return 0;
	max -= 1;
	if (f>= max)
		return max;

	if (lim_min>0) // left side of inequality
		return ceil(f);
	else
		return floor(f);
}

range_t map_to_output(int x, int y, conv_layer_t * layer)
{
	float a = x;
	float b = y;
	range_t output_range =
	{
		normalize_range((a-extend_filter + 1) / stride, layer->out->size->x, 1),
		normalize_range((b-extend_filter + 1) / stride, layer->out->size->y,1),
		0,
		normalize_range(a / stride, layer->out->size->x, 0),
		normalize_range(b / stride, layer->out->size->y, 0),
		(int)filters.size() - 1,
	};
	return output_range;
}
///
	// void activate(tensor_t& in )
	// {
	// 	this->in = in;
	// 	activate();
	// }

void activate(conv_layer_t * layer, tensor_t * in)
{
	for (int filter = 0; filter < layer->filters->size; filter++)
	{
		tensor_t * filter_data;
		filter_data->data = filters[filter];
		for (int x = 0; x < out.size.x; x++)
		{
			for (int y = 0; y < out.size.y; y++)
			{
				tdsize * mapped = map_to_input({(uint16_t)x, (uint16_t)y, 0 }, 0);
				float sum = 0;
				for ( int i = 0; i < extend_filter; i++ )
					for ( int j = 0; j < extend_filter; j++ )
						for ( int z = 0; z < in->size->z; z++ )
						{
							float f = filter_data( i, j, z );
							float v = in(mapped->x + i, mapped->y + j, z);
							sum += f*v;
						}
				out(x, y, filter) = sum;
			}
		}
	}
}

	// void fix_weights()
	// {
	// 	for ( int a = 0; a < filters.size(); a++ )
	// 		for ( int i = 0; i < extend_filter; i++ )
	// 			for ( int j = 0; j < extend_filter; j++ )
	// 				for ( int z = 0; z < in.size.z; z++ )
	// 				{
	// 					float& w = filters[a].get( i, j, z );
	// 					gradient_t& grad = filter_grads[a].get( i, j, z );
	// 					w = update_weight( w, grad );
	// 					update_gradient( grad );
	// 				}
	// }

	// void calc_grads( tensor_t<float>& grad_next_layer )
	// {

	// 	for ( int k = 0; k < filter_grads.size(); k++ )
	// 	{
	// 		for ( int i = 0; i < extend_filter; i++ )
	// 			for ( int j = 0; j < extend_filter; j++ )
	// 				for ( int z = 0; z < in.size.z; z++ )
	// 					filter_grads[k].get( i, j, z ).grad = 0;
	// 	}

	// 	for ( int x = 0; x < in.size.x; x++ )
	// 	{
	// 		for ( int y = 0; y < in.size.y; y++ )
	// 		{
	// 			range_t rn = map_to_output( x, y );
	// 			for ( int z = 0; z < in.size.z; z++ )
	// 			{
	// 				float sum_error = 0;
	// 				for ( int i = rn.min_x; i <= rn.max_x; i++ )
	// 				{
	// 					int minx = i * stride;
	// 					for ( int j = rn.min_y; j <= rn.max_y; j++ )
	// 					{
	// 						int miny = j * stride;
	// 						for ( int k = rn.min_z; k <= rn.max_z; k++ )
	// 						{
	// 							int w_applied = filters[k].get( x - minx, y - miny, z );
	// 							sum_error += w_applied * grad_next_layer( i, j, k );
	// 							filter_grads[k].get( x - minx, y - miny, z ).grad += in( x, y, z ) * grad_next_layer( i, j, k );
	// 						}
	// 					}
	// 				}
	// 				grads_in( x, y, z ) = sum_error;
	// 			}
	// 		}
	// 	}
#endif /* PRIM_CNN_Conv */