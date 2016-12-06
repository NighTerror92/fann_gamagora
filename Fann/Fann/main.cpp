#include <iostream>
#include "training.h"

int main(int argc, char *argv[])
{
	Ann_parameter ann_parameters = Ann_parameter();
	train("xor.data", "xor_float.net", ann_parameters);

/*
	fann_type *calc_out;
	fann_type input[2];

	struct fann *ann = fann_create_from_file("xor_float.net");

	input[0] = -1;
	input[1] = 1;
	calc_out = fann_run(ann, input);

	printf("xor test (%f,%f) -> %f\n", input[0], input[1], calc_out[0]);

	fann_destroy(ann);
<<<<<<< HEAD:Fann/Fann/main.cpp
	getchar();

=======
*/
	return 0;
}
