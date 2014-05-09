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

public:
	Neuron(int size)
	{
		srand(time(NULL));
		type = Linear;
		wages = vector<double>(size);
		for (int i = 0; i < size; ++i)
			wages[i] = ((double)(rand() % 100000))/10000;
	}

};

#endif