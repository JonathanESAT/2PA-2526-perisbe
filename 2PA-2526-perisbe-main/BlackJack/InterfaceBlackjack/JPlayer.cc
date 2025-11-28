#include "JPlayer.h"


ITable::Action DecidePlayerAction(const ITable& table, int player_index, int hand_index){
    return ITable::Action::Stand;
}

int DecideInitialBet(const ITable& table, int player_index){
    return 0;
}

bool DecideUseSafe(const ITable& table, int player_index){
    return true;
}
