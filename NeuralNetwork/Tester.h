#ifndef __TESTER__
#define __TESTER__

#include "NeuralNetwork.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

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
		structure.push_back(1);
		NeuralNetwork<> network(structure);

		network.Save("net.net");

		vector<long double> in, out;
		list<pair<vector<long double>, vector<long double> > > teachingSet;
		for (int i = 0; i < 2;++i)
		for (int j = 0; j < 2; ++j)
		{
			in.clear();
			out.clear();
			in.push_back(i);
			in.push_back(j);
			out.push_back(((i == 1) && (j == 0)) || ((i == 0) && (j == 1)));
			teachingSet.push_back(make_pair(in, out));
		}

		network.Teach(teachingSet,10);
		network.Save("xor.net");

		NeuralNetwork<long double> network2("xor.net");
		out = network2.Use(in);
		
		cout << out[0] << "\n";
	}

};

#endif