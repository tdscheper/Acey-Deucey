//
//  Game.cpp
//  Acey Deucey
//
//  Created by Tommy Scheper on 3/31/20.
//  Copyright © 2020 Tommy Scheper. All rights reserved.
//

#include "Game.hpp"
#include "utility.hpp"


Game::Game() {
    chipsInPot = 0;
    cardsUsed = 0;
}

void Game::rules() {
    cout << "\n -------------------------------------------------------------------------\n";
    cout << "|                                RULES                                    |\n";
    cout << "| Each player buys in and receives a certain number of chips, depending   |\n";
    cout << "|    on how much you choose to make a chip worth and how much the player  |\n";
    cout << "|    gives the dealer. For example, if a chip is worth $0.25 and you buy  |\n";
    cout << "|    in for $10, you receive 40 chips.                                    |\n";
    cout << "| Every player has to add a chip to the pot each time a round starts.     |\n";
    cout << "| When it's your turn, you're presented two cards, and a third will come  |\n";
    cout << "|    after you choose to make a bet or not.                               |\n";
    cout << "| You can make a bet that the third card's rank will be in between        |\n";
    cout << "|    the first two cards' ranks.                                          |\n";
    cout << "| You cannot bet over half the pot on your first turn of a round.         |\n";
    cout << "| You also can't bet more chips than you or the pot have.                 |\n";
    cout << "| If you win a bet, you collect the bet amount from the pot; if you lose, |\n";
    cout << "|    you give that amount to the pot.                                     |\n";
    cout << "| If it is in between, you win the bet.                                   |\n";
    cout << "| If it is not in between, you lose the bet.                              |\n";
    cout << "| However, in some situations, the bet is altered.                        |\n";
    cout << "| If the third card is the same rank as the first or second card, you     |\n";
    cout << "|    lose double the bet.                                                 |\n";
    cout << "| If it is the only possible card that can be in between the two cards    |\n";
    cout << "|    (i.e. 6 between 5 and 7), you win triple the bet.                    |\n";
    cout << "| If the first and second card match, you can pay a one chip fee to       |\n";
    cout << "|    split. This gives you two games to choose to bet on. If one of the   |\n";
    cout << "|    split cards matches the first two cards, you can pay another fee and |\n";
    cout << "|    split again.                                                         |\n";
    cout << "| The Ace can be the lowest card OR the highest card.                     |\n";
    cout << "| If the Ace is the second card flipped, it is always a High Ace.         |\n";
    cout << "| However, if it is the first, the player can choose if it is a Low or    |\n";
    cout << "|    High Ace.                                                            |\n";
    cout << "| If a player calls Low Ace and the second card is a High Ace and they    |\n";
    cout << "|    make a bet, and the next card is another Ace, the player loses four  |\n";
    cout << "|    times the bet.                                                       |\n";
    cout << "| If you lose a bet which you don't have enough chips for, you have to    |\n";
    cout << "|    pay for that amount, which is then used to add the chips to the pot. |\n";
    cout << "| Any time the pot is emptied, the round ends, and you can choose to play |\n";
    cout << "|    another round or not.                                                |\n";
 // cout << "| If you choose to end the game and there's still money in the pot, it    |\n";
 // cout << "|    is distributed among all players.                                    |\n";
    cout << " -------------------------------------------------------------------------\n";
}

void Game::add_player(Player p, int playerNumber) {
    player[playerNumber] = p;
}

void Game::add_to_pot(Player &p, int chips) {
    chipsInPot += chips;
    p.numChips -= chips;
}

void Game::take_from_pot(Player &p, int chips) {
    chipsInPot -= chips;
    p.numChips += chips;
}

void Game::new_round_fee() {
    for (int i = 0; i < numPlayers; ++i) {
        if (!player[i].inTheGame) {
            continue;
        }

        add_to_pot(player[i], 1);
    }
}

void Game::shuffle() {
    int randNum1;
    int randNum2;
    int randNum3;
    int randNum4;
    int randNum5;
    string tempCard;
    
    //Random big number (586) used to ensure good shuffle
    for (int i = 0; i < 586; ++i) {
        randNum1 = get_random_number() % NUM_CARDS;
        randNum2 = get_random_number() % NUM_CARDS;
        randNum3 = get_random_number() % NUM_CARDS;
        randNum4 = get_random_number() % NUM_CARDS;
        randNum5 = get_random_number() % NUM_CARDS;
        
        tempCard = deck[randNum1];
        deck[randNum1] = deck[randNum2];
        deck[randNum2] = deck[randNum3];
        deck[randNum3] = deck[randNum4];
        deck[randNum4] = deck[randNum5];
        deck[randNum5] = tempCard;
    }
}

bool Game::end_of_deck() {
    if (cardsUsed == NUM_CARDS) {
        cout << "\nReached the end of the deck. Shuffling cards\n";
        shuffle();
        cout << "Cards shuffled.\n\n";
        cardsUsed = 0;
        return true;
    }
    else {
        return false;
    }
}

int Game::card_value(Player &p, string card) {
    for (int i = 0; i < NUM_RANKS; ++i) {
        if (card == p.playerCardRanks[i]) {
            return i;
        }
    }
    
    //This will never happen, but it is necessary for code to run
    return 0;
}

bool Game::too_bad(int firstCardVal, int secondCardVal) {
    if (abs(firstCardVal - secondCardVal) == 1) {
        cout << "Too bad!\n";
        return true;
    }
    else {
        return false;
    }
}

bool Game::ask_another_round() {
    string answer;
    
    cout << "\nAnother round? --> ";
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
        return ask_another_round();
    }
}

void Game::wins_and_losses() {
    for (int i = 0; i < numPlayers; ++i) {
        //Shorten code with these three variables
        int chips = player[i].numChips;
        int origChips = player[i].origNumChips;
        int extra = player[i].extraChipsLost;
        
        cout << player[i].name;
        
        if (chips > origChips + extra) {
            cout << " won "
                 << chips_to_money(chipValue, chips - origChips - extra)
                 << endl;
        }
        else if (chips < origChips + extra) {
            cout << " lost "
                 << chips_to_money(chipValue, origChips - chips - extra)
                 << endl;
        }
        else {
            cout << " went even\n";
        }
    }
    
    Player winner[numPlayers];
    Player loser[numPlayers];
    winner[0] = player[0];
    loser[0] = player[0];
    int numWinners = 1;
    int numLosers = 1;
    int biggestProfit = player[0].numChips - player[0].origNumChips -
                        player[0].extraChipsLost;
    int biggestLoss = player[0].numChips - player[0].origNumChips -
                      player[0].extraChipsLost;
    
    for (int i = 1; i < numPlayers; ++i) {
        int difference = player[i].numChips - player[i].origNumChips -
                         player[i].extraChipsLost;
        
        if (difference > biggestProfit) {
            biggestProfit = difference;
            numWinners = 1;
            winner[0] = player[i];
        }
        else if (difference == biggestProfit) {
            ++numWinners;
            winner[numWinners - 1] = player[i];
        }
        else if (difference < biggestLoss) {
            biggestLoss = difference;
            numLosers = 1;
            loser[0] = player[i];
        }
        else if (difference == biggestLoss) {
            ++numLosers;
            loser[numLosers - 1] = player[i];
        }
    }
    
    cout << "Biggest " << pluralize("Winner", "Winners", numWinners) << ": ";
    for (int i = 0; i < numWinners; ++i) {
        cout << winner[i].name;
        if (i != numWinners - 1) {
            cout << ", ";
        }
    }
    cout << endl;
    
    cout << "Biggest " << pluralize("Loser", "Losers", numLosers) << ": ";
    for (int i = 0; i < numLosers; ++i) {
        cout << loser[i].name;
        if (i != numLosers - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

void Game::split_turn(Player &p, string card, int cardVal) {
    string leftSplit = deck[cardsUsed];
    string rightSplit = deck[cardsUsed + 1];
    int leftSplitVal = 0;
    int rightSplitVal = 0;
    bool newDeck;
    
    //Split fee
    add_to_pot(p, 1);
    cout << p.name << " added 1 chip to the pot\n";
    cout << "Pot: " << chipsInPot << " chips ("
         << chips_to_money(chipValue, chipsInPot) << ")\n";
    
    //Assign array value to left split card
    leftSplitVal = card_value(p, leftSplit);
    
    //Show card from before and left split card
    cout << "First card (from before): " << card << endl;
    cout << "Second card (left split): " << leftSplit << endl;
    ++cardsUsed;
    
    //If left split card was last card in deck, shuffle the deck
    newDeck = end_of_deck();
    if (newDeck) {
        //Make right split card first card in newly shuffled deck
        rightSplit = deck[cardsUsed];
    }

    execute_turn(p, card, leftSplit);

    //Assign array value to right split card
    rightSplitVal = card_value(p, rightSplit);
    
    //Show card from before and right split card
    cout << "First card (from before): " << card << endl;
    cout << "Second card (right split): " << rightSplit << endl;
    ++cardsUsed;
    newDeck = end_of_deck();
    
    execute_turn(p, card, rightSplit);
}

void Game::execute_turn(Player &p, string firstCard, string secondCard) {
    string thirdCard = deck[cardsUsed];
    int firstCardVal = 0;
    int secondCardVal = 0;
    int thirdCardVal = 0;
    int bet;
    int higherOfFirstTwo;
    int lowerOfFirstTwo;
    bool tooBad = false;
    bool ace = false;
    bool highAce = true;
    bool playItChoice;
    bool loss;
    bool split;
    string done;
    string junk;
    
    if (firstCard == "Ace") {
        ace = true;
        if (p.playerCardRanks[0] == "Ace") {
            highAce = false;
        }
    }
    
    //Assign cards to values in array
    firstCardVal = card_value(p, firstCard);
    secondCardVal = card_value(p, secondCard);
    thirdCardVal = card_value(p, thirdCard);
    
    //If first and second cards are one apart, too bad. Show third card, exit
    tooBad = too_bad(firstCardVal, secondCardVal);
    if (tooBad) {
        cout << "Third card: " << thirdCard << endl;
        ++cardsUsed;
        end_of_deck();
        return;
    }
    
    //If first and second card have same rank, give option for new cards
    if ((!ace && firstCard == secondCard) ||
        (ace && highAce && secondCard == "Ace")) {
        split = p.split_choice();
        //If player splits, play the split, exit
        if (split) {
            split_turn(p, firstCard, firstCardVal);
            return;
        }
        else {
            playItChoice = false;
        }
    }
    //If not, player chooses to play it or not
    else {
        playItChoice = p.play_it_choice();
    }
    
    //If player doesn't choose to play it, show third card, exit
    if (!playItChoice) {
        cout << "Third card: " << thirdCard << endl;
        ++cardsUsed;
        end_of_deck();
        return;
    }
    
    //Get bet
    cout << "How many chips are you betting? --> ";
    cin >> bet;
    getline(cin, junk);
   
    while (bet > p.numChips) {
        cout << "You don't have that many chips. Try again\n";
        cout << "How many chips are you betting? --> ";
        cin >> bet;
        getline(cin, junk);
    }
   
    while (!halfPotBetsOnly && bet > chipsInPot) {
        cout << "The pot only has " << chipsInPot << " chips. Try again\n";
        cout << "How many chips are you betting? --> ";
        cin >> bet;
        getline(cin, junk);
    }
   
    while (halfPotBetsOnly && bet > chipsInPot / 2) {
        cout << "Since it's the first time around with the new pot, you can "
             << "only bet half the pot. Try again\n";
        cout << "How many chips are you betting? --> ";
        cin >> bet;
        getline(cin, junk);
    }
    
    //Show third card
    cout << "Third card: " << thirdCard << endl;
    ++cardsUsed;
    
    if (firstCardVal < secondCardVal) {
        higherOfFirstTwo = secondCardVal;
        lowerOfFirstTwo = firstCardVal;
    }
    else {
        higherOfFirstTwo = firstCardVal;
        lowerOfFirstTwo = secondCardVal;
    }
    
    //If in between field goal, gain triple the bet
    if ((thirdCardVal == firstCardVal - 1 && thirdCardVal == secondCardVal + 1) ||
        (thirdCardVal == firstCardVal + 1 && thirdCardVal == secondCardVal - 1)) {
        bet *= 3;
        loss = false;
    }
    //If ace in between low ace and high ace, lose 4x the bet
    else if (!highAce && secondCardVal == 0 && thirdCardVal == 0) {
        bet *= 4;
        loss = true;
    }
    
    //Anything else between low and high ace is a win
    else if (!highAce && secondCardVal == 0) {
        loss = false;
    }
    
    //If same rank as one of the cards, lose double the bet
    else if (thirdCardVal == firstCardVal || thirdCardVal == secondCardVal) {
        bet *= 2;
        loss = true;
    }
    
    //If in between the normal way, gain bet
    else if (thirdCardVal > lowerOfFirstTwo && thirdCardVal < higherOfFirstTwo) {
        loss = false;
    }
    
    //If not in between, lose the bet
    else {
        loss = true;
    }
    
    //Win bet
    if (!loss) {
        take_from_pot(p, bet);
        cout << p.name << " took " << bet << " "
             << pluralize("chip", "chips", bet) << " from the pot\n";
    }
    
    //If player owes more chips to the pot than thay have, they have to pay up
    else if (loss && p.numChips < bet) {
        cout << p.name << ", you don't have enough chips.\n";
        cout << "You need to put " << bet << " chips in the pot, but you only "
             << "have " << p.numChips << " "
             << pluralize("chip", "chips", p.numChips) << ".\n";
        cout << "You have to give "
             << chips_to_money(chipValue, bet - p.numChips)
             << " to the dealer now. You can buy back in next round.\n";
        cout << "Enter \"done\" once you do that --> ";
        cin >> done;
        done = toUpperCase(done);
        while (done != "DONE") {
            cout << "Invalid input, try again: --> ";
            cin >> done;
            done = toUpperCase(done);
        }
        p.extraChipsLost += bet - p.numChips;
    }
    
    //Lose bet
    if (loss) {
        add_to_pot(p, bet);
        cout << p.name << " added " << bet << " "
             << pluralize("chip", "chips", bet) << " to the pot\n";
        
        //Keep player's numChips value >= 0
        if (p.numChips < 0) {
            p.numChips = 0;
        }
    }
    
    //Shuffle deck if third card was last card in deck
    end_of_deck();
}

void Game::full_turn(Player &p) {
    bool newDeck;
    bool ace = false;
    string firstCard = deck[cardsUsed];
    string secondCard = deck[cardsUsed + 1];
    string junk;
    
    //First card
    cout << "First card: " << firstCard << endl;
    ++cardsUsed;
    newDeck = end_of_deck();
    if (newDeck) {
        secondCard = deck[cardsUsed];
    }
    
    //If ace, choose high/low
    if (firstCard == origDeck[12] || firstCard == origDeck[25] ||
        firstCard == origDeck[38] || firstCard == origDeck[51]) {
        ace = true;
        p.high_low_choice();
    }
    
    //Second card
    cout << "Second card: " << secondCard << endl;
    ++cardsUsed;
    newDeck = end_of_deck();
    
    execute_turn(p, firstCard, secondCard);
    
    //Ensure player's card ranks are set to Ace being highest card after turn
    for (int i = 0; i < NUM_RANKS; ++i) {
        p.playerCardRanks[i] = highAceRanks[i];
    }
    
    //Take player out of game if they run out of chips
    if (p.numChips == 0) {
        p.take_player_out();
    }
}

void Game::play() {
    //Rules
    rules();
    
    //Ask how many players, price per chip
    cout << "\nHow many players? --> ";
    int players;
    cin >> players;
    numPlayers = players;
    cout << endl;
    
    cout << "How much is a chip worth? --> $";
    double chipVal;
    cin >> chipVal;
    string junk;
    getline(cin, junk);
    cout << endl;
    chipValue = chipVal;
    
    //Get player's names, buy-in amounts
    for (int i = 0; i < numPlayers; ++i) {
        cout << "Player " << i + 1 << ", what's your name? --> ";
        string nameVal;
        getline(cin, nameVal);
        
        cout << nameVal << ", how much are you buying in for? --> $";
        double amount;
        cin >> amount;
        getline(cin, junk);
        
        Player p(nameVal, chipValue, amount);
        add_player(p, i);
        
        cout << nameVal << " gets " << p.numChips << " chips\n\n";
    }
    
    //Play game
    int round = 0;
    bool gameEnded = false;
    int c = 0;
    cardsUsed = 0;
    
    while (!gameEnded) {
        //Give players not in game opportunity to come back
        //Give players in game opportunity to buy more chips
        if (round != 0) {
            for (int i = 0; i < numPlayers; ++i) {
                bool more = player[i].buy_more_choice();
                if (more) {
                    player[i].buy_more_chips(chipValue);
                }
            }
            cout << endl;
        }
        
        //Increment round number, show it
        ++round;
        cout << "Round " << round << endl;
        
        //Shuffle deck
        shuffle();
        
        //Round fee (1 chip)
        cout << "Everyone puts one chip in the pot\n";
        new_round_fee();
        
        //Make sure everyone has chips after the round fee
        for (int i = 0; i < numPlayers; ++i) {
            if (player[i].numChips == 0) {
                player[i].take_player_out();
            }
        }
        
        /* Count how many players went since new round to keep track of when
            players can start betting above half the pot */
        int numTurns = 0;
        halfPotBetsOnly = true;
        
        //Round (ends when pot is emptied)
        while (chipsInPot > 0) {
            //Skip player if not in game
            if (!player[c].inTheGame) {
                ++c;
                if (c == numPlayers) {
                    c = 0;
                }
            }
            
            //Display chips in pot, with $ value
            cout << "Pot: " << chipsInPot << " chips ("
                 << chips_to_money(chipValue, chipsInPot) << ")\n\n";
            
            //Display player name, chips
            if (player[c].numChips == 1) {
                cout << player[c].name << ", 1 chip ("
                     << chips_to_money(chipValue, 1) << ")\n";
            }
            else {
                cout << player[c].name << ", " << player[c].numChips << " chips"
                     << " (" << chips_to_money(chipValue, player[c].numChips)
                     << ")\n";
            }
                
            //Turn
            full_turn(player[c]);
            
            //Update counter variables c and numTurns
            if (c == numPlayers - 1) {
                c = 0;
            }
            else {
                ++c;
            }
            ++numTurns;
            
            /* If every player now has played their first turn of the round,
               betting over half the pot becomes legal */
            if (numTurns == numPlayers) {
                halfPotBetsOnly = false;
            }
        }
        
        //Ask if players want another round
        bool anotherRound = ask_another_round();
        
        //If yes, play another round
        if (anotherRound) {
            cout << endl;
        }
        
        //If not, print winnings/losses, end game
        else {
            wins_and_losses();
            gameEnded = true;
        }
    }
    
    cout << "\nThanks for playing Acey Deucey!\n";
}
