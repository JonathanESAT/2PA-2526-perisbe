#include "Rules.h"
#include "stdio.h"


class JRules: public BaseRules{


public:

    class JRulesIvan: public BaseRules {
        ~JRulesIvan() = default;

        int GetWinPoint() const  { return 25; }

        int NumberOfDecks() const { return 2; }

        int InitialCards() const { return 3; }

        int InitialPlayerMoney() const { return 4000; }

        int InitialDealerMoney() const { return 100000; }

        int MinimumInitialBet() const { return 100; }

        int MaximumInitialBet() const { return 10000; }

        int DealerStop() const { return 21; }

    };


    class JRulesJessica: public BaseRules {

        ~JRulesJessica() = default;

        int GetWinPoint() const  { return 20; }

        int NumberOfDecks() const { return 1; }

        int InitialCards() const { return 2; }

        int InitialPlayerMoney() const { return 4000; }

        int InitialDealerMoney() const { return 100000; }

        int MinimumInitialBet() const { return 100; }

        int MaximumInitialBet() const { return 10000; }

        int DealerStop() const { return 16; }
        

        
    };

    int ChooseRules();
};

