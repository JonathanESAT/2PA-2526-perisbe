#include <vector>
#include <stdio.h>
#include "Rules.h"
#include "JTable.h"
#include "JPlayer.h"
#include "JGame.h"
#include "JRules.h"

int main(int, char**) {

    // Show menu
    printf("\n");
    printf("*******************************************\n");
    printf("*        BLACKJACK GAME RULES MENU        *\n");
    printf("*******************************************\n");
    printf("\n");
    printf("Choose the rules you want to play with:\n");
    printf("\n");
    printf("  1. Base Rules (Classic Blackjack)\n");
    printf("     - Win Point: 21\n");
    printf("     - Decks: 1\n");
    printf("     - Initial Cards: 2\n");
    printf("     - Dealer Stops at: 17\n");
    printf("\n");
    printf("  2. Ivan Rules\n");
    printf("     - Win Point: 25\n");
    printf("     - Decks: 2\n");
    printf("     - Initial Cards: 3\n");
    printf("     - Dealer Stops at: 21\n");
    printf("\n");
    printf("  3. Jessica Rules\n");
    printf("     - Win Point: 20\n");
    printf("     - Decks: 1\n");
    printf("     - Initial Cards: 2\n");
    printf("     - Dealer Stops at: 16\n");
    printf("\n");
    printf("*******************************************\n");
    printf("Enter your choice (1-3): ");

    int choice = 0;
    scanf("%d", &choice);

    BaseRules* rules = nullptr;

    if (choice == 1) {
        rules = new BaseRules();
        printf("\nYou selected: Base Rules\n");
    } else if (choice == 2) {
        rules = new JRulesIvan();
        printf("\nYou selected: Ivan Rules\n");
    } else if (choice == 3) {
        rules = new JRulesJessica();
        printf("\nYou selected: Jessica Rules\n");
    } else {
        printf("\nInvalid choice! Using Base Rules by default.\n");
        rules = new BaseRules();
    }

    printf("*******************************************\n");
    printf("Starting game...\n");

    const unsigned int kNumPlayers = 6;

    JTable table{kNumPlayers, *rules};

    JPlayer p1{*rules};
    JPlayer p2{*rules};
    JPlayer p3{*rules};
    JPlayer p4{*rules};
    JPlayer p5{*rules};
    JPlayer p6{*rules};

    std::vector<IPlayer*> players = { &p1, &p2, &p3, &p4, &p5, &p6 };

    JGame game(table, players);

    game.PlayGame();

    delete rules;

    return 0;
}
