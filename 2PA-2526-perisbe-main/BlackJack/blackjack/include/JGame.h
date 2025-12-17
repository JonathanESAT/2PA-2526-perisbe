#pragma once

#include "IGame.h"
#include "JTable.h"
#include "JPlayer.h"
#include "IPlayer.h"
#include <vector>

/**
 * @class JGame
 * @brief Implementation of the Blackjack game logic.
 *
 * This class manages the game flow, including rounds, betting, card dealing,
 * and determining winners. It coordinates between the table and players.
 */
class JGame : public IGame {
  public:
    /**
     * @brief Constructs a new JGame object.
     *
     * @param table Reference to the game table
     * @param players Vector of pointers to player objects
     */
    JGame(JTable& table, const std::vector<IPlayer*>& players);

    void PlayGame() override;

  private:
    JTable& table_;                   ///< Reference to the game table
    std::vector<IPlayer*> players_;   ///< List of players in the game
    std::vector<bool> disqualified_;  ///< Track which players are disqualified for cheating
};
