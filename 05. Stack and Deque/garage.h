#ifndef GARAGE_H
#define GARAGE_H
/*
Ryan Park z1940877
 Assignment 6
 CSCI 340, Section 3

 I certify that this is my own work and where appropriate an
 extension of the starter code provided for the assignment.
*/
#include <deque>
#include <string>

#include "car.h"

class garage
{
public:
    garage(size_t limit = 10) : parking_lot_limit(limit) {}

    /// @param license The license of the car that has arrived.                                                           
    void arrival(const std::string& license);

    /// @param license The license of the car that has departed.                                                          
    void departure(const std::string& license);

private:
    int next_car_id = { 1 };
    std::deque<car> parking_lot;
    size_t parking_lot_limit;
};


#endif