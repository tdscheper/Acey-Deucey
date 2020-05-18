//
//  Game.hpp
//  Acey Deucey
//
//  Created by Tommy Scheper on 3/31/20.
//  Copyright © 2020 Tommy Scheper. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <iostream>
#include "utility.hpp"
#include "Player.hpp"
using namespace std;


struct Game {
    int numPlayers;
    Player player[MAX_PLAYERS];
    double chipValue;
    int chipsInPot;
    int cardsUsed;
    bool halfPotBetsOnly;
    string deck[NUM_CARDS] = {
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace",
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace",
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace",
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"
    };
    string origDeck[NUM_CARDS] = {
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace",
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace",
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace",
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"
    };
    //For testing
    string testDeck[NUM_CARDS] {
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace",
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace",
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace",
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"
    };
    
    /**
     * Requires: Nothing,
     * Modifies: chipsInPot, cardsUsed.
     * Effects: Default constructor. Sets chipsInPot and cardsUsed to 0.
     */
    Game();
    
    /**
     * Requires: Nothing,
     * Modifies: cout.
     * Effects: Displays rules in a box.
     */
    void rules();
    
    /**
     * Requires: playerNumber is in range [0, MAX_PLAYERS - 1].
     * Modifies: player[].
     * Effects: Sets player[playerNumber] to p.
     */
    void add_player(Player p, int playerNumber);
    
    /**
     * Requires: chips >= p.numChips.
     * Modifies: p, chipsInPot.
     * Effects: Adds chips (parameter) to chipsInPot, subtracts chips from p.numChips
     */
    void add_to_pot(Player &p, int chips);
    
    /**
     * Requires: chips <= chipsInPot.
     * Modifies: p, chipsInPot.
     * Effects: Subtracts chips (parameter) from chipsInPot, adds chips to p.numChips
     */
    void take_from_pot(Player &p, int chips);
    
    /**
     * Requires: Nothing.
     * Modifies: cout, chipsInPot, players in player[] that are in the game.
     * Effects: For every player in the game, takes one chip from player and adds it to the pot
     */
    void new_round_fee();
    
    /**
     * Requires: Nothing.
     * Modifies: Nothing.
     * Effects: Shuffles the deck (deck[]).
     */
    void shuffle();
    
    /**
     * Requires: Nothing.
     * Modifies: cout, cardsUsed.
     * Effects: If cardsUsed = NUM_CARDS, prompts the players that the end of the deck has been
     *       reached, shuffles the deck (deck[]), prompts the players that the cards have been shuffled,
     *       sets cardsUsed to 0, and returns true. If not, returns false.
     */
    bool end_of_deck();
    
    /**
     * Requires: card is an element in p's playerCardRanks[].
     * Modifies: Nothing.
     * Effects: Finds where card is in playerCardRanks[] and returns the index.
     * Example: If card = "4" = playerCardRanks[2], returns 2.
     */
    int card_value(Player &p, string card);
    
    /**
     * Requires: firstCardVal and secondCardVal are within range [0, NUM_CARDS - 1].
     * Modifies: cout.
     * Effects: If firstCardVal and secondCardVal are one apart, prints "Too bad!" with a newline and returns
     *       true. Otherwise, returns false.
     */
    bool too_bad(int firstCardVal, int secondCardVal);
    
    /**
     * Requires: Nothing.
     * Modifies: cout, cin.
     * Effects: Asks players if they want to play another round. If players enter anything other than yes, no, y,
     *       or nwith any combination of lowercase and uppercase letters, prompts player that invalid input
     *       was entered and returns the function. If player enters yes or y (any upper/lower combo),
     *       returns true. If player enters no or n (any upper/lower combo), returns false.
     */
    bool ask_another_round();
    
    /**
     * Requires: Nothing.
     * Modifies: cout, chipsInPot, each player in the game.
     * Effects: Evenly distributes chips in pot to the players. If it can't be evenly distributed, gives one extra to
     *       the next player until the pot is empty, starting at the first player (player[0]). Players not in the
     *       game do not receive any of the pot.
     */
    void distribute_pot();
    
    /**
     * Requires: Nothing.
     * Modifies: Nothing.
     * Effects: Displays how much each player won/lost, then displays biggest winner(s) and loser(s).
     */
    void wins_and_losses();
    
    /**
     * Requires: card is an element in deck[], cardVal is result of card_value(p, card).
     * Modifies: cout, cardsUsed, chipsInPot, p.
     * Effects: Charges split fee to p. Displays card and then the next card in the deck as the left split card.
     *       Shuffles deck if necessary and makes next card in deck the right split card. Executes turn with
     *       card and left split card. Next, displays card and then right split card. Shuffles deck if
     *       necessary. Executes turn with card and right split card.
     */
    void split_turn(Player &p, string card, int cardVal);
    
    /**
     * Requires: firstCard and secondCard are elements in deck[].
     * Modifies: cout, cin, cardsUsed, chipsInPot, p.
     * Effects: If firstCard and secondCard are the same, displays third card and exits function. If firstCard
     *       and secondCard are equal, gives p cance to split. Otherwise, gets p's choice to play. If choice
     *       is no, displays third card and exits function. If choice is yes, gets p's' bet, shows third card,
     *       and determines if p won or lost the bet. Only allows legal bets. Illegal bets result in the
     *       function prompting the user to make a legal bet. Displays how many chips p took from or
     *       added to the pot as a result of the bet. If p doesn't have enough chips to pay for the loss,
     *       prompts p to pay the dealer the amount leftover. Shuffles deck if necessary.
     */
    void execute_turn(Player &p, string firstCard, string secondCard);
    
    /**
     * Requires: Nothing.
     * Modifies: cout, cardsUsed, p.
     * Effects: Displays next card and card after that one. Makes player choose high or low ace if necessary.
     *       Shuffles deck when necessary. Executes turn. Takes player out of the game if they run out of
     *       chips.
     */
    void full_turn(Player &p);
    
    /**
     * Requires: Nothing,
     * Modifies: cout, cin, all member variables/arrays of Player and Game
     * Effects: Plays a game of Acey Deucey.
     */
    void play();
};

#endif /* Game_hpp */
