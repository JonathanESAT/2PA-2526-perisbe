#include "JPlayer.h"



JPlayer::JPlayer(){

    strategy_table_.clear();


    // HARD 8 -> siempre Hit
    for(int dealer = static_cast<int>(ITable::Value::ACE); dealer <= static_cast<int>(ITable::Value::KING); dealer++){

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

}


ITable::Action JPlayer::DecidePlayerAction(const ITable& table, int player_index, int hand_index){
    return ITable::Action::Stand;
}

int JPlayer::DecideInitialBet(const ITable& table, int player_index){
    return 0;
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
