#include <fann.h>

int strtoint(const char* str);

/**
 * @brief NeuralNetwork network_file player_score survival_time unmoving_time collision_count wall_count
 * Run a neural network with given arguments.
 * @param argc Number of arguments.
 * @param argv Arguments.
 *
 * @return The result of the neural network which is 0 or 1 on success cases and a negative value in case of error.
 */
int main(int argc, char** argv)
{
	if(argc == 7)
	{
		// Get arguments
		const char* network_file = 		argv[1];
		int 		player_score = 		strtoint(argv[2]);
		int 		survival_time = 	strtoint(argv[3]);
		int 		unmoving_time = 	strtoint(argv[4]);
		int			collision_count = 	strtoint(argv[5]);
		int			wall_count =		strtoint(argv[6]);

		// Create network
		struct fann *network = fann_create_from_file(network_file);
		if(network)
		{
			// Create inputs
			fann_type inputs[5];
			inputs[0] = (float)player_score;
			inputs[1] = (float)survival_time;
			inputs[2] = (float)unmoving_time;
			inputs[3] = (float)collision_count / (float)survival_time;
			inputs[4] = (float)wall_count / (float)survival_time;

			// Run network
			fann_type* output = fann_run(network, inputs);
			int result = output[0] > 0.0f;
			fann_destroy(network);
			return result;
		}
		return -2;
	}
	return -1;
}

/**
 * @brief Convert a string to an integer.
 *
 * @param str The string to convert.
 *
 * @return The numeric representation of the string.
 */
int strtoint(const char* str)
{
	int index = 0;
	int out = 0;
	while(str[index] >= '0' && str[index] <= '9')
	{
		out *= 10;
		out += str[index] - '0';
		index++;
	}
	return index;
}
