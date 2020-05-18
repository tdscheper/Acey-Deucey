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
    
    Game g;
    g.play();
    
    return 0;
}
