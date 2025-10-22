#include "parcheesi.h"
#include "piece.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


enum PieceColor {
  kPC_Yellow,
  kPC_Blue,
  kPC_Red,
  kPC_Green,
  kPC_None,
};

class IParcheesi {
  public:
    enum MovementType {
      kMT_Eat,
      kMT_End,
      kMT_Reach_Exit,
      kMT_Normal,
      kMT_No_Moves,
      kMT_Illegal_Pass,
      kMT_Illegal_Bridge,
      kMT_Illegal_Box_Full,
      kMT_Illegal_Past_End,
      kMT_Illegal_Entry_Blocked,
      kMT_Illegal_Piece_At_Home,
      kMT_Illegal_Must_Enter_Piece,
      kMT_Illegal_Must_Break_Bridge,
    };

    const static int board_size = 68;
    const static int exit_size = 8;
    const static int null_piece = -1;

    virtual int EntryBox(int player_index) const = 0;
    virtual int ExitBox(int player_index) const = 0;
    virtual int PiecesAtHome(int player_index) const = 0;
    virtual int PiecesAtEnd(int player_index) const = 0;
    virtual PieceColor ColorofPiece(int box_index, int piece_index) const = 0;
    virtual bool IsBoxSafe(int box_index) const = 0;

    virtual MovementType ApplyMovement(int piece_index, int count) = 0;
};


class MyParcheesi : public IParcheesi {

  public:

    static const int kNumPlayers = 4;
    static const int kPiecesPerPlayer = 4;
    static const int kMaxPlayers = 4;
    static const int kSafePoints = 12; 
    static const int kBoxNum = 68;


  private:

    const int safePoint[kSafePoints] = {5, 12, 17, 22, 29, 34, 39, 46, 51, 56, 63, 68};
    const int startPoint[kMaxPlayers] = {5, 22, 39, 56};
    const int finishPoint[kMaxPlayers] = {68, 17, 34, 51};

    int pos_[kNumPlayers * kPiecesPerPlayer];

  public:

  MyParcheesi() {

    for(int i = 0; i < kNumPlayers * kPiecesPerPlayer; i++){

      pos_[i] = 0;
    }
  }


  int EntryBox(int player_index) const{

    return startPoint[player_index % kMaxPlayers];
  }

  int ExitBox(int player_index) const {

    return finishPoint[player_index % kMaxPlayers];
  }

  int PiecesAtHome(int player_index) const {

    int counter = 0;
    int base = player_index * kPiecesPerPlayer;

    for(int i = 0; i < kPiecesPerPlayer - 1; i++){
      if(pos_[base + i] == 0) counter++;
    }
      
    return counter;
  }


  int PiecesAtEnd(int player_index) const {

    int counter = 0;
    int base = player_index * kPiecesPerPlayer;

    for(int i = 0; i < kPiecesPerPlayer; i++){
      if(pos_[base + i] == 76) counter++;
    }
      
    return counter;

  }


  bool IsBoxSafe(int box_index) const {

    if(box_index < 1 || box_index > kBoxNum) return false;

    for(int i = 0; i < kSafePoints; i++){

      if(safePoint[i] == box_index) return true;
    }

    return false;
  }


  PieceColor ColorofPiece(int box_index, int piece_index) const {

    if(box_index < 1 || box_index > kBoxNum) return kPC_None;

    if(piece_index < 0 || piece_index > 1) return kPC_None;

    int occ_player[2] = {-1, -1};

    int found = 0;

    for(int i = 0; i < kNumPlayers * kPiecesPerPlayer; i++){

      if(pos_[i] == box_index){

        if(found < 2){

          int pl = i / kPiecesPerPlayer;
          occ_player[found] = pl;
          found++;

          if (found == 2) break;
        }
      }
    }

    if(piece_index >= found) return kPC_None;
    
    int pl = occ_player[piece_index];

    switch (pl)
    {
    case 0:

    return kPC_Yellow;

    case 1:

    return kPC_Blue;

    case 2:

    return kPC_Red;

    case 3: 
    
    return kPC_Green;

    default:

    return kPC_None;
    }
  }


  MovementType ApplyMovement(int piece_index, int count) const {


  }
};





int DecideMovement(int player,int roll, const IParcheesi& board);

class Game {
  IParcheesi& p_;
  public:
    Game(IParcheesi& p) : p_{p} {}

    PlayTurn() {
      p_.ExitBox();
    }

    int Roll(){
      return (rand() % 6) + 1;
    };
    
    IsGameOver();
    ActivePlayer();

};

int main(){
  MyParcheesi myp;
  Game g{myp};

  while(g.IsGameOver() == kPC_None) {
    g.Turn();
  }
}

