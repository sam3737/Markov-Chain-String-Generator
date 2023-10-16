#include <fstream>
#include <map>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

/**
compareFunction

Returns if the ASCII of one character
is greater than another. Used for
alphabetizing the data.
**/
bool compareFunction (char a, char b) {return a<b;}

// CHAR FUNCTIONS

/**
makeCharsInFile

Create a vector with every character that
appears in the file in the order in which
they appear.
**/
vector<char> makeCharsInFile(string fileName) {

    // initialize varaibles
    vector<char> charsInFile;
    int mapSizeHolder;
    unordered_map<char, int> countMap;

    // get all of the text in the file
    ifstream file(fileName);
    stringstream buffer;
    buffer << file.rdbuf();
    string totalString = buffer.str();

    // convert the whole string to lowercase
    transform(totalString.begin(), totalString.end(), totalString.begin(),[](unsigned char c){ return tolower(c); });

    // for every char, try and add it to a map, if the
    // size of the map changes, add the char to the output
    for (int i = 0; i < totalString.length(); i++) {
        mapSizeHolder = countMap.size();
        countMap[totalString[i]]++;
        if (mapSizeHolder < countMap.size()) {
            charsInFile.push_back(totalString[i]);
        }
    }

    sort(charsInFile.begin(),charsInFile.end(),compareFunction);

    return charsInFile;
}

/**
makeCharMap

Create a map relating each character in charInFile
with its index.
**/
map<char, int> makeCharMap(vector<char> charInFile) {

    // for every char, add the char and its index to the map
    map<char, int> outputMap;
    for(int i=0; i<charInFile.size(); i++) {
        outputMap.insert({charInFile[i], i});
    }

    return outputMap;
}

/**
makeFirstCharDist

Return a vector of the amount of times that
each character appear at the beginning of a
data point.
**/
vector<int> makeFirstCharDist(string fileName, map<char, int> charMap) {

    // make a vector with a 0 element for every char
    vector<int> output(charMap.size());
    fill(output. begin(), output. end(), 0);

    //open the file
    fstream file(fileName);

    // for each line in the file, add 1 to the element
    // of the vector corresponding to the first char
    string line;
    while (getline(file, line)) {
        output[charMap[tolower(line[0])]]++;
    }

    file.close();

    return output;
}

/**
makeCharDist

Return a vector of the amount of times
each character appears in the file, excluding
appearances at the end of lines.
**/
vector<int> makeCharDist(string fileName, map<char, int> charMap) {

    // make a vector with a 0 element for every char
    vector<int> output(charMap.size());
    fill(output. begin(), output. end(), 0);

    // open the file
    fstream file(fileName);

    // for every char of every line, add 1 to the
    // corresponding element of the output
    string line;
    while (getline(file, line)) {
        for(char c : line) {
            output[charMap[c]]++;
        }
    }

    file.close();

    return output;
}

/**
makeFirstCharDistFlat

Take firstCharDist and make it so that
all of the elements of the array sum to
1, while maintaining the same ratio.
**/
vector<double> makeFirstCharDistFlat(vector<int> firstCharDist) {

    // create a vector of the same size as firstCharDist
    vector<double> output(firstCharDist.size());

    // sum all of the elements in firstCharDist
    int sum = 0;
    for(int i : firstCharDist) {
        sum += i;
    }

    // for every element in firstCharDist, add
    // that divided by the sum to the output
    for(int i=0; i<output.size(); i++) {
        output[i] = firstCharDist[i] / static_cast<double>(sum);
    }

    return output;
}

// DATA FUNCTIONS

/**
makeData

Return a vector with each line of a
file as a separate string element.
**/
vector<string> makeData(string fileName) {

    vector<string> output;

    // open the file
    fstream file(fileName);

    // for every line, add that line to output
    string line;
    while (getline(file, line)) {
        output.push_back(line);
    }

    file.close();

    return output;
}

/**
makeProbabilityDistFlat

Return a 2D vector where the dimensions are
characters and their consecutive character,
and the values are the frequency that the
consecutive character follows the character.
Each first dimension sums to 1.
**/
vector<vector<double>> makeProbabilityDistFlat(vector<string> data, map<char,int> charMap, vector<int> charDist) {

    // create a 2D vector with both dimensions have an element for every char
    vector<vector<double>> output(charMap.size(), vector<double>(charMap.size()));

    // For every char in data, add 1/n to the coordinates corresponding
    // to that letter and the next letter, where n is the total
    // quantity of the first letter in the file
    char currentLetter, nextLetter;
    for (string dataPoint : data) {
        for (int i=0; i<dataPoint.length(); i++) {
            currentLetter = dataPoint[i];
            nextLetter = dataPoint[i+1];
            if((int)nextLetter == 0) { // if the next letter is null, set it to '\n'
                nextLetter = '\n';
            }
            output[charMap[currentLetter]][charMap[nextLetter]] += 1.0 / charDist[charMap[currentLetter]];
        }
    }

    return output;
}

/**
weightedRand

Take a vector and randomly return one of its
indexes, with each index weighted according
to its value. The vector should sum to 1.
**/
int weightedRand(vector<double> weights) {

    // generate and random number from 0-1
    double randNum = (double) rand() / RAND_MAX;

    // default counter to 0, and weightAdder to the first weight
    int counter = 0;
    double weightAdder = weights[counter];

    // add weights, checking when randNum becomes greater
    while(randNum > weightAdder ) {
        counter++;
        weightAdder += weights[counter];
    }

    // return the index at which randNum becomes greater
    return counter;
}

/**
displayChar

Return the string "\\n" when the input
is '\n'. Otherwise return the input in
the form of a string.
**/
string displayChar(char charIn) {

    string output = "";

    switch(charIn) {
    // if charIn is '\n', return "\\n"
    case '\n':
        return "\\n";
        break;
    // otherwise, return charIn as a string
    default:
        return output.assign(1, charIn);
    }
}





