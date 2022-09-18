#ifndef STACK_H
#define STACK_H
#include <queue>

/*
Ryan Park z1940877
 Assignment 4
 CSCI 340, Section 3

 I certify that this is my own work and where appropriate an
 extension of the starter code provided for the assignment.
 */

template<typename T>
class Stack
{
private:
    std::queue<T> q1;	// These queues are where the stack's elements 
    std::queue<T> q2;	// are to be saved.

public:
    bool empty() const;
    int size() const;
    const T& top();
    void push(const T &val);
    void pop();
};


// Note that the members of a template go into a .h file since 
// they are not compiled directly into a .o file like the members 
// of regular/non-template classes.




// Place your Stack class member implementations here.

/* Checks if stack is empty
 *
 *@param none
 *@return True/False on case
 *************************/
template<typename T>
bool Stack<T>::empty() const
{
    if (q1.size() == 0)
        return true;
    else
        return false;
}

/* Returns size of elements in stack(q2)
 *
 *
 *@param none
 *@return int of size
 ****************************/
template<typename T>
int Stack<T>::size() const
{
    return q1.size();
}

/* Returns the top of the stack
 * aka front of q1
 *
 *@param none
 *@return cont T& to top of stack q1.front()
 *********************************************/
template<typename T>
const T& Stack<T>::top()
{
    if (q1.empty())
        exit(1);
    else
        return q1.front();
}


/* Push value into the stack
 *
 * @param refrence to const T
 * @return none
 ***************************/
template<typename T>
void Stack<T>::push(const T& val)
{
    // If q1 is empty then stack is empty, just insert val
    if (q1.empty())
    {
        q1.push(val);
    }
    // If its not, push all elements at front of q1 to q2 while poping
    else
    {
        // Push current stack into q2, poping as goes
        while (!q1.empty())
        {
            q2.push(q1.front());
            q1.pop();
        }
        // Push the value into q1
        q1.push(val);

        // Then take the elements back from q2.front and push them to q1 while poping
        while (!q2.empty())
        {
            q1.push(q2.front());
            q2.pop();
        }
    }

}

/* Removes value from the top of the stack
 *
 *@param none
 *@return none
 ***********************/
template<typename T>
void Stack<T>::pop()
{
    if (!q1.empty())
        q1.pop();
    else
        std::cerr << "\nError: Trying to pop an empty stack!\n";
}




#endif // STACK_H
