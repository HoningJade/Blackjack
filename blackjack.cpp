//
// Created by Ruiyu Li on 2020/6/30.
//

#include <iostream>
#include <string>
#include "deck.h"
#include "player.h"
#include "rand.h"

using namespace std;

//  Shuffles the deck for 7 times and print the corresponding message
void shuffle7(Deck &deck, Player *player) {
    cout << "Shuffling the deck\n";
    for (int i = 0; i < 7; i++) {
        int cut = get_cut();
        cout << "cut at " << cut << endl;
        deck.shuffle(cut);
    }
    player->shuffled();
}

// deal one card
void dealCard(const Card &curCard, Player *curPlayer, bool isExposed, Hand &hand, bool isPlayer) {
    hand.addCard(curCard);
    if (isExposed) {
        curPlayer->expose(curCard);
        if (isPlayer) {
            cout << "Player dealt ";
        } else {
            cout << "Dealer dealt ";
        }
        cout << SpotNames[curCard.spot] << " of " << SuitNames[curCard.suit] << endl;
    }
}

int main(int argc, char *argv[]) {
    const int MINI_BET = 5;  // the minimum bit
    int bankroll = stoi(argv[1]), maxHand = stoi(argv[2]), thishand = 0, betNum;
    Deck thisDeck;
    Hand playHand, dealHand;
    Player *player = (string(argv[3]) == "simple") ? get_Simple() : get_Counting();
    shuffle7(thisDeck, player);
    while (bankroll >= MINI_BET && thishand < maxHand) {
        cout << "Hand " << ++thishand << " bankroll " << bankroll << endl;
        if (thisDeck.cardsLeft() < 20)  // if there are fewer than 20 cards left, reshuffle the deck
            shuffle7(thisDeck, player);
        betNum = player->bet(bankroll, MINI_BET);
        cout << "Player bets " << betNum << endl;
        dealCard(thisDeck.deal(), player, true, playHand, true);
        Card dealerCard = thisDeck.deal();
        dealCard(dealerCard, player, true, dealHand, false);
        dealCard(thisDeck.deal(), player, true, playHand, true);
        Card holeCard = thisDeck.deal();
        dealCard(holeCard, player, false, dealHand, false);
        if (playHand.handValue().count == 21 && playHand.handValue().soft) {
            bankroll += 3 * betNum / 2;
            cout << "Player dealt natural 21\n";
        } else {  //  Draw cards until the player either stands or busts
            while (player->draw(dealerCard, playHand) && playHand.handValue().count < 22) {
                dealCard(thisDeck.deal(), player, true, playHand, true);
            }
            cout << "Player's total is " << playHand.handValue().count << endl;  // announce the player's total
            if (playHand.handValue().count > 21) {
                bankroll -= betNum;
                playHand.discardAll();
                cout << "Player busts\n";
            } else {
                player->expose(holeCard);
                cout << "Dealer's hole card is " << SpotNames[holeCard.spot] << " of " << SuitNames[holeCard.suit]
                     << endl;
                //  play the dealer’s hand and dealer hits until reaching seventeen or busting
                while (dealHand.handValue().count < 17)
                    dealCard(thisDeck.deal(), player, true, dealHand, false);
                cout << "Dealer's total is " << dealHand.handValue().count << endl;
                if (dealHand.handValue().count > 21) {  // If the dealer busts, credit the wager
                    cout << "Dealer busts\n";
                    bankroll += betNum;
                } else {
                    if (playHand.handValue().count > dealHand.handValue().count) {  // compare the totals
                        bankroll += betNum;
                        cout << "Player wins\n";  // announce the outcome
                    } else if (playHand.handValue().count < dealHand.handValue().count) {
                        bankroll -= betNum;
                        cout << "Dealer wins\n";
                    } else
                        cout << "Push\n";
                }
            }
        }
        playHand.discardAll();
        dealHand.discardAll();
    }
    cout << "Player has " << bankroll << " after " << thishand << " hands\n";
    return 0;
}
