#include "game.h"


class JPlayer : public IPlayer{

  private:

    int my_index_;

  public:

    JPlayer(int index): my_index_(index) {}

    int DecideMove(const IParcheesi& parcheesi, int dice_roll) const{

      int best_piece = -1;
      int best_score = -1;

      for(int piece = 0; piece < IParcheesi::pieces_per_player; piece++){

        IParcheesi* tmp = parcheesi.Clone();

        IParcheesi::Movement result = tmp->ApplyMovement(piece, my_index_, dice_roll);

        int score = 0;

        if(result == IParcheesi::Movement::ReachExit) {
          score = 4;

        }else if(result == IParcheesi::Movement::Eat) {
          score = 3;

        }else if(result == IParcheesi::Movement::Normal) {

          score = 2;

        }else{

          score = 0;

        }

        if(score > best_score) {

          best_score = score;
          best_piece = piece;
        }

        delete tmp;

      }


      return best_piece;

   

    }
};