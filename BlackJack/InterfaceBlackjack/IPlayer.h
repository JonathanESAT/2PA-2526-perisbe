#include "ITable.h"

class IPlayer {
    public:
        virtual ITable::Action DecidePlayerAction(const ITable& table, int player_index, int hand_index) = 0;
        virtual int DecideInitialBet(const ITable& table, int player_index) = 0;
        virtual bool DecideUseSafe(const ITable& table, int player_index) = 0;

        virtual ~IPlayer() = default;
};
