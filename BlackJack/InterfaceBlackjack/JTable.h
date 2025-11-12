#include "ITable.h"

class JTable: public ITable {
  public:
    const Hand& GetHand(int player_index,int hand_index) const = 0;
    int GetNumberOfHands(int player_index) const = 0;

    int GetPlayerCurrentBet(int player_index,int hand_index) const = 0;
    int GetPlayerMoney(int player_index) const = 0;
    void SetPlayerInitialBet(int player_index,int money) = 0;

    Card GetDealerCard() const = 0;

    int CroupierMoney() const = 0;

    // Dealer es parte de la mesa, no tiene elecciones propias mas alla de aplicar las reglas
    void DealCard(int player_index,int hand_index) = 0;

    void PlaySafeBet(int player_index) = 0;
    Result ApplyPlayerAction(int player_index,int hand_index,Action action) = 0;


    void StartRound() = 0;

    RoundEndInfo FinishRound() = 0;


  private:

    std::vector<std::vector<Hand>> hands_;              //hands_[player_index][hand_index];
    std::vector<std::vector<int>> player_bets_;         //player_bets_[player_index][hand_index];
    std::vector<int> total_player_money_;               //total_player_money_[player_index];

    Hand crupier_hand;                                  //Hand = std::vector<Card>
    int crupier_money = kCroupierStartMoney;
};

