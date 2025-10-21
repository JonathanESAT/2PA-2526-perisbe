#include "crupier.h"
#include "card.h"


void DealerPlay(Deck& deck, Hand& dealer){

    if(HandIsBlackjack(dealer)){
        dealer.finished = true;
        return;
    }

    while(true){

        int total = HandBestValue(dealer);
        bool soft = HandIsSoft(dealer);

        if(total > 21){

            dealer.finished = true;
            return;
        }

        if(total < 17){
            
            Card c;
            if(!DeckDraw(deck, c)) return;
            HandAddCard(dealer, c);
            continue;
        }

        if (total == 17) {
                    if (soft && kHitSoft17) {
                        
                        Card c;
                        if (!DeckDraw(deck, c)) return;
                        HandAddCard(dealer, c);
                        continue; 

                    } else {
                        dealer.finished = true; 
                        break;                   
                    }
                }

              
                dealer.finished = true;
                break;
            }
}