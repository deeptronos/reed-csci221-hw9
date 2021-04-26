# reed-csci221-hw9
Written by Cole Nemec

### Implementation Details
Both ```cities.cc``` and ```tsp.cc``` contain thorough commenting throughout their code, and should explain themselves fairly plainly, but here are a few particular details that may be worth including here:
* ```operator>>``` uses an additional helper function, ```getIntFromStream()```, as a means of simplifying the overloading code for my own benefit, since this is the first time I've overloaded ```operator>>```. 
* ```total_path_distance()``` uses an additional helper function as well, ```coordEuclideanDistance2D()```, which returns the distance between two ```coord_t```'s using the formula for 2D Euclidean distance. While this helper function isn't re-used by any other part of the ```Cities``` interface, I chose to separate it from ```total_path_distance()``` to make it easier to identify errors.
* ```random_permutation()``` was made a method of the ```Cities``` class so that it could be called easily whenever a ```Cities``` object is present, however it doesn't rely on any data or other methods present in the ```Cities``` object to which it belongs, of course.
    * Another detail to note: The randomness engine for this function, ```knuth_b```, was chosen because, in one test, it achieved the smallest distance I'd yet seen achieved (the results of that particular test are what ```shortest.gif``` and ```speed.gif``` visualize, actually!). I don't have any applicable further knowledge of randomness that made me select that particular engine, for the record.
#### Stylistic Choices
Anybody reviewing my code here may notice that comments are terminated with punctuation sporadically. Some end in periods, some end in exclamation marks, and some don't end in punctuation at all. None of these differences signify anything about the code or comments themselves, I simply didn't always terminate a comment with a punctuation symbol. 

#### Additional Credits
* Implementation of std::shuffle() partially based upon documentation at [cplusplus.com](http://www.cplusplus.com/reference/algorithm/shuffle/)
* Several lines of code which open an ifstream using a given file (present in ```tsp.cc``` and ```test_cities.cc```) were adapted from code written by Evan Sieden for the prior homework (HW8) that we collaborated on - specifically, from ```encoder.cc``` 