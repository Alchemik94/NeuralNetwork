#ifndef __NEURON__
#define __NEURON__

#include "Types.h"
#include <vector>
#include <time.h>

using namespace std;

template <typename FloatingNumber = double>
class Neuron
{
	ActivationFunction type;

	vector<FloatingNumber> wages;

	FloatingNumber LinearCombination(const vector<FloatingNumber>& input) const
	{
		FloatingNumber res = 0;
		for (int i = 0; i < wages.size(); ++i)
			res += wages[i]*input[i];
		return res;
	}

	const FloatingNumber Sigma(const FloatingNumber& linearCombination) const
	{
		//TODO
		;
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

	FloatingNumber ActivationFunction(const vector<FloatingNumber>& input) const
	{
		switch (this->type)
		{
		case Linear:
			return LinearCombination(input);
			break;
		case Sigmoidal:
			return Sigma(LinearCombination(input));
			break;
		case Bias:
			return (FloatingNumber)(1);
			break;
		default:
			break;
		}
	}


};

#endif