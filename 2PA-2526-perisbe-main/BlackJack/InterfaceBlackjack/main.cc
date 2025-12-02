#include <vector>
#include "Rules.h"
#include "JTable.h"
#include "JPlayer.h"
#include "JGame.h"

int main(int, char**) {
    BaseRules* rules; 

    rules = new BaseRules;

   

    JTable t{*rules};
    JPlayer p1{*rules},p2{*rules},p3{*rules},p4{*rules};
    JPlayer p5{*rules},p6{*rules},p7{*rules};
    std::vector<IPlayer*> Players = {&p1,&p2,&p3,&p4,&p5,&p6};
    JGame game(t, Players);
    game.PlayGame();
    delete rules;



return 0;



}