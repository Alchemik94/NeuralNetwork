#ifndef __NEURON__
#define __NEURON__

#include "Types.h"
#include <vector>
#include <time.h>

using namespace std;

class Neuron
{
	ActivationFunction type;

	vector<double> wages;

	double LinearCombination(const vector<double>& input)
	{
		double res = 0;
		for (int i = 0; i < wages.size(); ++i)
			res += wages[i]*input[i];
		return res;
	}

public:
	Neuron(int size)
	{
		srand(time(NULL));
		type = Linear;
		wages = vector<double>(size);
		for (int i = 0; i < size; ++i)
			wages[i] = ((double)(rand() % 100000))/10000;
	}

	double ActivationFunction(const vector<double>& input)
	{
		switch (this->type)
		{
		case Linear:
			return LinearCombination(input);
			break;
		default:
			break;
		}
	}


};

#endif