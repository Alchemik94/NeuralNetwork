#ifndef __PARSER__
#define __PARSER__

#include <vector>
#include <list>
#include <fstream>

using namespace std;

template <typename FloatingNumber = long double>
class Parser
{
	typedef list<pair<vector<FloatingNumber>, vector<FloatingNumber> > > TeachSet;

	int windowWidth = 19;

	string Aminoacid(const string& protein, int position)
	{
		string alphabetically = "0000000000000000000000000";
		if (protein[position] - 'A' < 0 || protein[position] - 'A' > 24)
			return "";
		alphabetically[protein[position] - 'A'] = '1';
		string coded = "";

		for (int i = 0, j = 0; i < alphabetically.length(); ++i)
		{
			//B,J,O,U,X,Z
			if (i==1 || i==9 || i==14 || i==20 || i==23 || i==24)
				continue;
			coded += alphabetically[i];
		}
		return coded;
	}

	vector<vector<FloatingNumber> > ParseProtein(const string& protein)
	{
		string aminoacid;
		vector<vector<FloatingNumber> > parsed(protein.length() - windowWidth);
		for (int i = 0; i < protein.length()-windowWidth; ++i)
		{
			for (int j = 0; j < windowWidth; ++j)
			{
				aminoacid = Aminoacid(protein, i + j);
				for (int k = 0; k < aminoacid.length(); ++k)
				{
					parsed[i].push_back((FloatingNumber)(aminoacid[k]-'0'));
				}
			}
		}
		return parsed;
	}

	string ClassOfStructure(const string& structure, int position)
	{
		if (structure[position] == 'C' || structure[position] == '-')
			return "100";
		else if (structure[position] == 'E')
			return "010";
		else if (structure[position] == 'H')
			return "001";
	}

	vector<vector<FloatingNumber> > ParseStructure(const string& structure)
	{
		string structureClass;
		vector<vector<FloatingNumber> > parsed(structure.length() - windowWidth);
		for (int i = 0; i < structure.length() - windowWidth; ++i)
		{
			for (int j = 0; j < windowWidth; ++j)
			{
				structureClass = ClassOfStructure(structure, i + j);
				for (int k = 0; k < structureClass.length(); ++k)
				{
					parsed[i].push_back((FloatingNumber)(structureClass[k] - '0'));
				}
			}
		}
		return parsed;
	}

	TeachSet ParseFront(const string& inputFilename)
	{
		fstream input;
		input.open(inputFilename.c_str(), ios::in);

		string line;

		list<pair<vector<FloatingNumber>, vector<FloatingNumber> > > listOfCases;

		vector<vector<FloatingNumber> > inputs, outputs;

		while (input.eof() == 0)
		{
			input >> line;
			input >> line;
			input >> line;
			if (input.eof() != 0) break;
			inputs = ParseProtein(line);
			input >> line;
			outputs = ParseStructure(line);
			for (int i = 0; i <= windowWidth / 2; ++i)
			{
				outputs[0].pop_back();
				outputs[0].pop_back();
				outputs[0].pop_back();
			}
			listOfCases.insert(listOfCases.end(), make_pair(inputs[0], outputs[0]));
		}

		input.close();

		return listOfCases;
	}

	TeachSet ParseBack(const string& inputFilename)
	{
		fstream input;
		input.open(inputFilename.c_str(), ios::in);

		string line;

		list<pair<vector<FloatingNumber>, vector<FloatingNumber> > > listOfCases;

		vector<vector<FloatingNumber> > inputs, outputs;

		vector<FloatingNumber> tmp;

		while (input.eof() == 0)
		{
			input >> line;
			input >> line;
			input >> line;
			if (input.eof() != 0) break;
			inputs = ParseProtein(line);
			input >> line;
			outputs = ParseStructure(line);
			tmp.clear();
			for (int i = (windowWidth / 2 + 1) * 3; i < outputs[outputs.size() - 1].size(); ++i)
			{
				tmp.push_back(outputs[outputs.size() - 1][i]);
			}
			listOfCases.insert(listOfCases.end(), make_pair(inputs[inputs.size()-1], tmp));
		}

		input.close();

		return listOfCases;
	}

	TeachSet ParseMiddle(const string& inputFilename)
	{
		fstream input;
		input.open(inputFilename.c_str(), ios::in);

		string line;

		list<pair<vector<FloatingNumber>, vector<FloatingNumber> > > listOfCases;

		vector<vector<FloatingNumber> > inputs, outputs;

		vector<FloatingNumber> tmp;

		while (input.eof() == 0)
		{
			input >> line;
			input >> line;
			input >> line;
			if (input.eof() != 0) break;
			inputs = ParseProtein(line);
			input >> line;
			outputs = ParseStructure(line);
			for (int i = 0; i < inputs.size() && i < outputs.size(); ++i)
			{
				tmp.clear();
				tmp.push_back(outputs[i][(windowWidth / 2)*3 ]);
				tmp.push_back(outputs[i][(windowWidth / 2)*3 + 1 ]);
				tmp.push_back(outputs[i][(windowWidth / 2)*3 + 2 ]);
				listOfCases.insert(listOfCases.end(), make_pair(inputs[i], tmp));
			}
		}

		input.close();

		return listOfCases;
	}

	public:
		Parser() : windowWidth(19){}
		Parser(int windowWidth) : windowWidth(windowWidth){}
		vector<TeachSet> Parse(const string& inputFilename)
		{
			vector<TeachSet> result;
			result.push_back(ParseFront(inputFilename));
			result.push_back(ParseMiddle(inputFilename));
			result.push_back(ParseBack(inputFilename));
			return result;
		}
};

#endif