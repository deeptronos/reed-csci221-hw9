#include "cities.hh"
//What's the difference between #include-ing iostream and istream/ostream separately?


#include <string> // std::stoi

int getIntFromStream(std::istream& iS, char& streamChar){

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
		throw std::invalid_argument("istream is nullptr.");
	}

	Cities::cityCollection_t cityCollection;
	char in;

	if(iS>>in) { //Attempt to read from the stream into in


		while (!iS.eof()) { // While we haven't reached the end of file...

			int pair[2] = {-1, -1};

			for (int i = 0; i <= 1; ++i) { // This loop will run twice
				if (iS.eof()) { printf("EOF on line 53"); break; } // If we encounter an EOF, break

				int num = getIntFromStream(iS, in);

				while(in == ' '|| in=='\n'){ //While in is a space char, get chars from stream, so that we skip past any whitespace
					if(iS.eof()){ // This while() get stuck in an infinite loop unless I check for an EOF
						break;
					}
					iS.get(in);
				}

				pair[i] = num; // Set the i-th entry in pair to our num

			} // now, pair contains the integers for a coord_t!

			if (pair[0] == -1 || pair[1] == -1 || iS.eof()) { break; } // if pair is unchanged from its initialization, or we reach EOF, break

			Cities::coord_t newCity(pair[0], pair[1]); // make a new coord_t based upon pair
			cityCollection.push_back(newCity); // Add newCity to cityCollection

		}

		// Now, we've read everything on the stream that we can into int pairs within cityCollection
		c.myCities = cityCollection;
		return iS;

	}else{ // If we failed to read from the stream...
		iS.setstate(std::ios_base::failbit); // Register failure
		return iS;

	}

}

//When implemented, we should be able to run code like:
	// std::cout << cities
std::ostream& operator<< (std::ostream& oS, Cities& c){

	if(!oS){ // Check if iS is a valid istream // SIDENOTE: i'm not sure if we can check a stream this way
		throw std::invalid_argument("istream is nullptr.");
	}
	for(Cities::coord_t city : c.myCities){ // For each city in myCities...
		oS << city.first << ' ' << city.second << '\n'; // Encode the coordinates of a city as "<posX> <posY>\n"
	}

	return oS;
}

// total_path_distance() should compute the total distance of traversing all the cities in the order defined by the permutation.
// Don't forget to add the distance going back from the last city in the permutation to the first one.
//double Cities::total_path_distance(const Cities::permutation_t &ordering) const {
//	return 0;
//}
//

