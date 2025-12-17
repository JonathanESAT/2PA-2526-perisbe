#include "JTable.h"
#include "Rules.h"
#include <cassert>
#include <algorithm>
#include <random>

// Constructor - initialize table with players
JTable::JTable(unsigned int num_players, const BaseRules& rules)
  : hands_(),
    player_bets_(),
    total_player_money_(),
    insurance_bet_(),
    initial_bet_(),
    dealer_money_(0),
    dealer_hand_(),
    deck_(),
    rules_(rules),
    num_players_(0) {

  // Limit players to max allowed
  if (num_players > kMaxPlayers) {
    num_players_ = kMaxPlayers;
  } else {
    num_players_ = num_players;
  }

  if (num_players_ == 0) {
    return;
  }

  // Initialize arrays for all players
  hands_.resize(num_players_);
  player_bets_.resize(num_players_);
  total_player_money_.resize(num_players_);
  initial_bet_.resize(num_players_);
  insurance_bet_.resize(num_players_);

  // Set initial money for dealer
  dealer_money_ = rules_.InitialDealerMoney();

  // Give each player their starting money
  for (unsigned int i = 0; i < num_players_; ++i) {
    hands_[i].clear();
    hands_[i].push_back(Hand{});

    player_bets_[i].clear();
    player_bets_[i].push_back(0);

    total_player_money_[i] = rules_.InitialPlayerMoney();

    initial_bet_[i]   = 0;
    insurance_bet_[i] = 0;
  }

  dealer_hand_.clear();
  deck_.clear();
}

JTable::Hand JTable::GetHand(int player_index, int hand_index) const {
  return hands_[player_index][hand_index];
}

int JTable::GetNumberOfHands(int player_index) const {
  return static_cast<int>(hands_[player_index].size());
}

int JTable::GetPlayerCurrentBet(int player_index,int hand_index) const {
  return player_bets_[player_index][hand_index];
}

int JTable::GetPlayerMoney(int player_index) const {
  return total_player_money_[player_index];
}

int JTable::DealerMoney() const {
  return dealer_money_;
}

JTable::Card JTable::GetDealerCard() const {
  if (dealer_hand_.empty()) {
    return {Value::end, Suit::end};
  }
  return dealer_hand_[0];
}

// Deal one card from deck to player hand
void JTable::DealCard(int player_index, int hand_index) {
  assert(player_index >= 0 && player_index < static_cast<int>(num_players_));
  assert(hand_index >= 0 && hand_index < static_cast<int>(hands_[player_index].size()));
  assert(!deck_.empty());

  Card dealed_card = deck_.back();
  hands_[player_index][hand_index].push_back(dealed_card);
  deck_.pop_back();
}

// Place initial bet for a player
JTable::Result JTable::PlayInitialBet(int player_index, int money) {
  // Check for cheating - invalid player index
  if (player_index < 0 || player_index >= static_cast<int>(num_players_)) {
    return Result::Illegal;
  }

  // Check for cheating - invalid bet amount
  if (money <= 0) {
    return Result::Illegal;
  }

  // Check for cheating - bet below minimum
  if (money < rules_.MinimumInitialBet()) {
    return Result::Illegal;
  }

  // Check for cheating - bet above maximum
  if (money > rules_.MaximumInitialBet()) {
    return Result::Illegal;
  }

  // Check for cheating - betting more money than they have
  if (money > total_player_money_[player_index]) {
    return Result::Illegal;
  }

  // Check for cheating - trying to bet twice
  if (player_bets_[player_index][0] != 0) {
    return Result::Illegal;
  }

  // Take money from player and give to dealer
  total_player_money_[player_index] -= money;
  dealer_money_                     += money;

  player_bets_[player_index][0] = money;
  initial_bet_[player_index]    = money;

  return Result::Ok;
}

int JTable::GetPlayerInitialBet(int player_index) const {
  return initial_bet_[player_index];
}

JTable::Result JTable::PlaySafeBet(int player_index) {
  // Check for cheating - invalid player index
  if (player_index < 0 || player_index >= static_cast<int>(num_players_)) {
    return Result::Illegal;
  }

  Card dealer_card = GetDealerCard();

  // Can only buy insurance if dealer shows ace
  if (dealer_card.value_ == Value::ACE) {

    int player_bet = GetPlayerInitialBet(player_index);
    // Check for cheating - no initial bet placed
    if (player_bet <= 0) return Result::Illegal;

    int safe_cost = player_bet / 2;
    if (safe_cost <= 0) return Result::Illegal;

    int player_money = GetPlayerMoney(player_index);
    // Check for cheating - not enough money for insurance
    if (player_money < safe_cost) return Result::Illegal;

    // Check for cheating - already bought insurance
    if (insurance_bet_[player_index] > 0) return Result::Illegal;

    total_player_money_[player_index] -= safe_cost;
    dealer_money_                     += safe_cost;
    insurance_bet_[player_index]       = safe_cost;

    return Result::Ok;
  }

  // Check for cheating - trying to buy insurance when dealer doesn't have ace
  return Result::Illegal;
}

int JTable::GetHandValue(const Hand& hand) {
  int sum = 0;
  int aces = 0;
  int win_point = rules_.GetWinPoint();

  for (const Card& c : hand) {
    sum += GetCardValue(c);
    if (c.value_ == Value::ACE) {
      ++aces;
    }
  }

  while (sum > win_point && aces > 0) {
    sum -= 10;
    --aces;
  }

  return sum;
}

// Create full deck with all cards
void JTable::FillDeck() {
  // Add cards for each deck
  for (int i = 0; i < rules_.NumberOfDecks(); ++i) {
    for (int j = 0; j < kSuitNum; ++j) {
      for (int k = 1; k < kValueNum; ++k) {
        Card tmp;
        tmp.value_ = static_cast<Value>(k);
        tmp.suit_  = static_cast<Suit>(j);
        deck_.push_back(tmp);
      }
    }
  }
}

// Shuffle the deck randomly
void JTable::ShuffleDeck() {
  std::random_device seed;
  std::mt19937 rand(seed());
  std::shuffle(deck_.begin(), deck_.end(), rand);
}

// Get value of a single card
int JTable::GetCardValue(Card card) {
  Value value = card.value_;

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

  assert(false);
  return 0;
}

JTable::HandInfo JTable::HandData(const Hand& hand) {
  HandInfo info{};
  std::vector<Value> values;

  for (const Card& card : hand) {
    values.push_back(card.value_);
    info.total += GetCardValue(card);
  }

  if (values.size() >= 2 && values[0] == values[1]) {
    info.is_pair = true;
  } else {
    info.is_pair = false;
  }

  if (values.size() >= 2 &&
      (values[0] == Value::ACE || values[1] == Value::ACE) &&
      info.total > 21) {
    info.total  -= 10;
    info.is_soft = false;
  } else if (!values.empty() &&
             (values[0] == Value::ACE ||
              (values.size() >= 2 && values[1] == Value::ACE))) {
    info.is_soft = true;
  } else {
    info.is_soft = false;
  }

  return info;
}

JTable::Result JTable::ApplyPlayerAction(int player_index, int hand_index, Action action) {
  // Check for cheating - invalid player index
  if (player_index < 0 || player_index >= static_cast<int>(num_players_)) {
    return Result::Illegal;
  }

  // Check for cheating - invalid hand index
  if (hand_index < 0 || hand_index >= static_cast<int>(hands_[player_index].size())) {
    return Result::Illegal;
  }

  Hand& hand = hands_[player_index][hand_index];

  switch (action) {
  case Action::Stand:
      return Result::Ok;

  case Action::Hit:
      // Check if deck is empty (shouldn't happen but check anyway)
      if (deck_.empty()) {
        return Result::Illegal;
      }
      DealCard(player_index, hand_index);
      return Result::Ok;

  case Action::Double: {
      int bet = GetPlayerCurrentBet(player_index, hand_index);

      // Check for cheating - no bet placed
      if (bet <= 0) {
        return Result::Illegal;
      }

      // Check for cheating - not enough money to double
      if (total_player_money_[player_index] < bet) {
        return Result::Illegal;
      }

      total_player_money_[player_index] -= bet;
      dealer_money_ += bet;

      player_bets_[player_index][hand_index] = bet * 2;

      // Check if deck is empty
      if (deck_.empty()) {
        return Result::Illegal;
      }
      DealCard(player_index, hand_index);
      return Result::Ok;
  }

  case Action::Split: {
      Hand& hand = hands_[player_index][hand_index];

      // Check for cheating - can only split with exactly 2 cards
      if (hand.size() != 2) {
        return Result::Illegal;
      }

      // Check for cheating - can only split pairs
      if (hand[0].value_ != hand[1].value_) {
        return Result::Illegal;
      }

      int bet = GetPlayerCurrentBet(player_index, hand_index);

      // Check for cheating - no bet placed
      if (bet <= 0) {
        return Result::Illegal;
      }

      // Check for cheating - not enough money to split
      if (total_player_money_[player_index] < bet) {
          return Result::Illegal;
      }

      Hand new_hand;
      new_hand.push_back(hand[1]);
      hand.resize(1);

      hands_[player_index].insert(
          hands_[player_index].begin() + hand_index + 1,
          new_hand);

      player_bets_[player_index].insert(
          player_bets_[player_index].begin() + hand_index + 1,
          bet);

      total_player_money_[player_index] -= bet;
      dealer_money_ += bet;

      // Check if deck has enough cards
      if (deck_.empty()) {
        return Result::Illegal;
      }
      DealCard(player_index, hand_index);

      if (deck_.empty()) {
        return Result::Illegal;
      }
      DealCard(player_index, hand_index + 1);

      return Result::Ok;
  }
  }

  return Result::Illegal;
}

// Prepare table for new round
void JTable::StartRound() {
  dealer_hand_.clear();
  deck_.clear();

  // Create and shuffle new deck
  FillDeck();
  ShuffleDeck();

  // Deal one card to dealer
  Card c = deck_.back();
  dealer_hand_.push_back(c);
  deck_.pop_back();
}

// Finish round and calculate winners
JTable::RoundEndInfo JTable::FinishRound() {
  RoundEndInfo info;

  int win_point = rules_.GetWinPoint();

  // Dealer draws cards until reaching stop value
  while (GetHandValue(dealer_hand_) < rules_.DealerStop() &&
         GetHandValue(dealer_hand_) <= win_point) {
    assert(!deck_.empty());
    Card c = deck_.back();
    deck_.pop_back();
    dealer_hand_.push_back(c);
  }

  int dealer_total = GetHandValue(dealer_hand_);
  bool dealer_bust = dealer_total > win_point;

  info.dealer_hand = dealer_hand_;

  info.winners.resize(num_players_);
  info.player_money_delta.resize(num_players_, 0);
  info.dealer_money_delta = 0;

  // Check each player's hands against dealer
  for (unsigned int p = 0; p < num_players_; ++p) {
    info.winners[p].resize(hands_[p].size(), false);

    for (unsigned int h = 0; h < hands_[p].size(); ++h) {
      int player_total = GetHandValue(hands_[p][h]);
      bool player_bust = player_total > win_point;
      int bet = player_bets_[p][h];

      bool player_wins = false;
      bool draw = false;

      // Determine if player wins, loses, or draws
      if (player_bust) {
        player_wins = false;
      } else if (dealer_bust) {
        player_wins = true;
      } else if (player_total > dealer_total) {
        player_wins = true;
      } else if (player_total < dealer_total) {
        player_wins = false;
      } else {
        draw = true;
      }

      info.winners[p][h] = player_wins;

      // Pay out winnings
      if (draw) {
        total_player_money_[p] += bet;
        dealer_money_ -= bet;
      } else if (player_wins) {
        total_player_money_[p] += 2 * bet;
        dealer_money_ -= 2 * bet;

        info.player_money_delta[p] += bet;
        info.dealer_money_delta -= bet;
      } else {
        info.player_money_delta[p] -= bet;
        info.dealer_money_delta += bet;
      }
    }
  }

  return info;
}

// Clean table for next round
void JTable::CleanTable() {
  // Reset all hands and bets
  for (unsigned int i = 0; i < num_players_; ++i) {
    hands_[i].clear();
    hands_[i].push_back(Hand{});

    player_bets_[i].clear();
    player_bets_[i].push_back(0);

    initial_bet_[i]   = 0;
    insurance_bet_[i] = 0;
  }

  dealer_hand_.clear();
  deck_.clear();
}


const BaseRules& JTable::GetRules() const {
  return rules_;
}
