#ifndef DECK_H
#define DECK_H

#include "card.h"


const int kMaxDecks = 4;
const int kMaxDeckCards = 52 * kMaxDecks;

struct Deck{
    Card cards[kMaxDeckCards];
    int size;
    int top;
};

#endif