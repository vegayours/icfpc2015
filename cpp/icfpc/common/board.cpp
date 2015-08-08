#include "board.h"

TBoard::TBoard(int width, int height, const folly::fbvector<TCellPosition>& filled)
    : Width(width)
      , Height(height)
      , Cells(height, folly::fbvector<TCell>(width))
{
    for (const auto& pos : filled)
        Cells[pos.Row][pos.Column].State = Filled;
}

TBoard::~TBoard()
{
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
    }
}
