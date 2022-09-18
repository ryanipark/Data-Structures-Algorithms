#include <iostream>
#include <stack>
#include "garage.h"
#include "car.h"

/*
Ryan Park z1940877
 Assignment 6
 CSCI 340, Section 3

 I certify that this is my own work and where appropriate an
 extension of the starter code provided for the assignment.
*/

/* Process arrivals of cars
 *
 *@param string license
 *@return nothing
 ************************/
void garage::arrival(const std::string& license)
{
	// Create the car
	car x(next_car_id, license);

	// If limit is met tell them the garage is full
	if (parking_lot.size() == parking_lot_limit)
	{
		std::cout << x << " has arrived.\n";
		std::cout << "    But the garage is full!\n\n";
	}
	else
	{
		// Otherwise you will state its arrived regardless
		// And place it into the back of the deque
		std::cout << x << " has arrived.\n\n";
		parking_lot.push_back(x);
		next_car_id++;
	}
}

/* Processes departures on cars
 *
 *@param license to search for in garage
 *@return none
 *****************************/
void garage::departure(const std::string& license)
{
	bool found = false;
	int foundIndex = 0;

	for (size_t i = 0; i < parking_lot.size(); i++)
	{
		if (parking_lot[i].get_license() == license)
		{
			// If license plate is found, set index equal to found index
			found = true;
			foundIndex = i;
		}
	}
	if (found == true)
	{
		// When its found, remove elements in the way up to foundindex, placing them in temp stack
		std::stack<car> temp;
		for (auto i = 0; i < foundIndex; i++)
		{
			temp.push(parking_lot.front()); // Push parking_lot.front() onto stack
			parking_lot.pop_front(); // Pop the front() from the deque
		}

		//Remove the car with given license plate from parking_lot
		// Incriment the moves, state the departure, and the num of moves
		std::cout << parking_lot[0] << " has departed,";
		parking_lot[0].move();
		if(parking_lot[0].get_num_moves() > 1)
			std::cout << "\n    car was moved " << parking_lot[0].get_num_moves()<< " times in the garage.\n\n";
		else
			std::cout << "\n    car was moved " << parking_lot[0].get_num_moves() << " time in the garage.\n\n";
		parking_lot.pop_front();

		// Now we move all the cars from the stack back into the deque
		while (!temp.empty())
		{
			(temp.top()).move();
			parking_lot.push_front(temp.top());
			temp.pop();
		}
	}
	// If found is false print accordingly
	if (found == false)
	{
		std::cout << "No car with license plate \"" << license << "\" is in the garage.\n\n"; // There is no refrence for this? Or find it
	}
}