#include <iostream>
#include "training.h"

int main(int argc, char *argv[])
{
	train("test.data", "test.net");

/*
	fann_type *calc_out;
	fann_type input[2];

	struct fann *ann = fann_create_from_file("xor_float.net");

	input[0] = -1;
	input[1] = 1;
	calc_out = fann_run(ann, input);

	printf("xor test (%f,%f) -> %f\n", input[0], input[1], calc_out[0]);

	fann_destroy(ann);
*/
	return 0;
}
