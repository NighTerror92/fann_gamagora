#include <iostream>
#include "training.h"

int main(int argc, char *argv[])
{
	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " input_file output_file\n";
		return -1;
	}
		
	
	Ann_parameter ann_parameters = Ann_parameter();
	train(argv[1], argv[2], ann_parameters);

	//pour la cross validation
	//float res = cross_validate(argv[1], 100, ann_parameters);
	//std::cout << "cross validation result: " << res << '\n';
	//getchar();

	return 0;
}
