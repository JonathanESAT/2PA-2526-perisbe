#ifndef DECK_H
#define DECK_H

#include "card.h"


const int kMaxDecks = 4;
const int kMaxDeckCards = 52 * kMaxDecks;
const int kNumSuits = 4;
const int kNumRanks = 13;

struct Deck{
    Card cards[kMaxDeckCards];
    int size;
    int top;
};

void DeckShuffle(Deck& d);

bool DeckDraw(Deck& d, Card& out_card);

#endif