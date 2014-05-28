#ifndef __NEURON__
#define __NEURON__

#include "Types.h"
#include <vector>
#include <time.h>
#include <cmath>

using namespace std;

template <typename FloatingNumber = long double>
class Neuron
{
	const FloatingNumber beta = 1;

	FloatingNumber LinearCombination(const vector<FloatingNumber>& input) const
	{
		FloatingNumber res = 0;
		for (int i = 0; i < wages.size(); ++i)
			res += wages[i]*input[i];
		return res;
	}

	FloatingNumber Sigma(const FloatingNumber& linearCombination) const
	{
		return ((FloatingNumber)(1))/((FloatingNumber)(1)+(FloatingNumber)(expl(-beta*linearCombination)));
	}
	FloatingNumber SigmaDerivative(const FloatingNumber& linearCombination) const
	{
		return beta*Sigma(linearCombination)*((FloatingNumber)(1) - Sigma(linearCombination));
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
	FloatingNumber ActivationFunctionDerivative(const vector<FloatingNumber>& input) const
	{
		switch (this->type)
		{
		case Linear:
			return (FloatingNumber)(1);
			break;
		case Sigmoidal:
			return SigmaDerivative(LinearCombination(input));
			break;
		case Bias:
			return (FloatingNumber)(0);
			break;
		default:
			break;
		}
	}

public:
	vector<FloatingNumber> wages;

	FloatingNumber lastResult;

	enum ActivationFunction type;
	
	Neuron(int size)
	{
		srand(time(NULL));
		type = ActivationFunction::Sigmoidal;
		lastResult = 0;
		wages = vector<FloatingNumber>(size);
		for (int i = 0; i < size; ++i)
			wages[i] = ((FloatingNumber)(rand() % 100000)) / 10000;
	}

	FloatingNumber Use(const vector<FloatingNumber>& input) const
	{
		return lastResult = ActivationFunction(input);
	}
	void Teach(const FloatingNumber& error, const FloatingNumber& learningCoefficient, const vector<FloatingNumber>& input)
	{
		if (type == Bias) return;
		FloatingNumber derivative = ActivationFunctionDerivative(input);
		for (int i = 0; i < wages.size(); ++i)
		{
			wages[i] += learningCoefficient*error*derivative*input[i];
		}
	}
};

#endif