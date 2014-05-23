#ifndef __NEURAL_NETWORK__
#define __NEURAL_NETWORK__

#include "Neuron.h"
#include <vector>

using namespace std;

template <typename FloatingNumber = long double>
class NeuralNetwork
{
	vector<vector<Neuron<FloatingNumber> > > network;

	static const FloatingNumber learningCoefficientLow = 0.2;
	static const FloatingNumber learningCoefficientHigh = 0.9;

	FloatingNumber MeanSquaredError(const FloatingNumber& given, const FloatingNumber& expected)
	{
		return ((FloatingNumber)(0.5))*((FloatingNumber)(given - expected))*((FloatingNumber)(given - expected));
	}

public:
	//Network has to have at least two layers: input and output
	NeuralNetwork(const vector<int>& structureDescription)
	{
		if (structureDescription.size() < 2)
			throw;
		network.clear();
		network.push_back(vector<Neuron<FloatingNumber> >(structureDescription[0], Neuron(1)));
		network[0][structureDescription[0]].type = Bias;
		for (int i = 1; i < structureDescription.size()-1; ++i)
		{
			network.push_back(vector<Neuron<FloatingNumber> >(structureDescription[i] + 1, Neuron(network[i - 1].size())));
			network[i][structureDescription[i]].type = Bias;
		}
		network.push_back(vector<Neuron<FloatingNumber> >(structureDescription[structureDescription.size() - 1], Neuron(structureDescription[structureDescription.size() - 2] + 1)));

	}

	vector<FloatingNumber> Use(const vector<FloatingNumber>& input)
	{
		vector<FloatingNumber> tmp, result;
		tmp = input;
		for (int i = 0; i < network.size(); ++i)
		{
			result.clear();
			result.reserve(network[i].size());
			for (int j = 0; j < network[i].size(); ++j)
				result[j] = network[i][j].Use(tmp);
			tmp = result;
		}
		return result;
	}
	

};

#endif