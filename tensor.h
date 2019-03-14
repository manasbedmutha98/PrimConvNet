#import <stdio.h>
#include <point_t.h>


//defining the structre for initialization method1
struct tensor( int _x, int _y, int _z )
	{

		tdsize size;
		float* data;


		data = malloc(_x * _y * _z*sizeof(float));
		size.x = _x;
		size.y = _y;
		size.z = _z;
	};


//defining a method to input a tensor into another tensor

 struct tensor load_tensor( struct tensor input)
	{
		t->data = malloc(input.size.x *input.size.y *input.size.z*sizeof(float));
		memcpy(
			t->data,
			input.data,
			input.size.x *input.size.y *input.size.z * sizeof( T )
		);
		t->size = other.size;

	}

//Adding the the elements of the tensors
   struct tensor add_tensor( struct tensor t, struct tensor other)
	{	
		struct tensor t_sum(t.size.x,t.size.y,t.size.z);
		t_sum.data = malloc(t.size.x*t.size.x*t.size.x)
		
		for ( int i = 0; i < t.size.x * t.size.y * t.size.z; i++ )
			t_sum.data[i] = t.data[i]+other.data[i];
		return t_sum;
	}	

//subtracting the elements of t from other
	struct tensor subtract_tensor( struct tensor t, struct tensor other)
	{	
		struct tensor t_sum(t.size.x,t.size.y,t.size.z);
		t_sum.data = malloc(t.size.x*t.size.x*t.size.x)
		
		for ( int i = 0; i < t.size.x * t.size.y * t.size.z; i++ )
			t_sum.data[i] = t.data[i]-other.data[i];
		return t_sum;
	}	

// "get" function takes in the coordinates of the point to be obtianed in the tensor and the tensor itslef , returning the memory add
// of the point
	float& get( int _x, int _y, int _z, struct tensor t )
	{	

		assert( _x >= 0 && _y >= 0 && _z >= 0 );
		assert( _x < t.data.size.x && _y < t.data.size.y && _z < t.data.size.z );

		return data[
			_z * (t.data.size.x * t.data.size.y) +
				_y * (t.data.size.x) +
				_x
		];
	}


// printing the tensor
	static void print_tensor( struct tensor& data )
 {
	int mx = data.size.x;
	int my = data.size.y;
	int mz = data.size.z;

	for ( int z = 0; z < mz; z++ )
	{  
		printf( "[Dim%d]\n", z );
		for ( int y = 0; y < my; y++ )
		{
			for ( int x = 0; x < mx; x++ )
			{
				printf( "%.2f \t", (float)data.get( x, y, z ) );
			}
			printf( "\n" );
		}
	}
}


// Loading the values of a 3D tensor into a tensor
static tensor to_tensor( float vector_3D )
{	
	   //tensor in which 3D vector is to be loaded
	int x = sizeof(vector_3D[0][0]) / sizeof(vector_3D[0][0][0]);
	
	int y = sizeof(vector_3D[0])/x;

	int z = sizeof(vector_3D)/y;

	struct tensor t( x, y, z );  // tensor into which the array will be loaded is initialized

	for ( int i = 0; i < x; i++ )
		for ( int j = 0; j < y; j++ )
			for ( int k = 0; k < z; k++ )
				get(i,j,k,t) = vector_3D[k][j][i];
	return t;
}