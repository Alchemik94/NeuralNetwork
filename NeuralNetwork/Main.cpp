#include "Parser.h"
#include "NeuralNetwork.h"

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

/// <summary>
/// Simple class containing whole program work. Made to make sure that every variable can be used in functions.
/// </summary>
class Program
{
	Parser<> parser;
	const int windowWidth = 9;
	const int aminoacidsTypes = 19, structuresTypes = 3;
	int numberOfEpochs;
	int whenReport;
	const enum Command
	{
		unknown,create, select, list, teach, save, epochs, report, from_directory, run_on_case, help, quit
	};

	vector<pair<string, vector<NeuralNetwork<> > > > base;
	Command cmd;
	int tmp, selected;
	string tmpstr;
	vector<NeuralNetwork<> > tmp_nns;

	/// <summary>
	/// Teaches the front part of selected neural network. Reads everything from file, parses and then teaches the network.
	/// </summary>
	/// <param name="teachingFileName">Name of file containing teaching set as proteins and their secondary structure.</param>
	void TeachingFront(const string& teachingFileName)
	{
		Parser<> parser(windowWidth);
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		base[selected-1].second[0].Teach(teachingSet[0], numberOfEpochs, whenReport);
	}
	/// <summary>
	/// Teaches the middle part of selected neural network. Reads everything from file, parses and then teaches the network.
	/// </summary>
	/// <param name="teachingFileName">Name of file containing teaching set as proteins and their secondary structure.</param>
	void TeachingMiddle(const string& teachingFileName)
	{
		Parser<> parser(windowWidth);
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		base[selected-1].second[1].Teach(teachingSet[1], numberOfEpochs, whenReport);
	}
	/// <summary>
	/// Teaches the ending part of selected neural network. Reads everything from file, parses and then teaches the network.
	/// </summary>
	/// <param name="teachingFileName">Name of file containing teaching set as proteins and their secondary structure.</param>
	void TeachingBack(const string& teachingFileName)
	{
		Parser<> parser(windowWidth);
		vector<NeuralNetwork<>::TeachingSet> teachingSet = parser.Parse(teachingFileName);

		base[selected-1].second[2].Teach(teachingSet[2], numberOfEpochs, whenReport);
	}

	/// <summary>
    /// Prints out options to use by user.
    /// </summary>
	void Help()
	{
		cout << "1. create - creates new neural network\n";
		cout << "2. select x - selects network number x\n";
		cout << "3. list - prints names of all networks\n";
		cout << "4. teach - teaches selected network\n";
		cout << "5. save - saves selected network\n";
		cout << "6. epochs - sets the number of epochs used in training\n";
		cout << "7. report - sets the number of epochs when report comes\n";
		cout << "8. read from file - creates new network from selected directory\n";
		cout << "9. work - uses network to work on single case\n";
		cout << "10. help - displays this message\n";
		cout << "11. quit - closes program\n";
	}

	/// <summary>
	/// Asks user to insert a structure of neural network.
	/// </summary>
	/// <returns>Vector used to create new neural vector</returns>
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

	/// <summary>
	/// Asks user to give the name for new neural network
	/// </summary>
	/// <returns>Name of new network</returns>
	string GetName()
	{
		cout << "Enter name for the new network.\n";
		cout << ">> ";
		string name;
		cin >> name;
		return name;
	}

	/// <summary>
	/// Teaches every part of user-side network.
	/// </summary>
	void Teach()
	{
		cout << "Enter training file name.\n";
		cout << ">> ";
		string training;
		cin >> training;
		cout << "Part 1 of 3:\n";
		TeachingFront(training);
		cout << "Part 2 of 3:\n";
		TeachingMiddle(training);
		cout << "Part 3 of 3:\n";
		TeachingBack(training);
	}

	/// <summary>
	/// Asks user to give the name of network directory.
	/// </summary>
	/// <returns>Network directory name</returns>
	string GetFilename()
	{
		string name;
		cout << "Enter name of the network directory.\n";
		cout << ">> ";
		cin >> name;
		return name;
	}

	/// <summary>
    /// Uses selected neural network to work on a single case. Asks user for case filename, parses it, predicts secondary structure and saves it.
    /// </summary>
	void RunOnCase()
	{
		cout << "Please enter case file name.\n";
		cout << ">> ";
		cin >> tmpstr;
		vector<vector<long double> > protein = parser.ParseSingleInput(tmpstr);
		cout << "Parsing done.\n";
		vector<vector<long double> > result;
		result.push_back(base[selected - 1].second[0].Use(protein[0]));
		for (int i = 1; i < protein.size() - 1; ++i)
			result.push_back(base[selected - 1].second[1].Use(protein[i]));
		result.push_back(base[selected - 1].second[2].Use(protein[protein.size()-1]));
		cout << "Calculations done.\n";
		cout << "Please enter output file name.\n";
		cout << ">> ";
		cin >> tmpstr;
		fstream out;
		out.open(tmpstr.c_str(), ios::out);
		for (int i = 0; i < result.size(); ++i)
		{
			for (int j = 0; j < result[i].size(); ++j)
			{
				out << result[i][j];
				if ((j + 1) % structuresTypes == 0)
					out << "\n";
				else
					out << " ";
			}
		}
		out.close();
	}

public:
	/// <summary>
    /// Runs the program.
    /// </summary>
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
				tmpstr = GetFilename();
				base[selected - 1].second[0].Save(".\\" + tmpstr + "\\_front.net");
				base[selected - 1].second[1].Save(".\\" + tmpstr + "\\_middle.net");
				base[selected - 1].second[2].Save(".\\" + tmpstr + "\\_back.net");
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
			case run_on_case:
				RunOnCase();
				cout << "Done.\n";
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