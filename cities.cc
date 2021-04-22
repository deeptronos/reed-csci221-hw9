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
		while (in != iS.eof()) {
			int pair[2] = {-1, -1};

			for (int i = 0; i <= 1; ++i) { // This loop will run twice
				if (in == iS.eof()) { break; } // If we encounter an EOF, break

				int num = getIntFromStream(iS, in);

				while(in == ' '|| in=='\n'){ //While in is a space char, get chars from stream, so that we skip past any whitespace
					iS.get(in);
				}

				pair[i] = num; // Set the i-th entry in pair to our num

			} // now, pair contains the integers for a coord_t!

			if (pair[0] == -1 || pair[1] == -1) { break; } // if pair is unchanged from its initialization, break

			Cities::coord_t newCity(pair[0], pair[1]); // make a new coord_t based upon pair
			cityCollection.push_back(newCity); // Add newCity to cityCollection
		}
		// Now, we've read everything on the stream that we can into int pairs within cityCollection
		c.my_Cities = cityCollection;
		return iS;

	}else{ // If we failed to read from the stream...
		iS.setstate(std::ios_base::failbit); // Register failure
		return iS;

	}

}