#ifndef __TESTER__
#define __TESTER__

#include "NeuralNetwork.h"
#include <vector>

class Tester
{
	
	const long double epsilon = 0.0001;

public:
	void Test()
	{
		//first test is to perform xor operation
		vector<int> structure;
		structure.push_back(2);
		structure.push_back(4);
		structure.push_back(4);
		structure.push_back(2);
		NeuralNetwork<> network(structure);



	}

};

#endif