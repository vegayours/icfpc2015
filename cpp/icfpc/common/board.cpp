#include "board.h"

TBoard::TBoard(int width, int height, const folly::fbvector<TCellPosition>& filled)
    : Width(width)
    , Height(height)
    , Cells(height, folly::fbvector<TCell>(width))
    , FilledInRow(height, 0)
{
    for (const auto& pos : filled) {
        Cells[pos.Row][pos.Column].State = Filled;
        FilledInRow[pos.Row]++;
    }
    RemoveFilled();
}

TBoard::~TBoard()
{
}

void TBoard::RemoveFilled() {
    int filledCnt = 0;
    auto cellsIt = Cells.begin();
    auto filledIt = FilledInRow.begin();
    for (;filledIt != FilledInRow.end();) {
        if (*filledIt == Width) {
            cellsIt = Cells.erase(cellsIt);
            filledIt = FilledInRow.erase(filledIt);
            filledCnt++;
        }
        else {
            cellsIt++;
            filledIt++;
        }
    }
    while (filledCnt--) {
        Cells.insert(Cells.begin(), folly::fbvector<TCell>(Width, Empty));
        FilledInRow.insert(FilledInRow.begin(), 0);
    }
}

bool TBoard::IsValidUnit(const TUnit& unit) const {
    for (const auto& pos : unit.GetCells()) {
        if (pos.Row < 0 || pos.Row >= Height || pos.Column < 0 || pos.Column >= Width)
            return false;
        if (Cells[pos.Row][pos.Column].State == ECellState::Filled)
            return false;
    }
    return true;
}
void TBoard::LockUnit(const TUnit& unit) {
    assert(IsValidUnit(unit));
    for (const auto& pos : unit.GetCells()) {
        Cells[pos.Row][pos.Column].State = ECellState::Filled;
        FilledInRow[pos.Row]++;
    }
    RemoveFilled();
}
