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