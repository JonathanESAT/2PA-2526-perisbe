#include "IGame.h"
#include "JTable.h"
#include "IPlayer.h"
#include <vector>

class JGame: public IGame {
    public:
        void PlayGame() override;
        JGame(const JTable& table, std::vector<IPlayer*>& Players);
};
