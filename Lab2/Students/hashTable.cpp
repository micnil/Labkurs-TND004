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

    // create the theLists

    theLists.resize(sizeOfTable);
    
    nItems=0;

    // HMM. är detta rätt? kolla på sen lite extra.
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

    // HMM. kolla lite mera på!
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
    //rehash (move over) old elements

     cout << "** Re-hashing completed ..." << endl;
     cout << "Hash table load factor = "
          << fixed << setprecision(2)
          << loadFactor() << endl;
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
        if( (*it)->word == x )
            return *it;
   }

   return nullptr;
}


//Insert item w with counter i into the hash table
//Return a pointer to the inserted item
//Assumes w is not in the table
//TO IMPLEMENT
Item* HashTable::insert(string w, short i)
{
    Item *newItem = new Item(w,i);
    int slotNumber = h(w, (int)theLists.size());
    
    theLists[slotNumber].push_back(newItem);

    //collisionList.insert(collisionList.begin(),newItem);

    ++nItems;
    // ška pŒ nItems
    return newItem;
}


//Remove item w from the hash table
//If w belongs to the table then return true,
//otherwise, return false
//TO IMPLEMENT
bool HashTable::remove(string w)
{
    
    //ADD CODE
    int slotNumber = h(w, (int)theLists.size());

    list<Item*> collisionList = theLists[slotNumber];

    Item* removeString = find(w);

    //remove removeString from hashtable

    if(removeString){
        collisionList.remove(removeString);
        return true;
        --nItems;
    }
    
    return false;
}


//Overloaded operator<<: outputs all items to stream os
//TO IMPLEMENT
ostream& operator <<(ostream& os, const HashTable& T)
{
    
   //ADD CODE
      for (list<Item*> collisionList : T.theLists){
          //cout << endl << "length: " << collisionList.size() << endl;

        std::list<Item*>::iterator it;
        for (it = collisionList.begin(); it!=collisionList.end(); ++it)
            cout << *(*it);
      }
    return os;
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */

