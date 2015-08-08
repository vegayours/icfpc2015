#pragma once

#include "cell.h"
#include "board.h"

#include <folly/FBVector.h>

#include <algorithm>
#include <functional>

class TBoard;

class TUnit {
public:
    TUnit();
    TUnit(folly::fbvector<TCellPosition> cells, const TCellPosition& pivot);
    ~TUnit();

    const folly::fbvector<TCellPosition>& GetCells() const {
        return Cells;
    }
    const TCellPosition& GetPivot() const {
        return Pivot;
    }

    int GetWidth() const {
        return Width;
    }

    int GetHeight() const {
        return Width;
    }

    TUnit PlaceToBoard(const TBoard& board);

    TUnit MoveLeft() const;
    TUnit MoveRight() const;
    TUnit MoveDownLeft() const;
    TUnit MoveDownRight() const;
private:
    TUnit MoveUnit(int rowDiff, int colDiff) const;

    TUnit MoveUnit(std::function<void(TCellPosition& pos)> move) const;

private:
    folly::fbvector<TCellPosition> Cells;
    TCellPosition Pivot;
    int Width;
    int Height;
};

