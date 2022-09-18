/*
 Ryan Park z1940877
 Assignment # 3
 CSCI 340, Section 3

 I certify that this is my own work and where appropriate an
 extension of the starter code provided for the assignment.
*/

#include "twosearch.h"

#include <getopt.h>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <vector>


/**
* see: 
* https://en.wikipedia.org/wiki/Usage_message
* https://www.ibm.com/docs/en/aix/7.2?topic=commands-usage-statements
*
* @param a0 The value of argv[0] (the name of the command) so that it 
*   can be printed.
*
* @note This function will terminate the application via exit(1).
******************************************************************************/
static void usage(const char *a0)
{
    std::cerr << "Usage: " << a0 << " [-l rand_low] [-h rand_high] [-a a_size] [-b b_size] [-x a_seed] [-y b_seed] [-c print_cols] [-w col_width]" << std::endl;
    std::cerr << "    rand_low   = rand() low bound (default=1)" << std::endl;
    std::cerr << "    rand_high  = rand() high bound (default=1000)" << std::endl;
    std::cerr << "    a_size     = size of vector A (default=200)" << std::endl;
    std::cerr << "    b_size     = size of vector B (default=100)" << std::endl;
    std::cerr << "    a_seed     = random seed for vector A (default=1)" << std::endl;
    std::cerr << "    b_seed     = random seed for vector B (default=3)" << std::endl;
    std::cerr << "    print_cols = number of colums per line (default=16)" << std::endl;
    std::cerr << "    col_width  = printed column value width (default=4)" << std::endl;
    exit(1);
} // End of usage()

/**
* Parse the command-line args, create and sort vector A, create vector B,
* search vector A for those elements appearing in vector B using both
* a linear and binary search, and print the hit-rate (the percentage of 
* items in B that have been located in A.)
*
* If an invalid command-line arg is encountered, print a Usage statement 
* and terminte with an exit-status of 1.
*
* @return zero
******************************************************************************/
int main(int argc, char **argv)
{
    // Demonstrate the use of getopt() to override default config parameters 
    int rand_low = 1;
    int rand_high = 1000;
    int a_size = 200;
    int b_size = 100;
    int a_seed = 1;
    int b_seed = 3;
    int print_cols = 16;
    int col_width = 4;

    int opt;
    // see: http://faculty.cs.niu.edu/~winans/CS340/2022-sp/#getopt
    while ((opt = getopt(argc, argv, "a:b:c:h:l:w:x:y:")) != -1)
    {
        switch(opt)
        {
        case 'a':
            // see https://en.cppreference.com/w/cpp/string/basic_string/stol
            a_size = std::stoi(optarg); // override the default for a_size
            break;

        case 'b':
            b_size = std::stoi(optarg);
            break;
        case 'c':
            print_cols = std::stoi(optarg);
            break;
        case 'h':
            rand_high = std::stoi(optarg);
            break;
        case 'l':
            rand_low = std::stoi(optarg);
            break;
        case 'w':
            col_width = std::stoi(optarg);
            break;
        case 'x':
            a_seed = std::stoi(optarg);
            break;
        case 'y':
            b_seed = std::stoi(optarg);
            break;

        default:
            // got an arg that is not recognized...
            usage(argv[0]);     // pass the name of the program so it can print it
        }
    }

    // Make sure there are not any more arguments (after the optional ones)
    if (optind < argc)
        usage(argv[0]);

    // Add application logic here...

    //1.
    std::vector<int> A(a_size);
    std::vector<int> B(b_size);

    //2  & 3
    init_vector(A, a_seed, rand_low, rand_high);
    init_vector(B, b_seed, rand_low, rand_high);

    //4
    std::cout << "A vector:" << std::endl;
    print_vector(A, print_cols, col_width);

    //5
    sort_vector(A);

    //6
    std::cout << "A vector sorted:" << std::endl;
    print_vector(A, print_cols, col_width);

    //7
    std::cout << "B vector :" << std::endl;
    print_vector(B, print_cols, col_width);

    //8
    int linsearch = search_vector(A, B, linear_search);

    //9
    std::cout << "Linear search: Percent of Successful Searches = ";
    print_stat(linsearch, B.size());

    //10
    int binsearch = search_vector(A, B, binary_search);

    //11
    std::cout << "\nBinary search: Percent of Successful Searches = ";
    print_stat(binsearch, B.size());
    std::cout << std::endl;
    return 0;

} // End of main()



/* Initializes values in vector according to
 * the seed/low/high passed to it.
 *
 *@param refrence to vector, a seed, low and high
 *@return none
 ***************************************************/
void init_vector(std::vector<int>& vec, int seed, int lo, int hi)
{
    //Initilize random number generator
    srand(seed);

    for (unsigned int i = 0; i < vec.size(); i++)
    {
        // Since vec is not resized, create variable and push back rand element
        //int j = rand()%(hi - lo + 1) + lo;
        //vec.push_back(j);
        vec[i] = rand() % (hi - lo + 1) + lo;
    }
}

/* Prints vector v given print_cols elements on each line
 * and each value setw()'d using col_width
 *
 *
 *@param refrence to vector, print_cols value, col_width value
 *@return none
 ****************************************************************/
void print_vector(const std::vector<int>& v, int print_cols, int col_width)
{
    // Add header
    for (int j = 0; j < (col_width + 2) * print_cols + 1; j++)
        std::cout << "-";
    
    // Main print code fragment
    for (unsigned int i = 0; i < v.size() ; i++)
    {
        if (i % print_cols == 0) // Creates rows
        {
            std::cout << std::endl;
            std::cout << "|";
        }

        std::cout << std::setw(col_width) << v[i] << " |";
    }

    // Simple yet complicated way to fill in remaining empty cells in table
    if (v.size() % print_cols != 0)
    {
        unsigned int rows = v.size() / print_cols + 1;
        unsigned int fill = (rows * print_cols) - v.size();
        for (unsigned int y = 0; y < fill; y++)
        {
            std::cout << std::setw(col_width) << " " << " |";
        }
    }


    // Add footer
    std::cout << std::endl;
    for (int x = 0; x < (col_width + 2) * print_cols + 1; x++)
        std::cout << "-";
    std::cout << std::endl;

}

/* Sorts vecotr in ascending order
 *
 *@param refrence to vector
 *@return none
 ************************************/
void sort_vector(std::vector<int>& v)
{
    // STL sort from <algorithm>
    sort(v.begin(), v.end());
}

/* Search vector
 *
 *
 *@param const refrence to vector v1 and v2
 *  ....and bool pointer p to a (const refrence to vector , int)
 * @return int found for pint_stat
 *******************************************************/
int search_vector(const std::vector<int>& v1, const std::vector<int>& v2, bool (*p)(const std::vector<int> &, int))
{
    // Initialized a found variable to return for print_stat
    int found = 0;

    // Loop through elements of v2 
    for (unsigned int i = 0; i < v2.size(); i++)
    {
        // For every element in v2, check if its in v1
        // where p is used in replacement of bool linear/binary_search
        if (p (v1, v2[i]) == true)
        {
            // if boolean phrase is true add 1 to found
            found++;
        }

    }
    // Return the total found
    return found;
}

/* Prints stat in float using values passed to it
 *
 *@param found, total both int
 *@return none
 ******************************************/
void print_stat(int found, int total)
{
    // Used for testing remove before submitting
    //std::cout << found << " " << total << std::endl;

    std::cout << std::setprecision(2) << std::fixed << ((float)found / (float)total) * 100 << "%";
}

/* Linear search a vector using refrence/value passed
 * using stl find()
 * 
 *@param refrence to const vector, and int to find
 *@return bool true/false dependable on case
 *************************************************/
bool linear_search(const std::vector<int>& v, int x)
{   
    
    // Where as the return value of find is an iterator should be the location
    // of where the first successful find was, if its end it is not found
    if (std::find(v.begin(), v.end(), x) != v.end())
        return true;
    else
        return false;
}

/* Binary search using stl binary_search()
 *
 *@param const refrence to vector and int o find
 *@return bool true/false depenable on case
 ********************************************/
bool binary_search(const std::vector<int>& v, int x)
{
   // The return value from binary_search stl is true or false therefor I wont check
    return std::binary_search(v.begin(), v.end(), x);
}



