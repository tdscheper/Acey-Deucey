//
//  Player.hpp
//  Acey Deucey
//
//  Created by Tommy Scheper on 3/31/20.
//  Copyright © 2020 Tommy Scheper. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <iostream>
#include <stdio.h>
#include "utility.hpp"
using namespace std;


struct Player {
    string name;
    int numChips;
    int origNumChips;
    bool inTheGame;
    int extraChipsLost;
    string playerCardRanks[NUM_RANKS] = {
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"
    };
    string lowAceRanks[NUM_RANKS] = {
        "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"
    };
    string highAceRanks[NUM_RANKS] = {
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"
    };
    
    /**
     * Requires: Nothing,
     * Modifies: name, numChips, origNumChips, inTheGame, extraChipsLost
     * Effects: Default constructor. Sets name to an empty string; numChips, origNumChips, and
     *       extraChipsLost to 0; and inTheGame to true.
     */
    Player();
    
    /**
     * Requires: Nothing,
     * Modifies: name, numChips, origNumChips, inTheGame, extraChipsLost
     * Effects: Non-default constructor. Sets name to name_in, numChips and origNumChips to
     *       buyInAmount / chipVal, inTheGame to true, and extraChipsLost to 0.
     */
    Player(string name_in, double chipVal, double buyInAmount);
    
    /**
     * Requires: Nothing.
     * Modifies: inTheGame.
     * Effects: Sets inTheGame to false.
     */
    void take_player_out();
    
    /**
     * Requires: Nothing.
     * Modifies: cout, cin, playerCardRanks[].
     * Effects: Asks player if they want a high or low ace. Valid input are high, low, hi, lo, h, and l with any
     *       combination of uppercase and lowercase letters. If player enters high/hi/h (any upper/lower
     *       combo), sets playerCardRanks[] to highAceRanks[]. If player enters low/lo/l (any upper/lower
     *       combo), sets playerCardRanks[] to lowAceRanks[]. If anything else is entered, prompts player
     *       that invalid input was entered and asks goes back to start of function.
     */
    void high_low_choice();
    
    /**
     * Requires: Nothing.
     * Modifies: cout, cin.
     * Effects: Asks player if they want to split. If player enters anything other than yes, no, y, or n with any
     *       combination of lowercase and uppercase letters, prompts player that invalid input was
     *       entered and returns the function. If player enters yes or y (any upper/lower combo), returns
     *       true. If player enters no or n (any upper/lower combo), returns false.
     */
    bool split_choice();
    
    /**
     * Requires: Nothing.
     * Modifies: cout, cin.
     * Effects: Asks player if they want to play it. If player enters anything other than yes, no, y, or n
     *       with any combination of lowercase and uppercase letters, prompts player that invalid input
     *       was entered and returns the function. If player enters yes or y (any upper/lower combo),
     *       returns true. If player enters no or n (any upper/lower combo), returns false.
     */
    bool play_it_choice();
    
    /**
     * Requires: Nothing.
     * Modifies: cout, cin.
     * Effects: If player is in the game, asks player if they want to buy more chips. If not, asks player if they
     *       want to buy back in. If player enters anything other than yes, no, y, or n with any combination
     *       of lowercase and uppercase letters, prompts player that invalid input was entered and returns
     *       the function. If player enters yes or y (any upper/lower combo), returns true. If player enters
     *       no or n (any upper/lower combo), returns false.
     */
    bool buy_more_choice();
    
    /**
     * Requires: Nothing.
     * Modifies: cout, cin, numChips, origNumChips, inTheGame.
     * Effects: If the player is buying back in: asks player how much they're buying in for, sets numChips
     *       to the chip equivalent of amount entered, adds numChips to origNumChips, sets inTheGame
     *       to true, and displays how many chips the player bought.
     *       If the player is just buying more chips: asks player how much they're paying the dealer, adds
     *       the chip equivalent of amount entered to numChips and origNumChips, prompts how many
     *       more chips the player bought.
     */
    void buy_more_chips(double chipVal);
};

#endif /* Player_hpp */
