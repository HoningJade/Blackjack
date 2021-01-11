#include "hand.h"

Hand::Hand() {
    this->discardAll();
}

void Hand::discardAll() {
    this->curValue.count = 0;
    this->curValue.soft = false;
}

void Hand::addCard(Card c) {
    // handle ACE, JACK, QUEEN and KING respectively
    if(c.spot == ACE) {
        if ((curValue.count + 11) < 22) {
            curValue.count += 11;
            this->curValue.soft = true;
            return;
        } else {
            curValue.count += 1;
        }
    } else if(c.spot == JACK || c.spot == QUEEN || c.spot == KING) {
        this->curValue.count += 10;
    } else {
        this->curValue.count += (c.spot + 2);
    }
    // change ACE to be 1 if count > 21
    if (this->curValue.soft && this->curValue.count > 21)
    {
        this->curValue.count -= 10;
        this->curValue.soft = false;
    }
}

HandValue Hand::handValue() const {
    return this->curValue;
}