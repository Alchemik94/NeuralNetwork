#ifndef __PARSER__
#define __PARSER__

#include <vector>
#include <list>
#include <fstream>

using namespace std;

template <typename FloatingNumber = long double>
class Parser
{
	int windowWidth = 20;

	vector<vector<FloatingNumber> > ParseProtein(const string& protein)
	{
		//TODO
	}

	vector<vector<FloatingNumber> > ParseStructure(const string& structure)
	{
		//TODO
	}

	public:
		Parser() : windowWidth(20){}
		Parser(int windowWidth) : windowWidth(windowWidth){}

		static list<pair<vector<FloatingNumber>,vector<FloatingNumber> > > Parse(const string& inputFilename)
		{
			fstream input;
			input.open(inputFilename.c_str, ios::in);

			string line;

			list<pair<vector<FloatingNumber>, vector<FloatingNumber> > > listOfCases;

			vector<vector<FloatingNumber> > inputs, outputs;

			while (input.eof() == 0)
			{
				input >> line;
				input >> line;
				inputs = ParseProtein(line);
				input >> line;
				outputs = ParseStructure(line);
				for (int i = 0; i < inputs.size() && i < outputs.size(); ++i)
					listOfCases.insert(listOfCases.end(), make_pair(inputs[i], outputs[i]));
			}

			input.close();

			return listOfCases;
		}
};

#endif