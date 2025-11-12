#include "ITable.h"



class BaseRules {
    public:
        virtual int GetWinPoint() { return 21; }
        virtual int NumberOfDecks() { return 1; }
        virtual int InitialCards() { return 2; }
        virtual bool PlayFirstEvenPlayers() { return false; }
        virtual ~BaseRules() = default;
};

class DifferentWinRules : public BaseRules {
    public:
        DifferentWinRules(int winpoints) : winpoints_{winpoints} {}
        virtual int GetWinPoint() override { return winpoints_; }
    private:
    int winpoints_;
};


class TwoDecksRules : public DifferentWinRules {
    public:
        TwoDecksRules() : DifferentWinRules{25} {}
        virtual int NumberOfDecks() override { return 2; }
        virtual int InitialCards() override { return 3; }
};

class RoundRules : public DifferentWinRules {
    public:
        RoundRules() : DifferentWinRules{20} {}
};