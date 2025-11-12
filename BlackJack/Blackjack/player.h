#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"

const int kMaxHandsPerPlayer = 4;

struct Player {
    Hand hands[kMaxHandsPerPlayer];
    int balance;
    int hand_count;
    int bet[kMaxHandsPerPlayer];
};

#endif

