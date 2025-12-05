#include "IGame.h"
#include "JTable.h"
#include "IPlayer.h"
#include <vector>

class JGame: public IGame {
    public:
        void PlayGame() override;
        JGame(const JTable& table, std::vector<IPlayer*>& players);

    private:

    JTable& table_;
    std::vector<IPlayer*> players_;
};
