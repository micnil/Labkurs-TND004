/**********************************************
* File: node.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: class Node                     *
***********************************************/

#include "node.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS


Node::Node(ELEMENT v, Node *l, Node *r)
 : value(v), left(l), right(r)
{
    l_thread = r_thread = false;
}


//Destructor
//recursively deletes the nodes in the left_subtree and right-subtree
Node::~Node()
{
    //ADD CODE
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{

    // the value is smaller, insert at left
    if ( (v.first).compare(value.first) < 0  ) {
        if (!l_thread) // the left is not a thread, go deeper down in the tree
            left->insert(v);
        else{
            Node *n = new Node(v, left, this);
            left = n;
            left->r_thread = left->l_thread = true;
            l_thread = false; // den vi Šr i
            
            return true;
        }
    }
    // the value is larger, insert at right
    else if( (v.first).compare(value.first) > 0 ) {
        if (!r_thread) // go deeper down in the tree
            right->insert(v);
        else{
            Node *n = new Node(v,this, right);
            right = n;
            right->r_thread = right->l_thread = true;
            r_thread = false; // den vi Šr i
            
            return true;
        }
        
    }

    // the element already exist in the tree
    return false;
}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{
    // use removeMe here
    // find the node to remove
    
    if( key.compare(value.first) < 0 ){
        if(!l_thread)
            return remove(key,left,false); // hmm, anvŠnda parent ngn stans..
        else
            return false;
    }
    else if(key.compare(value.first) > 0 ) {
        if(!r_thread)
            return remove(key, right, true);
        else
            return false;
    }
    else{ // they are alike!
        if(!l_thread && !r_thread){
            //replace value and then start recursion again! LITE OS€KER: MKT OS€KER
            // http://forums.devshed.com/programming-42/binary-search-tree-remove-function-303429.html
            value = findMin()->value;
            return remove(value.first, this, true);
        }
        else{
            //olika fall hŠr.. hmm
            removeMe(parent,isRight);
            return true;
        }
    }
    
    
}



//Remove this node -- this node has at most one child
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
//Remove has 6 cases
//1a: a left child with only a right child
//1b: a left child with only a left child
//1c: a left child with no children
//2a: a right child with only a right child
//2b: a right child with only a left child
//2c: a right child with no children
void Node::removeMe(Node* parent, bool isRight)
{
    if(!isRight){ // the node is a left child of parent
        if(!r_thread && !l_thread){ // no children
            parent->l_thread = true;
            parent->left = this->left;
            delete this;
        }
        else if(!r_thread){   // has only a right child
            // flytta en jŠvla massa pekare..
            parent->left = this->right;
            this->right->left = this->left;
            delete this;
        }
        else if(!l_thread){ // has only a left child
            parent->left = this->left;
            this->left->right = this->right;
            delete this;
        }
    }
    else { // the node is a right child of parent
        if(!r_thread && !l_thread){ // no children
            parent->r_thread = true;
            parent->right = this->right;
            delete this;
        }
        else if(!r_thread){   // has only a right child
            parent->right = this->right;
            this->right->left= this->left;
            delete this;
        }
        else if(!l_thread){ // has only a left child
            parent->right = this->right;
            this->left->right = this->right;
            delete this;
        }
    }
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    if(key.compare(value.first) == 0)
         return this;
    else if (key.compare(value.first) < 0 && !l_thread)
        return left->find(key);
    else if(key.compare(value.first) > 0 && !r_thread)
        return right->find(key);
    
    return nullptr;
}


//Return a pointer to the node storing the smalest value
//of the tree whose root is this node
Node* Node::findMin()
{
    Node *n = this;
    while (!n->l_thread)
        n = n->left;
        
    return n;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    Node *n = this;
    while (!n->r_thread)
        n = n->right;
    
    return n;
}



//Display in inorder all keys
//stored in the tree whose root is this node
//recursive function
//Used for debugging -- ONLY
void Node::display() const
{
    if ( !l_thread ) //display left sub-tree
        left->display();

    cout << value.first << " "; //display key stored in the node

    if ( !r_thread ) //display right sub-tree
        right->display();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
