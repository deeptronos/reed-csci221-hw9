#include "cities.hh"
//What's the difference between #include-ing iostream and istream/ostream separately?
#include <iostream>
#include <istream>
#include <ostream

//allow for the reading  / filling of a Cities object from a stream. Choose whether this needs to be a method or a free function.
//When implemented, we should be able to run code like:
	// std::cin >> cities;
std::istream& operator>>(std::istream&, Cities&){ // Read:

}