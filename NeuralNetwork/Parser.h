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

	}

	vector<vector<FloatingNumber> > ParseStructure(const string& structure)
	{
	
	}

	public:
		Parser() : windowWidth(20){}
		Parser(int windowWidth) : windowWidth(windowWidth){}

		static list<pair<vector<FloatingNumber>,vector<FloatingNumber> > > Parse(const string& inputFilename)
		{
			fstream input;
			input.open(inputFilename.c_str, ios::in);

			list<pair<vector<FloatingNumber>, vector<FloatingNumber> > > listOfCases;

			vector<vector<FloatingNumber> > inputs, outputs;

			while (input.eof() == 0)
			{
				
			}

			input.close();
		}
};

#endif