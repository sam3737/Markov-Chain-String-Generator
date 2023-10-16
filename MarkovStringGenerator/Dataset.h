#ifndef DATASET_H_INCLUDED
#define DATASET_H_INCLUDED

#include <vector>
#include <map>

using namespace std;

class Dataset {
private:

    string fileName; // name of file to get data from

    vector<char> charInFile; // all unique char in the file
    map<char, int> charMap; // map of chars to int, starting at 0
    vector<int> charDist; // how many of each char appear (excluding line ends)
    vector<int> firstCharDist; // how many of each char appear at the beginning of lines
    vector<double> firstCharDistFlat; // firstCharDist so all elements sum to 1

    vector<string> data; // each line of the file as an element
    vector<vector<int>> probabilityDist; // how many times each char follows each other char
    vector<vector<double>> probabilityDistFlat; // probabilityDist so each vector sums to 1

public:

    // constructors
    Dataset();
    Dataset(string fileName);

    // char variable accessors
    vector<char> getCharInFile() {return charInFile;};
    vector<int> getCharDist() {return charDist;};
    map<char, int> getCharMap() {return charMap;};
    vector<int> getFirstCharDist() {return firstCharDist;};
    vector<double> getFirstCharDistFlat() {return firstCharDistFlat;};

    // data variable accessors
    vector<string> getData() {return data;};
    vector<vector<double>> getProbabilityDistFlat() {return probabilityDistFlat;};

    string makeNewWord(int, int); // make a word based on probabilities
    void writeDataToFile(string); // write data to a .csv file
};

#endif // DATASET_H_INCLUDED
