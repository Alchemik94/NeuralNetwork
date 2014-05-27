#ifndef __NEURAL_NETWORK__
#define __NEURAL_NETWORK__

#define ABS(x) (x) >= 0 ? (x) : (-(x))

#include "Neuron.h"
#include <list>
#include <math.h>
#include <vector>

using namespace std;

template <typename FloatingNumber = long double>
class NeuralNetwork
{
	vector<vector<Neuron<FloatingNumber> > > network;

	static const FloatingNumber learningCoefficientLow = 0.2;
	static const FloatingNumber learningCoefficientHigh = 0.9;

	FloatingNumber MeanSquaredError(const FloatingNumber& given, const FloatingNumber& expected) const
	{
		return ((FloatingNumber)(0.5))*((FloatingNumber)(given - expected))*((FloatingNumber)(given - expected));
	}

	FloatingNumber LearningCoefficientForIthEpoch(const int& currentEpoch, const int& maxEpochs) const
	{
		return sqrt(learningCoefficientLow*learningCoefficientLow*((ABS(((FloatingNumber)(maxEpochs)) / 2 - currentEpoch)) / ((FloatingNumber)(maxEpochs))) + learningCoefficientHigh*learningCoefficientHigh*(1 - ((ABS(((FloatingNumber)(maxEpochs)) / 2 - currentEpoch)) / ((FloatingNumber)(maxEpochs)))));
	}

	FloatingNumber ErrorOnHidden(const int& layer, const int& neuronNumber, const vector<vector<FloatingNumber> >& error)
	{
		FloatingNumber result = 0;
		for (int i = 0; i < network[layer + 1].size(); ++i)
			result += (error[layer+1][i] * network[layer][i].wages[neuronNumber]);
		return result;
	}

	vector<vector<FloatingNumber> > ErrorValues(const vector<FloatingNumber>& input, const vector<FloatingNumber>& output)
	{
		vector<vector<FloatingNumber> > error(network.size(), vector<FloatingNumber>());
		
		//output layer
		error[error.size() - 1] = vector<FloatingNumber>(network[network.size() - 1].size());
		for (int i = 0; i < network[network.size() - 1].size(); ++i)
			error[error.size() - 1][i] = MeanSquaredError(network[network.size() - 1][i].lastResult, output[i]);

		//rest of the layers
		for (int i = network.size() - 2; i >= 0; --i)
		{
			error[i] = vector<FloatingNumber>(network[i].size());

			//error for each neuron
			for (int j = 0; j < network[i].size(); ++j)
				error[i][j] = ErrorOnHidden(i, j, error);

		}
		return error;
	}

	void TeachCase(const vector<FloatingNumber>& input, const vector<FloatingNumber>& output, const FloatingNumber& learningCoefficient)
	{
		Use(input);
		vector<vector<FloatingNumber> > error = ErrorValues(input,output);
		vector<FloatingNumber> currentInput = input;

		for (int i = 0; i < network.size(); ++i)
		{
			for (int j = 0; j < network[i].size(); ++j)
				network[i][j].Teach(error[i][j], learningCoefficient, currentInput);
			currentInput.clear();
			for (int j = 0; j < network[i].size(); ++j)
				currentInput.push_back(network[i][j].lastResult);
		}
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
	
	void Teach(list<pair<vector<FloatingNumber>, vector<FloatingNumber> > >& teachingSet, int epochs)
	{
		auto it = teachingSet.begin();
		FloatingNumber learningCoefficient;
		for (int i = 0; i < epochs; ++i)
		{
			learningCoefficient = LearningCoefficientForIthEpoch(i,epochs);
			for (it = teachingSet.begin(); it != teachingSet.end(); ++it)
				TeachCase(it->first, it->second, learningCoefficient);
		}
	}

};

#endif