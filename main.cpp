#ifndef __MAIN_CPP__
#define __MAIN_CPP__
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib> //for rand()
#include <cmath> //for sqrt()

#include "entry.hpp"

//Tasks to do in order:
//Implement getData. DONE
//Implement feature_search_demo with Forwards Selection
//Implement feature_search_demo with Backwards Elimination
//Implement Accuracy/cross-validation.
//Find real-world classification dataset and modify/clean data to work with existing code.

// Helper function to calculate distance in order to find nearest neighbor
// takes features from two data points and returns euclidean distance between them
float euclidean(std::vector<float> x, std::vector<float> y){
	float sum = 0;
	float diff, square;

	for(int i = 0; i < x.size(); i++){
		diff = x.at(i) - y.at(i);
		square = diff*diff;
		sum += square;
 	}

	return sqrt(sum);
}


// Stub functions for accuracy. Will implement later
double accuracy() {
	return rand();
}

//feature_search_demo


//Function takes as input a string containing the name of the .txt file you wish to extract the data from. Outputs the data in the form of a vector of Entries.
//Don't forget that the first feature listed in the Entry is the class. Might change later to store class into a separate variable.
std::vector<Entry> getData(std::string input) {
	std::vector<Entry> toReturn;
	std::ifstream inFS;
	inFS.open(input);
	if(!inFS) {
		std::cout << "Error opening file: " << input << "\n";
		return toReturn;
	}
	float feature;
	Entry tempEntry;
	std::string line;
	while(getline(inFS, line)) {
		std::stringstream sstream(line);
		while(sstream >> feature) {
			tempEntry.features.push_back(feature);
		}
		toReturn.push_back(tempEntry);
		tempEntry.features.clear();
	}
	return toReturn;
}


//Birthdays: 07/21 and 06/21. So that means we would use small dataset 21, large dataset 21, and XXXlarge dataset 13.
int main() {
	std::string input;
	std::cout << "Enter 1 for small dataset, 2 for large dataset, and 3 for XXXlarge dataset.\n";
	std::cin >> input;
	if(input == "1") {
		input = "CS170_small_Data__21.txt";
	} else if(input == "2") {
		input = "CS170_large_Data__21.txt";
	} else if(input == "3") {
		input = "CS170_XXXlarge_Data__13.txt";
	} else {
		std::cout << "ERROR: invalid input.\n";
	}
	std::vector<Entry> data = getData(input);

	for(unsigned i = 0; i < data.size(); ++i) {
		std::cout << "\nEntry #" << i << ":";
		for(unsigned j = 0; j < data.at(i).features.size(); ++j) {
			std::cout << ", " << data.at(i).features.at(j);
		}
	}

	float dist =  euclidean(data.at(20).features, data.at(30).features);
	std::cout << "\nEuclidean distance between entry 21 and 31: " << dist<< std::endl;
}




#endif //__MAIN_CPP__
