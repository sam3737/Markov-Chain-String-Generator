#include <fstream>

#include "Dataset.h"
#include "prototypes.h"

/**
Dataset::Dataset

Dataset's default constructor. All
variables are defaulted to empty.
**/
Dataset::Dataset() {

    // declare all variables as empty
    string fileName = "";

    vector<char> charInFile = {};
    vector<int> charDist = {};
    vector<double> charDistFlat = {};

    vector<string> data = {};
    vector<vector<int>> probabilityDist = {{}};
    vector<int> probabilityTotal = {};
    vector<vector<double>> probabilityDistFlat = {{}};
}

/**
Dataset::Dataset(string file)

Construct a dataset based on a file.
**/
Dataset::Dataset(string file) {

    fileName = file;

    // see functions.cpp
    // define character variables
    charInFile = makeCharsInFile(file);
    charMap = makeCharMap(charInFile);
    charDist = makeCharDist(file, charMap);
    firstCharDist = makeFirstCharDist(file, charMap);
    firstCharDistFlat = makeFirstCharDistFlat(firstCharDist);

    // define data variables
    data = makeData(file);
    probabilityDistFlat = makeProbabilityDistFlat(data, charMap, charDist);
}
/**
Dataset::makeNewWord

Return a string by picking a first character based on the
first character distribution. Then continue adding on until
\n is added and the word is longer than minLength or the
word is maxLength characters long. A maxLength less than or
equal to zero will have no effect.
**/
string Dataset::makeNewWord(int minLength = 0, int maxLength = 0) {

    string word = "";

    // pick a first character
    word += charInFile[weightedRand(firstCharDistFlat)];

    do {
        // add a letter to word based on its last character
        word += charInFile[weightedRand(probabilityDistFlat[charMap[word.back()]])];

        // if word is too short, remove the '\n'
        if(word.length() <= minLength && word.back() == '\n') {
            word.pop_back();
        }

        // if word has reached maxLength, add '\n'
        if(word.length() == maxLength && maxLength > 0 && word.back() != '\n') {
            word += '\n';
        }

    // continue until the last char is '\n'
    } while(word.back() != '\n');

    return word;
}

/**
Dataset::writeDataToFile

Write the characters present and their distributions
as well as the probability array to a file with name
fileName. Expects a .csv file.
**/
void Dataset::writeDataToFile(string fileName) {

    // initialize fstream variable
    fstream outputFile;

    // open the file and clear it
    outputFile.open(fileName, std::ofstream::out | std::ofstream::trunc);

    // write char data
    outputFile << "Character" << "," << "Distribution\n";
    for(int i=0; i<charInFile.size(); i++) {
        outputFile << displayChar(charInFile[i]) << "," << firstCharDistFlat[i] << "\n";
    }
    outputFile << "\n , ";

    // write label for probabilityDist
    for(int i=0; i<charInFile.size(); i++) {
        outputFile << displayChar(charInFile[i]) << ",";
    }
    outputFile << "\n";

    // write probability dist
    for(int i=0; i<probabilityDistFlat.size(); i++) {
        outputFile << displayChar(charInFile[i]) << ",";
        for(int j=0; j<probabilityDistFlat[0].size(); j++) {
            outputFile << probabilityDistFlat[j][i] << ",";
        }
        outputFile << "\n";
    }

    outputFile.close();
}
