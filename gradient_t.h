#pragma once


struct gradient_t
{
	float grad;
	float oldgrad;
	// gradient_t()
	// {
	// 	grad = 0;
	// 	oldgrad = 0;
	// };
	
};

struct gradient_t * init_grad(){
	struct gradient_t * gradtsr; 
	//= malloc(sizeof(gradient_t));
	gradtsr->grad = 0;
	gradtsr->oldgrad = 0;
	return gradtsr;
}
