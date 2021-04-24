#include "cities.hh"
//What's the difference between #include-ing iostream and istream/ostream separately?


#include <string> // std::stoi
#include <cmath> // std::sqrt, std::abs
#include <algorithm> //std::max_element
#include <chrono>
#include <random>

double coordEuclideanDistance2D(Cities::coord_t p1, Cities::coord_t p2){ // Helper function for calculating 2D Euclidean distance given two coord_t's.
	auto within = (double) (std::pow((p2.first - p1.first), 2) + std::pow((p2.second - p1.second), 2)); // cast the contents of the root to doubles, so that we return the type specified by the declaration of total_path_distance
	auto calc = std::sqrt(within);
	return calc;
}

int getIntFromStream(std::istream& iS, char& streamChar){ //Helper function to condense the code contained in operator>>, and for helping me with readability :)

	std::string numStr; //string to store chars within until we convert them to an integer

	while (true) { //Loop until break
		if (streamChar == ' ' || streamChar == iS.eof() ||
		    streamChar == '\n') { break; } // If we encounter a space, an EOF, or a newline, break

		numStr += streamChar; // add the character to numStr
		iS.get(streamChar); // Get next char
	}
	if(!numStr.empty()){ //If numStr isn't empty, we've successfully read an integer into it
		int num = std::stoi(numStr); // Convert numStr to an int
		return num;
	}
	return -1; //Otherwise, return -1
}

//allow for the reading  / filling of a Cities object from a stream. Choose whether this needs to be a method or a free function.
//When implemented, we should be able to run code like:
	// std::cin >> cities;
std::istream& operator>> (std::istream& iS, Cities& c){ // Read: a .tsv file, containing rows formatted as "int int", to populate a vector of pairs (i.e., a cityCollection_t)
	if(!iS){ // Check if iS is a valid istream // SIDENOTE: i'm not sure if we can check a stream this way
		throw std::invalid_argument("Invalid istream.");
	}

	Cities::cityCollection_t cityCollection;
	char in;

	if(iS>>in) { //Attempt to read from the stream into in.


		while (!iS.eof()) { // While we haven't reached the end of file...

			int pair[2] = {-1, -1};

			for (int i = 0; i <= 1; ++i) { // This loop will run twice
				if (iS.eof()) { break; } // If we encounter an EOF, break.

				int num = getIntFromStream(iS, in);

				while(in == ' '|| in=='\n'){ //While in is a space char, get chars from stream, so that we skip past any whitespace
					if(iS.eof()){ // This while() get stuck in an infinite loop unless I check for an EOF !----- COME BACK TO THIS AND FIGURE OUT WHY -------!
			//BEEP BEEP!!! THIS IS UR SECOND REMINDER!
						break;
					}
					iS.get(in);
				}

				pair[i] = num; // Set the i-th entry in pair to our num.

			} // now, pair contains the integers for a coord_t!

			if (pair[0] == -1 || pair[1] == -1) { break; } // if pair is unchanged from its initialization, or perhaps if num failed to read numbers from the stream, break

			Cities::coord_t newCity(pair[0], pair[1]); // make a new coord_t based upon pair.
			cityCollection.push_back(newCity); // Add newCity to cityCollection.

		}

		// Now, we've read everything on the stream that we can into int pairs within cityCollection.
		c.myCities = cityCollection;
		return iS;

	}else{ // If we failed to read from the stream...
		iS.setstate(std::ios_base::failbit); // Register failure.
		return iS;

	}

}

//When implemented, we should be able to run code like:
	// std::cout << cities
std::ostream& operator<< (std::ostream& oS, Cities& c){ //Cities out operator (operator<<)

	if(!oS){ // Check if oS is a valid stream. // SIDENOTE: i'm not sure if we can check a stream this way
		throw std::invalid_argument("Invalid ostream.");
	}
	for(Cities::coord_t city : c.myCities){ // For each city in myCities...
		oS << city.first << ' ' << city.second << '\n'; // Encode the coordinates of a city as "<posX> <posY>\n"
	}

	return oS;
}

// total_path_distance() should compute the total distance of traversing all the cities in the order defined by the permutation.
// Don't forget to add the distance going back from the last city in the permutation to the first one.
double Cities::total_path_distance(const Cities::permutation_t &ordering) const {

	if(*std::max_element(ordering.begin(), ordering.end()) > (myCities.size() - 1)){throw std::logic_error("Permutation includes elements that don't exist within Cities object");} // Make sure that total_path_distance is called with a valid ordering.

	double totalDist = 0;

	for(Cities::permutation_t::size_type i = 0; i < ordering.size(); ++i){
		if(i !=( ordering.size() - 1)){ // If there is an element in ordering after the i-th element...
			totalDist += coordEuclideanDistance2D(Cities::myCities[ordering[i]],Cities::myCities[ordering[i + 1]] ); // Get distance from ordering[i]-th element to the next element specified by ordering[].
		}else{
			totalDist += coordEuclideanDistance2D(Cities::myCities[ordering[i]], Cities::myCities[ordering.front()]); //Get distance from last element specified by ordering[i] to the first element specified by ordering, so that the salesperson completes their trip!
		}
	}
	return totalDist;
	// NOTE: if any element of the ordering permutation specifies a city that doesn't exist within Cities, getting the city at the index specified by that element from myCities will either return coordinates (0, 0), or coordinates of random numbers.
}

Cities Cities::reorder(const Cities::permutation_t &ordering) const {
	Cities reorderedCity;
	for(unsigned int pos:ordering){ //For each element in ordering...
		reorderedCity.myCities.push_back(Cities::myCities[pos]); //Add the city designated by that element to reorderedCity.
	}
	return reorderedCity;
}

Cities::permutation_t Cities::random_permutation(unsigned int len) {
	Cities::permutation_t newPermutation(len); // Initialize a new permutation_t of size len.

	for(unsigned i = 0; i < len; i++){ // Fill the permutation with ints from 0 to len-1.
		newPermutation[i] = i;
	}

	// Generate a time-based seed.
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	// Define random generation engine
	std::knuth_b engine(seed); // I've gotten my shortest distance yet with knuth_b, so, after testing most (if not each) of the random generators (as listed on cplusplus.com), that's why I chose it.

	// shuffle() permutation elements.
	std::shuffle(newPermutation.begin(), newPermutation.end(), engine);

	return newPermutation;
}


