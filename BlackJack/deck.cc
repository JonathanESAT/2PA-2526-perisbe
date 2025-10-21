#include "deck.h"
#include "stdlib.h"
#include "time.h"




void DeckInit(Deck& d, int num_decks){
    d.size = 0;
    d.top = 0;

    for(int i = 0; i < num_decks; i++){
        for(int j = 0; j < kNumSuits; j++){
            for(int k = 2; k < kNumRanks; k++){
                Suit suit = static_cast<Suit>(j);
                Rank rank = static_cast<Rank>(k);

                if(d.size < kMaxDeckCards){

                    d.cards[d.size].rank_ = rank;
                    d.cards[d.size].suit_ = suit;
                    d.size++;

                }else{

                    return;
                    
                }   
            }
        }
    }
}

void DeckShuffle(Deck& d){

    if(d.size <= 1){
        return;
    }

    for(int i = d.size - 1; i > 0; i--){

        int j = rand() % (i + 1);
        Card temp = d.cards[i];
        d.cards[i] = d.cards[j];
        d.cards[j] = temp;

    }

    d.top = 0;

}

bool DeckDraw(Deck& d, Card& out_card){

    if(d.top >= d.size){
        return false;
    }

    out_card = d.cards[d.top];
    ++d.top;

    return true;
}



