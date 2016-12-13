#ifndef TRAINING_H
#define TRAINING_H

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <random>
#include <algorithm>
#include "fann\include\fann.h"

struct Ann_parameter {
	unsigned int num_input;
	unsigned int num_output;
	unsigned int num_layers;
	unsigned int num_neurons_hidden;
	float desired_error;
	unsigned int max_epochs;
	unsigned int epochs_between_reports;

	Ann_parameter(unsigned int _num_input = 5,
		unsigned int _num_output = 1,
		unsigned int _num_layers = 3,
		unsigned int _num_neurons_hidden = 5,
		float _desired_error = 0.001,
		unsigned int _max_epochs = 500000,
		unsigned int _epochs_between_reports = 1000
		) : num_input(_num_input), 
			num_output(_num_output),
			num_layers(_num_layers), 
			num_neurons_hidden(_num_neurons_hidden), 
			desired_error(_desired_error), 
			max_epochs(_max_epochs), 
			epochs_between_reports(_epochs_between_reports) {}
};

void train(const std::string input, const std::string output, const Ann_parameter params);

/**
	effectue une validation croisée sur pour un ann, retourne l'erreur quadratique moyenne
*/
double cross_validate(const std::string input_file, unsigned int nb_validation, const Ann_parameter params);

#endif // TRAINING_H
