#include "game.h"
#include "jplayer.h"    
#include "jparcheesi.h" 
#include <windows.h>

int main() {

  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  JParcheesi board;

  
  JPlayer p0(0); 
  JPlayer p1(1); 
  JPlayer p2(2); 
  JPlayer p3(3); 

  
  const IPlayer* players[4] = { &p0, &p1, &p2, &p3 };

  
  Game game(board, players);

  
  while (game.IsGameOver() == IParcheesi::Color::None) {
    game.PlayTurn();
  }

  return 0;
}
