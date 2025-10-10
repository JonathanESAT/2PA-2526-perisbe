#ifndef HAND_H
#define HAND_H
#include "card.h"

const int kMaxCardInHand = 12;

struct Hand{
    Card cards[kMaxCardInHand];
    int count;
    bool finished;
};


#endif