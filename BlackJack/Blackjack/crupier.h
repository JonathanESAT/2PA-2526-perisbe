#ifndef CUPIER_H
#define CUPIER_H

#include "hand.h"
#include "deck.h"

const bool kHitSoft17 = false;

struct Crupier{
    Hand hand;
};

void DealerPlay(Deck& deck, Hand& dealer);

#endif


