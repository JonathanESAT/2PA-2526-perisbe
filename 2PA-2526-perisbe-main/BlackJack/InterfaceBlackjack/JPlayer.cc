#pragma once
#include "JPlayer.h"
#include "cassert"



JPlayer::JPlayer(const BaseRules& rules) :rules_{ rules } {

    strategy_table_.clear();


    // HARD 8 -> siempre Hit

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); dealer++) {

        Key key;
        key.is_pair = false;
        key.is_soft = false;
        key.total = 8;
        key.dealer_card = static_cast<ITable::Value>(dealer);
        strategy_table_[key] = Decision::Hit;


    }

    // HARD 9

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); dealer++) {

        Key key;
        key.is_pair = false;
        key.is_soft = false;
        key.total = 9;
        key.dealer_card = (ITable::Value)dealer;

        if (dealer >= static_cast<int>(ITable::Value::THREE) && dealer <= static_cast<int>(ITable::Value::SIX))
            strategy_table_[key] = Decision::Double;
        else
            strategy_table_[key] = Decision::Hit;
    }

    // HARD 10

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); dealer++) {

        Key key;
        key.is_pair = false;
        key.is_soft = false;
        key.total = 10;
        key.dealer_card = (ITable::Value)dealer;

        if (dealer >= static_cast<int>(ITable::Value::TWO) && dealer <= static_cast<int>(ITable::Value::NINE))
            strategy_table_[key] = Decision::Double;
        else
            strategy_table_[key] = Decision::Hit;
    }

    // HARD 11

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); dealer++) {

        Key key;
        key.is_pair = false;
        key.is_soft = false;
        key.total = 11;
        key.dealer_card = (ITable::Value)dealer;

        if (dealer == static_cast<int>(ITable::Value::ACE))
            strategy_table_[key] = Decision::Hit;
        else
            strategy_table_[key] = Decision::Double;
    }

    // HARD 12

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); dealer++) {

        Key key;
        key.is_pair = false;
        key.is_soft = false;
        key.total = 12;
        key.dealer_card = (ITable::Value)dealer;

        if (dealer >= static_cast<int>(ITable::Value::FOUR) && dealer <= static_cast<int>(ITable::Value::SIX))
            strategy_table_[key] = Decision::Stand;
        else
            strategy_table_[key] = Decision::Hit;
    }

    // HARD 13 a 16

    for (int total = 13; total <= 16; total++) {
        for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); dealer++) {

            Key Key;
            Key.is_pair = false;
            Key.is_soft = false;
            Key.total = total;
            Key.dealer_card = (ITable::Value)dealer;

            if (dealer >= static_cast<int>(ITable::Value::TWO) && dealer <= static_cast<int>(ITable::Value::SIX))
                strategy_table_[Key] = Decision::Stand;
            else
                strategy_table_[Key] = Decision::Hit;
        }
    }

    // HARD 17+

    for (int total = 17; total <= 21; total++) {

        for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); dealer++) {

            Key Key;
            Key.is_pair = false;
            Key.is_soft = false;
            Key.total = total;
            Key.dealer_card = (ITable::Value)dealer;

            strategy_table_[Key] = Decision::Stand;
        }
    }

    // SOFT 18 (A+7)

    int total = 18;

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

        Key key;
        key.is_pair = false;
        key.is_soft = true;
        key.total = total;
        key.dealer_card = static_cast<ITable::Value>(dealer);

        if (dealer == static_cast<int>(ITable::Value::TWO) || dealer == static_cast<int>(ITable::Value::SEVEN) || dealer == static_cast<int>(ITable::Value::EIGHT)) {

            strategy_table_[key] = Decision::Stand;

        }
        else if (dealer >= static_cast<int>(ITable::Value::THREE) && dealer <= static_cast<int>(ITable::Value::SIX)) {

            strategy_table_[key] = Decision::Double;

        }
        else {
            // 9, 10, J, Q, K, A
            strategy_table_[key] = Decision::Hit;
        }
    }

    // SOFT 17 (A+6)

    total = 17;

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

        Key key;
        key.is_pair = false;
        key.is_soft = true;
        key.total = total;
        key.dealer_card = static_cast<ITable::Value>(dealer);

        if (dealer >= static_cast<int>(ITable::Value::THREE) && dealer <= static_cast<int>(ITable::Value::SIX)) {

            strategy_table_[key] = Decision::Double;

        }
        else {

            strategy_table_[key] = Decision::Hit;
        }
    }

    // SOFT 15 y 16 (A+4, A+5)

    for (int total = 15; total <= 16; ++total) {

        for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

            Key key;
            key.is_pair = false;
            key.is_soft = true;
            key.total = total;
            key.dealer_card = static_cast<ITable::Value>(dealer);

            if (dealer >= static_cast<int>(ITable::Value::THREE) && dealer <= static_cast<int>(ITable::Value::FIVE)) {

                strategy_table_[key] = Decision::Double;

            }
            else {

                strategy_table_[key] = Decision::Hit;
            }

        }
    }

    // SOFT 13 y 14 (A+2, A+3)

    for (int total = 13; total <= 14; ++total) {

        for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

            Key key;
            key.is_pair = false;
            key.is_soft = true;
            key.total = total;
            key.dealer_card = static_cast<ITable::Value>(dealer);

            if (dealer == static_cast<int>(ITable::Value::FOUR) || dealer == static_cast<int>(ITable::Value::FIVE)) {

                strategy_table_[key] = Decision::Double;

            }
            else {

                strategy_table_[key] = Decision::Hit;
            }
        }
    }

    // PAIR A-A (total 12)

    total = 12;


    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

        Key key;
        key.is_pair = true;
        key.is_soft = false;
        key.total = total;
        key.dealer_card = static_cast<ITable::Value>(dealer);

        strategy_table_[key] = Decision::Split;
    }


    // PAIR 9-9 (total 18)

    total = 18;

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

        Key key;
        key.is_pair = true;
        key.is_soft = false;
        key.total = total;
        key.dealer_card = static_cast<ITable::Value>(dealer);

        if (dealer == static_cast<int>(ITable::Value::ACE) || (dealer >= static_cast<int>(ITable::Value::TWO) &&
            dealer <= static_cast<int>(ITable::Value::FIVE)) || dealer == static_cast<int>(ITable::Value::SEVEN) || dealer == static_cast<int>(ITable::Value::EIGHT)) {

            strategy_table_[key] = Decision::Split;

        }
        else {
            // dealer = 6, 9, 10/J/Q/K
            strategy_table_[key] = Decision::Stand;
        }
    }

    // PAIR 8-8 (total 16)

    total = 16;

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

        Key key;
        key.is_pair = true;
        key.is_soft = false;
        key.total = total;
        key.dealer_card = static_cast<ITable::Value>(dealer);

        strategy_table_[key] = Decision::Split;
    }

    // PAIR 7-7 (total 14)

    total = 14;

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

        Key key;
        key.is_pair = true;
        key.is_soft = false;
        key.total = total;
        key.dealer_card = static_cast<ITable::Value>(dealer);

        if (dealer <= static_cast<int>(ITable::Value::SIX)) {

            strategy_table_[key] = Decision::Split;

        }
        else {

            strategy_table_[key] = Decision::Hit;
        }
    }

    // PAIR 6-6

    total = 12;

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

        Key key;
        key.is_pair = true;
        key.is_soft = false;
        key.total = total;
        key.dealer_card = static_cast<ITable::Value>(dealer);

        if (dealer <= static_cast<int>(ITable::Value::FIVE)) {

            strategy_table_[key] = Decision::Split;

        }
        else {

            strategy_table_[key] = Decision::Hit;
        }
    }

    // PAIR 5-5 (total 10)

    total = 10;

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

        Key key;
        key.is_pair = true;
        key.is_soft = false;
        key.total = total;
        key.dealer_card = static_cast<ITable::Value>(dealer);

        if (dealer <= static_cast<int>(ITable::Value::EIGHT)) {

            strategy_table_[key] = Decision::Double;

        }
        else {

            strategy_table_[key] = Decision::Hit;
        }
    }

    // PAIR 4-4 (total 8)

    total = 8;

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

        Key key;
        key.is_pair = true;
        key.is_soft = false;
        key.total = total;
        key.dealer_card = static_cast<ITable::Value>(dealer);

        strategy_table_[key] = Decision::Hit;
    }

    // PAIR 2-2 (total 4) y 3-3 (total 6)

    for (int total : {4, 6}) {

        for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

            Key key;
            key.is_pair = true;
            key.is_soft = false;
            key.total = total;
            key.dealer_card = static_cast<ITable::Value>(dealer);

            if (dealer == static_cast<int>(ITable::Value::ACE) || dealer == static_cast<int>(ITable::Value::TWO)) {

                strategy_table_[key] = Decision::Hit;

            }
            else if (dealer >= static_cast<int>(ITable::Value::THREE) && dealer <= static_cast<int>(ITable::Value::SIX)) {

                strategy_table_[key] = Decision::Split;

            }
            else {

                strategy_table_[key] = Decision::Hit;
            }
        }
    }

    // PAIR 10-10 (total 20)

    total = 20;

    for (int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); ++dealer) {

        Key key;
        key.is_pair = true;
        key.is_soft = false;
        key.total = total;
        key.dealer_card = static_cast<ITable::Value>(dealer);

        strategy_table_[key] = Decision::Stand;
    }
}

int JPlayer::GetCardValue(JTable::Card card) {
    JTable::Value value = card.value_;


    switch (value)
    {
    case ITable::Value::ACE:
        return 11;
    case ITable::Value::TWO:
        return 2;
    case ITable::Value::THREE:
        return 3;
    case ITable::Value::FOUR:
        return 4;
    case ITable::Value::FIVE:
        return 5;
    case ITable::Value::SIX:
        return 6;
    case ITable::Value::SEVEN:
        return 7;
    case ITable::Value::EIGHT:
        return 8;
    case ITable::Value::NINE:
        return 9;
    case ITable::Value::TEN:
        return 10;
    case ITable::Value::JACK:
        return 10;
    case ITable::Value::QUEEN:
        return 10;
    case ITable::Value::KING:
        return 10;
    }

}


JPlayer::HandInfo JPlayer::HandData(const ITable::Hand& hand) {

  HandInfo info;
  info.is_pair = false;
  info.is_soft = false;
  info.total   = 0;

  
  if (hand.empty()) {

    return info;

  }

  int sum = 0;
  int aces_count = 0;

  
  for (const ITable::Card& card : hand) {

    if (card.value_ == ITable::Value::ACE) {
      aces_count++;
    }

    sum += GetCardValue(card);
  }

  
  int remaining_aces_as_11 = aces_count;

  while (sum > 21 && remaining_aces_as_11 > 0) {
    sum -= 10;              
    remaining_aces_as_11--;

  }

  info.total = sum;


  if (hand.size() == 2 && hand[0].value_ == hand[1].value_) {
    info.is_pair = true;

  } else {
    info.is_pair = false;

  }


  if (!info.is_pair) {

    if (aces_count > 0 && remaining_aces_as_11 > 0 && info.total <= 21) {
      info.is_soft = true;

    } else {
      info.is_soft = false;

    }

  } else {
   
    info.is_soft = false;
  }

  return info;
}

    


ITable::Action JPlayer::DecidePlayerAction(const ITable& table, int player_index, int hand_index) {
   
    ITable::Hand hand = table.GetHand(player_index, hand_index);

   
    if (hand.empty()) {

        return ITable::Action::Hit;
    }

    
    HandInfo info = HandData(hand);

  
    ITable::Card dealer_card = table.GetDealerCard();

   
    Decision decision = GetMatCorrectDecision(info, dealer_card);


    if (decision == Decision::Split) {
        if (!info.is_pair || hand.size() != 2) {
          
            if (info.total >= 17) {

                decision = Decision::Stand;

            } else {

                decision = Decision::Hit;
            }
        }
    }

   
    if (decision == Decision::Double && hand.size() != 2) {
       
        decision = Decision::Hit;
    }

    
    switch (decision) {

        case Decision::Stand: 
            return ITable::Action::Stand;

        case Decision::Hit:    
            return ITable::Action::Hit;

        case Decision::Split:  
            return ITable::Action::Split;

        case Decision::Double: 
            return ITable::Action::Double;

        default:               
            return ITable::Action::Stand;
    }
}


int JPlayer::DecideInitialBet(const ITable& table, int player_index) {

    int money = table.GetPlayerMoney(player_index);

    if (money <= 0) {
        return 0;
    }

    int min_bet = rules_.MinimumInitialBet();
    int max_bet = rules_.MaximumInitialBet();

    int bet = money / 20;

    assert(bet < min_bet);
        
    assert(bet > max_bet);

    assert(bet > money);

    return bet;
}


bool JPlayer::DecideUseSafe(const ITable& table, int player_index){
    return true;
}

JPlayer::Decision JPlayer::GetMatCorrectDecision(HandInfo info, ITable::Card dealer_card) {

    Key key;
    key.is_pair = info.is_pair;
    key.is_soft = info.is_soft;
    key.total = info.total;
    key.dealer_card = dealer_card.value_;

    auto it = strategy_table_.find(key);

    if(it != strategy_table_.end()){
        return it->second;
    }

    return Decision::Stand;
}
