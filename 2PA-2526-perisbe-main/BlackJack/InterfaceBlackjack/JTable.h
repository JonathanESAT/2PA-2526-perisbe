#include "ITable.h"
#include "Rules.h"

class JTable: public ITable {
  public:

    JTable(unsigned int num_players, const BaseRules& rules);

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

    int GetCardValue(Card card);

    


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
    unsigned int num_players_;
    const int kSuitNum = 4;
    const int kValueNum = 13;

    
    struct HandInfo{
      
      bool is_pair;
      bool is_soft;
      int total;
    };

    HandInfo HandData(const Hand& hand);


    
};

