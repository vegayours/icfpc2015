#include "board.h"

#include <cassert>

TBoard::TBoard(int width, int height, const folly::fbvector<TCellPos>& filled)
    : Width(width)
    , Height(height)
    , Cells(height, folly::fbvector<bool>(width, false))
    , FilledInRow(height, 0)
{
    for (const auto& pos : filled) {
        Cells[pos.Row][pos.Col] = true;
        FilledInRow[pos.Row]++;
    }
    RemoveFilled();
}

TBoard::~TBoard()
{
}

void TBoard::RemoveFilled() {
    int filledCnt = 0;
    for (int row = Height - 1; row >= filledCnt;) {
        if (FilledInRow[row] == Width) {
            ShiftRow(row);
            filledCnt++;
        }
        else {
            row--;
        }
    }
    for (int row = 0; row < filledCnt; row++) {
        for (int col = 0; col < Width; col++) {
            Cells[row][col] = false;
        }
        FilledInRow[row] = 0;
    }
}

void TBoard::ShiftRow(int row) {
    for (int i = row; i > 0; i--) {
        for (int j = 0; j < Width; j++) {
            Cells[i][j] = Cells[i - 1][j];
        }
        FilledInRow[i] = FilledInRow[i-1];
    }
}


bool TBoard::IsValidUnit(const TUnit& unit) const {
    for (const auto& pos : unit.Cells) {
        if (pos.Row < 0 || pos.Row >= Height || pos.Col < 0 || pos.Col >= Width)
            return false;
        if (Cells[pos.Row][pos.Col])
            return false;
    }
    return true;
}

void TBoard::LockUnit(const TUnit& unit) {
    assert(IsValidUnit(unit));
    for (const auto& pos : unit.Cells) {
        Cells[pos.Row][pos.Col] = true;
        FilledInRow[pos.Row]++;
    }
    RemoveFilled();
}
