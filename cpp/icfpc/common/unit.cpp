#include "unit.h"

TUnit::TUnit()
    : Cells()
    , Pivot()
    , Width(0)
    , Height(0)
{
}

TUnit::TUnit(folly::fbvector<TCellPos> cells, const TCellPos& pivot)
    : Cells(std::move(cells))
    , Pivot(pivot)
{
    const int kLimit = 10000000;
    int minCol = kLimit, minRow = kLimit;
    int maxCol = 0, maxRow = 0;
    for (const auto& c : Cells) {
        minCol = std::min(minCol, c.Col);
        maxCol = std::max(maxCol, c.Col);
        minRow = std::min(minRow, c.Row);
        maxRow = std::max(maxRow, c.Row);
    }
    Width = maxCol - minCol + 1;
    Height = maxRow - minRow + 1;
}

TUnit::~TUnit()
{
}

TUnit TUnit::PlaceToBoard(const TBoard& board) const {
    int colShift = colShift = board.Width / 2 - Width / 2;
    if (board.Width % 2 == 0 && Width % 2 == 1)
    {
        colShift--;
    }
    return MoveUnit(0, colShift);
}

TUnit TUnit::ApplyMove(EMove move) const {
    switch (move) {
        case EMove::MoveLeft:
            return MoveLeft();
        case EMove::MoveRight:
            return MoveRight();
        case EMove::MoveDownLeft:
            return MoveDownLeft();
        case EMove::MoveDownRight:
            return MoveDownRight();
        default:
            break;
    }
    assert(false);
    return TUnit();
}

TUnit TUnit::MoveLeft() const {
    return MoveUnit(0, -1);
}
TUnit TUnit::MoveRight() const {
    return MoveUnit(0, 1);
}
TUnit TUnit::MoveDownLeft() const {
    return MoveUnit([] (TCellPos& pos) {
        if (pos.Row % 2 == 0)
            pos.Col--;
        pos.Row++;
            });
}
TUnit TUnit::MoveDownRight() const {
    return MoveUnit([] (TCellPos& pos) {
        if (pos.Row % 2 == 1)
            pos.Col++;
        pos.Row++;
            });
}
TUnit TUnit::MoveUnit(int rowDiff, int colDiff) const {
    return MoveUnit([=](TCellPos& pos) {
            pos.Row += rowDiff;
            pos.Col += colDiff;
            });
}

TUnit TUnit::MoveUnit(std::function<void(TCellPos& pos)> move) const {
    TUnit copy = *this;
    for (auto& c : copy.Cells) {
        move(c);
    }
    move(copy.Pivot);
    return std::move(copy);
}
