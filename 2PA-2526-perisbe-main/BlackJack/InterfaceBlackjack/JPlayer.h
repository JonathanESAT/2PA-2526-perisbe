#pragma once
#include "IPlayer.h"
#include "Rules.h"
#include "JTable.h"
#include <unordered_map>

class JPlayer : public IPlayer {
  public: 
    JPlayer(const BaseRules& rules);
 

    ITable::Action DecidePlayerAction(const ITable& table, int player_index, int hand_index)override;

    int DecideInitialBet(const ITable& table, int player_index)override;

    bool DecideUseSafe(const ITable& table, int player_index)override;

    int GetCardValue(JTable::Card card);

   

  private:

    const BaseRules& rules_;

    enum class Decision : int{
      Stand = 0,
      Hit,
      Split,
      Double,
      end = 4,
    };

    struct Key {

      bool is_pair;
      bool is_soft;
      int total;
      ITable::Value dealer_card;

      bool operator==(const Key& other) const{

        return is_pair == other.is_pair && 
               is_soft == other.is_soft && 
               total == other.total && 
               dealer_card == other.dealer_card;
      }
    };

    struct KeyHash {

      size_t operator()(const Key& key) const{

        size_t h1 = std::hash<bool>()(key.is_pair);
        size_t h2 = std::hash<bool>()(key.is_soft);
        size_t h3 = std::hash<int>()(key.total);
        size_t h4 = std::hash<int>()(static_cast<int>(key.dealer_card));

        size_t running_val = h1;
        running_val = _rotr(running_val,8);
        running_val ^= h2;
        running_val = _rotr(running_val,8);
        running_val ^= h3;
        running_val = _rotr(running_val,8);
        running_val ^= h4;
        return running_val;

      }
    };


    struct HandInfo{

      bool is_pair;
      bool is_soft;
      int total;

    };

    std::unordered_map<Key, Decision, KeyHash> strategy_table_;
    HandInfo HandData(const ITable::Hand& hand);
    Decision GetMatCorrectDecision(HandInfo info, ITable::Card dealer_card);

};