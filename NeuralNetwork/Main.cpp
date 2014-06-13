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
	const enum Command
	{
		unknown,create, select, list, teach, save, help, quit
	};

	vector<pair<string, NeuralNetwork<> > > base;
	Command cmd;
	int tmp, selected;

public:
	/*void PrimaryTeaching(const string& teachingFileName, const string& networkNewFileName)
	{
		PrimaryTeachingFront(teachingFileName, networkNewFileName);
		PrimaryTeachingMiddle(teachingFileName, networkNewFileName);
		PrimaryTeachingBack(teachingFileName, networkNewFileName);
	}*/
	void TeachingFront(const string& teachingFileName)
	{
		Parser<> parser(windowWidth);
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		/*
		structure.push_back(windowWidth*aminoacidsTypes);
		structure.push_back(25);
		structure.push_back(30);
		structure.push_back(25);
		structure.push_back(15);
		structure.push_back((windowWidth / 2) * 3);
		*/
		base[selected-1].second.Teach(teachingSet[0], numberOfEpochs, whenReport);
	}
	void TeachingMiddle(const string& teachingFileName)
	{
		Parser<> parser(windowWidth);
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		/*
		structure.push_back(windowWidth*aminoacidsTypes);
		structure.push_back(20);
		structure.push_back(15);
		structure.push_back(6);
		structure.push_back(3);
		*/
		base[selected-1].second.Teach(teachingSet[1], numberOfEpochs, whenReport);
	}
	void TeachingBack(const string& teachingFileName)
	{
		Parser<> parser(windowWidth);
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		/*
		structure.push_back(windowWidth*aminoacidsTypes);
		structure.push_back(25);
		structure.push_back(30);
		structure.push_back(25);
		structure.push_back(15);
		structure.push_back((windowWidth / 2) * 3);
		*/
		
		base[selected-1].second.Teach(teachingSet[2], numberOfEpochs, whenReport);
	}

	void Help()
	{
		cout << "1. create - creates new neural network\n";
		cout << "2. select x - selects network number x\n";
		cout << "3. list - prints names of all networks\n";
		cout << "4. teach - teaches selected network\n";
		cout << "5. save - saves selected network\n";
		cout << "6. help - displays this message\n";
		cout << "7. quit - closes program\n";
	}

	vector<int> GetStructure()
	{
		cout << "Sequence ends with nonpositive number. Network has to have at least 3 layers.\n";
		int i;
		vector<int> structure;
		cout << ">> ";
		cin >> i;
		while (i > 0)
		{
			structure.push_back(i);
			cout << ">> ";
			cin >> i;
		}
		return structure;
	}

	string GetName()
	{
		cout << "Enter name for the new network.\n";
		cout << ">> ";
		string name;
		cin >> name;
		return name;
	}

	void Teach()
	{
		cout << "There are 3 options for teaching of the network:\n";
		cout << "1. Recognizing the fronts of the proteins' secondary structure.\n";
		cout << "2. Recognizing the middle of the proteins' secondary structure.\n";
		cout << "3. Recognizing the backs of the proteins' secondary structure.\n";
		cout << "Select one of them (as a number).\n";
		int sel;
		cout << ">> ";
		cin >> sel;
		cout << "Enter training file name.\n";
		cout << ">> ";
		string training;
		cin >> training;
		switch (sel)
		{
		case 1:
			TeachingFront(training);
			break;
		case 2:
			TeachingMiddle(training);
			break;
		case 3:
			TeachingBack(training);
			break;
		default:
			cout << "Error. Try again.\n";
			break;
		}
	}

	string GetFilename()
	{
		string name;
		cout << "Enter name of the network file.\n";
		cout << ">> ";
		cin >> name;
		return name;
	}

	void Run()
	{
		Help();
		selected = 0;
		cout << ">> ";
		cin >> tmp;
		cmd = (Command)tmp;
		while (cmd != quit)
		{
			switch (cmd)
			{
			case create:
				base.push_back(make_pair(GetName(), NeuralNetwork<>(GetStructure())));
				cout << "Network created.\n";
				break;
			case select:
				cin >> selected;
				cout << "Network " << selected << ". \"" << base[selected-1].first << "\" has been selected.\n";
				break;
			case list:
				cout << "Available networks:\n";
				for (int i = 0; i < base.size(); ++i)
					cout << i+1 << ". " << base[i].first << "\n";
				break;
			case teach:
				Teach();
				cout << "Selected network has been taught.\n";
				break;
			case save:
				base[selected - 1].second.Save(GetFilename());
				cout << "Selected network has been saved.\n";
				break;
			case help:
				Help();
				break;
			default:
				break;
			}
			cout << ">> ";
			cin >> tmp;
			cmd = (Command)tmp;
		}
	}

};

int main()
{
	/*
	int choice;
	cin >> choice;
	*/

	//Tester tester;

	Program program;

	program.Run();

	//string input = "CB396_dssp_short.txt", output = "";
	/*
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
	*/

	system("PAUSE\n");

	return 0;
}