#include <iostream>
#include <fstream>
#include <algorithm>
#include "graph.h"


using namespace std;
/*
 Ryan Park
 Assignment 11
 CSCI 340, Section 3

 I certify that this is my own work and where appropriate an
 extension of the starter code provided for the assignment.
*/

// Global vectors to hold values within traversal
std::vector<int> visited;
std::vector<pair<char,char>> output;

/* Graph constructor
 *  reads input from file, storing accordingly
 *
 *@param pointer to const char 
 *@return none
 */
Graph::Graph(const char* filename)
{
    ifstream input(filename, ios::in);
    char l;
    int val = 0;

    // Check if input is opened properly
    if(!input)
    {
        cout << "Couldnt open file!!!\n";
        exit(1);
    }

    // Take in first value size, convert char to int and set it to size
    input >> size;

    // Now read in labels 
    for(int i = 0; i < size; i++)
    {
        input >> l;
        labels.push_back(l);
    }

    // Now take in the rest after the first line of labels
    for(int i = 0; i < size; i++)
    {
        // Create a temporary list within the scope
        list<int> temp;
        // Dont care about the label and space
        input.ignore(2);
        for(int j = 0; j < size; j++)
        {
            // Take in int val, push it to temp
            input >> val;
            temp.push_back(val);
        }
        // Push temp to adj_list
        adj_list.push_back(temp);
    }
    // close file, and set visted for direct access in traversal
    input.close();
    visited.resize(size);
    for(int i = 0; i < size; i++)
    {
        visited[i] = -1;
    }
}
/* Destructor for a graph
 *
 *@param none
 *@return none
 */
Graph::~Graph()
{
    // Loop through vector of list
    for(unsigned i = 0; i < adj_list.size(); i++)
    {
        // while list in index i is not empty remove contents
        while(!adj_list[i].empty())
        {
            adj_list[i].pop_back();
        }
    }
    // remove all contents of labels
    while(!labels.empty())
    {
        labels.pop_back();
    }
}
/* Returns the size of graph
 *
 *@param none
 *@return none
 */
int Graph::Getsize() const 
{
    return size;
}

/* Private recursive funciton to traverse
 *
 *@param int v
 *@return none
 */
void Graph::Depthfirst(int v) 
{
    // Mark visit, and ouput
    visited[v] = v;
    cout << labels[v] << " ";
    int count = 0;
    // Searh through adj_list
    for(auto i = adj_list[v].begin(); i != adj_list[v].end(); i++)
    {
        // check if adj_list v and count are not the same 
        if(*i == 1 && visited[count] != count)
        {
            // Add the connection to output and recursively call
            output.push_back(make_pair(labels[v],labels[count]));
            Depthfirst(count);
        }
        count++;
    }
}

/* Public call to traverse/print node
 *
 *@param none
 *@return none
 */
void Graph::Traverse() 
{
    cout << "\n\n------- traverse of graph ------\n";
    
    // Loop through graph traversing using depthfirst
    for(int i = 0; i < size; i++)
    {
        // I is would be stored in visit index
        // if it was not visited do so
        if(visited[i] != i)
        {
            Depthfirst(i);
        }

    }
    // For the provided input this would work, but may not apply to all.
    //Depthfirst(0);

    // Format and output vector<pair<char,char>>
    cout << endl;
    for(size_t i = 0; i != output.size(); i++)
    {
        cout << "(" << output[i].first << ", " << output[i].second << ") ";
    }
    cout << endl;

    cout << "--------- end of traverse -------\n";
}

/* Prints the graph, verticies, then the edges between them
 *
 *@param none
 *@return none
 */
void Graph::Print() const 
{
    cout << "\nNumber of verticies in the graph: " << Getsize();
    cout << "\n\n-------- graph -------\n";

    for(int i = 0; i < size; i++)
    {
        // Print the label of i
        cout << labels[i] << ": ";
        int count = 0;
        int edges = 0;
        // loop through the adj_list at i, searching for 1's
        for(auto j = adj_list[i].begin(); j != adj_list[i].end(); j++)
        {
            // if 1 is found, then edge exists between verticies
            if(*j == 1)
            {
                // Simple yet complicated formatting
                if(edges > 0)
                {
                    cout << ", ";
                }
                cout << labels[count];
                if( edges < 0)
                {
                    cout << " ";
                }
                edges++;
            }
            count++;
        }
        cout << endl;
    }

    cout << "------- end of graph ------";
}