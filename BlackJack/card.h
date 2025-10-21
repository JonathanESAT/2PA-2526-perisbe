#ifndef CARD_H
#define CARD_H

enum Suit {
    kHearts = 0,
    kDiamonts,
    kClubs,
    kSpades
};

enum Rank {
    kR2 = 2,
    kR3,
    kR4,
    kR5,
    kR6,
    kR7,
    kR8,
    kR9,
    kR10,
    kJack,
    kQueen,
    kKing,
    kAce,
    kEnd
};


struct Card{
    Suit suit_;
    Rank rank_;
    Card() : suit_(kHearts), rank_(kR2) {}
};

int CardBaseValue(const Card& c);


#endif