#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "node.h"
#include "BinaryTree.h"
/*
    The start of implementing binarysearchtree class
*/
/*
 Ryan Park z1940877
 Assignment 9
 CSCI 340, Section 3

 I certify that this is my own work and where appropriate an
 extension of the starter code provided for the assignment.
*/


template <typename T>
class BinarySearchTree : public BinaryTree<T>
{
public:
    void Insert(const T &);       // inserts node with value x
    bool Search(const T &) const; // searches leaf with value x
    bool Remove(const T &);       // removes leaf with value x
private:
    void _Insert(Node<T> *&, const T &);      // private version of insert
    bool _Search(Node<T> *, const T &) const; // private version of search
    void _Remove(Node<T> *&, const T &);      // private version of remove
    bool _Leaf(Node<T> *node) const;          // checks if node is leaf
};

/* Public call to private function
 *
 *@param refrence to const T
 *@return none
 */
template<typename T>
void BinarySearchTree<T>::Insert(const T& d)
{
    _Insert(this->root, d);
}

/* Private recrusive function to insert a node
 *
 *@param refrence to pointer node type T, reference of a const T
 *@return none
 */
template<typename T>
void BinarySearchTree<T>::_Insert(Node<T> *& x, const T & d)
{
    // If root is nullptr insert as root
    if(x == nullptr)
    {
        x = new Node<T>(d);
    }
    // If data is less then x data insert left recursively
    else if(d < x->data)
    {
        _Insert(x->left, d);
    }
    // If data is greater then x data insert right recurisvely
    else if(d > x->data)
    {
        _Insert(x->right, d);
    }
    // If its none of these, it will be a duplicate, BST's dont have duplicates
    else
    {
        return;
    }
}

/* Public call to private function
 *
 *@param refrence to const T
 *@return bool true/false on case
 */
template<typename T>
bool BinarySearchTree<T>::Search(const T& d) const
{
    return _Search(this->root, d);
}

/* Private recurisve call from public call
 *
 *@param pointer to node of type T and refrence to const T
 *@return bool true/false on case
 */
 template<typename T>
 bool BinarySearchTree<T>::_Search(Node<T> * x, const T &d) const
 {
    // Check if node is null
    if(x == nullptr)
    {
        return false;
    }
    // Check if current node contains same data
    else if(x->data == d && _Leaf(x) == true)
    {
        return true;
    }
    // Other wise recursively call going left
    if(d < x->data)
    {
        return _Search(x->left, d);
    }
    // If its not left its right
    else
    {
        return _Search(x->right, d);
    }
 }


/* Public call to private function
 *
 *@param refrence to const T
 *@return bool true/false on case
 */
template<typename T>
bool BinarySearchTree<T>::Remove(const T& d)
{
    // If the data is found in the tree go ahead and remove
    if(Search(d) == true)
    {
        _Remove(this->root, d);
        return true;
    }
    // Otherwise its not found return false
    else
    {
        return false;
    }
    
}


/* Private call to public function to remove a leaf node
 *
 *@param refrence to pointer node of T, refrence to const T
 *@return none
 */
 template<typename T>
 void BinarySearchTree<T>::_Remove(Node<T>*& x, const T& d)
 {
    // Base case even though we reassure with search()
    if(x == nullptr)
    {
        return;
    }
    // Second base, Check if current node contains same data + is leaf, it deletes the node'
    //  then sets the refrence to nullptr and exits
    else if(x->data == d && _Leaf(x) == true)
    {
        delete x;
        x = nullptr;
        return;
    }
    // Other wise recursively call going left
    if(d < x->data)
    {
        _Remove(x->left, d);
    }
    // If its not left its right
    else
    {
        _Remove(x->right, d);
    }
 }


/* Checks if a node is a leaf or not
 *
 *@param pointer to node of type T
 *@return bool true/false on case
 */
template<typename T>
bool BinarySearchTree<T>::_Leaf(Node<T> *node) const
{
    // If its left and right is nullptr it is
    if(node->left == nullptr && node->right == nullptr)
    {
        return true;
    }
    // Fall through, it its not a nullptr node and has a left or right 
    // ptr its not a leaf
    return false;
}       

#endif