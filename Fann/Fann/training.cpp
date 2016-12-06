#include "training.h"

void train(const std::string input, const std::string output, const Ann_parameter params)
{
	struct fann *ann = fann_create_standard(params.num_layers, params.num_input, params.num_neurons_hidden, params.num_output);

	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

	fann_train_on_file(ann, input.c_str(), params.max_epochs, params.epochs_between_reports, params.desired_error);
	fann_save(ann, output.c_str());

	fann_destroy(ann);
}

/**
effectue une validation crois�e sur pour un ann, retourne le pourcentage de succes
*/
double cross_validate(const std::string input_file, unsigned int nb_validation) {
/*	std::ifstream input_file_stream = std::ifstream(input_file);

	if (!input_file_stream.is_open())
		return -1;
	
	unsigned int nb_data;

	input_file_stream >> nb_data;
	input_file.
*/
	return 0.0;
}