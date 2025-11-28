#include "IPlayer.h"

class JPlayer : public IPlayer {
  public: 
    JPlayer() = default;
 

    ITable::Action DecidePlayerAction(const ITable& table, int player_index, int hand_index) = 0;

    int DecideInitialBet(const ITable& table, int player_index) = 0;

    bool DecideUseSafe(const ITable& table, int player_index) = 0;

   

  private:

    enum class Decision : int{
      Stand = 0,
      Hit,
      Split,
      Double,
      end = 4,
    };

      std::vector<std::vector<Decision> > mat_correct_behaivour_  = {
       
        {Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // <= 8

        {Decision::Hit,   Decision::Double,Decision::Double,Decision::Double,Decision::Double,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // 9

        {Decision::Double,Decision::Double,Decision::Double,Decision::Double,Decision::Double,
        Decision::Double,Decision::Double,Decision::Double,Decision::Hit,   Decision::Hit},  // 10

        {Decision::Double,Decision::Double,Decision::Double,Decision::Double,Decision::Double,
        Decision::Double,Decision::Double,Decision::Double,Decision::Double,Decision::Hit},  // 11

        {Decision::Hit,   Decision::Hit,   Decision::Stand, Decision::Stand, Decision::Stand,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // 12

        {Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // 13

        {Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // 14

        {Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // 15

        {Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // 16

        {Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand,
        Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand}, // >= 17

        // Soft totals (A + X)
        {Decision::Stand, Decision::Double,Decision::Double,Decision::Double,Decision::Double,
        Decision::Stand, Decision::Stand, Decision::Hit,   Decision::Hit,   Decision::Hit},  // A - 7

        {Decision::Hit,   Decision::Double,Decision::Double,Decision::Double,Decision::Double,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // A - 6

        {Decision::Hit,   Decision::Hit,   Decision::Double,Decision::Double,Decision::Double,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // A - 5

        {Decision::Hit,   Decision::Hit,   Decision::Double,Decision::Double,Decision::Double,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // A - 4

        {Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Double,Decision::Double,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // A - 3

        {Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Double,Decision::Double,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // A - 2

        // Pairs
        {Decision::Split, Decision::Split, Decision::Split, Decision::Split, Decision::Split,
        Decision::Split, Decision::Split, Decision::Split, Decision::Split, Decision::Split}, // A - A

        {Decision::Split, Decision::Split, Decision::Split, Decision::Split, Decision::Split,
        Decision::Stand, Decision::Split, Decision::Split, Decision::Stand, Decision::Stand}, // 9 - 9

        {Decision::Split, Decision::Split, Decision::Split, Decision::Split, Decision::Split,
        Decision::Split, Decision::Split, Decision::Split, Decision::Split, Decision::Split}, // 8 - 8

        {Decision::Split, Decision::Split, Decision::Split, Decision::Split, Decision::Split,
        Decision::Split, Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // 7 - 7

        {Decision::Split, Decision::Split, Decision::Split, Decision::Split, Decision::Split,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // 6 - 6

        {Decision::Double,Decision::Double,Decision::Double,Decision::Double,Decision::Double,
        Decision::Double,Decision::Double,Decision::Double,Decision::Hit,   Decision::Hit},  // 5 - 5

        {Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,
        Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // 4 - 4

        {Decision::Hit,   Decision::Hit,   Decision::Split, Decision::Split, Decision::Split,
        Decision::Split, Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // 3 - 3

        {Decision::Hit,   Decision::Hit,   Decision::Split, Decision::Split, Decision::Split,
        Decision::Split, Decision::Hit,   Decision::Hit,   Decision::Hit,   Decision::Hit},  // 2 - 2

        {Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand,
        Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand, Decision::Stand}, // 10 - 10
    };

    int GetCardValue(ITable::Card card);

    struct HandInfo{

      bool is_pair;
      bool is_soft;
      int total;

    };

    HandInfo HandData(const ITable::Hand& hand);
    Decision GetMatCorrectDecision(HandInfo info, ITable::Card dealer_card);

    
    int HardRowIdx(int total);
    int SoftRowIdx(int total);
    int PairRowIdx(int pair_rank);
};