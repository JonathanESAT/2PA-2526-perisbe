#include "hand.h"
#include "card.h"
#include <stdlib.h>
#include <stdio.h>



void HandInit(Hand& h){

    h.count = 0;
    h.finished = false;
};

bool HandAddCard(Hand& h, const Card& c){

    if(h.count >= kMaxCardInHand){
        return false;
    }

    h.cards[h.count] = c;
    h.count++;
    return true;
}


int HandBestValue(const Hand& h){

    int total = 0;
    int num_ases = 0;

    for(int i = 0; i < h.count; i++){
        int v = CardBaseValue(h.cards[i]);
        total = total + v;

        if(h.cards[i].rank_ == kAce){
            num_ases++;
        }
    }

    while(total > 21 && num_ases > 0){
            total -= 10;
            num_ases--;
        }

    return total;

}

bool HandIsBlackjack(const Hand& h){

    if(h.count != 2){
        return false;
    }

    if(HandBestValue(h) != 21){
        return false;
    }

    const Card& c1 = h.cards[0];
    const Card& c2 = h.cards[1];

    if(c1.rank_ == kAce && CardBaseValue(c2) == 10 || c2.rank_ == kAce && CardBaseValue(c1) == 10){
        return true;
    }
    
    return false;
}

bool HandIsBust(const Hand& h){

    int total = HandBestValue(h);

    if(total > 21){
        
        return true;
    }

    return false;
}


bool HandIsSoft(const Hand& h){

    int total = 0;
    int num_ases = 0;

    for(int i = 0; i < h.count; i++){

        int v = CardBaseValue(h.cards[i]);
        total = total + v;

        if(h.cards[i].rank_ == kAce){
            num_ases++;
        }
    }


    while(total > 21 && num_ases > 0){

        total -= 10;
        num_ases--;
    }

    if(num_ases > 0){

        return true;
    }

    return false;
    
    
}
