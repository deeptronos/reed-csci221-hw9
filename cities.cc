#include "cities.hh"
//What's the difference between #include-ing iostream and istream/ostream separately?
#include <iostream>
#include <istream>
#include <ostream

#include <string> // std::stoi

//allow for the reading  / filling of a Cities object from a stream. Choose whether this needs to be a method or a free function.
//When implemented, we should be able to run code like:
	// std::cin >> cities;
std::istream& operator>>(std::istream& iS, Cities& c){ // Read: a .tsv file, containing rows formatted as "int int", to populate a vector of pairs (i.e., a cityCollection_t)
	if(iS == nullptr){ // Check if iS is a valid istream
		return nullptr;
	}

	Cities::cityCollection_t cityCollection;
	char in;
	iS.get(in); // Read the first char from the stream

	while(in != eof()) {

		int pair[2] = -1, -1;

		for (int i = 0; i <= 1; i++) {
			if(in == eof()){break;} // If we encounter an EOF, break

			std::string numStr;

			while (true) { //Loop until break
				if (in == ' ' || in == of() ||
				    in == '\n') { break } // If we encounter a space, an EOF, or a newline, break

				numStr += in; // add in to numStr
				iS.get(in); // Get next char
			}
			int num = std::stoi(numStr); // Convert numStr to an int
			pair[i] = num; // Set the i-th entry in pair to our num
		} // now, pair contains the integers for a coord_t!
		if(pair[0] == -1 || pair[1] == -1){break;} // if pair is unchanged from its initialization, break

		Cities::coord_t newCity(pair[0], pair[1]); // make a new coord_t based upon pair
		cityCollection.push_back(newCity); // Add newCity to cityCollection
	}

//	while(true){ //Loop will run until we break from it
//		if(in == eof()) { break; }// If we've just read in an EOF character, break!
//		else{
//			int num;
//			std::string numStr;
//
//			while( in != ' ' && in != '\n'){ // Get char from stream and store it in char in, until we reach a space char (' ') or a newline
//				numStr += in; // add char in to numStr
//				iS.get(in); // Read a char from the stream
//			}
//			if(in == ' '){ // If we've read in a space character...
//				while(in == ' '){ // Read from the stream until we read a non-space character
//					iS.get(in);
//				}
//			}else if(in == '\n') { // If we've read in a newline...
//
//			}
//		}
//
//	}




	if(iS>>i){ // Did we succeed at reading an int into i?

	}

}