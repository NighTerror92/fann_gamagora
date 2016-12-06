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
effectue une validation croisée sur pour un ann, retourne le pourcentage de succes
*/
double cross_validate(const std::string input_file, unsigned int nb_validation) {
	std::ifstream input_file_stream = std::ifstream(input_file);

	if (!input_file_stream.is_open())
		return -1;
	
	unsigned int nb_data;

	input_file_stream >> nb_data;

	#undef max //necessaire pour visual studio pour utiliser std::numeric_limits<std::streamsize>::max()
	input_file_stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (nb_data < nb_validation)
		nb_validation = nb_data;

	//creation d'une table de permutation pour selectionner les inputs d'exemple
	unsigned int *permutation_table = new unsigned int[nb_data];
	for (unsigned int i = 0; i < nb_data; ++i)
		permutation_table[i] = i;

	// Initialize a random engine with seed
	std::default_random_engine engine(175632);
	std::shuffle(permutation_table, permutation_table + nb_data, engine);



	return 0.0;
}
