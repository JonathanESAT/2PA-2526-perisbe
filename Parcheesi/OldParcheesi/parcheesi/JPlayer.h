#include "game.h"


class JPlayer : public IPlayer{

  IParcheesi::Color color_;

  int CountPiecesOnBox(int box);

};