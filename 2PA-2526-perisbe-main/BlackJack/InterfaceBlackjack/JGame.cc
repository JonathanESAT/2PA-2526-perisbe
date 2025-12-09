#include "JGame.h"


JGame::JGame(JTable& table, const std::vector<IPlayer*>& players) : table_(table), players_(players){}


void JGame::PrintCard(const ITable::Card& c) {
    printf("[%d-%d]", (int)c.value_, (int)c.suit_); 
}


void JGame::PlayGame() {

    const int kMaxRounds = 10000;

    for (int round = 0; round < kMaxRounds; ++round) {

        bool players_alive = false;
        for (int i = 0; i < (int)players_.size(); ++i) {
            if (table_.GetPlayerMoney(i) > 0) {
                players_alive = true;
                break;
            }
        }

        if (!players_alive || table_.DealerMoney() <= 0) {
            break;
        }

        printf("================= ROUND %d =================\n", round);
        printf("Dealer money at start: %d\n", table_.DealerMoney());
        for (int i = 0; i < (int)players_.size(); ++i) {
            printf("Player %d money = %d\n", i, table_.GetPlayerMoney(i));
        }

        table_.CleanTable();
        table_.StartRound();

        JTable::Card dealer_up = table_.GetDealerCard();
        printf("Dealer upcard: ");
        PrintCard(dealer_up);
        printf("\n");

        printf("Initial bets:\n");
        for (int i = 0; i < (int)players_.size(); ++i) {
            int money = table_.GetPlayerMoney(i);
            if (money <= 0) {
                continue;
            }

            int bet = players_[i]->DecideInitialBet(table_, i);
            if (bet <= 0) {
                continue;
            }

            ITable::Result r = table_.PlayInitialBet(i, bet);
            if (r != ITable::Result::Ok) {
                continue;
            }

            printf("Player %d bets %d\n", i, bet);
        }

        printf("Dealing cards...\n");
        for (int i = 0; i < (int)players_.size(); ++i) {
            if (table_.GetPlayerInitialBet(i) <= 0) {
                continue;
            }

            printf("Player %d receives:", i);
            for (int j = 0; j < 2; ++j) {
                table_.DealCard(i, 0);
                auto hand = table_.GetHand(i, 0);
                auto c = hand.back();
                PrintCard(c);
            }
            printf("\n");
        }

        JTable::Card dealer_card = table_.GetDealerCard();
        if (dealer_card.value_ == ITable::Value::ACE) {
            printf("Dealer shows ACE — offering insurance\n");
            for (int i = 0; i < (int)players_.size(); ++i) {
                if (table_.GetPlayerInitialBet(i) <= 0) {
                    continue;
                }
                if (players_[i]->DecideUseSafe(table_, i)) {
                    ITable::Result r = table_.PlaySafeBet(i);
                    if (r == ITable::Result::Ok) {
                        printf("Player %d buys insurance\n", i);
                    }
                }
            }
        }

        printf("Player actions:\n");
        for (int i = 0; i < (int)players_.size(); ++i) {
            if (table_.GetPlayerInitialBet(i) <= 0) {
                continue;
            }

            int num_hands = table_.GetNumberOfHands(i);
            for (int h = 0; h < num_hands; ++h) {
                while (true) {
                    ITable::Action action =
                        players_[i]->DecidePlayerAction(table_, i, h);

                    printf("Player %d hand %d action: %d\n",
                        i, h, (int)action);

                    if (action == ITable::Action::Stand) {
                        break;
                    }

                    ITable::Result res = table_.ApplyPlayerAction(i, h, action);
                    if (res != ITable::Result::Ok) {
                        break;
                    }

                    if (action == ITable::Action::Split) {
                        num_hands = table_.GetNumberOfHands(i);
                    }
                }
            }
        }

        printf("Resolving round...\n");
        table_.FinishRound();

        printf("End of round dealer money: %d\n", table_.DealerMoney());
        for (int i = 0; i < (int)players_.size(); ++i) {
            printf("Player %d money now = %d\n", i, table_.GetPlayerMoney(i));
        }
        printf("=============== END ROUND %d ===============\n\n", round);
    }

    printf("Final game end.\n");
}