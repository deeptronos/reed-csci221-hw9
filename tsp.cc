#include "cities.hh"

#include <iostream>
#include <fstream>

//Assignment:
//  The main() function reads in a cities file (the filename should be given as the first argument of the program).
//  It then iterates over a fixed number of iterations (say, one million), In each iteration, it generates
//  a new random permutation; evaluates the distance to travel the cities along this ordering;
//  compares it to the best (shortest) distance found so far, and if it's shorter, replaces the cities object with
//  the newly-reordered cities and prints out to the screen the iteration number,
//  followed by a space (or tab) and the total distance of the new path.
//  At the end of the loop, save your city ordering to a file called "shortest.tsv".

Cities::permutation_t generateDefaultPermutation(unsigned size){ // Helper function which generates a "default" permutation_t of ints from 0 to size-1.
	Cities::permutation_t perm;
	for(unsigned i = 0; i < size; ++i){
		perm.push_back(i);
	}
	return perm;
}

void printShortestPermutationUpdate(unsigned& i, double& distance){ // Helper function to print required information when a shortest permutation is found
	std::cout << i << ' ' << distance << std::endl;
}

// main() that will accept command line input
int main(int argc, char* argv[]){
	//Parameters
	unsigned iterations = 1000000;

	// Ensure filename was given
	if(argc != 2) { throw std::logic_error("Invalid number of arguments. Correct usage: ./<application> <filename>"); } // If it wasn't, throw an error.

	// Set up file I/O:
	std::ifstream in_file; // Open new in-filestream
	std::string in_filename = argv[1];
	in_file.open(argv[1]); // Open filestream
	if (!in_file) {throw std::logic_error{"Failed to open file."}; }

	std::ofstream outputFile("shortest.tsv", std::ofstream::out | std::ofstream::trunc); // Open a new out-filestream


	Cities citiesObject = Cities(); // Initialize a Cities

	in_file >> citiesObject; // Read a cities file in to a Cities object

	double shortestDistance = citiesObject.total_path_distance(generateDefaultPermutation(citiesObject.size())); // Initialize shortestDistance to the distance of traversing each city in their order as read from the file.

	for(unsigned i = 0; i < iterations; ++i){
		Cities::permutation_t newPermutation = citiesObject.random_permutation(citiesObject.size()); // Generate a random permutation of cityObject's size().
		double permutationPathDistance = citiesObject.total_path_distance(newPermutation); // Test the distance of traveling this permutation

		if(permutationPathDistance < shortestDistance){ // If this permutation requires less distance than the current shortest...
			shortestDistance = permutationPathDistance; // This is the new shortest distance!

			citiesObject = citiesObject.reorder(newPermutation); //Replace citiesObject with itself, reordered according to the new best permutation.
			printShortestPermutationUpdate(i, shortestDistance); // NOTE: is it really necessary/helpful to condense a single line of printing code to its own function?
		}
	}

	outputFile << citiesObject; // Write citiesObject to shortest.tsv
	return 0;
}