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
		netStructure.push_back(1500);
		netStructure.push_back(3000);
		netStructure.push_back(2000);
		netStructure.push_back(1500);
		netStructure.push_back(windowWidth * 3);
		NeuralNetwork<> network(netStructure);

		NeuralNetwork<>::TeachingSet teachingSet = parser.Parse(teachingFileName);

		network.Teach(teachingSet, 200, 5);

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