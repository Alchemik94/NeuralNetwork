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
	void TestOfXor()
	{
		//first test is to perform xor operation
		vector<int> structure;
		structure.push_back(2);
		//structure.push_back(8);
		structure.push_back(15);
		structure.push_back(25);
		structure.push_back(15);
		//structure.push_back(4);
		//structure.push_back(2);
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
			in.push_back(j);
			in.push_back(i);
			//out.push_back(1);
			cout << ((((i == 1) && (j == 0)) || ((i == 0) && (j == 1))) == 1) << "\n";
			out.push_back((((i == 1) && (j == 0)) || ((i == 0) && (j == 1)))==1);
			teachingSet.push_back(make_pair(in, out));
		}

		network.Teach(teachingSet, 20000);
		network.Save("xor.net");

		cout << "NN2:\n";
		NeuralNetwork<long double> network2("xor.net");
		
		in.clear();
		in.push_back(0);
		in.push_back(0);
		
		out = network2.Use(in);

		cout << in[0] << " xor " << in[1] << " = " << out[0] << "\n";

		in.clear();
		in.push_back(1);
		in.push_back(0);
			
		cout << in[0] << " xor " << in[1] << " = " << network2.Use(in)[0] << "\n";

		in.clear();
		in.push_back(0);
		in.push_back(1);

		cout << in[0] << " xor " << in[1] << " = " << network2.Use(in)[0] << "\n";

		in.clear();
		in.push_back(1);
		in.push_back(1);

		cout << in[0] << " xor " << in[1] << " = " << network2.Use(in)[0] << "\n\n\n";
		
	}

};

#endif