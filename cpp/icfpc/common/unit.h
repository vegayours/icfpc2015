#pragma once

#include "board.h"

#include <folly/FBVector.h>

#include <algorithm>
#include <functional>

namespace NCommon {

class TUnit {
public:
    TUnit(folly::fbvector<TCellPosition> cells, const TCellPosition& pivot)
        : Cells(std::move(cells))
        , Pivot(pivot)
    {
    }
    const folly::fbvector<TCellPosition>& GetCells() const {
        return Cells;
    }
    const TCellPosition& GetPivot() const {
        return Pivot;
    }

    TUnit PlaceToBoard(const TBoard& board) {
        uint32_t minCol = board.GetWidth() - 1;
        uint32_t maxCol = 0;
        for (const auto& c : Cells) {
            minCol = std::min(minCol, c.Column);
            maxCol = std::max(maxCol, c.Column);
        }
        uint32_t unitWidth = maxCol - minCol + 1;
        int colShift = colShift = board.GetWidth() / 2 - unitWidth / 2;
        if (board.GetWidth() % 2 == 0 && unitWidth % 2 == 1)
        {
            colShift--;
        }
        return MoveUnit(0, colShift);
    }

    TUnit MoveLeft() const {
        return MoveUnit(0, -1);
    }
    TUnit MoveRight() const {
        return MoveUnit(0, 1);
    }
    TUnit MoveDownLeft() const {
        return MoveUnit([] (TCellPosition& pos) {
            if (pos.Row % 2 == 0)
                pos.Column--;
            pos.Row++;
        });
    }
    TUnit MoveDownRight() const {
        return MoveUnit([] (TCellPosition& pos) {
            if (pos.Row % 2 == 1)
                pos.Column++;
            pos.Row++;
        });
    }
private:
    TUnit MoveUnit(int rowDiff, int colDiff) const {
        return MoveUnit([=](TCellPosition& pos) {
            pos.Row += rowDiff;
            pos.Column += colDiff;
        });
    }

    TUnit MoveUnit(std::function<void(TCellPosition& pos)> move) const {
        TUnit copy = *this;
        for (auto& c : copy.Cells) {
            move(c);
        }
        move(copy.Pivot);
        return std::move(copy);
    }

private:
    folly::fbvector<TCellPosition> Cells;
    TCellPosition Pivot;
};

};
