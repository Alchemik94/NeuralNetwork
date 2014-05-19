#ifndef __NEURON__
#define __NEURON__

#include "Types.h"
#include <vector>
#include <time.h>

using namespace std;

template <typename FloatingNumber>
class Neuron
{
	ActivationFunction type;

	vector<FloatingNumber> wages;

	FloatingNumber LinearCombination(const vector<FloatingNumber>& input)
	{
		FloatingNumber res = 0;
		for (int i = 0; i < wages.size(); ++i)
			res += wages[i]*input[i];
		return res;
	}

public:
	Neuron(int size)
	{
		srand(time(NULL));
		type = Linear;
		wages = vector<FloatingNumber>(size);
		for (int i = 0; i < size; ++i)
			wages[i] = ((FloatingNumber)(rand() % 100000)) / 10000;
	}

	FloatingNumber ActivationFunction(const vector<FloatingNumber>& input)
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