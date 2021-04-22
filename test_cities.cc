#include <fstream>
#include "cities.hh"
#include <iostream>

// main() that will accept command line input
int main(int argc, char* argv[]){
	// Ensure filename was given
	if(argc != 2) { throw std::logic_error("Invalid number of arguments. Correct usage: ./<application> <filename>"); }

	std::ifstream in_file;
	std::string in_filename = argv[1];

	in_file.open(argv[1]); // Open filestream
	if (!in_file) {throw std::logic_error{"Failed to open file."}; }

	Cities citiesObject; // Initialize a Cities

	in_file >> citiesObject; // Read contents of in_file into citiesObject


	return 0;
}