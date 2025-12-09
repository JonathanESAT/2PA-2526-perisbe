#include "JRules.h"

int JRules::ChooseRules() {

    int choosed_rules_;

    printf("Choose the initial Rules of the Table");
    printf("\nPress 1 to play with normal rules");
    printf("\nPress 2 to play with Ivan rules");
    printf("\nPress 3 to play with Jessica rules");
    scanf("%d", &choosed_rules_);

    if (choosed_rules_ > 3 || choosed_rules_ <= 0) return 1;
    return choosed_rules_;
}
