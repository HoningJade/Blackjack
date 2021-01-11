#include "deck.h"

Deck::Deck() {
    this->reset();
}

void Deck::reset() {
    // reset the suit of deck[]
    for(int i = 0; i < DeckSize/4; i++) {
        deck[i].suit = SPADES;
    }
    for(int i = DeckSize/4; i < DeckSize/2; i++) {
        deck[i].suit = HEARTS;
    }
    for(int i = DeckSize/2; i < 3 * DeckSize/4; i++) {
        deck[i].suit = CLUBS;
    }
    for(int i = 3 * DeckSize/4; i < DeckSize; i++) {
        deck[i].suit = DIAMONDS;
    }
    // reset the spot of deck[]
    deck[0].spot = deck[13].spot = deck[26].spot = deck[39].spot = TWO;
    deck[1].spot = deck[14].spot = deck[27].spot = deck[40].spot = THREE;
    deck[2].spot = deck[15].spot = deck[28].spot = deck[41].spot = FOUR;
    deck[3].spot = deck[16].spot = deck[29].spot = deck[42].spot = FIVE;
    deck[4].spot = deck[17].spot = deck[30].spot = deck[43].spot = SIX;
    deck[5].spot = deck[18].spot = deck[31].spot = deck[44].spot = SEVEN;
    deck[6].spot = deck[19].spot = deck[32].spot = deck[45].spot = EIGHT;
    deck[7].spot = deck[20].spot = deck[33].spot = deck[46].spot = NINE;
    deck[8].spot = deck[21].spot = deck[34].spot = deck[47].spot = TEN;
    deck[9].spot = deck[22].spot = deck[35].spot = deck[48].spot = JACK;
    deck[10].spot = deck[23].spot = deck[36].spot = deck[49].spot = QUEEN;
    deck[11].spot = deck[24].spot = deck[37].spot = deck[50].spot = KING;
    deck[12].spot = deck[25].spot = deck[38].spot = deck[51].spot = ACE;
    // Make the first card in this refreshed deck the next card to deal
    this->next = 0;
}

void Deck::shuffle(int n) {
    Card temp[DeckSize];
    int minNum = (n < DeckSize - n) ? n : (DeckSize - n);
    // Place cards into temp with first right then left order
    for(int i = 0; i < minNum; i++) {
        temp[2 * i + 1].spot = deck[i].spot;
        temp[2 * i + 1].suit = deck[i].suit;
        temp[2 * i].spot = deck[i + n].spot;
        temp[2 * i].suit = deck[i + n].suit;
    }
    // Replace deck[] with temp
    if(n < DeckSize - n) {
        for(int i = 0; i < n + minNum; i++) {
            deck[i].spot = temp[i].spot;
            deck[i].suit = temp[i].suit;
        }
    } else {
        for(int i = DeckSize - n; i < n; i++) {
            temp[i + DeckSize - n].spot = deck[i].spot;
            temp[i + DeckSize - n].suit = deck[i].suit;
        }
        for(int i = 0; i < DeckSize; i++) {
            deck[i].spot = temp[i].spot;
            deck[i].suit = temp[i].suit;
        }
    }
    // Make the first card in this shuffled deck the next card to deal
    this->next = 0;
}

Card Deck::deal() {
    if(this->next == DeckSize) {
        DeckEmpty empty;
        throw empty;
    } else {
        return this->deck[this->next++];
    }
}

int Deck::cardsLeft() {
    return DeckSize - this->next;
}