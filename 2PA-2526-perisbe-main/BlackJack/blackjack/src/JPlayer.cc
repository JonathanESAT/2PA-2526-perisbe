#include "JPlayer.h"
#include <cassert>

// Strategy table with all the rules for basic blackjack strategy
static const JPlayer::Rule kRules[] =
{
    // ========================= HARD HANDS =========================

    // Hard 8
    {false,false,8 , ITable::Value::ACE,   ITable::Value::KING, JPlayer::Decision::Hit},

    // Hard 9
    {false,false,9 , ITable::Value::THREE, ITable::Value::SIX,  JPlayer::Decision::Double},
    {false,false,9 , ITable::Value::ACE,   ITable::Value::TWO,  JPlayer::Decision::Hit},
    {false,false,9 , ITable::Value::SEVEN, ITable::Value::KING, JPlayer::Decision::Hit},

    // Hard 10
    {false,false,10, ITable::Value::TWO,   ITable::Value::NINE, JPlayer::Decision::Double},
    {false,false,10, ITable::Value::TEN,   ITable::Value::KING, JPlayer::Decision::Hit},
    {false,false,10, ITable::Value::ACE,   ITable::Value::ACE,  JPlayer::Decision::Hit},

    // Hard 11
    {false,false,11, ITable::Value::ACE,   ITable::Value::ACE,  JPlayer::Decision::Hit},
    {false,false,11, ITable::Value::TWO,   ITable::Value::KING, JPlayer::Decision::Double},

    // Hard 12
    {false,false,12, ITable::Value::FOUR,  ITable::Value::SIX,  JPlayer::Decision::Stand},
    {false,false,12, ITable::Value::ACE,   ITable::Value::THREE,JPlayer::Decision::Hit},
    {false,false,12, ITable::Value::SEVEN, ITable::Value::KING, JPlayer::Decision::Hit},

    // Hard 13–16
    {false,false,13, ITable::Value::TWO,   ITable::Value::SIX,  JPlayer::Decision::Stand},
    {false,false,13, ITable::Value::SEVEN, ITable::Value::KING, JPlayer::Decision::Hit},
    {false,false,13, ITable::Value::ACE,   ITable::Value::ACE,  JPlayer::Decision::Hit},

    {false,false,14, ITable::Value::TWO,   ITable::Value::SIX,  JPlayer::Decision::Stand},
    {false,false,14, ITable::Value::SEVEN, ITable::Value::KING, JPlayer::Decision::Hit},
    {false,false,14, ITable::Value::ACE,   ITable::Value::ACE,  JPlayer::Decision::Hit},

    {false,false,15, ITable::Value::TWO,   ITable::Value::SIX,  JPlayer::Decision::Stand},
    {false,false,15, ITable::Value::SEVEN, ITable::Value::KING, JPlayer::Decision::Hit},
    {false,false,15, ITable::Value::ACE,   ITable::Value::ACE,  JPlayer::Decision::Hit},

    {false,false,16, ITable::Value::TWO,   ITable::Value::SIX,  JPlayer::Decision::Stand},
    {false,false,16, ITable::Value::SEVEN, ITable::Value::KING, JPlayer::Decision::Hit},
    {false,false,16, ITable::Value::ACE,   ITable::Value::ACE,  JPlayer::Decision::Hit},

    // Hard 17–21
    {false,false,17, ITable::Value::ACE,   ITable::Value::KING, JPlayer::Decision::Stand},
    {false,false,18, ITable::Value::ACE,   ITable::Value::KING, JPlayer::Decision::Stand},
    {false,false,19, ITable::Value::ACE,   ITable::Value::KING, JPlayer::Decision::Stand},
    {false,false,20, ITable::Value::ACE,   ITable::Value::KING, JPlayer::Decision::Stand},
    {false,false,21, ITable::Value::ACE,   ITable::Value::KING, JPlayer::Decision::Stand},

    // ========================= SOFT HANDS =========================

    // Soft 18 (A+7)
    {false,true,18, ITable::Value::TWO,   ITable::Value::TWO,   JPlayer::Decision::Stand},
    {false,true,18, ITable::Value::SEVEN, ITable::Value::EIGHT, JPlayer::Decision::Stand},
    {false,true,18, ITable::Value::THREE, ITable::Value::SIX,   JPlayer::Decision::Double},
    {false,true,18, ITable::Value::NINE,  ITable::Value::ACE,   JPlayer::Decision::Hit},

    // Soft 17 (A+6)
    {false,true,17, ITable::Value::THREE, ITable::Value::SIX,   JPlayer::Decision::Double},
    {false,true,17, ITable::Value::ACE,   ITable::Value::TWO,   JPlayer::Decision::Hit},
    {false,true,17, ITable::Value::SEVEN, ITable::Value::KING,  JPlayer::Decision::Hit},

    // Soft 15–16 (A+4, A+5)
    {false,true,15, ITable::Value::THREE, ITable::Value::FIVE,  JPlayer::Decision::Double},
    {false,true,15, ITable::Value::ACE,   ITable::Value::TWO,   JPlayer::Decision::Hit},
    {false,true,15, ITable::Value::SIX,   ITable::Value::KING,  JPlayer::Decision::Hit},

    {false,true,16, ITable::Value::THREE, ITable::Value::FIVE,  JPlayer::Decision::Double},
    {false,true,16, ITable::Value::ACE,   ITable::Value::TWO,   JPlayer::Decision::Hit},
    {false,true,16, ITable::Value::SIX,   ITable::Value::KING,  JPlayer::Decision::Hit},

    // Soft 13–14 (A+2, A+3)
    {false,true,13, ITable::Value::FOUR, ITable::Value::FIVE,  JPlayer::Decision::Double},
    {false,true,13, ITable::Value::ACE,  ITable::Value::THREE, JPlayer::Decision::Hit},
    {false,true,13, ITable::Value::SIX,  ITable::Value::KING,  JPlayer::Decision::Hit},

    {false,true,14, ITable::Value::FOUR, ITable::Value::FIVE,  JPlayer::Decision::Double},
    {false,true,14, ITable::Value::ACE,  ITable::Value::THREE, JPlayer::Decision::Hit},
    {false,true,14, ITable::Value::SIX,  ITable::Value::KING,  JPlayer::Decision::Hit},

    // ========================= PAIRS =========================

    // A-A (total 12)
    {true,false,12, ITable::Value::ACE, ITable::Value::KING,  JPlayer::Decision::Split},

    // 9-9 (total 18)
    {true,false,18, ITable::Value::ACE,   ITable::Value::ACE,  JPlayer::Decision::Split},
    {true,false,18, ITable::Value::TWO,   ITable::Value::FIVE, JPlayer::Decision::Split},
    {true,false,18, ITable::Value::SEVEN, ITable::Value::EIGHT,JPlayer::Decision::Split},
    {true,false,18, ITable::Value::SIX,   ITable::Value::SIX,  JPlayer::Decision::Stand},
    {true,false,18, ITable::Value::NINE,  ITable::Value::KING, JPlayer::Decision::Stand},

    // 8-8 (total 16)
    {true,false,16, ITable::Value::ACE,   ITable::Value::KING, JPlayer::Decision::Split},

    // 7-7 (total 14)
    {true,false,14, ITable::Value::ACE,   ITable::Value::SIX,  JPlayer::Decision::Split},
    {true,false,14, ITable::Value::SEVEN, ITable::Value::KING, JPlayer::Decision::Hit},

    // 6-6 (total 12)
    {true,false,12, ITable::Value::ACE,   ITable::Value::FIVE, JPlayer::Decision::Split},
    {true,false,12, ITable::Value::SIX,   ITable::Value::KING, JPlayer::Decision::Hit},

    // 5-5 (total 10)
    {true,false,10, ITable::Value::ACE,   ITable::Value::EIGHT, JPlayer::Decision::Double},
    {true,false,10, ITable::Value::NINE,  ITable::Value::KING,  JPlayer::Decision::Hit},

    // 4-4 (total 8)
    {true,false,8 , ITable::Value::ACE,   ITable::Value::KING, JPlayer::Decision::Hit},

    // 3-3 y 2-2
    {true,false,4 , ITable::Value::THREE, ITable::Value::SIX,  JPlayer::Decision::Split},
    {true,false,6 , ITable::Value::THREE, ITable::Value::SIX,  JPlayer::Decision::Split},
    {true,false,4 , ITable::Value::ACE,   ITable::Value::KING, JPlayer::Decision::Hit},
    {true,false,6 , ITable::Value::ACE,   ITable::Value::KING, JPlayer::Decision::Hit},

    // 10-10 (total 20)
    {true,false,20, ITable::Value::ACE,   ITable::Value::KING, JPlayer::Decision::Stand}
};

// Constructor - builds the strategy table from rules
JPlayer::JPlayer(const BaseRules& rules)
  : rules_(rules) {

    strategy_table_.clear();

    const int num_rules = static_cast<int>(sizeof(kRules) / sizeof(kRules[0]));

    // Fill the hash table with all rules
    for (int i = 0; i < num_rules; ++i) {
        const Rule& r = kRules[i];

        // Expand rule for all dealer cards in range
        for (int dv = static_cast<int>(r.dealer_min);
             dv <= static_cast<int>(r.dealer_max);
             ++dv) {

            // Create key for this situation
            Key key;
            key.is_pair = r.is_pair;
            key.is_soft = r.is_soft;
            key.total = r.total;
            key.dealer_card = static_cast<ITable::Value>(dv);

            strategy_table_[key] = r.decision;
        }
    }
}

// Get the value of a card (Ace=11, faces=10)
int JPlayer::GetCardValue(ITable::Card card) {
    ITable::Value value = card.value_;

    switch (value) {
      case ITable::Value::ACE:   return 11;
      case ITable::Value::TWO:   return 2;
      case ITable::Value::THREE: return 3;
      case ITable::Value::FOUR:  return 4;
      case ITable::Value::FIVE:  return 5;
      case ITable::Value::SIX:   return 6;
      case ITable::Value::SEVEN: return 7;
      case ITable::Value::EIGHT: return 8;
      case ITable::Value::NINE:  return 9;
      case ITable::Value::TEN:   return 10;
      case ITable::Value::JACK:  return 10;
      case ITable::Value::QUEEN: return 10;
      case ITable::Value::KING:  return 10;
      case ITable::Value::end:   break;
    }
    
    return 0;
}

// Analyze a hand to get total, soft/hard, and pair info
JPlayer::HandInfo JPlayer::HandData(const ITable::Hand& hand) {

  HandInfo info;
  info.is_pair = false;
  info.is_soft = false;
  info.total = 0;

  if (hand.empty()) {
    return info;
  }

  int sum = 0;
  int aces_count = 0;

  // Calculate sum and count aces
  for (const ITable::Card& card : hand) {
    if (card.value_ == ITable::Value::ACE) {
      aces_count++;
    }
    sum += GetCardValue(card);
  }

  int remaining_aces_as_11 = aces_count;

  // Convert aces from 11 to 1 if needed to avoid busting
  int win_point = rules_.GetWinPoint();
  while (sum > win_point && remaining_aces_as_11 > 0) {
    sum -= 10;
    remaining_aces_as_11--;
  }

  info.total = sum;

  // Check if it's a pair (two cards with same value)
  if (hand.size() == 2 && hand[0].value_ == hand[1].value_) {
    info.is_pair = true;
  } else {
    info.is_pair = false;
  }

  // Check if hand is soft (has an ace counted as 11)
  if (!info.is_pair) {
    if (aces_count > 0 && remaining_aces_as_11 > 0 && info.total <= win_point) {
      info.is_soft = true;
    } else {
      info.is_soft = false;
    }
  } else {
    info.is_soft = false;
  }

  return info;
}

// Decide what action to take based on strategy table
ITable::Action JPlayer::DecidePlayerAction(const ITable& table, int player_index, int hand_index) {
    ITable::Hand hand = table.GetHand(player_index, hand_index);

    if (hand.empty()) {
        return ITable::Action::Hit;
    }

    HandInfo info = HandData(hand);
    ITable::Card dealer_card = table.GetDealerCard();

    // Look up decision in strategy table
    Decision decision = GetMatCorrectDecision(info, dealer_card);

    // Can't split if not a pair or more than 2 cards
    if (decision == Decision::Split) {
        if (!info.is_pair || hand.size() != 2) {
            if (info.total >= 17) {
                decision = Decision::Stand;
            }
            else {
                decision = Decision::Hit;
            }
        }
    }

    // Can only double on first 2 cards
    if (decision == Decision::Double && hand.size() != 2) {
        decision = Decision::Hit;
    }

    // Can't double if not enough money
    if (decision == Decision::Double) {
        int bet = table.GetPlayerCurrentBet(player_index, hand_index);
        int money = table.GetPlayerMoney(player_index);

        if (money < bet) {
            decision = Decision::Hit;
        }
    }

    // Convert internal decision to ITable action
    switch (decision) {
    case Decision::Stand:  return ITable::Action::Stand;
    case Decision::Hit:    return ITable::Action::Hit;
    case Decision::Split:  return ITable::Action::Split;
    case Decision::Double: return ITable::Action::Double;
    default:               return ITable::Action::Stand;
    }
}

// Decide how much to bet (proportional betting strategy)
int JPlayer::DecideInitialBet(const ITable& table, int player_index) {

    int money = table.GetPlayerMoney(player_index);

    int min_bet = rules_.MinimumInitialBet();
    int max_bet = rules_.MaximumInitialBet();

    // Can't bet if not enough money
    if(money < min_bet) return 0;
    assert(min_bet <= max_bet);

    // Proportional betting with limit: bet 5% of current money
    int bet = money / 20;

    // Ensure bet is at least the minimum
    if (bet < min_bet) bet = min_bet;

    // Cap at 3x minimum bet to avoid excessive risk
    if (bet > min_bet * 3) bet = min_bet * 3;

    // Respect table maximum
    if (bet > max_bet) bet = max_bet;

    assert(bet >= min_bet);
    assert(bet <= max_bet);
    assert(bet <= money);

    return bet;
}

// Decide if we want insurance (yes if we have blackjack)
bool JPlayer::DecideUseSafe(const ITable& table, int player_index) {

    ITable::Hand hand = table.GetHand(player_index, 0);

    if (hand.size() != 2) {
        return false;
    }

    HandInfo info = HandData(hand);

    // Take insurance only if we have blackjack
    if (info.total != rules_.GetWinPoint()) {
        return false;
    }

    return true;
}

// Look up the correct decision in the strategy table
JPlayer::Decision JPlayer::GetMatCorrectDecision(HandInfo info, ITable::Card dealer_card) {

    // Build lookup key
    Key key;
    key.is_pair = info.is_pair;
    key.is_soft  = info.is_soft;
    key.total = info.total;
    key.dealer_card = dealer_card.value_;

    // Find decision in table
    auto it = strategy_table_.find(key);

    if (it != strategy_table_.end()) {
        return it->second;
    }

    // Default to stand if no rule found
    return Decision::Stand;
}
