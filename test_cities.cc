#include <fstream>
#include "cities.hh"
#include <iostream>

int test_inOperator(std::ifstream& inStream, Cities& destinationCities){ // Tests taking input to a Cities
	inStream >> destinationCities;
	return 0;
}

int test_outOperator(Cities& citiesObj){ // Tests output of a Cities
	std::cout << citiesObj;
	return 0;
}

int test_total_path_distance(Cities& citiesObj){
	Cities::permutation_t perm = {1, 2, 3};
	double d = citiesObj.total_path_distance(perm);
	std::cout << "total_path_distance: " << d << std::endl;
	return 0;
}

// main() that will accept command line input
int main(int argc, char* argv[]){
	// Ensure filename was given
	if(argc != 2) { throw std::logic_error("Invalid number of arguments. Correct usage: ./<application> <filename>"); }

	std::ifstream in_file;
	std::string in_filename = argv[1];

	in_file.open(argv[1]); // Open filestream
	if (!in_file) {throw std::logic_error{"Failed to open file."}; }

	Cities citiesObject; // Initialize a Cities


	test_inOperator(in_file, citiesObject);
	in_file.close();

	test_outOperator(citiesObject);
	test_total_path_distance(citiesObject);

	return 0;
}

