/*
Ryan Park z1940877
 Assignment 5
 CSCI 340, Section 3

 I certify that this is my own work and where appropriate an
 extension of the starter code provided for the assignment.
*/
#include "josephus.h"

#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <getopt.h>


void print_underlined_string(const std::string &message);
void print_list(const std::list<std::string> &collection, const unsigned &eliminations, int num_cols);


/**
* Print a 'Usage' message and exit(1).
*
* @param a0 The name of the command to include in the usage message.
*****************************************************************************/
static void usage(const char *a0)
{
    std::cerr << "Usage: " << a0 << " [-n number of people] [-m modulus] [-p print frequency] [-c print columns]" << std::endl;
    exit(1);
}


/**
* Create a std::list of prople with generated ID/names and reduce the
* list as per the Josephus problem algorithm.
*****************************************************************************/
int main(int argc, char **argv)
{
    unsigned num_people = 41;       // The number of people to start with
    unsigned modulus = 3;           // The count used to determine the elimination
    unsigned print_frequency = 13;  // How often to print the state of the system
    unsigned num_cols = 12;         // Number of colums to print per line

    int opt;
    while ((opt = getopt(argc, argv, "n:m:p:c:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            std::istringstream(optarg) >> num_people;
            break;
        case 'm':
            std::istringstream(optarg) >> modulus;
            break;
        case 'p':
            std::istringstream(optarg) >> print_frequency;
            break;
        case 'c':
            std::istringstream(optarg) >> num_cols;
            break;
        default:
            usage(argv[0]);
        }
    }

    if (optind < argc)
        usage(argv[0]); // If we get here, there was extra junk on command line

    // Create an empty list of type string
    std::list<std::string> jlist;

    // Insert IDs/Names using provided generator class
    std::generate_n(std::back_inserter(jlist), num_people, SEQ(num_people));

    // Initial print_list
    print_list(jlist, 0, num_cols);

    // Initialization for loop
    std::list<std::string>::iterator it = jlist.begin();
    int elim = 0;

    //Create elimination steps
    while (jlist.size() > 1) // While there is more then 1 string in the list continue elimination loop
    {
       
        for (unsigned int i = 1; i < modulus; i++)
        {
            ++it;
            // Insure that we are operating in a circle pattern
            if (it == jlist.end())
            {
                it = jlist.begin();
            }
        }
        // erase the m'th value and incriment elim for print_freq...
        it = jlist.erase(it);
        elim++;

        // Insure that we are operating in a circle pattern
        // Needs to be done because erase COULD return end
        if (it == jlist.end())
        {
            it = jlist.begin();
        }
        // every print_frequency print the list
        if (elim % print_frequency == 0)
        {
            print_list(jlist, elim, num_cols);
        }
    }
    // After elims completed print the outcome
    std::cout << "\nEliminations Completed";
    print_list(jlist, elim, num_cols);
    std::cout << std::endl;
  return 0;
}

/* prints a list of strings from list in a format
 *
 *@param refrence to list of type string, refrence to const unsigned eliminations, int cols
 *@return nothing
 ***************************/
void print_list(const std::list<std::string> &collection, const unsigned& eliminations, int num_cols)
{

    if (eliminations <= 0)
    {
        std::cout << "Initial group of people\n";
        std::string initial = "-----------------------";
        print_underlined_string(initial);
    }
    else
    {
        std::cout << "\nAfter eliminating " << eliminations << " people\n";
        std::string after = "---------------------------";
        print_underlined_string(after);
    }

    // Print contents of list collection with num_cols
    int i = 0;
    for (auto it = collection.cbegin(); it != collection.cend(); it++)
    {
        if (i == num_cols) // Creates rows
        {
            std::cout << std::endl;
			i = 0;
        }
		if(i != num_cols && i != 0)
		{
			std::cout << ", ";
		}
		std::cout << *it;
		
        i++;
    }
    std::cout << std::endl;
}

/* Prints underline for specific print_list conditions
 *
 *@param refrence to string
 *@return none
 *****************************/
void print_underlined_string(const std::string& message)
{
    std::cout << message << std::endl;
}