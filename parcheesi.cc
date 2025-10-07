
//Parchis 26/09/2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "parcheesi.h"

const int Parcheesi::safePoint[Parcheesi::kSafePoints] = {5, 12, 17, 22, 29, 34, 39, 46, 51, 56, 63, 68};
const int Parcheesi::startPoint[Parcheesi::kMaxPlayers] = {5, 22, 39, 56};
const int Parcheesi::finishPoint[Parcheesi::kMaxPlayers] = {68, 17, 34, 51};

int RollDice(){
  return (rand() % 6) + 1;
}

Parcheesi::Parcheesi(int num_players)
  : num_players_{num_players}
  , current_turn_{0}
  , repeated_sixes_{0}
  , current_player_{kColor_Yellow}
  , player_{kColor_Yellow,kColor_Blue,kColor_Red,kColor_Green} {

}

int Parcheesi::CountPiecesOnBox(int box){
  int occupants = 0;
  for(int i = 0; i < num_players_; i++){
    occupants += player_[i].CountPiecesOnBox(box);
  }
  return occupants;
}

void Parcheesi::NextPlayer(){
  int num_player = static_cast<int>(current_player_);
  num_player = (num_player + 1) % num_players_;
  current_player_ = static_cast<Colors>(num_player);
}

void Parcheesi::PlayTurn(){
  int dice_num;
  dice_num = RollDice();
  for(int i = 0; i < Player::kPieceNum; i++){
    if(dice_num == 5 && player_[current_player_].piece_[i].position == 0 &&
        CountPiecesOnBox(startPoint[current_player_]) < 2){
      player_[current_player_].piece_[i].position = startPoint[current_player_];
      NextPlayer();
      return;
    }
  }
}

MovementOutput Parcheesi::ApplyMovement(int pieceIndex, int mov_num){

  if(pieceIndex < 0 || pieceIndex >= Player::kPieceNum) return kMovementOutput_NoMove;

  Player& current_player = player_[static_cast<int>(current_player_)];
  Piece& piece = current_player.piece_[pieceIndex];
  int actual_piece_position = piece.position;

  if(actual_piece_position == 0) return kMovementOutput_NoMove;


  if(actual_piece_position >= 69 && actual_piece_position <= 76){
    int destination = actual_piece_position + mov_num;
    if(destination > 76) return kMovementOutput_NoMove;
    piece.position = destination;
    if(destination == 76) return kMovementOutput_End;
    return kMovementOutput_BasicMove;
  }

  if(actual_piece_position >= 1 && actual_piece_position <= Parcheesi::kBoxNum){

    const int finish_point = Parcheesi::finishPoint[static_cast<int>(current_player_)];

    int steps_to_finish = (finish_point - actual_piece_position + Parcheesi::kBoxNum) % Parcheesi::kBoxNum;

    if(actual_piece_position == finish_point){

      int final_destination = Parcheesi::kBoxNum + mov_num;
      if(final_destination > 76) return kMovementOutput_NoMove;
      piece.position = final_destination;
      if(final_destination == 76) return kMovementOutput_End;
      return kMovementOutput_BasicMove;
    }

    if(mov_num < steps_to_finish) {
      int base = (actual_piece_position  - 1 + mov_num) % Parcheesi::kBoxNum;
      int destination = base + 1;
      piece.position = destination;
      return kMovementOutput_BasicMove;
    }


    if(mov_num == steps_to_finish){
      piece.position = finish_point;
      return kMovementOutput_BasicMove;
    }

    int base = (actual_piece_position - 1 + mov_num) % Parcheesi::kBoxNum;
    int destination = base + 1;
    piece.position = destination;
    return kMovementOutput_BasicMove;




  }

  return kMovementOutput_NoMove;

}

