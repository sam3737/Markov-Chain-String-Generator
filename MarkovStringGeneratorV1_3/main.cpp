#include <vector>
#include <fstream>
#include <map>
#include <chrono>
#include <iostream>

#include "Dataset.h"

int main()
{
    const bool getUserInput = true; // if the program should ask the user for inputs
    string INPUT = "input.txt"; // file to use as input
    const string OUTPUT = "output.txt"; // file to use as output
    const string DATA_OUT = "data.csv"; // file to use as data output
    int MAKE_WORDS = 100; // how many words to make

    ifstream file;
    bool invalidFile = false;

    if (getUserInput) {

        // get user input for name of input file
        cout << "Enter the name of the input file: ";
        cin >> INPUT;

        file.open(INPUT);

        while(!file) {
            cout << "Unable to open file.\nEnter the name of the input file: ";
            cin >> INPUT;
            file.open(INPUT);
        }

        // get user input for amount of words to make
        cout << "Enter amount of word to make: ";
        cin >> MAKE_WORDS;

        while(MAKE_WORDS < 1) {
            cout << "Words to make must be 1 or greater.\nEnter amount of words to make: ";
            cin >> MAKE_WORDS;
        }
    }

    // if default values are used
    else {

        // check if file is valid
        file.open(INPUT);
        if(!file) {
            cout << "Unable to open file.\n";
            invalidFile = true;
        }
    }

    // perform program function if file was opened
    if (!invalidFile) {

        // make a dataset based on the input file
        Dataset dataset(INPUT);

        // open a file to write produced words to and clear it
        fstream outputFile;
        outputFile.open(OUTPUT, std::ofstream::out | std::ofstream::trunc);

        // seed rand based on time
        srand(chrono::system_clock::now().time_since_epoch().count());

        // make and write the words
        for(int i = 0; i<MAKE_WORDS; i++) {
            outputFile << dataset.makeNewWord(3, 5);
        }

        // close output the file
        outputFile.close();

        // write data to data output file
        dataset.writeDataToFile(DATA_OUT);
    }

    return 0;
}
