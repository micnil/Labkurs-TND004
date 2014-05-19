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
    cout << setw(11) << "KEY" << setw(21) << "COUNTER" << endl;
    cout << setfill('=') << setw(35) << "="  << endl << setfill(' ');
    for(BiIterator it = table.begin(); it != table.end(); ++it)
        cout << setw(15) << it->first << setw(15) << it->second << endl;
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

    // read in from file
    while(textFile >> word)
    {
        // erase punctations (only char and numbers are kept)
        word.erase(remove_if(word.begin(), word.end(), isNotAlphaAndNotDigit), word.end());
        //convert to lower-case letters
        transform(word.begin(), word.end(), word.begin(), ::tolower);

        ELEMENT w(word, 1);
        table.insert(w);

    }


    /******************************************************
    * PHASE 1: Display                                    *
    * - number of words in the text                       *
    * - number of unique words (occurring only once)      *
    * - frequency table                                   *
    *******************************************************/

    // number of word in file, numberOfWords(table) is a function
    int counterWords = 0;
    for(BiIterator it = table.begin(); it != table.end(); ++it)
        counterWords += it->second;
    
    cout << "Number of words in the file: " << counterWords << endl;
   
    // number of unique words
    cout << "Number of unique words in the file: " << table.size() << endl;

    cout << endl << "Frequency table sorted alphabetically..." << endl << endl;
    displayElement(table);

    /******************************************************
    * PHASE 3: remove all words with counter 1            *
    *          and display table again                    *
    *******************************************************/
    
    string wait;
    getline(cin, wait);
    
    for (BiIterator it = table.begin(); it != table.end(); ++it){
        if(it->second == 1 ){
            string rm = it->first;
            --it;               // move back the iterator, otherwise it will not work...
            table.remove(rm);
        }
    }

    cout << endl << "Number of words after remove: " << table.size() << endl;
    cout << endl << "Frequency table sorted alphabetically again..." << endl << endl;
    displayElement(table);

    /***********************************************************
    * PHASE 4: request two words to the user w1 and w2         *
    *          then display all words in the interval [w1,w2]  *
    ************************************************************/

    string w1,w2;
    
    cout << endl << endl << "Enter two words: ";
    cin >> w1 >> w2;
    
    BiIterator it1 = table.find(w1);
    BiIterator it2 = table.find(w2);
    
    // TODO: check if the word exist in the table or not..
    
    
    --it1; // move on iterator so we can write this out also
    
    // larger to the smallest
    cout << endl << endl << "Frequency table in [" << w1 << ", " << w2 << "]" << endl;
    for( ; it1!=it2; --it2){
        cout << setw(15) << it2->first << setw(15) << it2->second << endl;
    }



    return 0;
}
