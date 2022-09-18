#include <iostream>
#include <iomanip>
#include <assert.h>

#include "matrix.h"

/* Constructor for rows and cols as param
 *
 *@param rows and cols
 *@return nothing
 **************************************/
matrix::matrix(unsigned int rows, unsigned int cols)
{
    resize(rows, cols); // If values are entered for rows and cols, resize mat to those
}

/* Allocates room in 2d vector using vector.resize()
 *
 *@param rows and cols for designated
 *@return nothing
 **************************************/
void matrix::resize(unsigned int rows, unsigned int cols)
{
    // Before resizing clear
    mat.clear();
    // Resizes current matrix mat vector rows
    mat.resize(rows); 

    for (unsigned int i = 0; i < rows; i++)
    {
        mat[i].resize(cols); // Loops a resizes each current mat vector row to have cols
    }
}

/* Take input from is stream and store them into the matrix
 *
 *@param &ifstream
 *@return nothing
 ***************************************/
void matrix::load(std::istream& is)
{
    
    unsigned int rows, cols;
    is >> rows >> cols; // Takes in rows and cols then resizes mat for it
    resize(rows, cols);

    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < cols; j++)
        {
            // Load in one by one and place in 2d vector
            is >> at(i,j);
        }
    }
}

/* Prints the matrix table for user display
 *
 *@param colWidth requested in argv
 *@return nothing
 *******************************************/
void matrix::print(int colWidth) const
{
    // Need to grab rows and cols for variables & display to user
    unsigned int rows = getRows();
    unsigned int cols = getCols();

    // Display to user the matrix problem
    std::cout << rows << " x " << cols << std::endl;

    // Add header
    for (unsigned int i = 0; i < (colWidth + 2) * cols + 1; i++)
        std::cout << "-";

    std::cout << std::endl;

    // Outer and inner loop to print rows/cols of matrix object
    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < cols; j++)
        {
            std::cout << "|" << std::setw(colWidth);
            std::cout << at(i, j) << " ";
        }
        std::cout << "|" << std::endl;
    }

    // Add footer - Same as header
    for (unsigned int i = 0; i < (colWidth + 2) * cols + 1; i++)
        std::cout << "-";

    std::cout << std::endl;
   
}

/* Operator overload for *, used to multiply
 *  two matrix objects
 *
 * @param rhs to multiply, then uses this-> for lhs
 * @return matrix object
 *********************************************/
matrix matrix::operator*(const matrix& rhs) const
{
     
    matrix result; // create result to return

    // Grab rows/cols from this-> and rhs
    unsigned int rows = this->getRows();
    unsigned int cols = this->getCols();
    unsigned int colsrhs = rhs.getCols();
    unsigned int rowsrhs = rhs.getRows();

    // Rule = Number of collums in this-> must == rhs rows
    assert(cols == rowsrhs);

    // Ensure result will have room for the results
    result.resize(rows, colsrhs);

    // Key on how I use this 
    //  result = c  - this-> = a - rhs = b
    //  c.at(i,j) += a.at(i,k) * b.at(k,j)

    for (unsigned int i = 0; i < rows; i++)
    {
        for (unsigned int j = 0; j < colsrhs; j++)
        {
            for (unsigned int k = 0; k < cols; k++)
            {
                result.at(i, j) += at(i, k) * rhs.at(k, j);
            }
        }
    }

    return result;
}
