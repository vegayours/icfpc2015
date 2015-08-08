#include "unit.h"

TUnit::TUnit()
    : Cells()
    , Pivot()
    , Width(0)
    , Height(0)
{
}

TUnit::TUnit(folly::fbvector<TCellPosition> cells, const TCellPosition& pivot)
    : Cells(std::move(cells))
    , Pivot(pivot)
{
    const int kLimit = 10000000;
    int minCol = kLimit, minRow = kLimit;
    int maxCol = 0, maxRow = 0;
    for (const auto& c : Cells) {
        minCol = std::min(minCol, c.Column);
        maxCol = std::max(maxCol, c.Column);
        minRow = std::min(minRow, c.Row);
        maxRow = std::max(maxRow, c.Row);
    }
    Width = maxCol - minCol + 1;
    Height = maxRow - minRow + 1;
}

TUnit::~TUnit()
{
}

TUnit TUnit::PlaceToBoard(const TBoard& board) {
    int colShift = colShift = board.GetWidth() / 2 - Width / 2;
    if (board.GetWidth() % 2 == 0 && Width % 2 == 1)
    {
        colShift--;
    }
    return MoveUnit(0, colShift);
}

TUnit TUnit::MoveLeft() const {
    return MoveUnit(0, -1);
}
TUnit TUnit::MoveRight() const {
    return MoveUnit(0, 1);
}
TUnit TUnit::MoveDownLeft() const {
    return MoveUnit([] (TCellPosition& pos) {
        if (pos.Row % 2 == 0)
            pos.Column--;
        pos.Row++;
            });
}
TUnit TUnit::MoveDownRight() const {
    return MoveUnit([] (TCellPosition& pos) {
        if (pos.Row % 2 == 1)
            pos.Column++;
        pos.Row++;
            });
}
TUnit TUnit::MoveUnit(int rowDiff, int colDiff) const {
    return MoveUnit([=](TCellPosition& pos) {
            pos.Row += rowDiff;
            pos.Column += colDiff;
            });
}

TUnit TUnit::MoveUnit(std::function<void(TCellPosition& pos)> move) const {
    TUnit copy = *this;
    for (auto& c : copy.Cells) {
        move(c);
    }
    move(copy.Pivot);
    return std::move(copy);
}
