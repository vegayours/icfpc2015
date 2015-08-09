#include "unit.h"

#include <algorithm>

TUnit::TUnit()
    : Cells()
    , Pivot()
{
}

TUnit::TUnit(folly::fbvector<TCellPos> cells, const TCellPos& pivot)
    : Cells(std::move(cells))
    , Pivot(pivot)
{
}

TUnit::~TUnit()
{
}

TUnit TUnit::PlaceToBoard(const TBoard& board) const {
    int width = Width();
    int colShift = colShift = board.Width / 2 - width / 2;
    if (board.Width % 2 == 0 && width % 2 == 1)
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

int TUnit::MinRow() const {
    return std::accumulate(Cells.begin() + 1, Cells.end(), Cells.begin()->Row,
            [] (int x, const TCellPos y) {return std::min(x, y.Row);});
}


int TUnit::MaxRow() const {
    return std::accumulate(Cells.begin() + 1, Cells.end(), Cells.begin()->Row,
            [] (int x, const TCellPos y) {return std::max(x, y.Row);});
}

int TUnit::MinCol() const {
    return std::accumulate(Cells.begin() + 1, Cells.end(), Cells.begin()->Col,
            [] (int x, const TCellPos y) {return std::min(x, y.Col);});
}


int TUnit::MaxCol() const {
    return std::accumulate(Cells.begin() + 1, Cells.end(), Cells.begin()->Col,
            [] (int x, const TCellPos y) {return std::max(x, y.Col);});
}

int TUnit::Width() const {
    return MaxCol() - MinCol() + 1;
}

int TUnit::Height() const {
    return MaxRow() - MinRow() + 1;
}
