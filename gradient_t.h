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

struct gradient_t * initialize(int grad, int oldgrad){
	struct gradient_t * gradtsr; 
	//= malloc(sizeof(gradient_t));
	gradtsr->grad = grad;
	gradtsr->oldgrad = oldgrad;
	return gradtsr;
}