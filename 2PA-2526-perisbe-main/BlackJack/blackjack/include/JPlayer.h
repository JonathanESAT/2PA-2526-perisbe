#pragma once
#include "IPlayer.h"
#include "Rules.h"
#include <unordered_map>

/**
 * @class JPlayer
 * @brief Implementation of a Blackjack player using basic strategy.
 *
 * This class implements an AI player that makes decisions based on
 * a pre-computed strategy table following optimal Blackjack strategy.
 */
class JPlayer : public IPlayer {
  public:
    /**
     * @brief Constructs a new JPlayer object.
     *
     * @param rules Reference to the game rules
     */
    JPlayer(const BaseRules& rules);

    ITable::Action DecidePlayerAction(const ITable& table, int player_index, int hand_index) override;

    int DecideInitialBet(const ITable& table, int player_index) override;

    bool DecideUseSafe(const ITable& table, int player_index) override;

    /**
     * @enum Decision
     * @brief Represents possible player decisions in strategy table.
     */
    enum class Decision : int {
      Stand = 0,  ///< Stand with current hand
      Hit,        ///< Request another card
      Split,      ///< Split a pair into two hands
      Double,     ///< Double bet and receive one more card
      end = 4,    ///< Sentinel value
    };

    /**
     * @struct Rule
     * @brief Defines a strategy rule based on hand and dealer card.
     */
    struct Rule {
      bool is_pair;               ///< Whether the hand is a pair
      bool is_soft;               ///< Whether the hand contains a soft ace
      int total;                  ///< Total value of the hand

      ITable::Value dealer_min;   ///< Minimum dealer card value for this rule
      ITable::Value dealer_max;   ///< Maximum dealer card value for this rule

      Decision decision;          ///< Recommended action for this situation
    };
   
  private:

    const BaseRules& rules_;  ///< Reference to the game rules

    /**
     * @struct Key
     * @brief Hash key for strategy table lookup.
     */
    struct Key {
      bool is_pair;               ///< Whether hand is a pair
      bool is_soft;               ///< Whether hand is soft
      int total;                  ///< Hand total value
      ITable::Value dealer_card;  ///< Dealer's visible card

      bool operator==(const Key& other) const {
        return is_pair == other.is_pair &&
               is_soft == other.is_soft &&
               total == other.total &&
               dealer_card == other.dealer_card;
      }
    };

    /**
     * @struct KeyHash
     * @brief Hash function for Key used in unordered_map.
     */
    struct KeyHash {
      size_t operator()(const Key& key) const {
        size_t h1 = std::hash<bool>()(key.is_pair);
        size_t h2 = std::hash<bool>()(key.is_soft);
        size_t h3 = std::hash<int>()(key.total);
        size_t h4 = std::hash<int>()(static_cast<int>(key.dealer_card));

        size_t running_val = h1;
        running_val = _rotr(running_val, 8);
        running_val ^= h2;
        running_val = _rotr(running_val, 8);
        running_val ^= h3;
        running_val = _rotr(running_val, 8);
        running_val ^= h4;
        return running_val;
      }
    };

    /**
     * @struct HandInfo
     * @brief Contains information about a hand's composition.
     */
    struct HandInfo {
      bool is_pair;   ///< Whether the hand is a pair
      bool is_soft;   ///< Whether the hand contains a soft ace
      int total;      ///< Total value of the hand
    };

    std::unordered_map<Key, Decision, KeyHash> strategy_table_;  ///< Pre-computed strategy decisions

    /**
     * @brief Calculates the value of a card.
     *
     * @param card The card to evaluate
     * @return int The numerical value of the card (Ace=1, Jack/Queen/King=10)
     */
    int GetCardValue(ITable::Card card);

    /**
     * @brief Analyzes a hand to extract key information.
     *
     * @param hand The hand to analyze
     * @return HandInfo Structure containing hand characteristics
     */
    HandInfo HandData(const ITable::Hand& hand);

    /**
     * @brief Gets the optimal decision from the strategy table.
     *
     * @param info Information about the current hand
     * @param dealer_card The dealer's visible card
     * @return Decision The recommended action
     */
    Decision GetMatCorrectDecision(HandInfo info, ITable::Card dealer_card);
};
