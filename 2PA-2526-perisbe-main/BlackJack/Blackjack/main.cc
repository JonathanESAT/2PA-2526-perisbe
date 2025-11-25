#include <stdio.h>
#include "blackjack.h"

int main() {

  Deck deck; DeckInit(deck, 6); DeckShuffle(deck);   
  Crupier dealer{};

 
  Player table[kTableSeats];
  for (int i = 0; i < kTableSeats; ++i) {
    table[i].balance = 500.0f;   
    table[i].hand_count = 1;
    table[i].bet[0] = 10.0f;    
    HandInit(table[i].hands[0]);
  }

  const float base_bet = 10.0f;

  int round = 1;
  while (true) {
  
    int active = 0;
    for (int i = 0; i < kTableSeats; ++i) {
      if (table[i].balance >= base_bet) active++;
    }
    if (active <= 1) break; 

    printf("\n==== RONDA %d ====\n", round);

    
    for (int i = 0; i < kTableSeats; ++i) {
      if (table[i].balance < base_bet) continue; 

      float before = table[i].balance;
      float delta  = PlayRoundWith(deck, table[i], dealer, base_bet);
      float after  = table[i].balance;

      printf("Jugador %d: delta = %+0.2f | saldo: %0.2f -> %0.2f\n",
             i+1, delta, before, after);
    }

    
    printf("Estado tras la ronda %d:\n", round);
    int still = 0;
    int last_idx = -1;

    for (int i = 0; i < kTableSeats; ++i) {
        printf("  J%d: %0.2f ", i + 1, table[i].balance);
    
    if (table[i].balance < base_bet) {
        printf("(Fuera)\n");
        
    } else {
        printf("\n");
        still++;
        last_idx = i;
    }
    }


    
    if (still <= 1) break;
    round++;
  }

 
  int winner = -1;
  float best_balance = -1.0f;
  for (int i = 0; i < kTableSeats; ++i) {
    if (table[i].balance > best_balance) {
      best_balance = table[i].balance;
      winner = i;
    }
  }

  printf("\n=== FIN DEL TORNEO ===\n");
  for (int i = 0; i < kTableSeats; ++i) {
    printf("Jugador %d: saldo final = %0.2f\n", i+1, table[i].balance);
  }
  if (winner >= 0)
    printf("\nGanador: Jugador %d con %0.2f\n", winner+1, table[winner].balance);
  else
    printf("\nSin ganador (todos fuera)\n");

  return 0;
}
