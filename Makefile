CXX =g++
CXXFLAGS =-Wall -Wextra -pedantic -Werror -std=c++17 -O0 -g
LDFLAGS=$(CXXFLAGS)
OBJ=$(SRC:.cc=.o)
# Not using directories for organizing source files or anything right now, but the below line can enable that:
#VPATH=src:inc

all: tsp test_cities

cities: cities.o
	$(CXX) $(LDFLAGS) -o $@ $^

tsp: tsp.o cities.o
	$(CXX) $(LDFLAGS) -o $@ $^

test_cities: test_cities.o cities.o
	$(CXX) $(LDFLAGS) -o $@ $^

%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -c -o $@ $<

clean:
	rm -rf *.o tsp test_cities

clean_o: # "make clean_o" removes only the .o files, leaving compiled apps
	rm -rf *.o

#test: all