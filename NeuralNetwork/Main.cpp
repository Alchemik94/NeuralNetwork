#include "NeuralNetwork.h"

#include "Tester.h"

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

class Program
{
	Parser<> parser;
	const int windowWidth = 9;
	const int aminoacidsTypes = 19;
	const int numberOfEpochs = 1000;
	const int whenReport = 100;
public:
	void PrimaryTeaching(const string& teachingFileName, const string& networkNewFileName)
	{
		PrimaryTeachingFront(teachingFileName, networkNewFileName);
		PrimaryTeachingMiddle(teachingFileName, networkNewFileName);
		PrimaryTeachingBack(teachingFileName, networkNewFileName);
	}
	void PrimaryTeachingFront(const string& teachingFileName, const string& networkNewFileName)
	{
		Parser<> parser(windowWidth);
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		vector<int> structure;
		structure.push_back(windowWidth*aminoacidsTypes);
		structure.push_back(50);
		structure.push_back(40);
		structure.push_back(30);
		structure.push_back(20);
		structure.push_back((windowWidth / 2) * 3);

		NeuralNetwork<> fronts(structure);

		fronts.Teach(teachingSet[0], numberOfEpochs, whenReport);

		fronts.Save(networkNewFileName + "_front.net");
	}
	void PrimaryTeachingMiddle(const string& teachingFileName, const string& networkNewFileName)
	{
		Parser<> parser(windowWidth);
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		vector<int> structure;
		structure.push_back(windowWidth*aminoacidsTypes);
		structure.push_back(50);
		structure.push_back(15);
		structure.push_back(6);
		structure.push_back(3);

		NeuralNetwork<> middles(structure);

		middles.Teach(teachingSet[1], numberOfEpochs, whenReport);

		middles.Save(networkNewFileName + "_middle.net");
	}
	void PrimaryTeachingBack(const string& teachingFileName, const string& networkNewFileName)
	{
		Parser<> parser(windowWidth);
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		vector<int> structure;
		structure.push_back(windowWidth*aminoacidsTypes);
		structure.push_back(50);
		structure.push_back(40);
		structure.push_back(30);
		structure.push_back(20);
		structure.push_back((windowWidth / 2) * 3);

		NeuralNetwork<> backs(structure);

		backs.Teach(teachingSet[2], numberOfEpochs, whenReport);

		backs.Save(networkNewFileName + "_back.net");
	}

};

int main()
{
	int choice;
	cin >> choice;

	Tester tester;

	Program program;

	string input = "CB396_dssp_short.txt", output = "";

	switch (choice)
	{
	case 1:
		program.PrimaryTeachingFront(input, output);
		break;
	case 2:
		program.PrimaryTeachingMiddle(input, output);
		break;
	case 3:
		program.PrimaryTeachingBack(input, output);
		break;
	default:
		program.PrimaryTeaching(input, output);
		break;
	}


	system("PAUSE\n");

	return 0;
}