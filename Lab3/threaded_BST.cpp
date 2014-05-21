/********************************************************
* File: threaded_BST.cpp                                *
* Author: Aida Nordman                                  *
* Course: TND004, Lab 3                                 *
* Date: VT2, 2014                                       *
* Description: class BST_threaded representing          *
*              a threaded binary search tree            *
*********************************************************/

#include "threaded_BST.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

using namespace std;


//Default Constructor: create an empty tree
//Empty tree has a dummy node as root
//The real tree is stored as left child of the dummy root
BST_threaded::BST_threaded()
 : counter(0)
{
    // create a dummy node
    ELEMENT dummy("DUMMY",0);
    root = new Node(dummy);
    // the root must point at itself
    root->left = root->right = root;
    // set the flags. see slide 19 on Lecture
    root->l_thread = root->r_thread = true;
}


//destructor
BST_threaded::~BST_threaded()
{
    if (!empty())
        delete root; // will call Nodes delete
}


//Test if the tree is empty
bool BST_threaded::empty() const
{
    // empty if the root left is pointing to the root, if the left thread of the root is true
    return (root->l_thread);

}

//Return mumber of keys (elements) stored in the tree
int BST_threaded::size() const
{
    return counter;
}


//Insert v in the tree
void BST_threaded::insert(ELEMENT v)
{
    if (empty())
    {
        //Insert first node of the BST as a left child of the BST
        root->left = new Node(v, root, root);
        root->left->l_thread = root->left->r_thread = true;
        counter = 1;

        root->l_thread = false;
    }
    else
        counter += root->left->insert(v); //call NODE::insert
}


//Remove node with key from the tree
void BST_threaded::remove(string key)
{
    // must go down to the left node since we need the parent
    if(!empty()) {
        counter -= root->left->remove(key, root, false); // send in key, parent and if right child
    }
}



//If key matches the key of an element in the container,
//then return a reference to the ELEMENT with the key
//If key does not match the key of any element in the container,
//then behaviour is undefined
ELEMENT& BST_threaded::operator[](string key)
{
    return *find(key); // since the BiIterator funcion will return ELEMENT&

    /*

    if(!empty()){
        Node *n = root->left->find(key);

        if(n)
            return n->value;
    }
     */

}


//Find the node in the BST storing key
//Return a BiIterator referring to the node storing the key, if the key is found.
//Otherwise, return this->end().
BiIterator BST_threaded::find(string key) const
{
    if(!empty()) {
        Node *ptr = root->left->find(key);

        if(ptr) // if found in the key
            return BiIterator(ptr);
    }

    return end();
}


//Return an iterator referring to the first node in the inorder traversal of the BST
BiIterator BST_threaded::begin() const
{
    if (empty()) return end();
    Node *ptr = root->left->findMin();//find the smallest node of the tree

    BiIterator it(ptr);

    return it;
}


 //Return a BiIterator referring to the past-the-end element in the BST
BiIterator BST_threaded::end() const
{
    BiIterator it(root);

    return it;
}


//Display all keys increasingly
//To be used for debugging -- ONLY
void BST_threaded::display() const
{
    if (!empty())
        root->left->display();
     else
        cout << "The container is empty!!" << endl;

}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
