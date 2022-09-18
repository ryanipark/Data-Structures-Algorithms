/*
Ryan Park z1940877
 Assignment 7
 CSCI 340, Section 3

 I certify that this is my own work and where appropriate an
 extension of the starter code provided for the assignment.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <utility>
#include <algorithm>

// Helper functions
void get_words(std::map<std::string, int>&);
void print_words(const std::map<std::string, int>&);
void clean_entry(const std::string&, std::string&);

// Used for lamba expressions in find_if()
bool ischar(char);
bool isNchar(char);
void makeLow(char&);

// Global variable for input words
int totalWords;

/* Simply creates map and calls utility functions
 *@param none
 *@return int of 0 upon execution of program
 *********************/
int main()
{
	std::map<std::string, int> m;
	get_words(m);
	print_words(m);

	return 0;
}


/* Reads words from stdin using any whitespace or \n as delim
 *  calls member function clean_entry to clean the word, examines word
 *  then either discards or incriments/creates the word on map m
 * 
 * @param refrence to map<string, int>
 * @return nothing
 */
void get_words(std::map<std::string, int>& m)
{
	// Create rawWord string for input seperated by any whitespace
	std::string rawWord;
	while (std::cin >> rawWord)
	{
		// Incriment total input words
		totalWords++;
		// local cleanWord for return of clean_entry
		std::string cleanWord;
		clean_entry(rawWord, cleanWord);

		// because if its 0 we dont care about it!
		if (cleanWord.length() != 0)
		{
			// Add the word if new or incriment frequency!
			m[cleanWord]++;
		}
	}

}

/* Cleans a word from std input of punctuation
 *
 *@param refrence to original string, and refrence to string to clean
 *@return none
 ***************************/
void clean_entry(const std::string& before, std::string& after)
{
	// Set i to first alphanumeric, and x to one before non-alphanumeric(if there is any)
	auto i = std::find_if(before.begin(), before.end(), ischar);
	auto x = std::find_if(i, before.end(), isNchar);
	// Create a new string using i and x as constructer arguments
	std::string done(i, x);
	// Make all contents of the word lowercase now that there all alphanumeric
	std::for_each(done.begin(), done.end(), makeLow);
	// Set after string passed to the same as done cleaned string(aka done)
	after = done;
}

/* Prints the output of map<string,int> m accordingly
 *
 *@param const refrence to map m
 *@return none
 ********************************/
void print_words(const std::map<std::string, int>& m)
{
	// Settings for width and num of words per line
	int NO_ITEMS = 4;
	int ITEM_WORD_WIDTH = 14;
	int ITEM_COUNT_WIDTH = 3;
	// int to count words per line
	int i = 0;

	// Loop to print contents of map
	for (auto it = m.cbegin(); it != m.cend(); ++it)
	{
		// Prints the first and second of it contained in m
		std::cout << std::setw(ITEM_WORD_WIDTH);
		std::cout << std::left << it->first;
		std::cout << ":";
		std::cout << std::setw(ITEM_COUNT_WIDTH) << it->second;
		
		//Incriment I, if i is the same as NO_ITEMS per line endl and set i to 0
		i++;
		if (i == NO_ITEMS)
		{
			std::cout << std::endl;
			i = 0;
		}
	}
	// Do proper formatting after words printed
	std::cout << std::endl;
	std::cout << "number of words in input stream   :" << totalWords << std::endl;
	std::cout << "number of words in output stream  :" << m.size() << std::endl;

}


/* used for find_if() lamba expression
 *
 * @param char i from find_if()
 * @return if i is alphanumeric
 **********************************/
bool ischar(char i)
{
	return std::isalnum(static_cast<unsigned char>(i));
}

/* used for find_if() lamba expression
 *
 * @param char i from find_if()
 * @return if i is not alphanumeric
 **********************************/
bool isNchar(char i)
{
	return !(std::isalnum(static_cast<unsigned char>(i)));
}

/* used for for_each() lamba expression
 *
 *@paran refrence to char i
 *@return none
 ****************************/
void makeLow(char& i)
{
	i = tolower(i);
}