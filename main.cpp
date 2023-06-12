#ifndef __MAIN_CPP__
#define __MAIN_CPP__
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <climits>
#include <cstdlib> //for rand()
#include <cmath> //for sqrt()

#include "entry.hpp"

//Tasks to do in order:
//Implement getData. Done and tested
//Implement feature_search_demo with Forwards Selection. Done but not tested.
//Implement feature_search_demo with Backwards Elimination. Done but not tested.
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

void forwards_selection(std::vector<Entry> data) {
	std::vector<int> currFeatures; //Tracks the current set of features used
	std::vector<int> bestFeatures; //Tracks the set of features used by the highest accuracy feature set
	double bestAccuracy; //Tracks the highest accuracy
	double bestSoFarAccuracy; //Tracks the highest accuracy found so far when considering which features to add
	int featureToAdd; //Tracks the feature with the highest bestSoFarAccuracy
	double currAccuracy; //Tracks the accuracy with currFeatures

	for(int i = 0; i < data.at(0).features.size(); ++i) {
		std::cout << "On level " << i << " of the search tree\n";
		bestSoFarAccuracy = INT_MIN;
		for(int k = 0; k < data.at(0).features.size(); ++k) {
			//checking if not already added
			auto result = std::find(currFeatures.begin(), currFeatures.end(), k);
			if(result != currFeatures.end()) { 
				continue;
			} 
			std::cout << "--Considering adding the " << k << " feature which would give an accuracy of ";
			//Check here during testing. Call with currFeatures
			currFeatures.push_back(k);
			currAccuracy = accuracy();
			currFeatures.pop_back();
			std::cout << currAccuracy << "\n";
			if(currAccuracy > bestSoFarAccuracy) {
				bestSoFarAccuracy = currAccuracy;
				featureToAdd = k;
			}
		}
		currFeatures.push_back(featureToAdd);
		if(bestAccuracy < bestSoFarAccuracy) {
			bestFeatures = currFeatures;
			bestAccuracy = bestSoFarAccuracy;
		}
		std::cout << "On level " << i << " I added " << featureToAdd << " to current set.\n";
		std::cout << "Current feature set is ";
		for(int k = 0; k < currFeatures.size(); ++k) {
			std::cout << currFeatures.at(k) << " ";
		}
		std::cout << "\n";
	}
	
}

void backwards_elimination(std::vector<Entry> data) {
        std::vector<int> currFeatures; //Tracks the current set of features used
        std::vector<int> bestFeatures; //Tracks the set of features used by the highest accuracy feature set
        double bestAccuracy; //Tracks the highest accuracy
        double bestSoFarAccuracy; //Tracks the highest accuracy found so far when considering which features to add
        int featureToRemove; //Tracks the feature with the highest bestSoFarAccuracy
        double currAccuracy; //Tracks the accuracy with currFeatures
	std::vector<int> tempFeatures;
	std::vector<int> temp1;
	for(int i = 0; i < data.at(0).features.size(); ++i) {
		currFeatures.push_back(i);
	}
	temp1 = currFeatures;
        for(int i = 0; i < data.at(0).features.size(); ++i) {
                std::cout << "On level " << i << " of the search tree\n";
                bestSoFarAccuracy = INT_MIN;
                for(int k = 0; k < data.at(0).features.size(); ++k) {
                        //checking if not already added
                        auto result = std::find(currFeatures.begin(), currFeatures.end(), k);
                        if(result == currFeatures.end()) {
                                continue;
                        }
                        std::cout << "--Considering removing the " << k << " feature which would give an accuracy of ";

			
			tempFeatures.clear();
			for(int x = 0; x < currFeatures.size(); ++x) {
				if(currFeatures.at(x) != k) {
					tempFeatures.push_back(currFeatures.at(x));
				}
			}

		
			//call with tempFeatures
                        currAccuracy = accuracy();
			std::cout << currAccuracy << "\n";
                        if(currAccuracy > bestSoFarAccuracy) {
                                bestSoFarAccuracy = currAccuracy;
                                featureToRemove = k;
				temp1 = tempFeatures;
                        }
                }
		currFeatures = temp1;
                if(bestAccuracy < bestSoFarAccuracy) {
                        bestFeatures = currFeatures;
                        bestAccuracy = bestSoFarAccuracy;
                }
                std::cout << "On level " << i << " I removed " << featureToRemove << " from the current set.\n";
                std::cout << "Current feature set is ";
                for(int k = 0; k < currFeatures.size(); ++k) {
                        std::cout << currFeatures.at(k) << " ";
                }
                std::cout << "\n";
        }

}




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
		sstream >> feature;
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
	//forwards_selection(data);
	backwards_elimination(data);
	/*
	for(unsigned i = 0; i < data.size(); ++i) {
		std::cout << "\nEntry #" << i << ":";
		for(unsigned j = 0; j < data.at(i).features.size(); ++j) {
			std::cout << ", " << data.at(i).features.at(j);
		}
	}*/

	}

	float dist =  euclidean(data.at(20).features, data.at(30).features);
	std::cout << "\nEuclidean distance between entry 21 and 31: " << dist<< std::endl;
}




#endif //__MAIN_CPP__
