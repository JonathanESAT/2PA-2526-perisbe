#include "jplayer.h"
#include <cstdlib>

int JPlayer::DecideMove(const IParcheesi& parcheesi, int player_index, int dice_roll) const {
  int best_piece = -1;
  int best_score = -1000000000;

  int before_home = parcheesi.PiecesAtHome(player_index);
  int before_end  = parcheesi.PiecesAtEnd(player_index);

  for (int piece = 0; piece < IParcheesi::pieces_per_player; ++piece) {
    IParcheesi* tmp = parcheesi.Clone();
    IParcheesi::Movement result = tmp->ApplyMovement(piece, player_index, dice_roll);

    int after_home = tmp->PiecesAtHome(player_index);
    int after_end  = tmp->PiecesAtEnd(player_index);

    int score = 0;

    if (result == IParcheesi::Movement::NoMoves) {
      delete tmp;
      continue; // skip invalid moves
    }

    // Base preference for making a valid move
    score += 50;

    // Strongly prefer eating an opponent
    if (result == IParcheesi::Movement::Eat) {
      score += 5000;
      if (after_end > before_end) score += 500;
      if (before_home > after_home) score += 300;
    }

    // Prefer reaching the exit (goal)
    else if (result == IParcheesi::Movement::ReachExit) {
      score += 4000;
    }

    // Prefer getting pieces out of home
    if (before_home > after_home) {
      score += 1200;
    }

    // Prefer moves that increase pieces at end
    if (after_end > before_end) {
      score += 1000;
    }

    // Small bonus for any normal progress
    if (result == IParcheesi::Movement::Normal) score += 200;

   
    if (score > best_score) {
      best_score = score;
      best_piece = piece;
    } else if (score == best_score) {
      if (std::rand() % 2 == 0) best_piece = piece;
    }

    delete tmp;
  }

  return best_piece;
}

