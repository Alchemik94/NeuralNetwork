#include "NeuralNetwork.h"

#include "Tester.h"

#include <cstdlib>

using namespace std;

class Program
{
	Parser<> parser;
	const int windowWidth = 19;
	const int aminoacidsTypes = 19;
	const int numberOfEpochs = 100;
	const int whenReport = 1;
public:
	void PrimaryTeachingFront(const string& teachingFileName, const string& networkNewFileName)
	{
		Parser<> parser;
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		vector<int> structure;
		structure.push_back(windowWidth*aminoacidsTypes);
		structure.push_back(100);
		structure.push_back(50);
		structure.push_back(50);
		structure.push_back((windowWidth / 2) * 3);

		NeuralNetwork<> fronts(structure);

		fronts.Teach(teachingSet[0],numberOfEpochs,whenReport);

		fronts.Save(networkNewFileName + "_front.net");
	}
	void PrimaryTeachingMiddle(const string& teachingFileName, const string& networkNewFileName)
	{
		Parser<> parser;
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		vector<int> structure;
		structure.push_back(windowWidth*aminoacidsTypes);
		structure.push_back(100);
		structure.push_back(50);
		structure.push_back(25);
		structure.push_back(3);

		NeuralNetwork<> middles(structure);

		middles.Teach(teachingSet[1], numberOfEpochs, whenReport);

		middles.Save(networkNewFileName + "_middle.net");
	}
	void PrimaryTeachingBack(const string& teachingFileName, const string& networkNewFileName)
	{
		Parser<> parser;
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		vector<int> structure;
		structure.push_back(windowWidth*aminoacidsTypes);
		structure.push_back(100);
		structure.push_back(50);
		structure.push_back(50);
		structure.push_back((windowWidth / 2) * 3);

		NeuralNetwork<> backs(structure);

		backs.Teach(teachingSet[2], numberOfEpochs, whenReport);

		backs.Save(networkNewFileName + "_back.net");
	}
	void PrimaryTeaching(const string& teachingFileName, const string& networkNewFileName)
	{
		PrimaryTeachingFront(teachingFileName, networkNewFileName);
		PrimaryTeachingMiddle(teachingFileName, networkNewFileName);
		PrimaryTeachingBack(teachingFileName, networkNewFileName);
	}
};

int main()
{
	Tester tester;

	Program program;

	program.PrimaryTeaching("CB396_dssp.txt","");

	system("PAUSE\n");

	return 0;
}