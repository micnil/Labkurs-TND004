#include "hashTable.h"

#include <iomanip>

#ifndef DOXYGEN_SHOULD_SKIP_THIS


/** \brief Test whether a number is a prime.
*
* \param n an integer.
* \pre true, if n is prime. Otherwise, return false.
*
*/
//function to test if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}


/** \brief Calculate the the next prime k such that k >= n .
*
* \param n an integer.
* \pre n is larger than zero.
* \pre a prime number larger or equal to n.
*/
//function to find a prime number at least as large as n
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for(; !isPrime( n ); n += 2 );

    return n;
}


//constructor
//TO IMPLEMENT
HashTable::HashTable(int tableSize, HASH f, int ml)
 : h(f), MAX_LOAD(ml)
{
    // make the size of the table a prime number
    int sizeOfTable = ( isPrime(tableSize) ) ?  tableSize : nextPrime(tableSize);

    // är detta verkligen rätt sätt?
    theLists.resize(sizeOfTable);
    
    nItems=0;
    
    cout << "Size of the table: " << sizeOfTable << endl;
}


//Empty the table
//The Items stored in the collison lists are deleted and the lists are emptied
//TO IMPLEMENT
void HashTable::makeEmpty()
{
    // for every list in theLists, go through the items in that list
    // and delete them.
    for (list<Item*> collisionList : theLists){

        std::list<Item*>::iterator it;
        for (it = collisionList.begin(); it!=collisionList.end(); ++it)
            collisionList.erase(it);
            // DELETE item itself also?
    }

    // HMM. kolla lite mera pÂ!
}


//destructor
HashTable::~HashTable()
{
    makeEmpty();

    nItems = 0;

    cout << "** Hash Table Destructor" << endl;
}


//Return the load factor of the table
//TO IMPLEMENT
double HashTable::loadFactor() const
{
    // load factor, numOfItems / numOfSlots
    return double(nItems) / theLists.size();
}


//Rehashing function
//TO IMPLEMENT
void HashTable::reHash()
{
    cout << "** Re-hashing ..." << endl;
    cout << "Hash table load factor = "
        << fixed << setprecision(2)
        << loadFactor() << endl;

    //ADD CODE
    //Create new hashTable (vector) with double size of previous.
    int newSize = (int)theLists.size()*2; // bad to do this conversion maybe.
    int sizeOfTable = ( isPrime(newSize) ) ?  newSize : nextPrime(newSize);
    
    vector<list<Item*>> rehashedList;
    rehashedList.resize(sizeOfTable);
    
    for (list<Item*> collisionList : theLists){
        list<Item*>::iterator it;
        for (it = collisionList.begin(); it!=collisionList.end(); ++it){
            string x = (*it)->word;
            unsigned slotNumber = h(x, (int)rehashedList.size());
            rehashedList[slotNumber].push_back(*it);
            
        }
    }
    theLists = rehashedList;

    // go trough all elements in the vector theLists
        // go trough all the list of items in theLists
        // use the hash-function to know the new slot
        // then place it in the new hashed table
    
    
    //rehash (move over) old elements

     cout << "** Re-hashing completed ..." << endl;
     cout << "Hash table load factor = "
          << fixed << setprecision(2)
          << loadFactor() << endl;
    
    
    // shit detta kommer krascha!!! 
 }


//Return a pointer to the item that matches word w
//If w does not belong to the table then return nullptr
//TO IMPLEMENT
Item* HashTable::find(string x) const
{
    // use hashfunction on the word x to find the right slot.
    unsigned slotNumber = h(x, (int)theLists.size());
    list<Item*> collisionList = theLists[slotNumber];
    
    // search through the collision list (in that slot) to find a match
    std::list<Item*>::iterator it;
    for (it = collisionList.begin(); it!=collisionList.end(); it++) {
        if( (*it)->word == x ) {
           return *it;
        }
    }

    return nullptr;
}


//Insert item w with counter i into the hash table
//Return a pointer to the inserted item
//Assumes w is not in the table
//TO IMPLEMENT
Item* HashTable::insert(string w, short i)
{
    ++nItems; // öka på först för att kunna kolla iaf över MAX_LOAD lr inte.
    
    // check if need to rehash..
    if(loadFactor() >  MAX_LOAD)
        reHash();
    
    Item *newItem = new Item(w,i); // creates the item
    
    int slotNumber = h(w, (int)theLists.size());
    
    theLists[slotNumber].push_back(newItem);

    return newItem;
}


//Remove item w from the hash table
//If w belongs to the table then return true,
//otherwise, return false
//TO IMPLEMENT
bool HashTable::remove(string w)
{
    
    // find where to look in the hash table
    int slotNumber = h(w, (int)theLists.size());

    // pick that specific list from theLists
    list<Item*> collisionList = theLists[slotNumber];

    Item* removeString = find(w);

    // if found, remove and return true. otherwise false
    if(removeString!=nullptr){
        collisionList.remove(removeString);
        theLists[slotNumber] = collisionList; //FULT SÄTT. HUR GÖRA IST? måste ju skriva över den som finns i klassen.
        --nItems;
        return true;
    }
    
    return false;
    
    
}

//Overloaded operator<<: outputs all items to stream os
//TO IMPLEMENT
ostream& operator <<(ostream& os, const HashTable& T)
{
    /**bara info från mig, snyggare output. ta bort sen
     var för att kunna jämföra med exempel-txt-filen som hon skickade med **/
    cout << endl;
    cout << "Size = " << T.theLists.size() << endl;
    cout << "Number of items in the table = " << T.nItems << endl;
    cout << "Load factor = " << T.loadFactor() << endl;
    /****************************************************/
    
    for (list<Item*> collisionList : T.theLists){
        list<Item*>::iterator it;
        for (it = collisionList.begin(); it!=collisionList.end(); ++it)
            cout << *(*it);
    }
    return os;
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */

