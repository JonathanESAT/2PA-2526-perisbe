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

    JParcheesi();

    // Clonación
    JParcheesi* Clone() const override;

    // Métodos públicos principales
    int EntryBox(int player_index) const;
    int ExitBox(int player_index) const;
    int PiecesAtHome(int player_index) const;
    int PiecesAtEnd(int player_index) const;
    bool IsBoxSafe(int box_index) const;
    Color ColorofPiece(int box_index, int piece_index) const;
    int GlobalIndex(int player_index, int piece_index) const;
    int CountPiecesOnBox(int box);
    int CountPiecesOnBoxPerPlayer(int box, int player_index) const;
    void SendPieceHome(int piece_index, int player_index) override;
    int PositionOfPiece(int player_index, int piece_index) const;
    Movement ApplyMovement(int piece_index, int player_index, int count) override;

private:
    // Constantes
    const int safePoint[kSafePoints] = { 5, 12, 17, 22, 29, 34, 39, 46, 51, 56, 63, 68 };
    const int startPoint[kMaxPlayers] = { 5, 22, 39, 56 };
    const int finishPoint[kMaxPlayers] = { 68, 17, 34, 51 };

    // Estado del tablero
    int pos_[kNumPlayers * kPiecesPerPlayer];

    // Métodos privados de lógica interna
    int FirstFinalBox(int player_index) const;
    int GoalBox(int player_index) const;
    int IsMyFinalPos(int player_index, int p) const;
    int NextBoxBoard(int box) const;
    int IsBridge(int box) const;
    int CountAllOnBox(int box) const;
    int CountMineOnBox(int box, int player_index) const;
    int StepForward(int player_index, int from) const;
    int TryAdvanceWithFinalRules(int player_index, int from, int steps, int* out_valid) const;
    void ChainEatBonus20(int player_index, int global_index);
};

#endif // JPARCHEESI_H
