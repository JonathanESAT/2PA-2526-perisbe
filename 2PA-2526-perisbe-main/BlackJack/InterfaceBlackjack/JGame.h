#pragma once

#include "IGame.h"
#include "JTable.h"
#include "JPlayer.h"
#include "IPlayer.h"
#include <vector>

class JGame : public IGame {
  public:
    JGame(JTable& table, const std::vector<IPlayer*>& players);
    void PlayGame() override;
    void PrintCard(const ITable::Card& c);

  private:
    JTable& table_;
    std::vector<IPlayer*> players_;
};
