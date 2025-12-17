#pragma once
#include "ITable.h"
#include "Rules.h"
#include <vector>

/**
 * @class JTable
 * @brief Implementation of the Blackjack game table.
 *
 * This class manages the game state including player hands, bets, dealer actions,
 * deck management, and round resolution according to specified rules.
 */
class JTable: public ITable {
  public:

    /**
     * @brief Constructs a new JTable object.
     *
     * @param num_players Number of players at the table
     * @param rules Reference to the game rules to use
     */
    JTable(unsigned int num_players, const BaseRules& rules);

    Hand GetHand(int player_index,int hand_index) const override;
    int GetNumberOfHands(int player_index) const override;

    int GetPlayerCurrentBet(int player_index,int hand_index) const override;
    int GetPlayerMoney(int player_index) const override;

    int DealerMoney() const override;
    Card GetDealerCard() const override;

    void DealCard(int player_index,int hand_index) override;

    Result PlayInitialBet(int player_index,int money) override;

    /**
     * @brief Gets the initial bet placed by a player at the start of the round.
     *
     * @param player_index Index of the player
     * @return int The initial bet amount
     */
    int GetPlayerInitialBet(int player_index) const override;

    void CleanTable() override;

    /**
     * @brief Fills the deck with cards according to the number of decks specified in rules.
     */
    void FillDeck();

    /**
     * @brief Shuffles the deck randomly.
     */
    void ShuffleDeck();


    Result PlaySafeBet(int player_index) override;
    Result ApplyPlayerAction(int player_index,int hand_index,Action action) override;


    void StartRound() override;
    RoundEndInfo FinishRound() override;

    /**
     * @brief Calculates the numerical value of a card.
     *
     * @param card The card to evaluate
     * @return int The value (Ace=1, face cards=10, others=face value)
     */
    int GetCardValue(Card card);

    /**
     * @brief Calculates the total value of a hand.
     *
     * Automatically handles soft aces (ace as 11) when beneficial.
     *
     * @param hand The hand to evaluate
     * @return int The optimal total value of the hand
     */
    int GetHandValue(const Hand& hand);

    /**
     * @brief Gets the game rules.
     *
     * @return const BaseRules& Reference to the game rules
     */
    const BaseRules& GetRules() const;




  private:

    std::vector<std::vector<Hand> > hands_;             ///< hands_[player_index][hand_index]
    std::vector<std::vector<int> > player_bets_;        ///< player_bets_[player_index][hand_index]
    std::vector<int> total_player_money_;               ///< total_player_money_[player_index]
    std::vector<int> insurance_bet_;                    ///< insurance_bet[player_index]
    std::vector<int> initial_bet_;                      ///< initial_bet[player_index]

    int dealer_money_;                                  ///< Current dealer money
    Hand dealer_hand_;                                  ///< Dealer's current hand
    std::vector<Card> deck_;                            ///< Deck of cards
    const BaseRules& rules_;                            ///< Reference to game rules
    unsigned int num_players_;                          ///< Number of players at table
    const int kSuitNum = 4;                             ///< Number of suits in deck
    const int kValueNum = 13;                           ///< Number of card values per suit


    /**
     * @struct HandInfo
     * @brief Contains analyzed information about a hand.
     */
    struct HandInfo{

      bool is_pair;   ///< Whether the hand is a pair
      bool is_soft;   ///< Whether the hand contains a soft ace
      int total;      ///< Total value of the hand
    };

    /**
     * @brief Analyzes a hand to extract key characteristics.
     *
     * @param hand The hand to analyze
     * @return HandInfo Structure containing hand information
     */
    HandInfo HandData(const Hand& hand);


    
};

