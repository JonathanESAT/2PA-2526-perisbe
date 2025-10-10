#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "player.h"
#include "crupier.h"
#include "deck.h"

enum Outcome {
    kLose = 0,
    kPush,
    kWin,
    kBlackJack
};

struct Table{
    Deck deck;
    Player player;
    Crupier crupier;
    int base_bet;
};

#endif