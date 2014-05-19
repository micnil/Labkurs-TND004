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
    if (!l_thread) delete left;  //destructor called recursively for left child node
    if (!r_thread) delete right; //destructor called recursively for right child node
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{

    // the value is smaller, insert at left
    if ( v.first < value.first ) {
        if (!l_thread) // the left is not a thread (have a child), go deeper down in the tree
            return left->insert(v);
        else{
            Node *n = new Node(v, left, this);
            n->r_thread = n->l_thread = true;
            
            left = n; // hang the new node on to the tree
            l_thread = false; // it is not a thread anymore
            return true;
        }
    }
    // the value is larger, insert at right
    else if( v.first > value.first ) {
        if (!r_thread) // go deeper down in the tree
            return right->insert(v);
        else{
            Node *n = new Node(v, this, right);
            n->r_thread = n->l_thread = true;
            
            right = n; // hang the new node on to the tree
            r_thread = false; // it is not a thread anymore
            return true;
        }

    }

    // the element already exist in the tree, add counter
    value.second++;//= v.second;
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

    if(  key < value.first  /*key.compare(value.first) < 0 */){ // smaller
        if(!l_thread)
            return left->remove(key,this,false);
        else
            return false;
    }
    else if( key > value.first  /*key.compare(value.first) > 0*/ ) { // larger
        if(!r_thread)
            return right->remove(key, this, true);
        else
            return false;
    }
    else{ // found the key in the table
        if(!l_thread && !r_thread){
            // replace with min of the right tree value and then start recursion again!
            // lecture 5, slide 27
            value = right->findMin()->value;
            return right->remove(value.first, this, true);
        }
        else{
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
        if(r_thread && l_thread){ // no children, 1c
            parent->l_thread = true;
            parent->left = this->left;
            
            delete this;
        }
        else if(!r_thread){   // has only a right child, 1a
            parent->left = this->right;

            // find the most left child of right
            right->findMin()->left = this->left;

            this->right = nullptr; //disconnect from subtrees

            delete this;
        }
        else if(!l_thread){ // has only a left child, 1b
            parent->left = this->left;

            // find the most right child of left
            left->findMax()->right = this->right;

            this->left = nullptr; //disconnect from subtrees

            delete this;
        }
    }
    else { // the node is a right child of parent
        if(r_thread && l_thread){ // no children, 2c
            parent->r_thread = true;
            parent->right = this->right;
            
            delete this;
        }
        else if(!r_thread){   // has only a right child, 2a
            parent->right = this->right;

            // find the most left child
            right->findMin()->left = this->left;

            this->right = nullptr; //disconnect from subtrees

            delete this;
        }
        else if(!l_thread){ // has only a left child, 2b
            parent->right = this->left;

            // find the most right child
            left->findMax()->right = this->right;

            this->left = nullptr; //disconnect from subtrees

            delete this;
        }
    }
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    if(key.compare(value.first) == 0) // the same
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
