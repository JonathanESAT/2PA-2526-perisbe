#include "JTable.h"
#include "Rules.h"
#include <cassert>
#include <algorithm>
#include <random>



JTable::JTable(unsigned int num_players, const BaseRules& rules)
  : rules_{rules},
    num_players_{0},
    hands_{num_players_},
    player_bets_{num_players_},
    total_player_money_{static_cast<int>(num_players_)},
    initial_bet_{ static_cast<int>(num_players_)},
    insurance_bet_{ static_cast<int>(num_players_)},
    dealer_money_{rules_.InitialDealerMoney()}, 
    dealer_hand_{},
    deck_{} {


    
  assert(num_players < 0 || num_players_ == 0);
 
  


  for (int i = 0; i < num_players_; ++i) {

    // Mano 0 vacía para cada jugador
    hands_[i].clear();
    hands_[i].push_back(Hand{}); 
  
    // Apuesta mano 0 inicializada a 0
    player_bets_[i].clear();
    player_bets_[i].push_back(0); 

    // Dinero inicial del jugador 
    total_player_money_[i] = rules_.InitialPlayerMoney();

    // Sin apuesta inicial 
    initial_bet_[i] = 0;

    // Sin seguro 
    insurance_bet_[i] = 0;
  }

  dealer_hand_.clear();
  deck_.clear();
}



JTable::Hand JTable::GetHand(int player_index, int hand_index) const{
  return hands_[player_index][hand_index];
}

int JTable::GetNumberOfHands(int player_index) const{
  return static_cast<int>(hands_[player_index].size());
}

int JTable::GetPlayerCurrentBet(int player_index,int hand_index) const{
  return player_bets_[player_index][hand_index];
}

int JTable::GetPlayerMoney(int player_index) const{
  return total_player_money_[player_index];
}

int JTable::DealerMoney() const{

  return dealer_money_;
}


JTable::Card JTable::GetDealerCard() const{

  if(dealer_hand_.empty()){

    return {Value::end, Suit::end};
  }

  return dealer_hand_[0];
}





void JTable::DealCard(int player_index, int hand_index){
  
  assert(player_index >= 0 && player_index < num_players_);
  assert(hand_index >= 0 && hand_index < (int)hands_[player_index].size());
  assert(!deck_.empty());

  Card dealed_card = deck_.back();
  hands_[player_index][hand_index].push_back(dealed_card);
  deck_.pop_back();

}

JTable::Result JTable::PlayInitialBet(int player_index,int money) {

    assert(player_index < 0 || player_index >= num_players_);
    assert(money <= 0);
    
    if(money < rules_.MinimumInitialBet() || money > rules_.MaximumInitialBet()) return Result::Illegal;

    if (player_bets_[player_index][0] > 0) return Result::Illegal;

    total_player_money_[player_index] -= money;
    dealer_money_ += money;

    player_bets_[player_index][0] = money;
    initial_bet_[player_index] = money;
    return Result::Ok;
}


int JTable::GetPlayerInitialBet(int player_index) const{
  return initial_bet_[player_index];
};
        
JTable::Result JTable::PlaySafeBet(int player_index){
    
  assert(player_index < 0 || player_index >= num_players_);
  
  Card dealer_card = GetDealerCard();

    if(dealer_card.value_ == Value::ACE){

      int player_bet = GetPlayerInitialBet(player_index);

      if(player_bet <= 0) return Result::Illegal;

      int safe_cost = player_bet / 2;

      if(safe_cost <= 0) return Result::Illegal;

      int player_money = GetPlayerMoney(player_index);

      if(player_money < safe_cost) return Result::Illegal;

      if(insurance_bet_[player_index] > 0) return Result::Illegal;

      total_player_money_[player_index] -= safe_cost;
      dealer_money_ += safe_cost;
      insurance_bet_[player_index] = safe_cost;

      return Result::Ok;
    }

  return Result::Illegal;
  
}

void JTable::FillDeck(){

  for(int i = 0; i < rules_.NumberOfDecks(); i++){

    for(int j = 0; j < kSuitNum; j++){

      for(int k = 0; k < kValueNum; k++){

        Card tmp;
        tmp.value_ = static_cast<Value>(k);
        tmp.suit_ = static_cast<Suit>(j);
        deck_.push_back(tmp);

      }
    }
  }
}

void JTable::ShuffleDeck(){

    std::random_device seed;
    std::mt19937 rand(seed());

    std::shuffle(deck_.begin(), deck_.end(), rand);
}

int JTable::GetCardValue(Card card){
  Value value = card.value_;
  

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

JTable::HandInfo JTable::HandData(const Hand& hand){
  HandInfo info{};
  std::vector<Value> values;

  for (const Card& card : hand)
  {
    values.push_back(card.value_);
    info.total += GetCardValue(card);
  }
  
  if(values[0] == values[1]) info.is_pair = true;
  if((values[0] == Value::ACE || values[1] == Value::ACE)
     && info.total > 21){
      info.total -= 10;
      info.is_soft = false;
     } else info.is_soft = true;

  return info;
}

JTable::Result JTable::ApplyPlayerAction(int player_index,int hand_index,Action action){
  Hand checked_hand = GetHand(player_index, hand_index);

  if(action == Action::Stand)return Result::Ok;
    
  

  if(action == Action::Hit){
    DealCard(player_index, hand_index);
    return Result::Ok;
  }

  if(action == Action::Double){

    player_bets_[player_index][hand_index] = GetPlayerCurrentBet(player_index, hand_index) * 2;
    return Result::Ok;
  }

  if(action == Action::Split){

    hands_[player_index][hand_index][0] = checked_hand[0];
    hands_[player_index][hand_index + 1][0] = checked_hand[1];
    player_bets_[player_index][hand_index + 1] = player_bets_[player_index][hand_index];
    return Result::Ok;
  }
   
}


void JTable::StartRound() {

  if(dealer_hand_.size() > 0){

    dealer_hand_.clear();
  }

  FillDeck();

  ShuffleDeck();

  Card c = deck_.back();
  dealer_hand_.push_back(c);
  deck_.pop_back();
  
}




JTable::RoundEndInfo JTable::FinishRound(){

  RoundEndInfo info;
  return info;
}

void JTable::CleanTable(){

  for(int i = 0; i < num_players_; i++){
    hands_[i].clear();
    player_bets_[i].clear();
    insurance_bet_.clear();
    
  }
}