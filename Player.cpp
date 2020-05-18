//
//  Player.cpp
//  Acey Deucey
//
//  Created by Tommy Scheper on 3/31/20.
//  Copyright © 2020 Tommy Scheper. All rights reserved.
//

#include "Player.hpp"


Player::Player() {
    name = "";
    numChips = 0;
    origNumChips = 0;
    inTheGame = true;
    extraChipsLost = 0;
}

Player::Player(string name_in, double chipVal, double buyInAmount) {
    name = name_in;
    numChips = buyInAmount / chipVal;
    origNumChips = numChips;
    inTheGame = true;
    extraChipsLost = 0;
}

void Player::take_player_out() {
    inTheGame = false;
}

void Player::high_low_choice() {
    string choice;
    string junk;
    bool valid = false;
    
    while (!valid) {
        cout << "High or low? --> ";
        cin >> choice;
        choice = toUpperCase(choice);
        
        if (choice == "HIGH" || choice == "HI" || choice == "H") {
            for (int i = 0; i < NUM_RANKS; ++i) {
                playerCardRanks[i] = highAceRanks[i];
            }
            valid = true;
        }
        else if (choice == "LOW" || choice == "LO" || choice == "L") {
            for (int i = 0; i < NUM_RANKS; ++i) {
                playerCardRanks[i] = lowAceRanks[i];
            }
            valid = true;
        }
        else {
            cout << "Invalid input, try again" << endl;
            getline(cin, junk);
            valid = false;
        }
    }
}

bool Player::split_choice() {
    string choice;
    string junk;
    
    cout << "Split? --> ";
    cin >> choice;
    choice = toUpperCase(choice);
    
    if (choice == "YES" || choice == "Y") {
        return true;
    }
    else if (choice == "NO" || choice == "N") {
        return false;
    }
    else {
        cout << "Invalid input, try again" << endl;
        getline(cin, junk);
        return split_choice();
    }
}

bool Player::play_it_choice() {
    string playChoice;
    string junk;
    
    cout << "Play it? --> ";
    cin >> playChoice;
    getline(cin, junk);
    playChoice = toUpperCase(playChoice);
    
    if (playChoice == "YES" || playChoice == "Y") {
        return true;
    }
    else if (playChoice == "NO" || playChoice == "N") {
        return false;
    }
    else {
        cout << "Invalid input, try again\n";
        getline(cin, junk);
        return play_it_choice();
    }
}

bool Player::buy_more_choice() {
    string answer;
    string junk;
    
    if (numChips == 0) {
        cout << name << ", want to buy back in? --> ";
    }
    
    else {
        cout << name << ", want to buy more chips? --> ";
    }
    
    cin >> answer;
    answer = toUpperCase(answer);
    
    if (answer == "YES" || answer == "Y") {
        return true;
    }
    else if (answer == "NO" || answer == "N") {
        return false;
    }
    else {
        cout << "Invalid input, try again" << endl;
        getline(cin, junk);
        return buy_more_choice();
    }
}

void Player::buy_more_chips(double chipVal) {
    double amount;
    string junk;
    
    //Bringing back in:
    if (numChips == 0) {
        cout << name << ", how much are you buying in for? --> $";
        cin >> amount;
        getline(cin, junk);
        cout << endl;
        
        numChips = money_to_chips(chipVal, amount);
        origNumChips += numChips;
        inTheGame = true;
        
        cout << name << " gets " << numChips << " chips\n";
    }
    
    //Just buying more chips
    else {
        cout << name << ", how much are you giving the dealer? --> $";
        cin >> amount;
        getline(cin, junk);
        
        numChips += money_to_chips(chipVal, amount);
        origNumChips += money_to_chips(chipVal, amount);
        
        cout << name << " gets " << money_to_chips(chipVal, amount)
             << " more chips\n";
    }
}
