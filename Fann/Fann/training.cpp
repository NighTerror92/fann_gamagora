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
effectue une validation croisée sur pour un ann, retourne l'erreur quadratique moyenne
*/
double cross_validate(const std::string input_file, unsigned int nb_validation, const Ann_parameter params) {
	static const char temp_filename[] = "temp_data.data";
	std::ifstream input_file_stream = std::ifstream(input_file);

	if (!input_file_stream.is_open())
		return -1;
	
	unsigned int nb_data;
	unsigned int nb_input;
	unsigned int nb_output;

	input_file_stream >> nb_data >> nb_input >> nb_output;

	struct fann_data_t {
		fann_type *input;
		fann_type *output;
	};

	if (nb_data < nb_validation)
		nb_validation = nb_data;

	fann_data_t *fann_data = new fann_data_t[nb_data];

	//lecture des données dans le fichier
	for (unsigned int i = 0; i < nb_data; ++i) {
		fann_data[i].input = new fann_type[nb_input];
		fann_data[i].output = new fann_type[nb_output];
		for (unsigned int cpt_input = 0; cpt_input < nb_input; ++cpt_input)
			input_file_stream >> fann_data[i].input[cpt_input];
		for (unsigned int cpt_output = 0; cpt_output < nb_output; ++cpt_output)
			input_file_stream >> fann_data[i].output[cpt_output];
	}
	//creation d'une table de permutation pour selectionner les inputs d'exemple
	unsigned int *permutation_table = new unsigned int[nb_data];
	for (unsigned int i = 0; i < nb_data; ++i)
		permutation_table[i] = i;

	// Initialize a random engine with seed
	std::default_random_engine engine(175632);
	std::shuffle(permutation_table, permutation_table + nb_data, engine);

	fann_type square_sum = 0;

	for (unsigned int i = 0; i < nb_validation; ++i) {
		//ecriture des données
		std::ofstream output_file_stream = std::ofstream(temp_filename, std::ios_base::trunc);
		output_file_stream << nb_data - 1 << ' ' << nb_input << ' ' << nb_output << '\n';
		for (unsigned int j = 0; j < nb_data; ++j) {
			if (j != permutation_table[i]) {
				for (unsigned int cpt_input = 0; cpt_input < nb_input; ++cpt_input)
					output_file_stream << fann_data[j].input[cpt_input] << ' ';
				output_file_stream << '\n';
				for (unsigned int cpt_output = 0; cpt_output < nb_output; ++cpt_output)
					output_file_stream << fann_data[j].output[cpt_output] << ' ';
				output_file_stream << '\n';
			}
		}
		output_file_stream.close();
		//creation du reseau de neuronne a tester
		struct fann *ann = fann_create_standard(params.num_layers, params.num_input, params.num_neurons_hidden, params.num_output);

		fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
		fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

		fann_train_on_file(ann, temp_filename, params.max_epochs, params.epochs_between_reports, params.desired_error);

		fann_type *ouptut = fann_run(ann, fann_data[i].input);
		fann_type tmp_sqr = 0;
		for (unsigned int cpt_output = 0; cpt_output < nb_output; ++cpt_output) {
			const fann_type &&tmp = fann_data[i].output[cpt_output] - ouptut[cpt_output];
			tmp_sqr += tmp * tmp;
		}
		square_sum += tmp_sqr / nb_output;
		//destruction du reseau
		fann_destroy(ann);
	}


	//cleanup
	for (unsigned int i = 0; i < nb_validation; ++i) {
		delete[] fann_data[i].input;
		delete[] fann_data[i].output;
	}
	delete[] fann_data;
	delete[] permutation_table;
	return square_sum / nb_validation;
}
