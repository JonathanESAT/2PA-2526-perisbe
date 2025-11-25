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

    const int safePoint[kSafePoints] = { 5, 12, 17, 22, 29, 34, 39, 46, 51, 56, 63, 68 };
    const int startPoint[kMaxPlayers] = { 5, 22, 39, 56 };
    const int finishPoint[kMaxPlayers] = { 68, 17, 34, 51 };

    int pos_[kNumPlayers * kPiecesPerPlayer];

    int FirstFinalBox(int player_index) const {
        return 69 + 8 * (player_index % kMaxPlayers);
    }

    int GoalBox(int player_index) const {
        return FirstFinalBox(player_index) + 7;
    }

    int IsMyFinalPos(int player_index, int p) const {
        int a = FirstFinalBox(player_index);
        int b = GoalBox(player_index);
        if (p >= a && p <= b) return 1;
        return 0;
    }

    int NextBoxBoard(int box) const {
        int b = box + 1;
        if (b > kBoxNum) b = 1;
        return b;
    }

    int IsBridge(int box) const {
        int c = 0;
        for (int i = 0; i < kNumPlayers * kPiecesPerPlayer; ++i) {
            if (pos_[i] == box) {
                ++c;
                if (c >= 2) return 1;
            }
        }
        return 0;
    }

    int CountAllOnBox(int box) const {
        int c = 0;
        for (int i = 0; i < kNumPlayers * kPiecesPerPlayer; ++i) {
            if (pos_[i] == box) ++c;
        }
        return c;
    }

    int CountMineOnBox(int box, int player_index) const {
        int base = player_index * kPiecesPerPlayer;
        int c = 0;
        for (int i = 0; i < kPiecesPerPlayer; ++i) {
            if (pos_[base + i] == box) ++c;
        }
        return c;
    }

    int StepForward(int player_index, int from) const {
        if (IsMyFinalPos(player_index, from)) {
            int g = GoalBox(player_index);
            if (from < g) return from + 1;
            return g;
        }
        else {
            int next = NextBoxBoard(from);
            if (next == ExitBox(player_index)) return FirstFinalBox(player_index);
            return next;
        }
    }

    int TryAdvanceWithFinalRules(int player_index, int from, int steps, int* out_valid) const {
        int cur = from;
        int remaining = steps;
        while (remaining > 0) {
            int nxt = StepForward(player_index, cur);
            if (!IsMyFinalPos(player_index, nxt)) {
                if (IsBridge(nxt)) {
                    if (out_valid) *out_valid = 1;
                    return cur;
                }
                cur = nxt;
                remaining -= 1;
            }
            else {
                int tempCur = cur;
                int tempRem = remaining;
                int ok = 1;
                while (tempRem > 0) {
                    int tempNext;
                    if (IsMyFinalPos(player_index, tempCur)) {
                        int g = GoalBox(player_index);
                        if (tempCur < g) tempNext = tempCur + 1;
                        else tempNext = g;
                    }
                    else {
                        tempNext = StepForward(player_index, tempCur);
                    }
                    int g2 = GoalBox(player_index);
                    if (tempNext > g2) tempNext = g2;
                    if (tempNext == g2 && tempRem > 1) {
                        ok = 0;
                        break;
                    }
                    if (CountAllOnBox(tempNext) > 0) {
                        if (tempNext == g2) {
                            int all = CountAllOnBox(tempNext);
                            int mine = CountMineOnBox(tempNext, player_index);
                            if (mine == all) {
                            }
                            else {
                                ok = 0;
                                break;
                            }
                        }
                        else {
                            ok = 0;
                            break;
                        }
                    }
                    tempCur = tempNext;
                    tempRem -= 1;
                }
                if (!ok) {
                    if (out_valid) *out_valid = 0;
                    return from;
                }
                else {
                    if (out_valid) *out_valid = 1;
                    return tempCur;
                }
            }
        }
        if (out_valid) *out_valid = 1;
        return cur;
    }

    void ChainEatBonus20(int player_index, int global_index) {
        int cur = pos_[global_index];
        for (int chain = 0; chain < 16; ++chain) {
            int ok = 0;
            int dest = TryAdvanceWithFinalRules(player_index, cur, 20, &ok);
            if (!ok) {
                pos_[global_index] = cur;
                return;
            }
            if (IsMyFinalPos(player_index, dest)) {
                pos_[global_index] = dest;
                return;
            }
            int total_on_dest = CountAllOnBox(dest);
            int mine_on_dest = CountMineOnBox(dest, player_index);
            int safe_dest = IsBoxSafe(dest);
            if (total_on_dest == 0) {
                cur = dest;
                pos_[global_index] = cur;
                return;
            }
            if (total_on_dest == 1 && mine_on_dest == 1) {
                cur = dest;
                pos_[global_index] = cur;
                return;
            }
            if (total_on_dest == 1 && mine_on_dest == 0) {
                if (safe_dest) {
                    pos_[global_index] = cur;
                    return;
                }
                else {
                    for (int i = 0; i < kNumPlayers * kPiecesPerPlayer; ++i) {
                        if (pos_[i] == dest) {
                            int enemy_player = i / kPiecesPerPlayer;
                            if (enemy_player != player_index) {
                                int enemy_piece = i % kPiecesPerPlayer;
                                SendPieceHome(enemy_piece, enemy_player);
                                break;
                            }
                        }
                    }
                    cur = dest;
                    pos_[global_index] = cur;
                    continue;
                }
            }
            if (total_on_dest >= 2) {
                pos_[global_index] = cur;
                return;
            }
            cur = dest;
            pos_[global_index] = cur;
            return;
        }
        pos_[global_index] = cur;
    }

public:

    JParcheesi() {
        for (int i = 0; i < kNumPlayers * kPiecesPerPlayer; i++) {
            pos_[i] = 0;
        }
    }

    JParcheesi* Clone() const override {
        return new JParcheesi{ *this };
    }

    int EntryBox(int player_index) const {
        return startPoint[player_index % kMaxPlayers];
    }

    int ExitBox(int player_index) const {
        return finishPoint[player_index % kMaxPlayers];
    }

    int PiecesAtHome(int player_index) const {
        int counter = 0;
        int base = player_index * kPiecesPerPlayer;
        for (int i = 0; i < kPiecesPerPlayer; i++) {
            if (pos_[base + i] == 0) counter++;
        }
        return counter;
    }

    int PiecesAtEnd(int player_index) const {
        int counter = 0;
        int base = player_index * kPiecesPerPlayer;
        int goal = GoalBox(player_index);
        for (int i = 0; i < kPiecesPerPlayer; i++) {
            if (pos_[base + i] == goal) counter++;
        }
        return counter;
    }

    bool IsBoxSafe(int box_index) const {
        if (box_index < 1 || box_index > kBoxNum) return false;
        for (int i = 0; i < kSafePoints; i++) {
            if (safePoint[i] == box_index) return true;
        }
        return false;
    }

    Color ColorofPiece(int box_index, int piece_index) const {
        if (box_index < 1 || box_index > kBoxNum) return Color::None;
        if (piece_index < 0 || piece_index > 1) return Color::None;
        int occ_player[2] = { -1, -1 };
        int found = 0;
        for (int i = 0; i < kNumPlayers * kPiecesPerPlayer; i++) {
            if (pos_[i] == box_index) {
                if (found < 2) {
                    int pl = i / kPiecesPerPlayer;
                    occ_player[found] = pl;
                    found++;
                    if (found == 2) break;
                }
            }
        }
        if (piece_index >= found) return Color::None;
        int pl = occ_player[piece_index];
        switch (pl) {
        case 0: return Color::Yellow;
        case 1: return Color::Blue;
        case 2: return Color::Red;
        case 3: return Color::Green;
        default: return Color::None;
        }
    }

    int GlobalIndex(int player_index, int piece_index) const {
        return player_index * kPiecesPerPlayer + piece_index;
    }

    int CountPiecesOnBox(int box) {
        int counter = 0;
        for (int i = 0; i < kNumPlayers * kPiecesPerPlayer; i++) {
            if (pos_[i] == box) counter++;
        }
        return counter;
    }

    int CountPiecesOnBoxPerPlayer(int box, int player_index) const {
        int counter = 0;
        int base = player_index * kPiecesPerPlayer;
        for (int i = 0; i < kPiecesPerPlayer; i++) {
            if (pos_[base + i] == box) counter++;
        }
        return counter;
    }

    void SendPieceHome(int piece_index, int player_index) override {
        int global = GlobalIndex(player_index, piece_index);
        pos_[global] = 0;
    }

    int PositionOfPiece(int player_index, int piece_index) const {
        int global = GlobalIndex(player_index, piece_index);
        return pos_[global];
    }

    virtual Movement ApplyMovement(int piece_index, int player_index, int count) override {

        int global_index = GlobalIndex(player_index, piece_index);

        int current_pos = pos_[global_index];

        if (current_pos == 0) {

            if (count != 5) return Movement::NoMoves;

            int start_box = EntryBox(player_index);

            if (CountPiecesOnBox(start_box) >= 2) return Movement::NoMoves;

            int is_safe = IsBoxSafe(start_box);

            int my_on_start = CountPiecesOnBoxPerPlayer(start_box, player_index);

            int total_on_start = CountPiecesOnBox(start_box);

            if (total_on_start == 1 && my_on_start == 0) {

                if (is_safe) return Movement::NoMoves;

                for (int i = 0; i < kNumPlayers * kPiecesPerPlayer; i++) {
                    if (pos_[i] == start_box) {
                        int enemy_player = i / kPiecesPerPlayer;
                        if (enemy_player != player_index) {
                            int enemy_piece = i % kPiecesPerPlayer;
                            SendPieceHome(enemy_piece, enemy_player);
                            break;
                        }
                    }
                }

                pos_[global_index] = start_box;

                ChainEatBonus20(player_index, global_index);

                return Movement::Eat;
            }

            pos_[global_index] = start_box;

            return Movement::Normal;
        }

        int ok = 0;

        int destination = TryAdvanceWithFinalRules(player_index, current_pos, count, &ok);

        if (!ok) return Movement::NoMoves;

        if (destination == GoalBox(player_index)) {

            pos_[global_index] = destination;

            return Movement::ReachExit;
        }

        if (IsMyFinalPos(player_index, destination)) {

            pos_[global_index] = destination;

            return Movement::Normal;
        }

        int total_on_dest = CountAllOnBox(destination);

        int mine_on_dest = CountMineOnBox(destination, player_index);

        int safe_dest = IsBoxSafe(destination);

        if (total_on_dest == 0) {

            pos_[global_index] = destination;

            return Movement::Normal;
        }

        if (total_on_dest == 1 && mine_on_dest == 1) {

            pos_[global_index] = destination;

            return Movement::Normal;
        }

        if (total_on_dest == 1 && mine_on_dest == 0) {

            if (safe_dest) return Movement::NoMoves;

            for (int i = 0; i < kNumPlayers * kPiecesPerPlayer; i++) {
                if (pos_[i] == destination) {
                    int enemy_player = i / kPiecesPerPlayer;
                    if (enemy_player != player_index) {
                        int enemy_piece = i % kPiecesPerPlayer;
                        SendPieceHome(enemy_piece, enemy_player);
                        break;
                    }
                }
            }

            pos_[global_index] = destination;

            ChainEatBonus20(player_index, global_index);

            return Movement::Eat;
        }

        if (total_on_dest >= 2) return Movement::NoMoves;

        return Movement::NoMoves;
    }
};

#endif
