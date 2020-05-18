//
//  main.cpp
//  Acey Deucey
//
//  Created by Tommy Scheper on 3/15/20.
//  Copyright © 2020 Tommy Scheper. All rights reserved.
//

#include <iostream>
#include "Player.hpp"
#include "Game.hpp"
using namespace std;

void startTests();

int main() {
    cout << "Welcome to Acey Deucey!\nmade by Tommy Scheper\n";
    
    /*
    cout << "\nWhat do you want to do?\n";
    cout << "1) Play Acey Deucey\n2) Run tests\n";
    cout << "\nChoice --> ";
 
    int choice;
    cin >> choice;
    string junk;
    getline(cin, junk);
 
    if (choice == 1) {
        Game g1;
        g1.play();
    }
    else if (choice == 2) {
        startTests();
    }
    */
    
    Game g;
    g.play();
    
    return 0;
}
