#include "ITable.h"
#include "Rules.h"

class JTable: public ITable {
  public:

    JTable(int num_players, const BaseRules& rules);

    Hand GetHand(int player_index,int hand_index) const override;
    int GetNumberOfHands(int player_index) const override;

    int GetPlayerCurrentBet(int player_index,int hand_index) const override;
    int GetPlayerMoney(int player_index) const override;
  
    int DealerMoney() const override;
    Card GetDealerCard() const override;

    // Dealer es parte de la mesa, no tiene elecciones propias mas alla de aplicar las reglas
    void DealCard(int player_index,int hand_index) override;

    Result PlayInitialBet(int player_index,int money) override;
    int GetPlayerInitialBet(int player_index) const override;

    void CleanTable() override;
    void FillDeck();
    void ShuffleDeck();


    Result PlaySafeBet(int player_index) override;
    Result ApplyPlayerAction(int player_index,int hand_index,Action action) override;


    void StartRound() override;
    RoundEndInfo FinishRound() override;


  private:

    std::vector<std::vector<Hand> > hands_;              //hands_[player_index][hand_index];
    std::vector<std::vector<int> > player_bets_;         //player_bets_[player_index][hand_index];
    std::vector<int> total_player_money_;               //total_player_money_[player_index];
    std::vector<int> insurance_bet_;                    //insurance_bet[player_index];
    std::vector<int> initial_bet_;                      //initial_bet[player_index];

    int dealer_money_;
    Hand dealer_hand_;                                  //Hand = std::vector<Card>
    std::vector<Card> deck_;
    const BaseRules& rules_;
    int num_players_;
    const int kSuitNum = 4;
    const int kValueNum = 13;

    std::vector<std::vector<char> > table = {
   // 2     3     4     5     6     7     8     9     10    A
    {'H',  'D',  'D',  'D',  'D',  'H',  'H',  'H',  'H',  'H'}, // 9
    {'D',  'D',  'D',  'D',  'D',  'D',  'D',  'D',  'H',  'H'}, // 10
    {'D',  'D',  'D',  'D',  'D',  'D',  'D',  'D',  'D',  'H'}, // 11
    {'H',  'H',  'S',  'S',  'S',  'H',  'H',  'H',  'H',  'H'}, // 12
    {'S',  'S',  'S',  'S',  'S',  'H',  'H',  'H',  'H',  'H'}, // 13
    {'S',  'S',  'S',  'S',  'S',  'H',  'H',  'H',  'H',  'H'}, // 14
    {'S',  'S',  'S',  'S',  'S',  'H',  'H',  'H',  'H',  'H'}, // 15
    {'S',  'S',  'S',  'S',  'S',  'H',  'H',  'H',  'H',  'H'}, // 16
    {'S',  'S',  'S',  'S',  'S',  'S',  'S',  'S',  'S',  'S'}, // >= 17
    {'S',  'D',  'D',  'D',  'D',  'S',  'S',  'H',  'H',  'H'}, // A - 7
    {'H',  'D',  'D',  'D',  'D',  'H',  'H',  'H',  'H',  'H'}, // A - 6
    {'H',  'H',  'D',  'D',  'D',  'H',  'H',  'H',  'H',  'H'}, // A - 5
    {'H',  'H',  'D',  'D',  'D',  'H',  'H',  'H',  'H',  'H'}, // A - 4
    {'H',  'H',  'H',  'D',  'D',  'H',  'H',  'H',  'H',  'H'}, // A - 3
    {'H',  'H',  'H',  'D',  'D',  'H',  'H',  'H',  'H',  'H'}, // A - 2
    {'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P'},// A - A
    {'P',  'P',  'P',  'P',  'P',  'S',  'P',  'P',  'S',  'S'}, // 9 - 9
    {'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P'},// 8 - 8
    {'P',  'P',  'P',  'P',  'P',  'P',  'H',  'H',  'H',  'H'}, // 7 - 7
    {'P',  'P',  'P',  'P',  'P',  'H',  'H',  'H',  'H',  'H'}, // 6 - 6
    {'D',  'D',  'D',  'D',  'D',  'D',  'D',  'D',  'H',  'H'}, // 5 - 5
    {'H',  'H',  'H',  'H',  'H',  'H',  'H',  'H',  'H',  'H'}, // 4 - 4
    {'H',  'H',  'P',  'P',  'P',  'P',  'H',  'H',  'H',  'H'}, // 3 - 3
    {'H',  'H',  'P',  'P',  'P',  'P',  'H',  'H',  'H',  'H'}, // 2 - 2
    {'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P',  'P'}  //10 - 10
    
  };
    
};

