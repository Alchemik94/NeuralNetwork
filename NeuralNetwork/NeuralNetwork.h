#ifndef __NEURAL_NETWORK__
#define __NEURAL_NETWORK__

#define ABS(x) (x) >= 0 ? (x) : (-(x))

#include "Neuron.h"
#include <list>
#include <math.h>
#include <time.h>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

template <typename FloatingNumber = long double>
class NeuralNetwork
{
	vector<vector<Neuron<FloatingNumber> > > network;

	const FloatingNumber learningCoefficientLow = 0.2;
	const FloatingNumber learningCoefficientHigh = 0.9;

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
			result += (error[layer + 1][i] * network[layer][i].wages[neuronNumber]);
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
		vector<vector<FloatingNumber> > error = ErrorValues(input, output);
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
		srand(time(NULL));
		if (structureDescription.size() < 2)
			throw;
		network.clear();
		network.push_back(vector<Neuron<FloatingNumber> >(structureDescription[0]));
		for (int i = 0; i < network[0].size(); ++i)
			network[0][i] = Neuron<FloatingNumber>(1);
		for (int i = 1; i < structureDescription.size() - 1; ++i)
		{
			network.push_back(vector<Neuron<FloatingNumber> >(structureDescription[i] + 1));
			for (int j = 0; j < network[i].size(); ++j)
				network[i][j] = Neuron<FloatingNumber>(network[i - 1].size());
			network[i][structureDescription[i]].type = Bias;
		}
		network.push_back(vector<Neuron<FloatingNumber> >(structureDescription[structureDescription.size() - 1]));
		for (int i = 0; i < network[network.size() - 1].size(); ++i)
			network[network.size() - 1][i] = Neuron<FloatingNumber>(structureDescription[structureDescription.size() - 2] + 1);
	}

	//Constructing from file
	NeuralNetwork(const string& filename)
	{
		srand(time(NULL));
		fstream in;
		in.open(filename.c_str(), ios_base::in);

		int tmp;
		in >> tmp;
		network = vector<vector<Neuron<FloatingNumber> > >(tmp, vector<Neuron<FloatingNumber> >());
		
		//for every layer
		for (int i = 0; i < network.size(); ++i)
		{
			//number of neurons
			in >> tmp;
			network[i].resize(tmp);
			//for every neuron
			for (int j = 0; j < network[i].size(); ++j)
			{
				//number of wages
				in >> tmp;
				network[i][j].wages.resize(tmp);
				//every wage
				for (int k = 0; k < network[i][j].wages.size(); ++k)
				{
					in >> network[i][j].wages[k];
				}
				//and type of activation function
				in >> tmp;
				network[i][j].type = (ActivationFunction)tmp;
			}
		}

		in.close();
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
			learningCoefficient = LearningCoefficientForIthEpoch(i, epochs);
			for (it = teachingSet.begin(); it != teachingSet.end(); ++it)
				TeachCase(it->first, it->second, learningCoefficient);
		}
	}

	void Save(const string& filename)
	{
		fstream out;
		out.open(filename.c_str(), ios_base::out);

		out << network.size() << "\n";

		//for every layer
		for (int i = 0; i < network.size(); ++i)
		{
			out << network[i].size() << "\n";
			//for every neuron
			for (int j = 0; j < network[i].size(); ++j)
			{
				//number of wages
				out << network[i][j].wages.size() << "\n";
				//every wage
				for (int k = 0; k < network[i][j].wages.size(); ++k)
				{
					out << network[i][j].wages[k] << " ";
				}
				out << "\n";
				//and type of activation function
				out << (int)network[i][j].type << "\n";
			}
		}

		out.close();
	}
};

#endif