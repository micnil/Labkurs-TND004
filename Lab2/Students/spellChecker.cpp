#include "spellChecker.h"

#include <fstream>
#include <algorithm>
#include <cctype>
#include <iomanip>

/** \brief Hash function for English words
*
* \note Polynomial accumulation is used. See pag. 213 of course book.
* \param s a string (word).
* \param tableSize an integer representing the size of the hash table.
* \return unsigned int representing the hash value of s (overlow is allowed).
*
*/
//Hash function for English words
//Polynomial accumulation
//the Horner's rule is used to compute the value
//See pag. 213 of course book
unsigned my_hash(string s, int tableSize)
{
    unsigned hashVal = 0;

    for(int i= 0; i < s.length(); i++)
        hashVal= 37 * hashVal + s[i];

    hashVal %= tableSize;

    return hashVal;
}


bool isNotAlpha(char c)
{
    return !isalpha(c);
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS

//Constructor
//Text file fileName should contain a dictionary with n words
//TO IMPLEMENT
SpellChecker::SpellChecker(string fileName, int n)
{
    // when creating the dictionary, set the max load factor allowed.
    // HashTable(tableSize, hashFunction, max_load) anroppa på detta sätt typ

    dictionary = new HashTable(n, my_hash, 2);

    // read in all the words from file and add to dictionary
    ifstream file(fileName);
    if (!file) {
        cerr << "Dictionary file could not be opened!!" << endl;
        exit(1);
    }

    //load the dictionary
    string w;

    while(file >> ws && getline(file, w,'\r')) // på mac behövs '\r', annars ska det vara '\n'
    {
        addWord(w); 
    }


    nWords = n;

    //ADD CODE
}


//Destructor
//TO IMPLEMENT
SpellChecker::~SpellChecker()
{
   //ADD CODE

   cout << "** Spell Checker Destructor" << endl;
}


//Test whether word w is in the dictionary
//If w is a correct word (belongs to the dictionary) then return true, else return false
//If w is a misspelling then the dictionary and
//the misspeling list might need to be updated
//TO IMPLEMENT
bool SpellChecker::testSpelling(string w)
{
    //remove non-alpha chars
    w.erase(remove_if(w.begin(), w.end(), isNotAlpha), w.end());

    //convert to lower-case letters
    transform(w.begin(), w.end(), w.begin(), ::tolower);

    if (w == "") return true; //case of a word consisting only of punctuation signs

    //ADD CODE
    Item* word = dictionary->find(w);
    if(word && word->counter==0)
        return true;
    else if(word && word->counter > 0){
        word->counter++;
        return false;
    }
    else
    {
        Item* newItem = dictionary->insert(w,1);
        misspellings.push_front(newItem);
        
        // do stuff!
        // if not in the dictionary, add
        // also add to the misspellings
        return false;
    }




    return false;
}


//Add a new word w to the dictionary
//The list of addedWords is also updated
//TO IMPLEMENT
void SpellChecker::addWord(string w)
{
    // behövs det kollas hur många ord som redan finns??
    dictionary->insert(w,0);

    //ADD CODE
}


//Remove all extra added words from the dictionary
//This function can be called before starting to spell check a new text file
//TO IMPLEMENT
void SpellChecker::clean()
{
    //ADD CODE
}


//1. Create the log file with the misspellings
//2. Empty the misspellings list
//TO IMPLEMENT
void SpellChecker::createLog(ostream& os)
{
    os << "*** LIST OF MISSPELLINGS" << endl;
    os << "=========================" << endl;

    // go trough the list of misspellings and show
    list<Item*>::iterator it;
    for (it = misspellings.begin(); it!=misspellings.end(); ++it){
        os << *(*it);
    }

    //ADD CODE
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
