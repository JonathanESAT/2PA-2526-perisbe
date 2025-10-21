#include "blackjack.h"

Blackjack::Blackjack(Deck deck, Player player, Crupier crupier)
    :deck_{deck}
    ,player_{player}
    ,crupier_{crupier} {

}

Outcome ResolveOutcome(const Hand& player, const Hand& dealer){

    if(HandIsBlackjack(player) == true && HandIsBlackjack(dealer) == false) return kWin;

    if(HandIsBlackjack(player) == false && HandIsBlackjack(dealer) == true) return kLose;

    if(HandIsBlackjack(player) == true && HandIsBlackjack(dealer) == true) return kPush;

    if(HandIsBust(player)) return kLose;

    if(HandIsBust(dealer)) return kWin;

    int pv = HandBestValue(player);

    int dv = HandBestValue(dealer);

    if(pv > dv) return kWin;

    if(pv < dv) return kLose;

    if(pv == dv) return kPush;

}


float Payout(float bet, bool player_has_blackjack, Outcome o){

    if(o == kLose) return -bet;

    if(o == kPush) return 0;

    if(o == kWin){

        if(player_has_blackjack) 
        
            return bet * 3/2;

        else 

            return bet;
    }

    return 0.0f;
}

float PlayRoundWith(Deck& deck, Player& player, Crupier& crupier, float base_bet) {

  if (deck.size - deck.top < 52) {
    DeckShuffle(deck);
  }


  HandInit(player.hands[0]);
  HandInit(crupier.hand);
  player.hand_count = 1;

  float bet = base_bet;
  Card c;

 
  DeckDraw(deck, c); HandAddCard(player.hands[0], c);
  DeckDraw(deck, c); HandAddCard(crupier.hand,    c);
  DeckDraw(deck, c); HandAddCard(player.hands[0], c);
  DeckDraw(deck, c); HandAddCard(crupier.hand,    c);


  bool pBJ = HandIsBlackjack(player.hands[0]);
  bool dBJ = HandIsBlackjack(crupier.hand);
  if (pBJ || dBJ) {
    Outcome o = ResolveOutcome(player.hands[0], crupier.hand);
    float delta = Payout(bet, pBJ, o);
    player.balance += delta;
    return delta;
  }

 
  while (HandBestValue(player.hands[0]) < 17) {
    if (!DeckDraw(deck, c)) break;
    HandAddCard(player.hands[0], c);
    if (HandIsBust(player.hands[0])) {
      Outcome o = ResolveOutcome(player.hands[0], crupier.hand);
      float delta = Payout(bet, false, o); 
      player.balance += delta;
      return delta;
    }
  }


  DealerPlay(deck, crupier.hand);

  
  Outcome o = ResolveOutcome(player.hands[0], crupier.hand);
  float delta = Payout(bet, false, o);
  player.balance += delta;
  return delta;
}



float PlayRound(Blackjack& g) {
 
  if (g.deck_.size - g.deck_.top < 52) {
    DeckShuffle(g.deck_);
  }

 
  HandInit(g.player_.hands[0]);
  HandInit(g.crupier_.hand);
  g.player_.hand_count = 1;

  
  float bet = g.base_bet;


  Card c;
  DeckDraw(g.deck_, c); HandAddCard(g.player_.hands[0], c);
  DeckDraw(g.deck_, c); HandAddCard(g.crupier_.hand,    c);
  DeckDraw(g.deck_, c); HandAddCard(g.player_.hands[0], c);
  DeckDraw(g.deck_, c); HandAddCard(g.crupier_.hand,    c);


  bool pBJ = HandIsBlackjack(g.player_.hands[0]);
  bool dBJ = HandIsBlackjack(g.crupier_.hand);
  if (pBJ || dBJ) {
    Outcome o = ResolveOutcome(g.player_.hands[0], g.crupier_.hand);
    float delta = Payout(bet, pBJ, o);
    g.player_.balance += delta;
    return delta;
  }

  
  while (HandBestValue(g.player_.hands[0]) < 17) {
    if (!DeckDraw(g.deck_, c)) break;
    HandAddCard(g.player_.hands[0], c);
    if (HandIsBust(g.player_.hands[0])) {
      Outcome o = ResolveOutcome(g.player_.hands[0], g.crupier_.hand);
      float delta = Payout(bet, false, o);
      g.player_.balance += delta;
      return delta;
    }
  }

 
  DealerPlay(g.deck_, g.crupier_.hand);

  
  Outcome o = ResolveOutcome(g.player_.hands[0], g.crupier_.hand);
  float delta = Payout(bet, false, o);
  g.player_.balance += delta;
  return delta;
}