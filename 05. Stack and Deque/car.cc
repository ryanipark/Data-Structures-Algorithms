#include <iostream>
#include "car.h"

/* set function, incirments num_moves
 *
 *@param none
 *@return none
 *****************/
void car::move()
{
	num_moves++;
}

/* get function, returns num_moves
 *
 *@param none
 *@return int of num_moves
 ***********************/
int car::get_num_moves() const
{
	return num_moves;
}

/* get function, for car license
 *
 *@param none
 *@return refrence to string
 ******************************/
const std::string& car::get_license() const
{
	return license;
}

/* Operator overload to print a car.
 *
 *@param lhs ostream refrence, rhs refrence to a car
 *@return ostream refrence 
 ******************************/
std::ostream& operator<<(std::ostream& lhs, const car& rhs)
{
	lhs << "Car " << rhs.id << " with license plate \"" << rhs.get_license() << "\"";

	return lhs;
}