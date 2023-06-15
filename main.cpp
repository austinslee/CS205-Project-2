#ifndef __MAIN_CPP__
#define __MAIN_CPP__
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <climits>
#include <cmath> //for sqrt()

#include "entry.hpp"

//Tasks to do in order:
//Implement getData. Implemented. Tested.
//Implement feature_search_demo with Forwards Selection. Implemented. Tested.
//Implement feature_search_demo with Backwards Elimination. Implemented. Tested.
//Implement Accuracy/cross-validation. Implemented. Tested.
//Find real-world classification dataset and modify/clean data to work with existing code.


// Accuracy function. Determines accuracy of our classifier using leave-one-out evaluation
double accuracy(std::vector<Entry> data, std::vector<int> currentSet) {
	double num_correctly_classified = 0;
	bool within;
	for(int i = 0; i < data.size(); ++i) {
		double nn_distance = std::numeric_limits<double>::max();
		Entry object_to_classify;
		for(int k = 0; k < data.size(); ++k) {
			if(k != i) {
				double distance = 0.0;
				for(int x = 0; x < data.at(0).features.size();++x) {
					auto it = std::find(currentSet.begin(), currentSet.end(), x);
					if(it != currentSet.end()) {
						distance += pow(data.at(i).features.at(x) - data.at(k).features.at(x), 2);                  
					}
				}
				distance = sqrt(distance);
				if(distance < nn_distance) {
					nn_distance = distance;
					object_to_classify = data.at(k);
				}
			}
		}
		if(object_to_classify.classification == data.at(i).classification) {
			num_correctly_classified++;
		}
	}
	return num_correctly_classified / data.size();
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
			currAccuracy = accuracy(data, currFeatures);
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
		else{
			std::cout << "Accuracy went down. stopping search"<< std::endl;
			break;
		}

		std::cout << "On level " << i << " I added " << featureToAdd << " to current set.\n";
		std::cout << "Current feature set is ";
		for(int k = 0; k < currFeatures.size(); ++k) {
			std::cout << currFeatures.at(k) << " ";
		}
		std::cout << "\n";

	}
	std::cout << "\nHighest accuracy: " << bestAccuracy << "\n";
	std::cout << "Using feature set: ";
	for(int i = 0; i < bestFeatures.size(); ++i) {
		std::cout << bestFeatures.at(i) << ", ";
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
                        currAccuracy = accuracy(data, tempFeatures);
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
				else{
					std::cout << "Accuracy went down. stopping search"<< std::endl;
					break;
				}
                std::cout << "On level " << i << " I removed " << featureToRemove << " from the current set.\n";
                std::cout << "Current feature set is ";
				if(currFeatures.empty()) {
					std::cout << "empty.";
				} else {
	                for(int k = 0; k < currFeatures.size(); ++k) {
        	                std::cout << currFeatures.at(k) << " ";
                	}
				}
                std::cout << "\n";
        }
        std::cout << "\nHighest accuracy: " << bestAccuracy << "\n";
        std::cout << "Using feature set: ";
        for(int i = 0; i < bestFeatures.size(); ++i) {
                std::cout << bestFeatures.at(i) << ", ";
        }

}




//Function takes as input a string containing the name of the .txt file you wish to extract the data from. Outputs the data in the form of a vector of Entries.
//Don't forget that the first feature listed in the Entry is the class. Might change later to store class into a separate variable.
std::vector<Entry> getData(std::string input) {
	std::vector<Entry> toReturn;
	int numFeatures = 0;
	int numInstances = 0;
	bool track = true;
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
		++numInstances;
		std::stringstream sstream(line);
		sstream >> feature;
		tempEntry.classification = feature;
		while(sstream >> feature) {
			if(track == true) {
				++numFeatures;
			}
			tempEntry.features.push_back(feature);
		}
		track = false;
		toReturn.push_back(tempEntry);
		tempEntry.features.clear();
	}
	std::cout << "This dataset has " << numFeatures << " features (not including the class attribute), with " << numInstances << " instances.\n";
	return toReturn;
}


//Birthdays: 07/21 and 06/21. So that means we would use small dataset 21, large dataset 21, and XXXlarge dataset 13.
int main() {
	std::string input;
	std::cout << "Enter 1 for small dataset, 2 for large dataset, 3 for XXXlarge dataset, or 4 for real-world dataset.\n";
	std::cin >> input;
	if(input == "1") {
		input = "CS170_small_Data__21.txt";
	} else if(input == "2") {
		input = "CS170_large_Data__21.txt";
	} else if(input == "3") {
		input = "CS170_XXXlarge_Data__13.txt";
	} else if(input == "4") {
		input = "realWorld.txt";
	} else {
		std::cout << "ERROR: invalid input.\n";
	}
	std::vector<Entry> data = getData(input);
	std::cout << "Enter 1 for Forwards Selection, 2 for Backwards Elimination\n";
	std::cin >> input;
	if(input == "1") {
		forwards_selection(data);
	} else if(input == "2") {
		backwards_elimination(data);
	} else {
		std::cout << "ERROR: invalid input\n";
	}
}




#endif //__MAIN_CPP__
