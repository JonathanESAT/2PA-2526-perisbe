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

struct Blackjack{
    Deck deck_;
    Player player_;
    Crupier crupier_;
    int base_bet;

    Blackjack(Deck deck, Player player, Crupier crupier);
};


Outcome ResolveOutcome(const Hand& player, const Hand& dealer);

int Payout(int bet, bool player_has_blackjack, Outcome o);

#endif