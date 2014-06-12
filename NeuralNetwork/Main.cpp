#include "NeuralNetwork.h"

#include "Tester.h"

#include <cstdlib>

using namespace std;

class Program
{
	Parser<> parser;
	const int windowWidth = 20;
public:
	void PrimaryTeaching(const string& teachingFileName, const string& networkNewFileName)
	{
		vector<int> netStructure;
		netStructure.push_back(windowWidth*19);
		netStructure.push_back(500);
		netStructure.push_back(300);
		netStructure.push_back(150);
		netStructure.push_back(100);
		netStructure.push_back(windowWidth * 3);
		NeuralNetwork<> network(netStructure);

		NeuralNetwork<>::TeachingSet teachingSet = parser.Parse(teachingFileName);
		cout << "Size of teaching set: " << teachingSet.size() << "\n";
		for (int i = 0; i < 200; ++i)
		{
			cout << "Epoch " << i << " out of 201.\n";
			network.Teach(teachingSet, 1, true);
			network.Save(networkNewFileName);
		}
		network.Teach(teachingSet, 1, 1, true);
		network.Save(networkNewFileName);
	}
};

int main()
{
	Tester tester;

	Program program;

	program.PrimaryTeaching("CB396_dssp.txt","ProteinPrediction.net");

	system("PAUSE\n");

	return 0;
}