/*
Ryan Park z1940877
 Assignment 6
 CSCI 340, Section 3

 I certify that this is my own work and where appropriate an
 extension of the starter code provided for the assignment.
*/

#include <iostream>
#include <deque>
#include <string>

#include "garage.h"
#include "car.h"

void get_input_vals(const std::string& line, char& xact_type, std::string& license);

int main()
{
	// Create a line for stdin, as well as a garage object to start the program
	std::string line;
	garage parking;

	while (std::getline(std::cin, line, '\n')) // Read line from file
	{
		std::string license;
		char type;
		
		// Have the license and type parsed
		get_input_vals(line, type, license);

		// Pass the input along accordinlgy or print error
		if (type == 'A')
			parking.arrival(license);
		else if (type == 'D')
			parking.departure(license);
		else
			std::cout << "'" << type << "': invalid action!\n\n";
	}
	return 0;
}

void get_input_vals(const std::string& line, char& xact_type, std::string& license)
{
	std::string delim = ":"; // What to remove from input
	size_t pos; // used to indicate index within find/substr function

	//Sift the begining for the type of event
	if (line[0] == 'A')
		xact_type = 'A';
	else if (line[0] == 'D')
		xact_type = 'D';
	else
		xact_type = line[0];

	license = line; // Set license to the line passed
	license.erase(0, 2); // Easily get rid of this because we already know what it wants
	pos = license.find(delim); // Get the index of the next delim (:)
	license = license.substr(0, pos); // cut it up until next delim and set it to that
}