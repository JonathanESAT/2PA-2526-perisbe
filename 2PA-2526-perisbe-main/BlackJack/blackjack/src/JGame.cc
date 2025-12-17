#include "JGame.h"

// Constructor
JGame::JGame(JTable& table, const std::vector<IPlayer*>& players)
  : table_(table), players_(players), disqualified_(players.size(), false) {}

void JGame::PlayGame() {
    int round = 0;

    // Main game loop - continues until all players are eliminated or dealer runs out of money
    while (true) {
        // Count players with money and not disqualified
        int alive_count = 0;
        for (int i = 0; i < players_.size(); i++) {
            if (!disqualified_[i] && table_.GetPlayerMoney(i) > 0) {
                alive_count++;
            }
        }

        // Game ends if no players have money
        if (alive_count == 0) {
            break;
        }

        // Game ends if dealer runs out of money
        if (table_.DealerMoney() <= 0) {
            break;
        }

        // Check and disqualify players with insufficient funds before round starts
        for (int i = 0; i < players_.size(); i++) {
            if (disqualified_[i]) {
                continue;
            }
            int money = table_.GetPlayerMoney(i);
            if (money <= 0 || money < table_.GetRules().MinimumInitialBet()) {
                disqualified_[i] = true;
                printf("Player %d DISQUALIFIED (insufficient funds for minimum bet)\n", i);
            }
        }

        // Show round info
        printf("\n");
        printf("*******************************************\n");
        printf("*          ROUND %d                       *\n", round);
        printf("*******************************************\n");
        printf("Dealer money: $%d\n", table_.DealerMoney());

        for (int i = 0; i < players_.size(); i++) {
            if (!disqualified_[i]) {
                printf("Player %d money: $%d\n", i, table_.GetPlayerMoney(i));
            }
        }
        printf("-------------------------------------------\n");

        // Prepare table for new round
        table_.CleanTable();
        table_.StartRound();

        JTable::Card dealer_card = table_.GetDealerCard();

        // Convert dealer card to string for printing
        const char* suit_symbol;
        if (dealer_card.suit_ == ITable::Suit::HEARTS) {
            suit_symbol = "\x03";  // Heart
        } else if (dealer_card.suit_ == ITable::Suit::DIAMONDS) {
            suit_symbol = "\x04";  // Diamond
        } else if (dealer_card.suit_ == ITable::Suit::CLUBS) {
            suit_symbol = "\x05";  // Club
        } else {
            suit_symbol = "\x06";  // Spade
        }

        char value_card[4];
        if (dealer_card.value_ == ITable::Value::ACE) {
            value_card[0] = 'A';
            value_card[1] = '\0';
        } else if (dealer_card.value_ == ITable::Value::JACK) {
            value_card[0] = 'J';
            value_card[1] = '\0';
        } else if (dealer_card.value_ == ITable::Value::QUEEN) {
            value_card[0] = 'Q';
            value_card[1] = '\0';
        } else if (dealer_card.value_ == ITable::Value::KING) {
            value_card[0] = 'K';
            value_card[1] = '\0';
        } else if (dealer_card.value_ == ITable::Value::TEN) {
            value_card[0] = '1';
            value_card[1] = '0';
            value_card[2] = '\0';
        } else {
            int num = (int)dealer_card.value_;
            value_card[0] = '0' + num;
            value_card[1] = '\0';
        }

        printf("\nDealer upcard: [%s%s]\n\n", value_card, suit_symbol);

        // Betting phase
        printf(">> Initial bets:\n");

        // Ask each player for their bet
        for (int i = 0; i < players_.size(); i++) {
            if (disqualified_[i]) {
                continue;
            }

            int money = table_.GetPlayerMoney(i);
            if (money <= 0) {
                continue;
            }

            int bet = players_[i]->DecideInitialBet(table_, i);
            if (bet <= 0) {
                continue;
            }

            ITable::Result result = table_.PlayInitialBet(i, bet);
            if (result != ITable::Result::Ok) {
                disqualified_[i] = true;
                printf("Player %d DISQUALIFIED for cheating (illegal bet)\n", i);
                continue;
            }

            printf("Player %d bets $%d\n", i, bet);
        }

        // Deal initial cards
        printf("\n>> Dealing cards...\n");
        for (int i = 0; i < players_.size(); i++) {
            if (disqualified_[i] || table_.GetPlayerInitialBet(i) <= 0) {
                continue;
            }

            printf("Player %d receives: ", i);

            // Deal first card
            table_.DealCard(i, 0);
            ITable::Hand hand = table_.GetHand(i, 0);
            JTable::Card card1 = hand.back();

            // Get suit symbol for card 1
            const char* s1;
            if (card1.suit_ == ITable::Suit::HEARTS) {
                s1 = "\x03";  // Heart
            } else if (card1.suit_ == ITable::Suit::DIAMONDS) {
                s1 = "\x04";  // Diamond
            } else if (card1.suit_ == ITable::Suit::CLUBS) {
                s1 = "\x05";  // Club
            } else {
                s1 = "\x06";  // Spade
            }

            char v1[4];
            if (card1.value_ == ITable::Value::ACE) {
                v1[0] = 'A';
                v1[1] = '\0';
            } else if (card1.value_ == ITable::Value::JACK) {
                v1[0] = 'J';
                v1[1] = '\0';
            } else if (card1.value_ == ITable::Value::QUEEN) {
                v1[0] = 'Q';
                v1[1] = '\0';
            } else if (card1.value_ == ITable::Value::KING) {
                v1[0] = 'K';
                v1[1] = '\0';
            } else if (card1.value_ == ITable::Value::TEN) {
                v1[0] = '1';
                v1[1] = '0';
                v1[2] = '\0';
            } else {
                int n = (int)card1.value_;
                v1[0] = '0' + n;
                v1[1] = '\0';
            }

            printf("[%s%s] ", v1, s1);

            // Deal second card
            table_.DealCard(i, 0);
            hand = table_.GetHand(i, 0);
            JTable::Card card2 = hand.back();

            // Get suit symbol for card 2
            const char* s2;
            if (card2.suit_ == ITable::Suit::HEARTS) {
                s2 = "\x03";  // Heart
            } else if (card2.suit_ == ITable::Suit::DIAMONDS) {
                s2 = "\x04";  // Diamond
            } else if (card2.suit_ == ITable::Suit::CLUBS) {
                s2 = "\x05";  // Club
            } else {
                s2 = "\x06";  // Spade
            }

            char v2[4];
            if (card2.value_ == ITable::Value::ACE) {
                v2[0] = 'A';
                v2[1] = '\0';
            } else if (card2.value_ == ITable::Value::JACK) {
                v2[0] = 'J';
                v2[1] = '\0';
            } else if (card2.value_ == ITable::Value::QUEEN) {
                v2[0] = 'Q';
                v2[1] = '\0';
            } else if (card2.value_ == ITable::Value::KING) {
                v2[0] = 'K';
                v2[1] = '\0';
            } else if (card2.value_ == ITable::Value::TEN) {
                v2[0] = '1';
                v2[1] = '0';
                v2[2] = '\0';
            } else {
                int n = (int)card2.value_;
                v2[0] = '0' + n;
                v2[1] = '\0';
            }

            printf("[%s%s]\n", v2, s2);
        }

        // Check if dealer has ace for insurance
        JTable::Card card = table_.GetDealerCard();
        if (card.value_ == ITable::Value::ACE) {
            printf("\n!! Dealer shows ACE - offering insurance !!\n");
            // Ask players if they want insurance
            for (int i = 0; i < players_.size(); i++) {
                if (disqualified_[i] || table_.GetPlayerInitialBet(i) <= 0) {
                    continue;
                }
                int wants_insurance = players_[i]->DecideUseSafe(table_, i);
                if (wants_insurance == 1) {
                    ITable::Result res = table_.PlaySafeBet(i);
                    if (res == ITable::Result::Ok) {
                        printf("Player %d buys insurance\n", i);
                    } else {
                        // Player tried to cheat, disqualify them
                        disqualified_[i] = true;
                        printf("Player %d DISQUALIFIED for cheating (illegal insurance)\n", i);
                    }
                }
            }
        }

        // Players take actions
        printf("\n>> Player actions:\n");
        for (int i = 0; i < players_.size(); i++) {
            if (disqualified_[i] || table_.GetPlayerInitialBet(i) <= 0) {
                continue;
            }

            int num_hands = table_.GetNumberOfHands(i);
            // Process each hand 
            for (int h = 0; h < num_hands; h++) {
                int keep_playing = 1;
                while (keep_playing == 1) {
                    // Get player decision
                    ITable::Action action = players_[i]->DecidePlayerAction(table_, i, h);

                    // Convert action to text
                    char* action_name;
                    if (action == ITable::Action::Stand) {
                        action_name = "STAND";
                    } else if (action == ITable::Action::Hit) {
                        action_name = "HIT";
                    } else if (action == ITable::Action::Double) {
                        action_name = "DOUBLE";
                    } else if (action == ITable::Action::Split) {
                        action_name = "SPLIT";
                    } else {
                        action_name = "UNKNOWN";
                    }

                    printf("Player %d hand %d -> %s\n", i, h, action_name);

                    // Stop if player stands
                    if (action == ITable::Action::Stand) {
                        keep_playing = 0;
                        break;
                    }

                    // Apply the action
                    ITable::Result res = table_.ApplyPlayerAction(i, h, action);
                    if (res != ITable::Result::Ok) {
                        // Player tried to cheat, disqualify them
                        disqualified_[i] = true;
                        printf("   Player %d DISQUALIFIED for cheating (illegal action)\n", i);
                        keep_playing = 0;
                        break;
                    }

                    // Update hand count if player split
                    if (action == ITable::Action::Split) {
                        num_hands = table_.GetNumberOfHands(i);
                    }
                }
            }
        }

        // Finish the round and calculate winners
        printf("\n>> Resolving round...\n");
        table_.FinishRound();

        // Show results
        printf("\n--- END OF ROUND ---\n");
        printf("Dealer money: $%d\n", table_.DealerMoney());
        for (int i = 0; i < players_.size(); i++) {
            if (!disqualified_[i]) {
                printf("Player %d money: $%d\n", i, table_.GetPlayerMoney(i));
            }
        }
        printf("*******************************************\n");

        round++;
    }

    // Show final results
    printf("\n");
    printf("*******************************************\n");
    printf("*         GAME OVER - FINAL RESULTS       *\n");
    printf("*******************************************\n");
    printf("Dealer final money: $%d\n", table_.DealerMoney());
    for (int i = 0; i < players_.size(); i++) {
        if (!disqualified_[i]) {
            printf("Player %d final money: $%d\n", i, table_.GetPlayerMoney(i));
        }
    }
    printf("*******************************************\n");
}
