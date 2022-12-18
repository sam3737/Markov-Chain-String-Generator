#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

using namespace std;

// char maker functions
vector<char> makeCharsInFile(string);
int makeUniqueChar(string);
vector<char> makeFirstChars(string);
map<char, int> makeCharMap(vector<char>);
vector<int> makeFirstCharDist(string, map<char, int>);
vector<int> makeCharDist(string, map<char, int>);
vector<double> makeFirstCharDistFlat(vector<int>);

// data maker functions
vector<string> makeData(string);
vector<vector<int>> makeProbabilityDist(vector<string>, map<char,int>);
vector<vector<double>> makeProbabilityDistFlat(vector<string> data, map<char,int> charMap, vector<int> charDist);

// other functions
int weightedRand(vector<double> weights);
string displayChar(char);
bool compareFunction (char, char);

#endif // PROTOTYPES_H_INCLUDED
