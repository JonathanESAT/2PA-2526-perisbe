#pragma once
#ifndef MOCK_PARCHEESI_H
#define MOCK_PARCHEESI_H

#include "iparcheesi.h"

class MockParcheesi : public IParcheesi {
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

  MockParcheesi() {

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

  virtual Movement ApplyMovement(int piece_index, int player_index, int count) override { 
    
    Player& turn_player = player_[player_index];
    Piece& turn_piece = turn_player.piece_[piece_index];

    if(turn_piece.position == 0){
      if(count != 5){
        return NoMoves;
      }else{
        if(CountPiecesOnBox(startPoint[player_index]) >= 2){
          return NoMoves;
        } else {
          turn_piece.position = startPoint[player_index];
        }
      }
    }
 
    if (count == 6)
    {
      Parcheesi::repeated_sixes_++;
      if (repeated_sixes_ == 3)
      {
        turn_piece.position = 0;
        return kMovementOutput_IllegalMove; 
      }
    }
    

    //check bridges
    for (int i = 1; i <= count; i++)
    {
      if(CountPiecesOnBox(turn_piece.position + i) >= 2) {
        return NoMoves;
      }
    }
    
    //check if enters final runway
    if(turn_piece.position + count == finishPoint[player_index]){
      return kMovementOutput_End;
    }

    if(turn_piece.position + count > kBoxNum){
      int full_cycle = turn_piece.position - kBoxNum;
      turn_piece.position = full_cycle;
    }
    
    bool is_safe = false;
    for (int i = 0; i < kSafePoints; i++)
    {
      if(safePoint[i] == turn_piece.position) is_safe = true;
    }
    
    bool did_eat = false;
    if(!is_safe){
      if(CountPiecesOnBox(turn_piece.position + count) == 1){
        for(int i = 0; i < num_players_; i++){
          if(i == static_cast<int>(player_index)) continue;

          if(player_[i].CountPiecesOnBox(turn_piece.position + count) == 1){
            for (int j = 0; j < Player::kPieceNum; j++)
            {
              if (player_[i].piece_[j].position == turn_piece.position + count)
              {
                player_[i].piece_[j].position = 0;
                did_eat = true;
              }
            }
          }
        }
      }
    }
    turn_piece.position += count;
    
    if (Parcheesi::repeated_sixes_ < 3 && Parcheesi::repeated_sixes_ > 0)
    {
      return kMovementOutput_RollAgain;
    }else{
      Parcheesi::repeated_sixes_ = 0;
    }
    
    if (did_eat)
    {
      return kMovementOutput_Eat;
    }

    return kMovementOutput_BasicMove;
  }
}


  void SendPieceHome(int piece_index) override {};


#endif // MOCK_PARCHEESI_H