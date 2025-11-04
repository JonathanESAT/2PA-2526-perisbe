#include "jplayer.h"


int JPlayer::DecideMove(const IParcheesi& parcheesi,int player_index, int dice_roll) const {
    int best_piece = -1;
    int best_score = -1;

    for (int piece = 0; piece < IParcheesi::pieces_per_player; piece++) {
        IParcheesi* tmp = parcheesi.Clone();
        IParcheesi::Movement result = tmp->ApplyMovement(piece, player_index, dice_roll);

        int score = 0;

        if (result == IParcheesi::Movement::ReachExit) {
            score = 4;
        }
        else if (result == IParcheesi::Movement::Eat) {
            score = 3;
        }
        else if (result == IParcheesi::Movement::Normal) {
            score = 2;
        }
        else {
            score = 0;
        }

        if (score > best_score) {
            best_score = score;
            best_piece = piece;
        }

        delete tmp;
    }

    return best_piece;
}
