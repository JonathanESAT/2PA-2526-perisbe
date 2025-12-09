#pragma once
#include "Rules.h"
#include "stdio.h"


class JRules: public BaseRules{


public:

    class JRulesIvan: public BaseRules {
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


    class JRulesJessica: public BaseRules {

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

    int ChooseRules();
};

