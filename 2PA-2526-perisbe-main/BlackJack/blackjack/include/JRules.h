#pragma once
#include "Rules.h"

/**
 * @class JRulesIvan
 * @brief Ivan's custom Blackjack rules with higher win point and more cards.
 *
 * This variant uses 2 decks, deals 3 initial cards, has a win point of 25,
 * and the dealer stops at 21.
 */
class JRulesIvan : public BaseRules {
public:
    ~JRulesIvan() = default;

    int GetWinPoint() const override { return 25; }
    int NumberOfDecks() const override { return 2; }
    int InitialCards() const override { return 3; }
    int InitialPlayerMoney() const override { return 4000; }
    int InitialDealerMoney() const override { return 100000; }
    int MinimumInitialBet() const override { return 100; }
    int MaximumInitialBet() const override { return 10000; }
    int DealerStop() const override { return 21; }
};

/**
 * @class JRulesJessica
 * @brief Jessica's custom Blackjack rules with lower win point and earlier dealer stop.
 *
 * This variant uses 1 deck, deals 2 initial cards, has a win point of 20,
 * and the dealer stops at 16.
 */
class JRulesJessica : public BaseRules {
public:
    ~JRulesJessica() = default;

    int GetWinPoint() const override { return 20; }
    int NumberOfDecks() const override { return 1; }
    int InitialCards() const override { return 2; }
    int InitialPlayerMoney() const override { return 4000; }
    int InitialDealerMoney() const override { return 100000; }
    int MinimumInitialBet() const override { return 100; }
    int MaximumInitialBet() const override { return 10000; }
    int DealerStop() const override { return 16; }
};

