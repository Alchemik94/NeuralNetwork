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
	int numberOfEpochs;
	int whenReport;
	const enum Command
	{
		unknown,create, select, list, teach, save, epochs, report, from_directory, help, quit
	};

	vector<pair<string, vector<NeuralNetwork<> > > > base;
	Command cmd;
	int tmp, selected;
	string tmpstr;
	vector<NeuralNetwork<> > tmp_nns;

public:
	void TeachingFront(const string& teachingFileName)
	{
		Parser<> parser(windowWidth);
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		base[selected-1].second[0].Teach(teachingSet[0], numberOfEpochs, whenReport);
	}
	void TeachingMiddle(const string& teachingFileName)
	{
		Parser<> parser(windowWidth);
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		base[selected-1].second[1].Teach(teachingSet[1], numberOfEpochs, whenReport);
	}
	void TeachingBack(const string& teachingFileName)
	{
		Parser<> parser(windowWidth);
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		base[selected-1].second[2].Teach(teachingSet[2], numberOfEpochs, whenReport);
	}

	void Help()
	{
		cout << "1. create - creates new neural network\n";
		cout << "2. select x - selects network number x\n";
		cout << "3. list - prints names of all networks\n";
		cout << "4. teach - teaches selected network\n";
		cout << "5. save - saves selected network\n";
		cout << "6. epochs - sets the number of epochs used in training\n";
		cout << "7. report - sets the number of epochs when report comes\n";
		cout << "8. read from file - creates new network from selected file\n";
		cout << "9. help - displays this message\n";
		cout << "10. quit - closes program\n";
	}

	vector<NeuralNetwork<> > GetStructure()
	{
		vector<NeuralNetwork<> > result;
		cout << "Sequences end with nonpositive numbers. Network has to have at least 3 layers.\n";
		int i;
		vector<int> structure;
		for (int j = 0; j<3 ; ++j)
		{
			cout << "Part " << j + 1 << " of 3:\n";
			structure.clear();
			cout << ">> ";
			cin >> i;
			while (i > 0)
			{
				structure.push_back(i);
				cout << ">> ";
				cin >> i;
			}
			result.push_back(NeuralNetwork<>(structure));
		}
		return result;
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
		cout << "Enter training file name.\n";
		cout << ">> ";
		string training;
		cin >> training;
		TeachingFront(training);
		TeachingMiddle(training);
		TeachingBack(training);
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
		selected = 1;
		numberOfEpochs = 1000;
		whenReport = 100;
		cout << ">> ";
		cin >> tmp;
		cmd = (Command)tmp;
		while (cmd != quit)
		{
			switch (cmd)
			{
			case create:
				base.push_back(make_pair(GetName(), GetStructure()));
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
				base[selected - 1].second[0].Save(".\\" + GetFilename() + "\\_front.net");
				base[selected - 1].second[1].Save(".\\" + GetFilename() + "\\_middle.net");
				base[selected - 1].second[2].Save(".\\" + GetFilename() + "\\_back.net");
				cout << "Selected network has been saved.\n";
				break;
			case epochs:
				cout << "Enter number of epochs used in training.\n";
				cout << ">> ";
				cin >> numberOfEpochs;
				cout << "Set training for " << numberOfEpochs << " epochs.\n";
				break;
			case report:
				cout << "Enter number of epochs after which report comes.\n";
				cout << ">> ";
				cin >> whenReport;
				cout << "Set report to appear after every " << whenReport << " epochs.\n";
				break;
			case from_directory:
				cout << "Enter name of network file.\n";
				cout << ">> ";
				cin >> tmpstr;
				tmp_nns.clear();
				tmp_nns.push_back(NeuralNetwork<>(".\\"+tmpstr+"\\_front.net"));
				tmp_nns.push_back(NeuralNetwork<>(".\\" + tmpstr + "\\_middle.net"));
				tmp_nns.push_back(NeuralNetwork<>(".\\" + tmpstr + "\\_back.net"));
				base.push_back(make_pair(tmpstr, tmp_nns));
				cout << "Added network from directory.\n";
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
	Program program;

	program.Run();

	return 0;
}