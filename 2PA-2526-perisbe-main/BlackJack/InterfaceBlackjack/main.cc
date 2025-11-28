#include <vector>
#include "Rules.h"
#include "JTable.h"
#include "JPlayer.h"
#include "JGame.h"

int main() {
    RoundRules rules;

    JTable t{rules};
    JPlayer p1{rules},p2{rules},p3{rules},p4{rules};
    JPlayer p5{rules},p6{rules},p7{rules};
    JGame g{rules,t,p1,p2,p3,p4,p5,p6,p7};

    g.PlayGame();




}