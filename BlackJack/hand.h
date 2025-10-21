#ifndef HAND_H
#define HAND_H
#include "card.h"

const int kMaxCardInHand = 12;

struct Hand{
    Card cards[kMaxCardInHand];
    int count;
    bool finished;
};

void HandInit(Hand& h);

bool HandAddCard(Hand& h, const Card& c);

int HandBestValue(const Hand& h);

bool HandIsBlackjack(const Hand& h);

bool HandIsBust(const Hand& h);

bool HandIsSoft(const Hand& h);

#endif