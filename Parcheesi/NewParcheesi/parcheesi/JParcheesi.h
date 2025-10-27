#pragma once
#ifndef JPARCHEESI_H
#define JPARCHEESI_H

#include "iparcheesi.h"

class JParcheesi : public IParcheesi {
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

  JParcheesi() {

    for(int i = 0; i < kNumPlayers * kPiecesPerPlayer; i++){

      pos_[i] = 0;
    }
  }


  JParcheesi* JParcheesi::Clone() const {

    return new JParcheesi{*this};
    
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

      for(int i = 0; i < kPiecesPerPlayer ; i++){
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


  Color ColorofPiece(int box_index, int piece_index) const {

      if(box_index < 1 || box_index > kBoxNum) return Color::None;

      if(piece_index < 0 || piece_index > 1) return Color::None;

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

      if(piece_index >= found) return Color::None;
      
      int pl = occ_player[piece_index];

      switch (pl)
      {
      case 0:

      return Color::Yellow;

      case 1:

      return Color::Blue;

      case 2:

      return Color::Red;

      case 3: 
      
      return Color::Green;

      default:

      return Color::None;
      }
    }

  int GlobalIndex(int player_index, int piece_index) const{
      return player_index * kPiecesPerPlayer + piece_index;
    }

  int CountPiecesOnBox(int box){

      int counter = 0;

      for(int i = 0; i < kNumPlayers * kPiecesPerPlayer; i++){
          if(pos_[i] == box) counter++;
      }
      return counter;
    }


  int CountPiecesOnBoxPerPlayer(int box, int player_index) const {

      int counter = 0;

      int base = player_index * kPiecesPerPlayer;

      for(int i = 0; i < kPiecesPerPlayer; i++){

        if(pos_[base + i] == box) counter++;

      }

      return counter;
    }


  void SendPieceHome(int piece_index, int player_index) override {

      int global = GlobalIndex(player_index, piece_index);

      pos_[global] = 0;

    };


  int PositionOfPiece(int player_index, int piece_index) const {

      int global = GlobalIndex(player_index, piece_index);

      return pos_[global];

    };



  virtual Movement ApplyMovement(int piece_index, int player_index, int count) override {

    
    int global_index = GlobalIndex(player_index, piece_index);


    int current_pos = pos_[global_index];

    
    if (current_pos == 0) {

      
      if (count != 5) {

        return Movement::NoMoves;
      }

      int start_box = EntryBox(player_index);

      if (CountPiecesOnBox(start_box) >= 2) {

        return Movement::NoMoves;
      }

      bool is_safe = IsBoxSafe(start_box);

      int my_on_start = CountPiecesOnBoxPerPlayer(start_box, player_index);
    
      int total_on_start = CountPiecesOnBox(start_box);

      
      if (total_on_start == 1 && my_on_start == 0) {
        

        if (is_safe) {
          
          return Movement::NoMoves;

        } else {

          for(int i = 0; i < kNumPlayers * kPiecesPerPlayer; i++){

            if(pos_[i] == start_box){

              int enemy_player = i / kPiecesPerPlayer;
              int enemy_piece = i % kPiecesPerPlayer;

              SendPieceHome(enemy_piece, enemy_player);
              break;
            }
          }

          pos_[global_index] = start_box;
          return Movement::Eat;
        }
      }

      pos_[global_index] = start_box;
      return Movement::Normal;
    }

    if(current_pos != 0){

      int destination = current_pos + count;

      if(destination > kBoxNum){

        destination -= kBoxNum;
      }

      int step_pos = current_pos;

      for(int i = 1; i <= count; i++){

        step_pos = step_pos + 1;

        if(step_pos > kBoxNum){

          step_pos -= kBoxNum;
        }

        if(CountPiecesOnBox(step_pos) >= 2){

          return Movement::NoMoves;
        }
      }

      if(destination == ExitBox(player_index)){

        pos_[global_index] = destination;

        return Movement::ReachExit;
      }
      
      int total_on_dest = CountPiecesOnBox(destination);
      int mine_on_dest = CountPiecesOnBoxPerPlayer(destination, player_index);
      bool safe_dest = IsBoxSafe(destination);


      if(total_on_dest == 0){

        pos_[global_index] = destination;

        return Movement::Normal;
      }


       if(total_on_dest == 1 && mine_on_dest == 1){

        pos_[global_index] = destination;

        return Movement::Normal;
      }

       if(total_on_dest == 1 && mine_on_dest == 0){

        if(safe_dest){

          return Movement::NoMoves;

        }else{

          for(int i = 0; i < kNumPlayers * kPiecesPerPlayer; i++){

            if(pos_[i] == destination) {

              int enemy_player = i / kPiecesPerPlayer;
              int enemy_piece = i % kPiecesPerPlayer;

              SendPieceHome(enemy_piece, enemy_player);
              break;
            }
          }

          pos_[global_index] = destination;

          return Movement::Eat;
        }

        
      }


       if(total_on_dest >= 2 ){

        return Movement::NoMoves;
      }

      return Movement::NoMoves;
      
    }

    return Movement::NoMoves;
  }

};

#endif 