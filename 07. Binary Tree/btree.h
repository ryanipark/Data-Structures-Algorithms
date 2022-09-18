#ifndef H_BTREE
#define H_BTREE

/*
 Ryan Park z1940877
 Assignment Number
 CSCI 340, Section 3

 I certify that this is my own work and where appropriate an
 extension of the starter code provided for the assignment.
*/
#include "node.h"

// Used for random left/right insertion
typedef enum { left_side, right_side } SIDE;
SIDE rnd()
{
    return rand() % 2 ? right_side : left_side;
}

template <typename T> class BinaryTree{

public:
    BinaryTree();                                      // default constructor
    unsigned     getSize() const;                      // returns size of tree
    unsigned     getHeight() const;                    // returns height of tree
    virtual void Insert(const T&);                     // inserts node in tree
    void         Inorder(void (*)(const T&));          // inorder traversal of tree

protected:
    Node<T> *root;                                      // root of tree

private:
    unsigned _getSize(Node<T> *) const;                 // private version of getSize()
    unsigned _getHeight(Node<T> *) const;               // private version of getHeight()
    void     _Insert(Node<T> *&, const T&);             // private version of Insert()
    void     _Inorder(Node<T> *, void (*)(const T&));   // private version of Inorder()
};

/* Default constructer, set root to nullptr
 *
 *@param none
 *@return none
 *****************/
template<typename T>
BinaryTree<T>::BinaryTree()
{
    root = nullptr;
}


/* Public call to private function
 *
 *@param none
 *@return size of tree starting at root
 *******************/
template<typename T>
unsigned BinaryTree<T>::getSize() const
{
    return _getSize(root);
}

/*Private call to recrusively find size of tree
 *
 *@param pointer to node root
 *@return unsigned value of size
 ***********************/
template<typename T>
unsigned BinaryTree<T>::_getSize(Node<T>* x) const
{
    // If root is null then size is 0 obviously
    if (x == nullptr)
    {
        return 0;
    }
    // Otheriwse recrusively return left and right +1 for root
    else
    {
        return (_getSize(x->left) + _getSize(x->right) + 1);
    }

}

/* Public call to private function
 *
 *@param none
 *@return height of tree starting at root
 *******************/
template<typename T>
unsigned BinaryTree<T>::getHeight() const
{
    return _getHeight(root);
}

/*Private call to recursively grab height of tree
 *
 *@param pointer to node x
 *@return unsigned value of left_h or right_h
 *************************/
template<typename T>
unsigned BinaryTree<T>::_getHeight(Node<T>* x) const
{
    unsigned left_h;
    unsigned right_h;

    // If passed node(root) is null height is 0
    if (x == nullptr)
    {
        return 0;
    }

    //Otherwise we recursively call _getHeight using left_h and right_h
    left_h = _getHeight(x->left);
    right_h = _getHeight(x->right);
    
    // Once done accounting for left/right we return the true height of the tree on case
    if (left_h > right_h)
    {
        return left_h + 1;
    }
    else
    {
        return right_h + 1;
    }
}

/* Public call to private function
 *
 *@param none
 *@return inserts node into a tree 
 *******************/
template<typename T>
void BinaryTree<T>::Insert(const T& d)
{
    _Insert(root, d);
}


/* Private call to insert data D into node x
 *
 *@param refrence to pointer node X, refrence to const T data
 *@return none
 **************************/
template<typename T>
void BinaryTree<T>::_Insert(Node<T>*& x, const T& d)
{
    // If root is null I.E. Tree empty, insert D as the root
    if (x == nullptr)
    {
        x = new Node<T> (d);
    }
    // Otherwise create a SIDE object with rnd()
    else
    {
        SIDE side = rnd();
        //If side is left insert to the left with data
        if (side == left_side)
        {
            _Insert(x->left, d);
        }
        //otherwise its right insert right with data
        else
        {
            _Insert(x->right, d);
        }
    }
}

/*Public call to private function
 *
 *@param function pointer of const refrence T
 *@return none
 *******************/
template<typename T>
void BinaryTree<T>::Inorder(void (*print)(const T&))
{
    _Inorder(root, print);
}

/* Private recrusive call for inorder
 *
 *@param pointer to node, function pointer of const reference T
 *@return none
 ***********************/
template<typename T>
void BinaryTree<T>::_Inorder(Node<T>* x, void (*print)(const T&))
{
    // If x is valid I.E. not null, follow inorder traversal
    if (x)
    {
        // left
        _Inorder(x->left, print);
        // node print
        print(x->data);
        // right
        _Inorder(x->right, print);
    }
}


#endif // End of H_BTREE


