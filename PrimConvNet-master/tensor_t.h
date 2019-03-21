#ifndef PRIM_CNN_TENSOR
#define PRIM_CNN_TENSOR

#include <stdlib.h>
#include "point_t.h"


//defining the structre for initialization method1

//Manas: Defining typedef for now; will refactor later
typedef struct tensor_t
	{

		tdsize* size;
		float* data;
	} tensor_t;


//defining a method to input a tensor into another tensor

 struct tensor_t* init_tensor(x,y,z)	
 {
 	struct tensor_t * t = malloc(sizeof(struct tensor_t*));
    t->data = malloc((x *y *z*sizeof(float)));
	t->size->x = x;
	t->size->y = y;
	t->size->z = z;

	return t;
 }

 struct tensor_t * load_tensor( struct tensor_t * input)
	{
		struct tensor_t* t;

		t = init_tensor(input->size->x, input->size->y, input->size->z);
		

	    for ( int i = 0; i < t->size->x * t->size->y * t->size->z; i++ )
			{

				*((t->data)+i) = *((input->data)+i);
			}
		
		return t;
	}
	

//Adding the the elements of the tensors
   struct tensor_t* add_tensor( struct tensor_t* t, struct tensor_t* other)
	{	
		struct tensor_t* t_sum;

		t_sum = init_tensor(t->size->x,t->size->y,t->size->z);
		
		for ( int i = 0; i < t->size->x * t->size->y * t->size->z; i++ )
			*((t_sum->data)+i) = *((t->data)+i)+*((other->data)+i);
		
		return t_sum;
	}	

//subtracting the elements of t from other
	struct tensor_t* subtract_tensor( struct tensor_t* t, struct tensor_t* other)
	{	
		struct tensor_t* t_sub;
		t_sub = init_tensor(t->size->x,t->size->y,t->size->z);
		t_sub->data = malloc(t->size->x* t->size->x* t->size->x);

		for ( int i = 0; i < t->size->x* t->size->y* t->size->z; i++ )
			*((t_sub->data)+i) = *((t->data)+i) - *((other->data)+i);
		return t_sub;
	}	

// "get" function takes in the coordinates of the point to be obtianed in the tensor and the tensor itslef , returning the memory add
// of the point
	float* get( int _x, int _y, int _z, struct tensor_t* t )
	{	

		assert(_x >= 0 && _y >= 0 && _z >= 0);
		assert(_x < t->size->x && _y < t->size->y && _z < t->size->z);

		return ((t->data)+_z * (t->size->x * t->size->y) +_y * (t->size->x) +_x);       
	}
#endif /* PRIM_CNN_TENSOR */

// Loading the values of a 3D tensor into a tensor
/*static struct tensor* to_tensor( float* vector_3D, int x,y,z )
{	
	   //tensor in which 3D vector is to be loaded
	
	  
	struct tensor* t =  init_tensor(x,y,z); // tensor into which the array will be loaded is initialized
	for ( int i = 0; i < x; i++ )
		for ( int j = 0; j < y; j++ )
			for ( int k = 0; k < z; k++ )
				get(i,j,k,t) = vector_3D[k][j][i];
	return t;
}
*/