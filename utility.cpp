//
//  utility.cpp
//  Acey Deucey
//
//  Created by Tommy Scheper on 3/31/20.
//  Copyright © 2020 Tommy Scheper. All rights reserved.
//

#include "utility.hpp"


string toUpperCase(string original) {
    string upperCaseString;
    
    for (int i = 0; i < original.size(); ++i) {
        //Each lowercase letter turns uppercase
        if (islower(original.at(i))) {
            original.at(i) = toupper(original.at(i));
            upperCaseString += original.at(i);
        }
        //If a character isn't a lowercase letter, it doesn't change
        else {
            upperCaseString += original.at(i);
        }
    }
    return upperCaseString;
}

string pluralize(string singular, string plural, int number) {
    if (number == 1) {
        return singular;
    }
    return plural;
}

int get_random_number() {
    static std::chrono::time_point<std::chrono::system_clock> p1 = chrono::system_clock::now();
    long elapsed = static_cast<long>(chrono::duration_cast<chrono::milliseconds>(p1.time_since_epoch()).count());
    return (rand() + elapsed) % numeric_limits<int>::max();
}

string chips_to_money(double chipVal, int chips) {
    double moneyVal = chipVal * chips;
    
    //Make sure there are always two decimals (ex: $25.00)
    string moneyValString = to_string(moneyVal);
    for (int i = 0; i < 4; ++i) {
        moneyValString.pop_back();
    }
    
    return "$" + moneyValString;
}

int money_to_chips(double chipVal, double amount) {
    return amount / chipVal;
}
