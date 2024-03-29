/**********************************************
* File: BiIterator.cpp                        *
* Author: Aida Nordman                        *
* Course: TND004, Lab 2                       *
* Date: VT2, 2014                             *
* Description: class biIterator               *
* Represents bidirectional iterators          *
***********************************************/


#include "BiIterator.h"


#ifndef DOXYGEN_SHOULD_SKIP_THIS


// Constructor
BiIterator::BiIterator(Node *ptr)
 : current(ptr)
 {

 }

//Dereferencing operator
ELEMENT& BiIterator::operator*() const
{
    return current->value;
}


//Member access operator
ELEMENT* BiIterator::operator->() const
{
    return &(current->value);
}


//Equality comparison operator
bool BiIterator::operator==(const BiIterator &it) const
{
    // if same they return 0.
    return (current->value.first == it.current->value.first); // use string compares
   // return !(current->value.first).compare(it.current->value.first); // == 0
}


//Inequality comparison operator
bool BiIterator::operator!=(const BiIterator &it) const
{
    return (current->value.first != it.current->value.first);
    //return ( (current->value.first).compare(it.current->value.first) !=0 );
}


//Pre increment operator
BiIterator& BiIterator::operator++()
{
    if(!current->r_thread)
        current = current->right->findMin(); // find the smallest node of the right subtree
    else
        current = current->right; // follow right thread

    return *this;
}



//Pos increment operator: see page 277 and 278 of C++ direkt
BiIterator BiIterator::operator++(int)
{
    BiIterator temp = *this;
    ++(*this); //this->operator??();

    return temp;
}

//Pre decrement operator
BiIterator& BiIterator::operator--()
{
    if(!current->l_thread)
        current = current->left->findMax(); // find the max node of the left subtree
    else
        current = current->left;

    return *this;
}

//Pos decrement operator
BiIterator BiIterator::operator--(int)
{
    BiIterator temp = *this;
    --(*this);

    return temp;

}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */
