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
		netStructure.push_back(900);
		netStructure.push_back(900);
		netStructure.push_back(700);
		netStructure.push_back(450);
		netStructure.push_back(windowWidth * 3);
		NeuralNetwork<> network(netStructure);

		NeuralNetwork<>::TeachingSet teachingSet = parser.Parse(teachingFileName);
		cout << "Size of teaching set: " << teachingSet.size() << "\n";
		for (int i = 0; i < 200; ++i)
		{
			network.Teach(teachingSet, 2, 1);
			network.Save(networkNewFileName);
		}
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