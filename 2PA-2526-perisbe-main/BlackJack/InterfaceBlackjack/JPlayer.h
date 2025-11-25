#include "IPlayer.h"

class JPlayer : public IPlayer {
  public: 
    JPlayer(int player_index, int hand_index, const ITable::Hand& hand)
      : player_index_(player_index),
        hand_index_(hand_index),
        player_hand_(hand) {}


    ITable::Action DecidePlayerAction(const ITable& table, int player_index, int hand_index) = 0;

    int DecideInitialBet(const ITable& table, int player_index) = 0;

    bool DecideUseSafe(const ITable& table, int player_index) = 0;

   

  private:
    int player_index_;
    int hand_index_;
    ITable::Hand player_hand_;
};