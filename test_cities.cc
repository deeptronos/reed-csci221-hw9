#include <fstream>
#include "cities.hh"
#include <iostream>

void test_random_permutation(Cities& citiesObj){
	citiesObj.random_permutation(5);
}

void test_reorder(Cities& citiesObj){
	std::cout << "Initial order:\n" << citiesObj << std::endl;
	Cities reorder = citiesObj.reorder({ 3, 2, 4, 0, 1 });
	std::cout << "Re-ordered:\n" << reorder << std::endl;
}

void test_total_path_distance(Cities& citiesObj){
	//Cities::permutation_t perm = {1, 2, 3};
	Cities::permutation_t perm = {0, 1, 2, 3, 4};
	double d = citiesObj.total_path_distance(perm);
	std::cout << "total_path_distance: " << d << std::endl;
}

void test_inOperator(std::ifstream& inStream, Cities& destinationCities){ // Tests taking input to a Cities
	inStream >> destinationCities;
}

void test_outOperator(Cities& citiesObj){ // Tests output of a Cities
	std::cout << citiesObj;
}


// main() that will accept command line input
int main(int argc, char* argv[]){
	// Ensure filename was given
	if(argc != 2) { throw std::logic_error("Invalid number of arguments. Correct usage: ./<application> <filename>"); }

	// Set up files:
	std::ifstream in_file; //New in-file-stream
	std::string in_filename = argv[1];
	in_file.open(argv[1]); // Open filestream
	if (!in_file) {throw std::logic_error{"Failed to open file."}; }


	Cities citiesObject; // Initialize a Cities


	test_inOperator(in_file, citiesObject);
	in_file.close();

	test_outOperator(citiesObject);

	test_total_path_distance(citiesObject);

	test_reorder(citiesObject);

	test_random_permutation(citiesObject);

	return 0;
}

