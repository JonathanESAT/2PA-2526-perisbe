#include "IPlayer.h"
#include "Rules.h"
#include <unordered_map>

class JPlayer : public IPlayer {
  public: 
    JPlayer(const BaseRules& rules);
 

    ITable::Action DecidePlayerAction(const ITable& table, int player_index, int hand_index)override;

    int DecideInitialBet(const ITable& table, int player_index)override;

    bool DecideUseSafe(const ITable& table, int player_index)override;

   

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

        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);

      }
    };

    int GetCardValue(ITable::Card card);

    struct HandInfo{

      bool is_pair;
      bool is_soft;
      int total;

    };

    std::unordered_map<Key, Decision, KeyHash> strategy_table_;
    HandInfo HandData(const ITable::Hand& hand);
    Decision GetMatCorrectDecision(HandInfo info, ITable::Card dealer_card);

    
    int HardRowIdx(int total);
    int SoftRowIdx(int total);
    int PairRowIdx(int pair_rank);
};