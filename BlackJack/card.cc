#include "card.h"

Card::Card(Suit suit, Rank rank)
    : suit_{suit}
    , rank_{rank} {

}

int CardBaseValue (const Card& c){

    switch (c.rank_)
    {
    case kR2:
        return 2;
    case kR3:
        return 3;
    case kR4:
        return 4;
    case kR5:
        return 5;
    case kR6:
        return 6;
    case kR7:
        return 7;
    case kR8:
        return 8;
    case kR9:
        return 9;
    case kR10:
        return 10;
    case kJack:
        return 10;
    case kQueen:
        return 10;
    case kKing:
        return 10;
    case kAce:
        return 11;
    }
};


