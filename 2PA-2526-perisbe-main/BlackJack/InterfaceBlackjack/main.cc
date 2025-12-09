#include <vector>
#include "Rules.h"
#include "JTable.h"
#include "JPlayer.h"
#include "JGame.h"

int main(int, char**) {

   
    BaseRules rules;

   
    const unsigned int kNumPlayers = 6;

    
    JTable table{kNumPlayers, rules};

 
    JPlayer p1{rules};
    JPlayer p2{rules};
    JPlayer p3{rules};
    JPlayer p4{rules};
    JPlayer p5{rules};
    JPlayer p6{rules};


    std::vector<IPlayer*> players = { &p1, &p2, &p3, &p4, &p5, &p6 };


    JGame game(table, players);


    game.PlayGame();

    return 0;
}
