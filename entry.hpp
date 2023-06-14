#ifndef __ROW_HPP__
#define __ROW_HPP__

#include <iostream>
#include <vector>


//The class Entry contains all the features/data for one entry of the the dataset
class Entry {
	public:
		int classification;
		std::vector<float> features;
};

#endif //__ROW_HPP__