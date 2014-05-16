/**********************************************
* File: main.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: frequency table                *
* DO NOT MODIFY                               *
***********************************************/

#include "threaded_BST.h"
#include "BiIterator.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <algorithm>


using namespace std;



/*******************************
* 2. Main function             *
********************************/

bool isNotAlphaAndNotDigit(char c)
{
    return !isalnum(c);
}

void displayElement(const MAP &table){
    for(  BiIterator it = table.begin(); it != table.end(); it++)
        cout << setw(15) << (*it).first << setw(15) << (*it).second << endl;
}

int main()
{
    MAP table;

    string name;

    /******************************************************
    * PHASE 0: Load the words in the text file            *
    *          into a the table                           *
    *******************************************************/

    cout << "File name? ";
    getline(cin, name);

    ifstream textFile(name.c_str());

    if (!textFile) {
        cerr << "Text file could not be opened!!" << endl;
        return 1;
    }

    string word;
    int counterWords=0;

    // läs in från filnamnet, while ord finns
    while(textFile >> word)
    {

        // erase punctations (only char and numbers are kept)
        word.erase(remove_if(word.begin(), word.end(), isNotAlphaAndNotDigit), word.end());
        //convert to lower-case letters
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        ELEMENT w(word, 1);

        ++counterWords;
        table.insert(w);

    }


    /******************************************************
    * PHASE 1: Display                                    *
    * - number of words in the text                       *
    * - number of unique words (occurring only once)      *
    * - frequency table                                   *
    *******************************************************/

    // number of word in file
    counterWords = 0;

    // is this necessary since we can count when we read from file?
    BiIterator it = table.begin();
    for( ; it != table.end(); it++)
        counterWords += (*it).second;

    cout << "Number of words in the file: " << counterWords << endl;
    // number of unique words
    cout << "Number of unique words in the file: " << table.size() << endl;

    cout << endl << "Frequency table sorted alphabetically..." << endl << endl;
    cout << setw(11) << "KEY" << setw(21) << "COUNTER" << endl;
    cout << setfill('=') << setw(35) << "="  << endl << setfill(' ');

    displayElement(table);

    /******************************************************
    * PHASE 3: remove all words with counter 1            *
    *          and display table again                    *
    *******************************************************/

    for(it = table.begin(); it != table.end(); it++) {
        string rw = it->first;
        if(it->second == 1 ){
            table.remove( rw); // get the key to remove
        }
    }

    //displayElement(table);

   // string wait;
   // getline(cin, wait);

    //ADD CODE



    /***********************************************************
    * PHASE 4: request two words to the user w1 and w2         *
    *          then display all words in the interval [w1,w2]  *
    ************************************************************/

    //ADD CODE



    return 0;
}
