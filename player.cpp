#include "player.h"


class simplePlayer : public Player {
public:
    int bet(unsigned int bankroll, unsigned int minimum);
    // REQUIRES: bankroll >= minimum
    // EFFECTS: returns the player's bet, between minimum and bankroll inclusive

    virtual bool draw(Card dealer, const Hand &player);
    // EFFECTS: returns true if the player wishes to be dealt another card, false otherwise.

    void expose(Card c);
    // expose is no need for simple player

    void shuffled();
    // shuffled is no need for simple player
};

int simplePlayer::bet(unsigned int bankroll, unsigned int minimum) {
    return (int)minimum;
}

bool simplePlayer::draw(Card dealer, const Hand &player) {
    //  decides to hit or stand based on rules and whether the player has a “hard count” or not
    if (!player.handValue().soft) {
        if (player.handValue().count < 12) {
            return true;
        } else if (player.handValue().count == 12) {
            return !(dealer.spot == FOUR || dealer.spot == FIVE || dealer.spot == SIX);
        } else if (player.handValue().count >= 13 && player.handValue().count <= 16) {
            return !(dealer.spot == TWO || dealer.spot == THREE || dealer.spot == FOUR || dealer.spot == FIVE ||
                     dealer.spot == SIX);
        } else {
            return false;
        }
    } else {
        if (player.handValue().count < 18) {
            return true;
        } else if (player.handValue().count == 18) {
            return !(dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT);
        } else {
            return false;
        }
    }
}

void simplePlayer::expose(Card c) {}

void simplePlayer::shuffled() {}

static simplePlayer player1;

Player *get_Simple() {
    return &player1;
}

class countingPlayer : public Player {
private:
    int count;
public:
    countingPlayer() {
        this->count = 0;
    }

    int bet(unsigned int bankroll, unsigned int minimum);
    // if count >= 2 and bankroll >= the double of the minimum, the Counting player bets double the minimum

    bool draw(Card dealer, const Hand &player);
    // EFFECTS: returns true if the player wishes to be dealt another card, false otherwise.

    void expose(Card c);
    // keeps a running “count” of the cards based on what is seen from the deck


    void shuffled();
    //  if the deck is shuffled, reset the count to be zero
};

int countingPlayer::bet(unsigned int bankroll, unsigned int minimum) {
    if (this->count >= 2 && bankroll >= 2 * minimum) {
        return (int)(2 * minimum);
    } else {
        return (int)minimum;
    }
}

bool countingPlayer::draw(Card dealer, const Hand &player) {
    return player1.draw(dealer, player);
}

void countingPlayer::expose(Card c) {
    if (c.spot >= TEN && c.spot <= ACE) {
        this->count--;
    }
    if (c.spot >= TWO && c.spot <= SIX) {
        this->count++;
    }
}

void countingPlayer::shuffled() {
    this->count = 0;
}

static countingPlayer player2;

Player *get_Counting() {
    return &player2;
}