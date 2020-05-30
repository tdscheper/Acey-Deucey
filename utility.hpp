//
//  utility.hpp
//  Acey Deucey
//
//  Created by Tommy Scheper on 3/31/20.
//  Copyright © 2020 Tommy Scheper. All rights reserved.
//

#ifndef utility_hpp
#define utility_hpp

#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <ctime>
#include <limits>
#include <chrono>
#include <cstdlib>
using namespace std;


const int MAX_PLAYERS = 50;
const int NUM_CARDS = 52;
const int NUM_RANKS = 13;
const string lowAceRanks[NUM_RANKS] = {
    "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"
};
const string highAceRanks[NUM_RANKS] = {
    "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"
};

/**
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects: Returns a copy of original string with all alphabetical
 *       characters converted to uppercase. All other characters are unchanged.
 */
string toUpperCase(string original);

/**
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects: Returns singular if number = 1. Otherwise, returns plural.
 */
string pluralize(string singular, string plural, int number);

/**
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects: Returns a random integer.
 */
int get_random_number();

/**
 * Requires: Nothing.
 * Modifies: Nothing.
 * Effects: Returns the dollar value of chips in the form of a string, with '$' at the front and always has two
 *       decimal places.
 * Examples: chips_to_money(0.25, 5) returns "$1.25"
 *         chips_to_money(0.25, 4) returns "$1.00"
 */
string chips_to_money(double chipVal, int chips);

/**
 * Requires: amount % chipVal = 0.
 * Modifies: Nothing.
 * Effects: Returns the number of chips equivalent to the amount passed as parameter.
 * Example: money_to_chips(0.25, 5) returns 20
 */
int money_to_chips(double chipVal, double amount);

#endif /* utility_hpp */
